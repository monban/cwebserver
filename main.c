#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

const int PORT = 3000;

int main() {
  struct sockaddr_in a = {
      .sin_family = AF_INET, .sin_port = htons(PORT), .sin_addr = INADDR_ANY};

  int s = socket(PF_INET, SOCK_STREAM, 0);
  if (s == 0) {
    perror(NULL);
    exit(1);
  }

  int err = bind(s, (struct sockaddr *)&a, sizeof(a));
  if (err < 0) {
    perror(NULL);
    exit(1);
  }

  listen(s, 1);
  struct sockaddr a2;
  socklen_t l;
  int s2 = accept(s, &a2, &l);
  char b[256];
  read(s2, &b, 256);
  printf("%s", b);

  dprintf(s2, "HTTP/1.1 200 OK\r\n\r\n%s\r\n", b);

  shutdown(s2, SHUT_RDWR);
  shutdown(s, SHUT_RDWR);
}
