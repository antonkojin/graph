/* Anton Kozhin 830515 */
#ifndef MALLOC_CHECK_H
#define MALLOC_CHECK_H
#include <stdlib.h>

void *malloc_check(size_t size);
void *calloc_check(size_t nmemb, size_t size);

#endif
