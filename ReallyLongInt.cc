//ReallyLongInt.cc
//Author: Horace Facey (Sept 2016)
//This module defines the methods and functions for a class, ReallyLongInt,
// which can handle reaaallllyyy looooonnnnggggg integers.

#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <cmath>
#include <climits>
#include "ReallyLongInt.h"

using namespace std;

ReallyLongInt::ReallyLongInt()
{
  numDigits = 1;
  unsigned int* rli = new unsigned int[numDigits];
  rli[0] = 0;
  isNeg = false;
  digits = rli;
}

ReallyLongInt::ReallyLongInt(long long num)
{
  stringstream numVal; //converting from a long long to a string
  numVal << num;
  string numStr;
  numVal >> numStr;
  
  unsigned i,j=0;
  if(numStr[0]=='-')
    {
      numDigits = numStr.size()-1;
      isNeg = true;
    }
  else
    {
      numDigits = numStr.size();
      isNeg = false;      
    }
  unsigned int* rli = new unsigned int[numDigits];
  for(i=isNeg;i<numStr.size();i++)
    {
      stringstream strVal; //conversion of const char* to int
      strVal << numStr[i];
      unsigned int numVal;
      strVal >> numVal;
      rli[j] = numVal;
      j++;
    }

  removeLeadingZeros(rli,numDigits);
  if(numDigits == 1 and rli[0] == 0)
    {isNeg = false;}

  digits = rli;
}//I would've created a private method and have both the string and num
//constructor call it, but that would've meant changing the header file.

ReallyLongInt::ReallyLongInt(const string& numStr)
{
  unsigned i,j=0;
  if(numStr[0]=='-')
    {
      numDigits = numStr.size()-1;
      isNeg = true;
    }
  else
    {
      numDigits = numStr.size();
      isNeg = false;      
    }
  unsigned int* rli = new unsigned int[numDigits];
  for(i=isNeg;i<numStr.size();i++)
    {
      stringstream strVal; //conversion of const char* to int
      strVal << numStr[i];
      unsigned int numVal;
      strVal >> numVal;
      rli[j] = numVal;
      j++;
    }

  removeLeadingZeros(rli,numDigits);
  if(numDigits == 1 and rli[0] == 0)
    {isNeg = false;}

  digits = rli;
      
}


void ReallyLongInt::removeLeadingZeros(unsigned* x,unsigned& xSize)
{
  if(x[0] == 0)
    {
      unsigned int t, i = 0,j = 0;
      while(i < xSize and x[i]==0)
	{i++;}
      if(i+1 <= xSize) //found a non-zero value
	{
	  for(t = i;t < xSize;t++)
	    {
	      x[j] = x[t];
	      j++;
	    }

	  xSize = j;
	}
      else
	{xSize = 1;} //an array of only zeros
    }

}

ReallyLongInt::ReallyLongInt(const ReallyLongInt& other)
{
  this->isNeg = other.isNeg;
  this->numDigits = other.numDigits;

  unsigned int* tempD = new unsigned int[this->numDigits];

  for(unsigned j=0;j<this->numDigits;j++)
    {tempD[j] = other.digits[j];} //creating a deep copy

  this->digits = tempD;

}

ReallyLongInt::ReallyLongInt(unsigned* digitArr, unsigned arrSize, bool isNeg)
{
  removeLeadingZeros(digitArr,arrSize);

  if(arrSize == 1 and digitArr[0]==0)
    {this->isNeg = false;}
  else
    {this->isNeg = isNeg;}
  this->digits = digitArr;
  this->numDigits = arrSize;
}

ReallyLongInt::~ReallyLongInt()
{delete[] digits;}

ReallyLongInt& ReallyLongInt::operator=(const ReallyLongInt& other)
{
  swap(other);
  return *this;
}

ReallyLongInt& ReallyLongInt::operator+=(const ReallyLongInt& other)
{
  *this = *this + other;
  return *this;
}

ReallyLongInt& ReallyLongInt::operator-=(const ReallyLongInt& other)
{
  *this = *this - other;
  return *this;
}

ReallyLongInt& ReallyLongInt::operator*=(const ReallyLongInt& other)
{
  *this = *this * other;
  return *this;
}

ReallyLongInt& ReallyLongInt::operator/=(const ReallyLongInt& other)
{
  *this = *this / other;
  return *this;
}

ReallyLongInt& ReallyLongInt::operator%=(const ReallyLongInt& other)
{
  *this = *this % other;
  return *this;
}

ReallyLongInt& ReallyLongInt::operator++()
{
  *this += 1;
  return *this;
}

ReallyLongInt& ReallyLongInt::operator--()
{
  *this-= 1;
  return *this;
}

ReallyLongInt ReallyLongInt::operator++(int dummy)
{
  ReallyLongInt x = *this;
  *this += 1;
  return x;
}

ReallyLongInt ReallyLongInt::operator--(int dummy)
{
  ReallyLongInt x = *this;
  *this-= 1;
  return x;
}

