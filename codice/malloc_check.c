#include "malloc_check.h"
#include <stdio.h>

void *malloc_check(size_t size){
  void *mem;
  mem = malloc(size);
  if(!mem){
    fprintf(stderr, "OUT OF MEMORY ERROR");
    exit(EXIT_FAILURE);
  }
  return mem;
}

void *calloc_check(size_t nmemb, size_t size){
  void *mem;
  mem = calloc(nmemb, size);
  if(!mem){
    fprintf(stderr, "OUT OF MEMORY ERROR");
    exit(EXIT_FAILURE);
  }
  return mem;
}