//factorial.cc
//Author: Horace Facey (Sept 2016)
//This module accepts a positive integer n and finds n! (n factorial)
//without the usual overflow issues

#include <iostream>
#include <string>
#include "ReallyLongInt.h"

using namespace std;

int main(int argc, char** argv)
{
  ReallyLongInt endNum(argv[1]);
  ReallyLongInt base("1");

  if(base >= endNum) //handles 0! and 1!
    {cout<<base<<endl;}
  else
    {
      ReallyLongInt prev("1");
      ReallyLongInt now;
      ReallyLongInt i("1");

      while(i <= endNum)
	{
	  now = prev * i;
	  prev = now;
	  i++;
	}
      cout<<now<<endl;
    }
}
