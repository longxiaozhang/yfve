#include <string.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <netdb.h>
#include <errno.h>
#include "usage.h"

#define MAX_WAIT_TIME   5
#define MAX_NO_PACKETS  3
#define ICMP_HEADSIZE 8 
#define PACKET_SIZE     4096
struct timeval tvsend,tvrecv;	
pid_t pid;
char sendpacket[PACKET_SIZE];
char recvpacket[PACKET_SIZE];
void timeout(int signo);

bool NetCheck::netDnsIsOk(const std::string& url)
{
	struct hostent * host = NULL;
	
	if ((host = gethostbyname(url.c_str())) == NULL) {
		printf("file:%s line:%d error : Can't get serverhost info!\n", __FILE__, __LINE__);
		return false;
	}
	
	return true;
}

bool NetCheck::netIsOk(const std::string& srcAddr, const std::string& destAddr)
{
	int socketfd;
	int flag;
	struct sockaddr_in src_addr, dest_addr;
	
	if ( (socketfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) < 0) {
		printf("file:%s line:%d error : socket\n", __FILE__, __LINE__);
		return false;
	}
	src_addr.sin_family = AF_INET;	
	src_addr.sin_addr.s_addr = inet_addr( srcAddr.c_str() );
	dest_addr.sin_family = AF_INET;
	dest_addr.sin_addr.s_addr = inet_addr( destAddr.c_str() );
	
	if ( bind(socketfd, (struct sockaddr *)(&src_addr), sizeof(struct sockaddr)) < 0) {
		printf("file:%s line:%d error : bind\n", __FILE__, __LINE__);
		return false;
	}
	
	if ( (flag = fcntl(socketfd, F_GETFL, 0)) < 0) {
		printf("file:%s line:%d error : fcntl(socketfd,F_GETFL,0)\n", __FILE__, __LINE__);
		close(socketfd);
		socketfd = 0;
		return false;
	}
	
	flag |= O_NONBLOCK;
	if ( (flag = fcntl(socketfd, F_SETFL, flag)) < 0) {
		printf("file:%s line:%d  error : fcntl(socketfd,F_SETFL,flag)\n", __FILE__, __LINE__);
		close(socketfd);
		socketfd = 0;
		return false;
	}
	
	for(int i=0;i<MAX_NO_PACKETS;i++)
	{		
		if( send_packet(socketfd, dest_addr, i, sendpacket)<0 )
		{
			printf("file:%s line:%d  error : send_packet\n", __FILE__, __LINE__);
			close(socketfd);
			socketfd = 0;
			return false;
		}	
		if(recv_packet(socketfd, i,recvpacket)>0)
		{
			close(socketfd);
			socketfd = 0;
			return true;
		}
	} 
}


int NetCheck::send_packet(int sockfd, const struct sockaddr_in& dest_addr, int pkt_no, char *sendpacket)
{    
	int packetsize;       
	packetsize=pack(pkt_no,sendpacket); 
	gettimeofday(&tvsend,NULL);
	if(sendto(sockfd,sendpacket,packetsize,0,(struct sockaddr *)&dest_addr,sizeof(dest_addr) )<0)
	{     
		printf("errno:%d message:%s\n", errno, strerror(errno)); 
		printf("file:%s line:%d  error : sendto\n", __FILE__, __LINE__);
		return -1;
	}
	return 1;
}

int NetCheck::pack(int pkt_no,char*sendpacket)
{      
	int i,packsize;
	struct icmp *icmp;
	struct timeval *tval;
	icmp=(struct icmp*)sendpacket;
	icmp->icmp_type=ICMP_ECHO;   //设置类型为ICMP请求报文
	icmp->icmp_code=0;
	icmp->icmp_cksum=0;
	icmp->icmp_seq=pkt_no;
	icmp->icmp_id=pid;			//设置当前进程ID为ICMP标示符
	packsize=ICMP_HEADSIZE+sizeof(struct timeval);
	tval= (struct timeval *)icmp->icmp_data;
	gettimeofday(tval,NULL);
	icmp->icmp_cksum=cal_chksum( (unsigned short *)icmp,packsize); 
	return packsize;
}


unsigned short NetCheck::cal_chksum(unsigned short *addr,int len)
{       
	int nleft=len;
	int sum=0;
	unsigned short *w=addr;
	unsigned short answer=0;
	while(nleft>1)		//把ICMP报头二进制数据以2字节为单位累加起来
	{       
		sum+=*w++;
		nleft-=2;
	}
	if( nleft==1)		//若ICMP报头为奇数个字节,会剩下最后一字节.把最后一个字节视为一个2字节数据的高字节,这个2字节数据的低字节为0,继续累加
	{
		*(unsigned char *)(&answer)=*(unsigned char *)w;
		sum+=answer;
	}
	sum=(sum>>16)+(sum&0xffff);
	sum+=(sum>>16);
	answer=~sum;
	return answer;
}


int NetCheck::recv_packet(int sockfd,int pkt_no, char *recvpacket)
{       	
	int n;
	socklen_t fromlen;
	fd_set rfds;
	FD_ZERO(&rfds);
	FD_SET(sockfd,&rfds);
	signal(SIGALRM,timeout);
	fromlen=sizeof(recv_addr);
	alarm(MAX_WAIT_TIME);
	while(1)
	{
		select(sockfd+1, &rfds, NULL, NULL, NULL);
		if (FD_ISSET(sockfd,&rfds))
		{  
			if( (n=recvfrom(sockfd,recvpacket,PACKET_SIZE,0,(struct sockaddr *)&recv_addr,&fromlen)) <0)
    		{   
			if(errno==EINTR)
				return -1;
				perror("recvfrom error\n");
				return -2;
      		}
		}
		gettimeofday(&tvrecv,NULL); 
		if(unpack(pkt_no,recvpacket,n)==-1)
			continue;
		return 1;
	}
}

int NetCheck::unpack(int cur_seq,char *buf,int len)
{    
	int iphdrlen;
	struct ip *ip;
	struct icmp *icmp;
	ip=(struct ip *)buf;
	iphdrlen=ip->ip_hl<<2;		//求ip报头长度,即ip报头的长度标志乘4
	icmp=(struct icmp *)(buf+iphdrlen);		//越过ip报头,指向ICMP报头
	len-=iphdrlen;		//ICMP报头及ICMP数据报的总长度
	if( len<8)
		return -1;       
	if( (icmp->icmp_type==ICMP_ECHOREPLY) && (icmp->icmp_id==pid) && (icmp->icmp_seq==cur_seq))
		return 0;	
	else return -1;
}


void timeout(int signo)
{
	printf("Request Timed Out\n");
}

void NetCheck::tv_sub(struct timeval *out,struct timeval *in)
{       
	if( (out->tv_usec-=in->tv_usec)<0)
	{       
		--out->tv_sec;
		out->tv_usec+=1000000;
	}
	out->tv_sec-=in->tv_sec;
}




