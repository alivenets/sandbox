#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
    int ret = 0;

    if (argc < 3) {
	fprintf(stderr, "Usage: %s <host> <port>\n", argv[0]);
	return 1;
    }


    struct in_addr addr;
    ret = inet_pton(AF_INET, argv[1], &addr);

    if (ret <= 0) {
	perror("inet_pton");
	return errno;
    }

    unsigned short port = atoi(argv[2]);

    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
	perror("socket");
	return errno;
    }

    struct timeval tv = {0};
    tv.tv_sec = 1;
    tv.tv_usec = 0;

    ret = setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(struct timeval));
    if (ret < 0) {
	perror("setsockopt");
	return errno;
    }

    struct sockaddr_in dest_addr = {0};

    dest_addr.sin_family = AF_INET;
    dest_addr.sin_addr = addr;
    dest_addr.sin_port = htons(port);

    ret = connect(sock, (struct sockaddr*)&dest_addr, sizeof(struct sockaddr_in));
    if (ret < 0) {
	perror("connect");
	return errno;
    }
    
    unsigned char buf[128];

    const char TEST_MESSAGE[] = "HELLO";

    while (1) {
	ret = send(sock, TEST_MESSAGE, sizeof(TEST_MESSAGE), 0);
	if (ret < 0) {
	    perror("send");
	    continue;
	}

	printf("send: %s\n", TEST_MESSAGE);

	ret = recv(sock, buf, sizeof(buf), 0);
	if (ret < 0) {
	    perror("recv");
	    continue;
	}

	if (ret >= sizeof(buf))
	    ret = sizeof(buf);

	buf[ret-1] = '\0';

	printf("recv: %s\n", buf);
	sleep(1);
    }
}