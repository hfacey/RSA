//decrypt.cc
//Author: Horace Facey (Sept 2016)
//This module accepts a private key, an encrypted input file and an output file
// and decrypts the encrypted file using the RSA algorithm

#include <iostream>
#include <fstream>
#include <string>
#include "numberTheory.h"
#include "ReallyLongInt.h"

using namespace std;

int main(int argc, char** argv)
{
  ifstream privFile(argv[1]);

  ReallyLongInt exp,mod,base,decrypt;
  string expStr, modStr, baseStr;  
  privFile >> expStr;
  privFile >> modStr;
  exp = expStr;
  mod = modStr;

  ifstream encrypted(argv[2]);
  ofstream plain(argv[3]);
  long long decryptInt;

  encrypted >> baseStr;
  base = baseStr;
  while(!encrypted.eof()) //goes through the file one integer at a time.
    {
      decrypt = modPower(base,exp,mod);
      decryptInt = decrypt.toLongLong();
      plain << (char) decryptInt;
      encrypted >> baseStr;
      base = baseStr;
    }
}
