// ...

/**
 *	TCP server side:
 *	socket() -> bind() -> listen() -> accept() -> read() -> write()
 */

#include "common.h"

void commit_suicide(string message) {
	perror(message);
	exit(7);
}

int main (int argc, char const * argv []) {
	
	sockaddr_in_t server_address, client_address;

	int sockfd, nsckfd, i;
	socklen_t clen = sizeof(server_address);

	char buffer[BUFLEN];
	char output[BUFLEN];
	int received_length;

	int pid;

	// create a TCP Server
	if ((sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
		commit_suicide("socket()");
	}
	// zero out the structure
	memset((char *)&server_address, 0, clen);

	// set family, address and port
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(PORT);
	server_address.sin_addr.s_addr = INADDR_ANY;

	// bind socket to port
	if (bind(sockfd, (sockaddr_p_t)&server_address, clen) < 0) {
		commit_suicide("bind()");
	}

	// listen
	if (listen(sockfd, 6) < 0) {
		commit_suicide("listen()");
	}

	while (YES) {

		printf("Server [%s:%d] waiting...\n", inet_ntoa(server_address.sin_addr), ntohs(server_address.sin_port));

		// reset memory buffer
		memset(buffer, '\0', BUFLEN);

		// blocking call; try to get some data from the client?
		if ((nsckfd = accept(sockfd, (sockaddr_p_t)&client_address, &clen)) < 0) {
			commit_suicide("accept()");
		}

		pid = fork();

		if (pid == 0) {

			close(sockfd);

			size_t flen = 0;

			if ((received_length = read(nsckfd, &flen, sizeof(size_t))) < 0) {
				commit_suicide("read()");
			}

			// read into buffer
			if ((received_length = read(nsckfd, buffer, flen)) < 0) {
				commit_suicide("read()");
			}
			
			FILE *file;
			file = fopen("tmp.c", "w+");
			fwrite(buffer, sizeof(char), received_length, file);
			fclose(file);

			// exeggute tmp.o
			// Get the output and send it back
			system("gcc -o tmp.o tmp.c");
			system("./tmp.o > out.txt");

			FILE *outfile;
			outfile = fopen("out.txt", "r");
			fseek(outfile, 0, SEEK_END);
			flen = ftell(outfile);
			fseek(outfile, 0, SEEK_SET);
			fread(output, sizeof(char), flen, outfile);

			printf("Client [%s:%d] sent file.\n", inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port));

			if (write(nsckfd, output, BUFLEN) < 0) {
				commit_suicide("write()");
			}

			system("rm out.txt tmp.o tmp.c");

			fclose(outfile);
			close(nsckfd);
			exit(0);

		} else if (pid < 0) {
			commit_suicide("fork()");
			return -2;
		} else {
			close(nsckfd);
		}

	}

	close(nsckfd);
	close(sockfd);

	return 0;
}