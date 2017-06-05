#include "test.h"
#include "hash_table.h"
/*
 * hash(data):
 * compute the hash of the nul terminated string data.
 */
uint32_t hash(char *data)
{
  uint32_t h = 0;
  while (*data != '\0')
  {
    h += *data;
    h+= h*1024;
    h = h^h/64;
    data++;
  }
  h+= h*8;
  h = h^h/2048;
  h+= h*32768;
  return h;

}

/*
 * create_htable(capacity):
 * build a new hash table with initial capacity.
 */
struct htable *create_htable(size_t capacity)
{
  struct htable *htab = malloc(sizeof(struct htable));
  htab->size = 0;
  htab->capacity = capacity;
  htab->tab = malloc(sizeof(struct pair) * capacity);
  for(size_t i = 0; i < capacity; i++)
  {
    htab->tab[i] = NULL;
  }
  return htab;

}

/*
 * access_htable(htable, key):
 * returns a pointer to the pair containing the given key
 */
struct pair *access_htable(struct htable *htable, char *key)
{
  uint32_t hashage = hash(key) % htable->capacity;
  struct pair *save = htable->tab[hashage];
  while(htable->tab[hashage])
  {
    if(strcmp(key,htable->tab[hashage]->key)==0)
    {
      struct pair *retour = htable->tab[hashage];
      htable->tab[hashage] = save;
      return retour;
    }
    htable->tab[hashage] = htable->tab[hashage]->next;
  }
  htable->tab[hashage] = save;
  return NULL;
}

/*
 * add_htable(htable,key,value):
 * add the pair (key,value) to the hash table
 */
int add_htable(struct htable *htable, char *key, void *value)
{
  uint32_t hashage = hash(key) % htable->capacity;
  struct pair *save = htable->tab[hashage];
  while(htable->tab[hashage])
  {
    if(strcmp(key,htable->tab[hashage]->key)== 0)
    {
      htable->tab[hashage] = save;
      return 0;
    }
    htable->tab[hashage] = htable->tab[hashage]->next;
  }
  htable->tab[hashage] = save;
  if (100 * (htable->size-1)/htable->capacity > 75)
  {
    struct htable *tmp = create_htable(htable->capacity * 2);
    for(size_t i = 0; i < htable->capacity ; i++)
    {
      for(;htable->tab[i]; htable->tab[i] = htable->tab[i]->next)
      {
         add_htable(tmp, htable->tab[i]->key, htable->tab[i]->value);
      } 
    }
    clear_htable(htable);
    htable->tab = tmp->tab;
    htable->capacity = tmp->capacity;
    htable->size = tmp->size;
  }
  struct pair *tmp = malloc(sizeof(struct pair));
  tmp->next = save;
  htable->tab[hashage] = tmp;
  tmp->hkey = hashage;
  tmp->key = key;
  (tmp->value) = value;
  htable->size++;
  return 1;
}

/*
 * remove_htable(htable, key):
 * removes the pair containing the given key from the hash table
 */
void remove_htable(struct htable *htable, char *key)
{
  uint32_t hashage = hash(key) % htable->capacity;
  struct pair *save = htable->tab[hashage];
  struct pair *prec = save;
  for(int i = 0;htable->tab[hashage];i++)
  {
    if(!strcmp(key,htable->tab[hashage]->key))
    {
      if( i == 0)
        save = save->next;
      else 
        prec->next = htable->tab[hashage]->next;
    }
    htable->tab[hashage] = htable->tab[hashage]->next;
    if( i != 0)
      prec = prec->next;
  }
  htable->tab[hashage] = save;
  htable->size--;
}

/*
 * clear_htable(htable):
 * delete all pairs in the table
 */
void clear_htable(struct htable *htable)
{
  if(htable)
  {
    for(int i = 0;htable->tab[i]; i++)
    {
      for(; htable->tab[i]; htable->tab[i] = htable->tab[i]->next)
      {
        free(htable->tab[i]);
      }
      htable->tab[i] = NULL;
    }
    htable->size = 0;
  }
}

