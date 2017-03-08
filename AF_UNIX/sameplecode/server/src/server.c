#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

int main()
{
    int fd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (-1 == fd ){
   	printf("error socket\n");
	return -1;
    } 
    if (unlink("/tmp/afunix.server")) {
   	printf("error unlink %s\n", strerror(errno));
    }   
    struct sockaddr_un serverSockaddr = {AF_UNIX, "/tmp/afunix.server"};
    if (bind(fd, (struct sockaddr*)&serverSockaddr, sizeof(struct sockaddr_un))) {
        printf("error bind\n");
        return ;
    }
    char buf[1024]={};
    struct sockaddr_un clientSockaddr;
    int len =  sizeof(struct sockaddr_un);  
  while (1){
    	size_t cnt = recvfrom(fd, buf, sizeof(buf), 0, (struct sockaddr*)&clientSockaddr, &len);
	if( cnt < 0) {
		printf ("recvfrom %s\n",strerror(errno));
	}
	printf("recvfrom :%s\n",buf);
  }
 return -1;
}
