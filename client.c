/*
 * Name: Kethan Pilla
 * CS440-1
 * Assignment #1
 * Collaborators: stumpati
 * Resources: w3Schools, manpage(arc4random,printf,style), bgnet
 * Description: Client sends a yes/no question to the server.
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <err.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define SERVER_PORT 11609
#define MAX_LINE 256

	int
main(int argc, char *argv[])
{
	char buf[MAX_LINE];
	struct hostent *hp;
	struct sockaddr_in sin;
	char *host;
	int s;
	ssize_t n;
	size_t len;

	if (argc != 2)
		errx(1, "usage: %s hostname", argv[0]);
	host = argv[1];
	hp = gethostbyname(host); /* translates hostName to ip address.*/
	if (!hp)
		errx(1, "unknown host %s", host);
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	memcpy(&sin.sin_addr, hp->h_addr, hp->h_length);
	sin.sin_port = htons(SERVER_PORT);
	if ((s = socket(PF_INET, SOCK_STREAM, 0)) == -1)
		err(2, "socket");
	if (connect(s, (struct sockaddr *)&sin, sizeof(sin)) == -1) {
		close(s);
		err(3, "connect");
	}
	printf("Enter your (yes/no) question: "); /* Prompt for the user to ask a question */
	if (!fgets(buf, sizeof(buf), stdin)) {
		close(s);   /* exit, if failed to read input */
		return 0;
	}
	buf[strcspn(buf, "\r\n")] = 0;
	len = strnlen(buf, sizeof(buf));
	if (send(s, buf, len, 0) == -1) {
		perror("send");
		close(s);
		return 1;
	}
	memset(buf, 0, sizeof(buf)); /* Receive servers response */
	n = recv(s, buf, sizeof(buf) - 1, 0);
	if (n < 0) {
		perror("recv");
	} else if (n == 0) {
		fprintf(stderr, "Server closed connection\n");
	} else {
		buf[n] = '\0';
		printf("%s\n", buf);    /* response from server */
	}
	close(s);
	return 0;
}
