/* Home Work */
 
# include <stdlib.h>
 
# include "math_func.h"
 
unsigned long fact(unsigned long n) {
  unsigned long i = 1,a=n;
  
  if (n>1)
    {i=n-1;
      while (i>1)
	{
	  a = a*(i);
	  i=i-1;
	}
	
     return a;
    }
  else
    {
      return i;
    }
}
 
unsigned long fibo(unsigned long n){
  unsigned long  first=0,second=1;
  unsigned long tmp;
  while (n!=0)
    {
      tmp=first+second;
      first=second;
      second=tmp;
      n=n-1;
    }
  return first;  
}
 
unsigned long int_sqrt(unsigned long n)
{
  unsigned x = n;
  if (n==0)
    {
      return 0;
    }
  while (!((x*x<=n) && ((x+1)*(x+1)>n)))
    {
      x= (x+(n/x))/2;
      
    }
  return x ;
  
}
 
unsigned long digit_number(unsigned long n) {
  unsigned long a=0;
  if (n==0)
    {
      return 1;
    }

  while( n !=0)
    { n=n/10;
      a=a+1;
    }
  return a;
 
}
 
unsigned long binary_digit_number(unsigned long n) {
  unsigned long a=0;
   if (n==0)
    {
      return 1;
    }
  while( n !=0)
    { n=n/2;
      a=a+1;
    }
  return a;
 
}
 
unsigned long power_of_2(unsigned long n) {
  unsigned long a=0,b=1 ;
  while (a<n)
    {
        b =2*b;
	a=a+1;
    }
  return b;
}
 
unsigned long divisor_sum(unsigned long n) {
  unsigned long result = 1;
  unsigned long sqrt = int_sqrt(n);
  for(unsigned long i = 2 ;i<=sqrt;i++)
    {
      if (n%i==0 )
	{
	  result+=i;
	  if (n/i!=sqrt)
	    {
	      result+=n/i;
	    }
	}
    }
  return result;
   
}
