#include <stdio.h>  
#include <string>  
#include <string.h>
#include <iostream>  
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "usage.h"

using namespace std;  

int main(int argc, char* argv[])  
{ 
   //check tbox and radio inner comunication
   {
	NetCheck net1;
	if (net1.netIsOk("192.168.4.100","192.168.8.100")) {
		std::cout<<"tbox and radio connected with ethernet!"<<std::endl;
	}
	else {
		std::cout<<"Error:tbox and radio inner connection!"<<std::endl;
	}
   } 

   //check radio connect to internet with peer's ip
   {
	NetCheck net2;
        if (net2.netIsOk("192.168.4.102","114.114.114.114")) {
                std::cout<<"radio connect to 114.114.114.114  okay!"<<std::endl;
        }
        else {
                std::cout<<"Error:radio connect to 114.114.114.114 failed!"<<std::endl;
        }
   }

   //check radio dns parser
   {
	NetCheck net3;
        if (net3.netDnsIsOk("www.baidu.com")) {
                std::cout<<"radio dns parser  okay!"<<std::endl;
        }
        else {
                std::cout<<"Error:radio dns parser failed!"<<std::endl;
        }
   }
/*
    sockaddr_in sin;  

    int sfd = socket(PF_INET,SOCK_STREAM,0);  

    memset(&sin,0,sizeof(sin));  
    sin.sin_family = AF_INET;  
    sin.sin_port = htons(80);
    //sin.sin_addr.s_addr = inet_addr();
    //sin.sin_addr.S_un.S_addr=inet_addr("203.208.37.99");  
    struct hostent* hptr = gethostbyname("www.google.cn");
    
    memcpy(&sin.sin_addr.s_addr,hptr->h_addr,hptr->h_length);  
    
    if(connect(sfd, (struct sockaddr*)&sin, sizeof(sin)))  
    {  
        cout<<"connect failed"<<endl;  
        return 0;  
    }  
    else  
    {  
        cout<<"connect success"<<endl;  
    }  

    char buffersend[]="GET/HTTP1.1/nHOST:www.google.cn/nconnection:close/n/n";  
    //send(s,buffersend,strlen(buffersend),0);  

    //string ss; 
    //int len = recv(s,const_cast<char*>(ss.c_str()),2000,0);
    char bufferecv[10240];  
    int len=recv(sfd,bufferecv,10240,0);  
    printf("the length of page is %d/n", len);  
    if(len==-1)  
    {  
        cout<<"receive failed"<<endl;  
        return -1;  
    }  
    else   
        cout<<"receive success"<<endl;  
    for (int i = 0; i < len; i++)  
        printf("%c",bufferecv[i]);  

    //close(sfd);
*/
    return 0;  
}   
