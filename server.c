/*Name: Kethan Pilla
 * Course-Section: CS440-section #1
 * Assignment: #1
 * Date due: 02/12/2025
 * Collaborators: stumpati
 * Resources: w3Schools(fileStream), manpage(arc4random,printf,style),bgnet.
 * Description: A server that listens for a client question and responds*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <err.h>
#include <netinet/in.h>
#define SERVER_PORT 11609
#define MAX_LINE 256
#define RESPONSE_FILE "responses.txt"

void handle_client(int client_fd)
{
	char buf[MAX_LINE] = {0}, response[MAX_LINE];
	FILE *file;
	char responses[20][MAX_LINE];
	int count = 0, random_index;

	if (recv(client_fd, buf, MAX_LINE - 1, 0) <= 0) {
		perror("recv");
		close(client_fd);
		return;
	}
	buf[strcspn(buf, "\r\n")] = 0;
	if (!(file = fopen(RESPONSE_FILE, "r"))) {
		perror("fopen");
		close(client_fd);
		return;
	}
	while (count < 20 && fgets(responses[count], MAX_LINE, file)) {
		responses[count][strcspn(responses[count], "\r\n")] = 0;
		count++;
	}
	fclose(file);
	random_index = arc4random_uniform(count);
	snprintf(response, MAX_LINE, "Q: \"%s\"\nR: \"%s\"\n\n", 
			buf, responses[random_index]);
	send(client_fd, response, strlen(response), 0);
	close(client_fd);
}

int main(void)
{
	int server_fd, client_fd;
	struct sockaddr_in sin, client_addr;
	socklen_t client_len = sizeof(client_addr);

	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		err(1, "socket");
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons(SERVER_PORT);
	if (bind(server_fd, (struct sockaddr *)&sin, sizeof(sin)) == -1)
		err(2, "bind");
	if (listen(server_fd, 5) == -1)
		err(3, "listen");

	printf("Server listening on port %d...\n", SERVER_PORT);
	while (1) {
		client_fd = accept(server_fd, (struct sockaddr *)&client_addr, 
				&client_len);
		if (client_fd == -1) {
			perror("accept");
			continue;
		}
		handle_client(client_fd);
	}
	close(server_fd);
	return 0;
}
