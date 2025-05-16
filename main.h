#include <arpa/inet.h>
#include <asm-generic/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <assert.h>

const int PORT = 3000;
const int HEADER_KEY_SIZE = 64;
const int HEADER_VALUE_SIZE = 256;
#define BUF_SIZE 256

int main(void);

struct http_header {
  char key[HEADER_KEY_SIZE];
  char value[HEADER_VALUE_SIZE];
};

struct http_headers {
  struct http_header *headers;
  int length;
};

enum http_verb { GET, POST, PUT, DELETE };

struct http_request {
  enum http_verb verb;
  char path[256];
  struct http_headers h;
};
