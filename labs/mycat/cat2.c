#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define  BYTES 128

int main(int argc, char const *argv[]) {
  if (argc < 2) {
    printf("Usage: ./mycat <file>\n");
    exit(1);
  }
  int fileRead, fileWrite;
  fileRead = open(argv[1], O_RDONLY);
  if (fileRead < 0) {
    char *message = "Message: No such File or Directory.\n";
    int len = strlen(message);
    write(1, message, len);
    //perror("Error message: ");
    exit(0);
  }
  char *buffer;
  buffer = calloc(BYTES, sizeof(char));
  while ((read(fileRead, buffer, BYTES-1)) > 0) {
    write(1, buffer, BYTES);
    memset(buffer, '\0', BYTES);
  }
  close(fileRead);
  exit(0);
}
