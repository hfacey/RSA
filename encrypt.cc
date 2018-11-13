//encrypt.cc
//Author: Horace Facey (Sept 2016)
//This module accepts a public key, input and output file,
// and encrypts the input file using the RSA algorithm.

#include <iostream>
#include <fstream>
#include <string>
#include "numberTheory.h"
#include "ReallyLongInt.h"

using namespace std;

int main(int argc, char** argv)
{  
  ifstream pubFile(argv[1]);
  string expStr, modStr;
  ReallyLongInt exp,mod,base,crypt;
  pubFile >> expStr;
  pubFile >> modStr;
  exp = expStr;
  mod = modStr;

  ofstream encrypted(argv[3]);
  ifstream plain(argv[2]);
  char c;

  while(plain.get(c)) //iterates through the file 1 character at a time
    {
      base = c;
      crypt = modPower(base,exp,mod);
      encrypted << crypt << endl;
    }
}