void ReallyLongInt::swap(ReallyLongInt other)
{
  bool tNeg = other.isNeg;
  unsigned tNum = other.numDigits;
  const unsigned* tempD = other.digits;

  other.digits = this->digits;
  other.isNeg = this->isNeg;
  other.numDigits = this->numDigits;
  this->digits = tempD;
  this->isNeg=tNeg;
  this->numDigits = tNum;

}

bool ReallyLongInt::equal(const ReallyLongInt& other) const
{
  if(isNeg != other.isNeg)
    {return false;}
  else if(numDigits != other.numDigits)
    {return false;}
  else
    {
      unsigned i = 0;
      while(i<numDigits)
	{
	  if(digits[i] == other.digits[i])
	    {i++;}
	  else
	    {return false;}
	}
      return true;
    }
}

bool ReallyLongInt::absGreater(const ReallyLongInt& other) const
{
  if(numDigits > other.numDigits)
    {return true;}
  else if(numDigits < other.numDigits)
    {return false;}
  else if(equal(other))
    {return false;}
  else
    {
      unsigned i = 0;
      while(i < numDigits)
	{
	  if(digits[i] > other.digits[i])
	    {return true;}
	  else if(digits[i] < other.digits[i])
	    {return false;}
	  else
	    {i++;}
	}
      return false; //This should never be executed since equality is tested
    }
}

bool ReallyLongInt::greater(const ReallyLongInt& other) const
{
  if(isNeg == false and other.isNeg==true)
    {return true;}
  else if(isNeg == true and other.isNeg==false)
    {return false;}
  else if(isNeg ==true) //then both numbers are negative
    {return not absGreater(other);}
  else //then both numbers are positive
    {return absGreater(other);}
}

ReallyLongInt ReallyLongInt::absAdd(const ReallyLongInt& other) const
{
  long long i,j;
  unsigned sum,resultSize,carry = 0;
  const unsigned* longer;
  const unsigned* shorter;
  if(this->numDigits>= other.numDigits)
    {
      longer = this->digits;
      shorter = other.digits;
      resultSize = this->numDigits +1;
      j = other.numDigits-1;
    }
  else
    {
      longer = other.digits;
      shorter = this->digits;
      resultSize = other.numDigits+1;
      j = this->numDigits-1;
    }

  unsigned int* sumArr = new unsigned int[resultSize];
  for(i=0;i<resultSize;i++)
    {sumArr[i]=0;}

  for(i = resultSize-2;i>=0;i--)
    {
      if(j>=0)
	{
	  sum = longer[i] + shorter[j] + carry;
	  j--;
	}
      else
	{sum = longer[i] + carry;}
      if(sum>=10)
	{carry = 1;}
      else
	{carry = 0;}
      sumArr[i+1] = sum%10;

    }

  if(carry)
    {sumArr[0] = 1;}

  return ReallyLongInt(sumArr,resultSize,false);

}

ReallyLongInt ReallyLongInt::absSub(const ReallyLongInt& other) const
{
  long long i,j;
  unsigned resultSize;
  bool makeNeg;
  const unsigned* top;
  const unsigned* under;
  if(absGreater(other))
    {
      top = this->digits;
      under = other.digits;
      resultSize = this->numDigits;
      j = other.numDigits-1;
      makeNeg = false;
    }
  else
    {
      top = other.digits;
      under = this->digits;
      resultSize = other.numDigits;
      j = this->numDigits-1;
      makeNeg = true;
    }

  unsigned int* diffArr = new unsigned int[resultSize];
  unsigned int* carryTop = new unsigned int[resultSize];
  for(i=0;i<resultSize;i++)
    {
      diffArr[i]=0;
      carryTop[i]=top[i];
    }

  for(i = resultSize-1;i>-1;i--)
    {
      if(j>-1 and carryTop[i] < under[j])
	{
	  long long t = i-1;
	  while(carryTop[t]==0)
	    {t--;}
	  while(t<i)
	    {
	      carryTop[t] -= 1;
	      carryTop[t+1] += 10;
	      t++;
	    }

	  diffArr[i] = carryTop[i] - under[j];
	  j--;
	}
      else if(j>-1)
	{
	  diffArr[i] = carryTop[i] - under[j];
	  j--;
	}
      else
	{diffArr[i] = carryTop[i];}
    }
  delete[] carryTop;
  return ReallyLongInt(diffArr,resultSize,makeNeg);
}

ReallyLongInt ReallyLongInt::add(const ReallyLongInt& other) const
{
  if(this->isNeg and other.isNeg)
    {return -absAdd(other);}
  else if(this->isNeg)
    {return -absSub(other);}
  else if(other.isNeg)
    {return absSub(other);}
  else
    {return absAdd(other);}
}

ReallyLongInt ReallyLongInt::sub(const ReallyLongInt& other) const
{
  if(this->isNeg and other.isNeg)
    {return -absSub(other);}
  else if(other.isNeg and not this->isNeg)
    {return absAdd(other);}
  else if(not other.isNeg and this->isNeg)
    {return -absAdd(other);}
  else
    {return absSub(other);}

}

