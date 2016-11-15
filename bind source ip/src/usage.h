#ifndef USAGE_H__
#define USGAE_H__
#include <iostream>
#include <string>
#include <arpa/inet.h>
#include <sys/types.h>

class NetCheck{
public:
	NetCheck(){}
	~NetCheck(){}
	bool netDnsIsOk(const std::string& url);
	bool netIsOk(const std::string& srcAddr, const std::string& destAddr);
	
private:
	struct sockaddr_in recv_addr;
	int send_packet(int sockfd, const struct sockaddr_in& dest_addr, int pkt_no, char *sendpacket);
	int recv_packet(int sockfd, int pkt_no,char *recvpacket);
	int pack(int pkt_no,char*sendpacket);
	int unpack(int cur_seq,char *buf,int len);
	unsigned short cal_chksum(unsigned short *addr,int len);
//	void timeout(int signo);
	void tv_sub(struct timeval *out,struct timeval *in);
};

#endif
