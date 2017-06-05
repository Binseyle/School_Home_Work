#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/socket.h>
#include <err.h>
#include <unistd.h>




char* build_query(const char *url, size_t *len)
{
  char *query = NULL;
  asprintf(&query,"GET %s HTTP/1.0\n\r\n\r",url) ;
  *len = strlen(query);
  return query;
}

void get_page(const char *name, const char *url, const char *port)
{ 
  struct addrinfo hints;
  struct addrinfo *result, *rs;
  size_t query_len =0;
  int connex;

  // hints describes what we want
  // first fill the structure with 0s
  memset(&hints, 0, sizeof (struct addrinfo));
  // We only want IPv4, use AF_UNSPEC if you don't care which one
  hints.ai_family = AF_INET;
  // We want TCP
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = 0;
  hints.ai_protocol = 0;

  // name and port are strings (domaine name and port, obviously)
  // result will contain the result

  int addrinfo_error;
  addrinfo_error = getaddrinfo(name, port, &hints, &result);

  // Error management
  if (addrinfo_error != 0) 
  {
    errx(EXIT_FAILURE, "Fail getting address for %s on port %s: %s",
        name, port, gai_strerror(addrinfo_error));
  }

    for (rs = result; rs; rs = rs->ai_next)
  {
    connex = socket(rs->ai_family, rs->ai_socktype, rs->ai_protocol);
    if (connect(connex,rs->ai_addr,rs->ai_addrlen) !=1)
      break;
    close(connex);
  }
  
  freeaddrinfo(result);
  if(!rs)
    err(3,"could not find any adress to connect to");

  char *query = build_query(url,&query_len);
  if(send(connex,query,query_len,0) == -1)
    err(3,"problem during the request's send");
  
	char buf[50];
  int r;
  while ( (r = read(connex, buf, 50)) != 0) {
    if (r == -1)
      err(3, "error while reading");
    r = write(STDOUT_FILENO, buf, r);
    if (r == -1)
      err(3, "error while writing");
  }
 close(connex);
 free(query);
}

int main ()
{
 /* size_t len = 0;
  char *query = build_query("http://perdu.com",&len);
  printf("query : %s ",query);*/
  get_page("perdu.com", "http://perdu.com", "80");
  printf("Connexion closed by the server\n");
  return 0;
}

