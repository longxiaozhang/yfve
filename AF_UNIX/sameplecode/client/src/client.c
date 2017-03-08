#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

void RR(void *arg)
{

}
int main()
{
    int fd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (-1 == fd ){
   	printf("error socket\n");
	return -1;
    } 
    if (unlink("/tmp/afunix.client")) {
   	printf("error unlink %s\n", strerror(errno));
    }   
    struct sockaddr_un clientSockaddr = {AF_UNIX, "/tmp/afunix.client"};
    if (bind(fd, (struct sockaddr*)&clientSockaddr, sizeof(struct sockaddr_un))) {
        printf("error bind\n");
        return ;
    }
//    pthread_attr_init(&attr);
//    pthread_create();
    char buf[]="check connection!";
    struct sockaddr_un serverSockaddr = { AF_UNIX, "/tmp/afunix.server"};
   
    while (1){
    	size_t cnt = sendto(fd, buf, sizeof(buf), 0, (struct sockaddr*)&serverSockaddr, sizeof(struct sockaddr_un));
	printf("cnt %d\n", cnt);
	if (cnt == -1) {
		printf ("sendto %s\n",strerror(errno));
	continue;
	}
	printf("send okay\n");
	sleep(3);	  
  }
 return -1;
}
