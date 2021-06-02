
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Fuzzer demo and control case for fuzzer automation.
 * LLVM function calls our stuff, through a series of conditionals the fuzzer
 *finds an input shape which causes crash. If this was a real program its
 *narrative might be something like: 1) If input string starts with particular
 *character, branch1, else branch2. 2) If the input ends with certain char, get
 *ready to write it to the heap. 3) If chars < num then copy once, else copy
 *twice(sometimes used to split first from last name, for example) This
 *branching logic often becomes difficult to unit test. Enter fuzzing to save
 *the day. Sighandling was helpful in keeping libfuzzer from crashing before
 *writing a crash file.
 **/

void branch1(const char* chars, size_t size) {
  /** Buggy branch **/
  // printf("%s\n", "[-] bug branch");

  // Here we plan to allocate a little extra memory, at least 2x for the double
  // copy Obvious name and scale to make example clear but same could happen
  // with any sufficiently large input.
  int datatypeOverflow = size * 10000000;

  // Some ending char causes execution. More hoops for fuzzer to jump through.
  if (chars[0] == '\\') {
    // oh look, another branch.
    if (size < 40) {
      char* vars = (char*)calloc(datatypeOverflow, sizeof(char));
      // off-nominal check, 3-4 conditionals in. could be missed by unit tests.
      if (vars == NULL) {
        printf("%s\n", "[-] NEGATIVE STARFIGHTER 1");
        printf("%s\n", chars);
        printf("size: %ld\n", size);
        printf("datatypeOverflow: %d\n", datatypeOverflow);
      }
      strcpy(vars, chars);
      // printf("\n%p: ", vars);
      // printf("%s\n\n", vars);
      free(vars);
    } else {
      for (int i = 0; i < 2; i++) {
        // Double failure. First we allocate with what could be a negative
        // number Then we check for vars==null but forget to retun. Nominal unit
        // tests countinue to pass but large, structured, input causes crashy.
        char* vars = (char*)calloc(datatypeOverflow, sizeof(char));
        if (vars == NULL) {
          printf("%s\n", "[-] NEGATIVE STARFIGHTER 2");
          printf("%s\n", chars);
          printf("size: %ld\n", size);
          printf("datatypeOverflow: %d\n", datatypeOverflow);
        }
        strcpy(vars, chars);
        // printf("%p: ", vars + i);
        // printf("%s\n", vars);
        free(vars);
      }
    }
  }
}

void branch2() {
  /** Noop. Branch is super bug free **/
  // printf("%s\n", "[-] bug free branch");
  return;
}

void iOverflowAndAllocate(const char* chars, size_t size) {
  /** Simple branching logic to exercis fuzzer **/
  char lastChar = chars[size - 2];

  // We dont want it to be so simple that basic unit tests catch the error.
  // Some condition leads to branch1 executing. In this case we see
  // if the fuzzer is smart enough to formulate an input that starts with '\'
  if (lastChar == '\\') {
    branch1(chars, size);
  } else {
    branch2();
  }
}
