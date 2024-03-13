//***************************//
//*Template by pulgamecanica*//
//***************************//

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <errno.h>

#include "Spectator.h"

static void ft_exit_on_error(int res, char * fallback_msg) {
	if (res == -1) {
		perror(fallback_msg);
		exit(EXIT_FAILURE);
	}
}

static void setnonblocking(int fd) {
	int flags = fcntl(fd, F_GETFL, 0);
	ft_exit_on_error(flags, "fcntl()");
	ft_exit_on_error(fcntl(fd, F_SETFL, flags | O_NONBLOCK), "fcntl");
}

static int connect_to_server(char *host, char * port) {
	int              sfd, s;
	struct addrinfo  hints;
	struct addrinfo  *result, *rp;

	/* Obtain address(es) matching host/port. */

	bzero(&hints, sizeof(hints) * 1);
	hints.ai_family = AF_INET;    	/* Allow IPv4 */
	hints.ai_socktype = SOCK_STREAM; /* tcp socket bidirectional */
	hints.ai_flags = 0;
	hints.ai_protocol = 0;          /* Any protocol */

	s = getaddrinfo(host, port, &hints, &result);
	if (s != 0) {
	fprintf(stderr, "getaddrinfo(): %s\n", gai_strerror(s));
	exit(EXIT_FAILURE);
	}

	/* getaddrinfo() returns a list of address structures.
	Try each address until we successfully connect(2).
	If socket(2) (or connect(2)) fails, we (close the socket
	and) try the next address. */

	for (rp = result; rp != NULL; rp = rp->ai_next) {
	   sfd = socket(rp->ai_family, rp->ai_socktype,
	                rp->ai_protocol);
	   if (sfd == -1)
	       continue;
	   if (connect(sfd, rp->ai_addr, rp->ai_addrlen) != -1)
	       break;                  /* Success */
	   close(sfd);
	}

	freeaddrinfo(result);           /* No longer needed */

	if (rp == NULL) {               /* No address succeeded */
	   fprintf(stderr, "*%sERROR%s* Couldn't connect\n", RED, ENDC);
	   exit(EXIT_FAILURE);
	}
	setnonblocking(sfd);
	return (sfd);
}

#define DEFAULT_PORT "4242"
#define DEFAULT_HOST "localhost"
#define BUF 1024
int	main(int ac, char *av[]) {
	int socket_fd;
	char * port;
	char * host;

	if (ac != 3) {
		printf("*%sWARNING%s* Usage: %s <host> <port>\n", YELLOW, ENDC, av[0]);
		printf("Using default host & port: %s:%s\n", DEFAULT_HOST, DEFAULT_PORT);
		host = DEFAULT_HOST;
		port = DEFAULT_PORT;
	} else {
		host = av[1];
		port = av[2];
	}
	socket_fd = connect_to_server(host, port);

	int read_bytes;
	char buf[BUF + 1];
	while (42) {
		bzero(buf, sizeof(char) * (BUF + 1));
		read_bytes = recv(socket_fd, buf, BUF, MSG_DONTWAIT);
		if (read_bytes == -1) {
			if (errno != EAGAIN && errno != EWOULDBLOCK)
				ft_exit_on_error(read_bytes, "recv()");
		} else if (read_bytes == 0) {
			puts("Server dissconnected");
			break ;
		} else {
			// TODO: README.md encoding & data transfer protocole to implement
			// Trust the server, Data encoding correct 100%
			// Receive Encoding
			// If object has been received compleately
			//   update()
			// graphic update
			puts(buf);
		}
	}
	puts("Good Buy\nPulgamecanica greets you :D");
	close(socket_fd);
	return (0);
}

