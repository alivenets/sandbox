#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>

int main(int argc, char *argv[])
{
    if (argc < 2) {
	fprintf(stderr, "Usage: %s <port>\n", argv[0]);
	return 1;
    }

    unsigned int port = atoi(argv[1]);
    
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
	perror("socket");
	return errno;
    }

    struct sockaddr_in addr = {0};

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = 0;
    addr.sin_port = htons(port);

    int ret = bind(sock, (struct sockaddr*)&addr, sizeof(struct sockaddr_in));
    if (ret < 0) {
	perror("bind");
	return errno;
    }

    struct timeval tv = {0};
    tv.tv_sec = 1;
    tv.tv_usec = 0;

    ret = setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(struct timeval));
    unsigned char buf[128];

    while (1) {
	memset(&addr, 0, sizeof(addr));
	socklen_t len = sizeof(struct sockaddr_in);
	ret = recvfrom(sock, buf, sizeof(buf)-1, 0, (struct sockaddr*)&addr, &len);
	if (ret < 0) {
	    if (errno != EAGAIN)
		    perror("recv");
	    continue;
	}
	if (ret > sizeof(buf))
	    ret = sizeof(buf);

        buf[ret-1] = '\0';

	printf("Echo: %s\n", buf);
	ret = sendto(sock, buf, ret, 0, (struct sockaddr*)&addr, len);
	if (ret < 0) {
	    perror("send");
	}
    }
}