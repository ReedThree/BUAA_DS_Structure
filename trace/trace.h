#ifndef __TRACE_H__
#define __TRACE_H__

#include <stddef.h>

#define DEFAULT_STORE_CAPACITY 100

void traceInit();
void traceFree();
void traceSummarize();
void *_malloc(size_t __size);
void _free(void *__ptr);
void *_realloc(void *__ptr, size_t __size);

#endif