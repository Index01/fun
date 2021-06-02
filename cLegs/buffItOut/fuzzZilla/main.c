
#include <getopt.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fuzzControlCase.h"

int main(int argc, char** argv) {
  int opt;
  char* optArg = NULL;
  if (!argv[1]) {
    printf("%s\n", "[+] default mode");
  }
  while ((opt = getopt(argc, argv, "i:")) != -1) {
    switch (opt) {
      case 'i':
        printf("%s\n", "[+] stdin mode");
        LLVMFuzzerTestOneInput(optarg, strlen(optarg));
        break;
      default:
        printf("%s\n", "[+] default mode");
    }
  }

  char* line = NULL;
  size_t len = 0;
  ssize_t read;
  while ((read = getline(&line, &len, stdin)) != -1) {
    LLVMFuzzerTestOneInput(line, read);
  }
  free(line);

  printf("%s\n", "[+] Main fin");
}
