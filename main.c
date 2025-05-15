#include "main.h"

int main(void) {
  struct sockaddr_in a = {
      .sin_family = AF_INET, .sin_port = htons(PORT), .sin_addr = {INADDR_ANY}};

  int s = socket(PF_INET, SOCK_STREAM, 0);
  if (s < 0) {
    perror("socket");
    exit(1);
  }

  int err;
  int reuse_addr = 1;
  err =
      setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &reuse_addr, sizeof(reuse_addr));
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
  FILE *stream = fdopen(s2, "r+");
  // char b[BUF_SIZE] = {0};
  // err = read(s2, &b, BUF_SIZE);
  char *verb, *path, *version;
  fscanf(stream, "%ms %ms %ms\r\n", &verb, &path, &version);
  printf("verb: %s\npath: %s\nversion: %s\n", verb, path, version);
  free(verb);
  free(path);
  free(version);
  if (err < 0) {
    perror("read");
    exit(1);
  } else if (err == 0) {
    printf("got EOF while reading from socket\n");
  }
  // printf("received %d bytes:\n%s", err, b);

  // dprintf(s2, "HTTP/1.1 200 OK\r\n\r\n%s\r\n", b);

  close(s2);
  close(s);
  return 0;
}

