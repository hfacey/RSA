//keygen.cc
//Author: Horace Facey (Sept 2016)
//This module accepts two prime numbers and two files, and generates the
//public and private keys needed for the RSA algorithm.

#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include "numberTheory.h"
#include "ReallyLongInt.h"

using namespace std;

int main(int argc, char** argv)
{
  ReallyLongInt p(argv[1]);
  ReallyLongInt q(argv[2]);

  if(p > 100000 or q > 100000)
    {cout<<"Numbers are very large so primality not tested"<<endl;}
  else if(isPrime(p) != 1 or isPrime(q) != 1)
    {
      cout << "At least one number provided was not prime" <<endl;
      return 1;
    }

  ReallyLongInt n,t,e,gcd,x,y;
  n = p * q;
  t = (p-1)*(q-1);

  bool done = false;
  e = 2;
  while(not done)
    {
      gcd = extendedEuclid(e,t,&x,&y);
      if(gcd == 1)
	{done = true;}
      else
	{e++;}
    }

  if(x<0)
    {x += t;}

  ofstream pri(argv[4]);
  ofstream pub(argv[3]);
  pub << e <<" "<<n<<endl;
  pri << x <<" " <<n<<endl;
}