ReallyLongInt ReallyLongInt::absMult(const ReallyLongInt& other) const
{

  unsigned carry,sum,d,i,j,resultSize;
  resultSize = this->numDigits + other.numDigits;
  unsigned int* p = new unsigned int[resultSize];

  for(i=0;i<resultSize;i++)
    {p[i]=0;}

  for(i=1;i<=this->numDigits;i++)
    {
      carry = 0;
      for(j=0;j<other.numDigits;j++)
	{
	  d = this->numDigits+other.numDigits-i-j;
	  sum=p[d]+this->digits[this->numDigits-i]*other.digits[other.numDigits-1-j]+carry;
	  p[d] = sum%10;
	  carry = sum/10;
	}
      p[this->numDigits-i]= p[this->numDigits-i]+carry;
    }

  return ReallyLongInt(p,resultSize,false);
}

ReallyLongInt ReallyLongInt::mult(const ReallyLongInt& other) const
{
  if(this->isNeg and other.isNeg)
    {return absMult(other);}
  else if(this->isNeg or other.isNeg)
    {return -absMult(other);}
  else
    {return absMult(other);}
}

void ReallyLongInt::absDiv(const ReallyLongInt& other, ReallyLongInt& quotient,
			   ReallyLongInt& remainder) const
{
  unsigned int* q = new unsigned int[this->numDigits];
  for(unsigned j=0; j<this->numDigits;j++)
    {q[j]= 0;}

  remainder = 0;
  for(unsigned i = 0; i < this->numDigits;i++)
    {
      remainder = 10*remainder;
      remainder = remainder + this->digits[i];
      unsigned d=0;
      while(not other.absGreater(remainder))
	{
	  //cout<<remainder<<endl;
	  remainder = remainder.absSub(other);
	  d = d+1;
	}
      q[i] = d;
    }
  quotient = ReallyLongInt(q,this->numDigits,false);
}

void ReallyLongInt::div(const ReallyLongInt& denominator, ReallyLongInt& quotient, ReallyLongInt& remainder) const
{
  absDiv(denominator,quotient,remainder);
  if(this->isNeg and denominator.isNeg)
    {quotient.isNeg = false;}
  else if((this->isNeg or denominator.isNeg) and not quotient.isZero())
    {quotient.isNeg = true;}
  else
    {quotient.isNeg = false;}
  
  if(this->isNeg and not remainder.isZero())
    {remainder.isNeg = true;}
}

void ReallyLongInt::flipSign()
{
  if(this->numDigits == 1 and this->digits[0] == 0)
    {this->isNeg = false;}
  else
    {this->isNeg = not this->isNeg;}
}

ReallyLongInt ReallyLongInt::operator-() const
{
  ReallyLongInt c = *this;
  c.flipSign();
  return c;
}

long long ReallyLongInt::toLongLong() const
{
  ReallyLongInt divisor = LLONG_MAX;
  divisor += 1;
  ReallyLongInt conNum = *this%divisor;
  string numStr,j;

  if(conNum.isNeg)
    {numStr += '-';}
  for(unsigned i=0;i<conNum.numDigits;i++)
    {
      stringstream ss;
      ss << conNum.digits[i];
      string j = ss.str();
      numStr+=j;
    }

  stringstream strVal;
  strVal << numStr;
  long long longNum;
  strVal >> longNum;
  return longNum;
}

ReallyLongInt operator+(const ReallyLongInt& x, 
				       const ReallyLongInt& y)
{return x.add(y);}

ReallyLongInt operator-(const ReallyLongInt& x, 
				       const ReallyLongInt& y)
{return x.sub(y);}

ReallyLongInt operator*(const ReallyLongInt& x, const ReallyLongInt& y)
{return x.mult(y);}

ReallyLongInt operator/(const ReallyLongInt& x, const ReallyLongInt& y)
{
  ReallyLongInt q,r;
  x.div(y,q,r);
  return q;
}

ReallyLongInt operator%(const ReallyLongInt& x, const ReallyLongInt& y)
{
  ReallyLongInt q,r;
  x.div(y,q,r);
  return r;
}

ostream& ReallyLongInt::print(ostream& out) const
{
  if(isNeg)
    {out<<'-';}

  for(unsigned i=0;i<numDigits;i++)
    {out<<digits[i];}

  return out;
}

ostream& operator<<(ostream& out, const ReallyLongInt& x)
{
  x.print(out);
  return out;
}

bool operator==(const ReallyLongInt& x, const ReallyLongInt& y)
{return x.equal(y);}

bool operator!=(const ReallyLongInt& x, const ReallyLongInt& y)
{return not x.equal(y);}

bool operator>(const ReallyLongInt& x, const ReallyLongInt& y)
{return x.greater(y);}

bool operator<(const ReallyLongInt& x, const ReallyLongInt& y)
{return (not x.greater(y))and(not x.equal(y));}

bool operator>=(const ReallyLongInt& x, const ReallyLongInt& y)
{return x.greater(y) or x.equal(y);}

bool operator<=(const ReallyLongInt& x, const ReallyLongInt& y)
{return not x.greater(y);}
