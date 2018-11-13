//numberTheory.h
//Author: Horace Facey (Sept 2016)
//This module has the external function templates.

#ifndef NUMBERTHEORY_H
#define NUMBERTHEORY_H

template <class X>
X modPower(const X& base, const X& exponent, const X& modulus)
{
  if(exponent == 0 and modulus != 1)
    {return 1;}

  if(exponent == 0 and modulus == 1)
    {return 0;}
  
  if(exponent == 1)
    {return base%modulus;}

  else
    {
      X powerNow;
      powerNow = modPower(base,exponent/2,modulus);
      if(exponent%2 == 0)
	{return (powerNow * powerNow)%modulus;}
      
      else
	{return((powerNow*powerNow)%modulus)*(base%modulus)%modulus;} 
    }
}

template <class X>
bool isPrime(const X& num)
{
  if(num <= 1)
    {return false;}
  if(num <= 3)
    {return true;} // since num is int, returns true for 2 or 3
  if(num%2 == 0 or num%3 == 0)
    {return false;}

  X i = 5, sq;
  sq = num/2;

  while(i <= sq)
    {
      if((num%i == 0) or (num%(i+2)==0))
	{return false;}

      i += 6;
    }
  return true; //wikipedia primality test pseudocode adaptation
}

template <class X>
X extendedEuclid(const X& a,const X& b, X* px, X* py)
{
  if(b == 0)
    {
      *px = 1;
      *py = 0;
      return a;
    }
  else
    {
      X d, temp;
      d = extendedEuclid(b, a%b, px, py);
      temp = *px;
      *px = *py;
      *py = temp - *py * (a/b);
      return d;
    }

}

#endif
