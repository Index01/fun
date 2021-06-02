
#ifndef FUZZCONTROLCASE_H
#define FUZZCONTROLCASE_H

#include <stdlib.h>

int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size);
void iOverflowAndAllocate(const char* chars, size_t size);


#endif
