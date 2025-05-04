#include <arpa/inet.h>
#include <asm-generic/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

const int PORT = 3000;
#define BUF_SIZE 256

int main() {
  struct sockaddr_in a = {
      .sin_family = AF_INET, .sin_port = htons(PORT), .sin_addr = INADDR_ANY};

  int s = socket(PF_INET, SOCK_STREAM, 0);
  if (s < 0) {
    perror("socket");
    exit(1);
  }

  int err;
  int reuse_addr = 1;
  err = setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &reuse_addr, sizeof(reuse_addr));
  if (err < 0) {
    perror("setsockopt");
    exit(1);
  }
  
  err = bind(s, (struct sockaddr *)&a, sizeof(a));
  if (err < 0) {
    perror("bind");
    exit(1);
  }

  err = listen(s, 1);
  if (err < 0) {
    perror("listen");
    exit(1);
  }

  struct sockaddr a2;
  socklen_t l;
  int s2 = accept(s, &a2, &l);

  char b[BUF_SIZE] = {0};
  err = read(s2, &b, BUF_SIZE);
  if (err < 0) {
    perror("read");
    exit(1);
  } else if (err == 0) {
    printf("got EOF while reading from socket\n");
  }
  printf("received %d bytes:\n%s", err, b);

  dprintf(s2, "HTTP/1.1 200 OK\r\n\r\n%s\r\n", b);

  close(s2);
  close(s);
  return 0;
}
