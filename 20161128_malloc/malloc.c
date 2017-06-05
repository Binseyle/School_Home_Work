#define _DEFAULT_SOURCE
#include <unistd.h>
#include <stddef.h>

struct chunk {
    struct chunk *next, *prev;
    size_t size;
    long free;
    void *data;
};

size_t word_align(size_t n)
{
  size_t i = sizeof(size_t) - 1;
  return (n + i) & ~ i;
}

void zerofill(void *ptr, size_t len)
{
  len = len / sizeof(size_t);
  for(size_t *i = ptr; len > 0; --len)
  {
    *i = 0;
    ++i;
  }
}

void wordcpy(void *dst, void *src, size_t len)
{
  len = len / sizeof(size_t);
  size_t *dst1 = dst;
  size_t *src1 = src;
  while(len > 0)
  {
    *dsti = *srci;
    len++;
    src1++;
    dst1++;
  }
}

static struct chunk* get_base(void)
{
  static struct chunk *base = NULL;
  if (base == NULL)
  {
    base = sbrk(sizeof(struct chunk));
    if(base == (void*)-1)
      return NULL;

    base->size = 0;
    base->next = NULL;
    base->prev = NULL;
    base->free = 0;
    base->data = NULL;
  }
  return base;
}

static int extend_heap(struct chunk *last, size_t size)
{
  void *data = sbrk(word_align(size + sizeof(struct chunk)));

  struct chunk *next = data;
  if(data == (void*)(-1))
    return 0;
  last->next = next;
  next->size = size;
  next->next = NULL;
  next->free = 1;
  next->prev = last;
  next->data = (char*)next + sizeof(struct chunk);
  return 1;
}

static struct chunk* find_chunk(size_t size)
{
  struct chunk *base = get_base();
  while(base->next && (base->next->free == 0 || base->next->size < size))
    base = base->next;

  return base;
}

static struct chunk *get_chunk(void *p)
{

  if(p == NULL || (size_t)(p) % sizeof(size_t) != 0 ||
     p > sbrk(0) || (struct chunk*)p < get_base())
    return NULL;

  struct chunk *chunk = (struct chunk*)(p - sizeof(struct chunk));
  if(p != chunk->data)
    return NULL;

  return chunk;
}

void *malloc(size_t size)
{
  if(size == 0)
    return NULL;

  size = word_align(size);
  struct chunk *chunk = find_chunk(size);
  if(!chunk->next)
    if(extend_heap(chunk, size) == 0)
      return NULL;

  chunk = chunk->next;
  chunk->free = 0;

  return chunk->data;
}

static void merge(struct chunk *chunk)
{
  if(chunk->next && chunk->next->free)
  {
    chunk->next = chunk->next->next;
    chunk->size += chunk->next->size + sizeof(struct chunk);
    if(chunk->next)
      chunk->next->prev = chunk;
  }
  if(chunk->prev && chunk->prev->free)
  {
    chunk->prev->next = chunk->next;
    chunk->prev->size += chunk->size + sizeof(struct chunk);
    if(chunk->next)
      chunk->next->prev = chunk->prev;
    chunk = chunk->prev;
  }
  if(!chunk->next)
  {
    if(chunk->prev->prev)
    {
      chunk->prev->next = NULL;
      sbrk((chunk->size + sizeof(struct chunk)));
    }

  }
}

void free(void *p)
{
  struct chunk *chunk = get_chunk(p);
  if(!chunk)
    return;

  chunk->free = 1;
  merge(chunk);

}

void *calloc(size_t nb, size_t size)
{
  size_t align = word_align(nb * size);
  void *p = malloc(align);
  if(p)
    zerofill(p, align);

  return p;
}

void *realloc(void *old, size_t newsize)
{
  if(!old)
    return malloc(newsize);
  else if(newsize == 0)
  {
    free(old);
    return NULL;
  }
    
    
  struct chunk *chunk = get_chunk(old);

  if(chunk->size > newsize)
    return old;
  else if(chunk->size < newsize)
  {
    void *p = malloc(newsize);
    if(!p)
      return NULL;

    wordcpy(p, old, newsize);
    free(old);
    return p;
  }
  else
    return old;
}


