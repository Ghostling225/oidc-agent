#include "memory.h"

#include <stdlib.h>
#include <string.h>

#include "memzero.h"
#include "oidc_error.h"
#include "utils/logger.h"

void* secCalloc(size_t nmemb, size_t size) { return secAlloc(nmemb * size); }

void* secAlloc(size_t size) {
  if (size == 0) {
    return NULL;
  }
  size_t sizesize = sizeof(size);
  void*  p        = calloc(size + sizesize, 1);
  if (p == NULL) {
    oidc_errno = OIDC_EALLOC;
    logger(ALERT, "Memory alloc failed when trying to allocate %lu bytes",
           size);
    return NULL;
  }
  *(size_t*)p = size;
  return p + sizeof(size);
}

void* secRealloc(void* p, size_t size) {
  if (p == NULL) {
    return secAlloc(size);
  }
  if (size == 0) {
    secFree(p);
    return NULL;
  }
  size_t oldsize = *(size_t*)(p - sizeof(size_t));
  size_t movelen = oldsize < size ? oldsize : size;
  void*  newp    = secAlloc(size);
  if (newp == NULL) {
    return NULL;
  }
  memmove(newp, p, movelen);
  secFree(p);
  return newp;
}

void _secFreeArray(char** arr, size_t size) {
  size_t i;
  for (i = 0; i < size; i++) { secFree(arr[i]); }
  secFree(arr);
}

void _secFree(void* p) {
  if (p == NULL) {
    return;
  }
  void*  fp  = p - sizeof(size_t);
  size_t len = *(size_t*)fp;
  secFreeN(fp, len);
}
/** @fn void secFree(void* p, size_t len)
 * @brief clears and frees allocated memory.
 * @param p a pointer to the memory to be freed
 * @param len the length of the allocated memory
 */
void _secFreeN(void* p, size_t len) {
  if (p == NULL) {
    return;
  }
  moresecure_memzero(p, len);
  free(p);
}

void* oidc_memcopy(void* src, size_t size) {
  void* dest = secAlloc(size);
  memcpy(dest, src, size);
  return dest;
}

void oidc_memshiftr(void* src, size_t size) {
  char tmp = ((char*)src)[size - 1];
  memmove(src + 1, src, size - 1);
  ((char*)src)[0] = tmp;
}
