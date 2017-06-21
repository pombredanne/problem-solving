#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <bitset>
#include <cassert>

#define for if ( false ); else for

int max(int a, int b) { return (a >= b)? a : b; }

using namespace std;

/* Ǥ��Ĺ�����δ�����ѹ�������ˤϰʲ��� */
/* 5 �Ĥι��ܤ�Ŭ�ڤ�Ĵ�����뤳��. */
typedef int digit;

#define BASE 10000
#define NDIGIT 4
#define FRONT "%d"
#define FORMAT "%04d"

/* ��Ӥ�����ͤ����������Ѥ���. */
#define LESS (-1)
#define EQUAL 0
#define GREATER 1


/* ����դ�Ǥ��Ĺ�������饹 BigInteger */
/* June 01, 2003 */
class BigInteger {
public:

  /* ������� BASE ̤���ο��ǹԤ�����.
     �����������¤�Ϲ�®�ʽ�������ݾڤǤ���.
     ʸ����ǽ��������Τ��Ǥ����. ���餫�� BASE ��꾮����
     ���Ȥ��ݾڤǤ�����ˤΤ߻Ȥ�����. */
  BigInteger( digit n = 0 ) {
    assert( abs(n) < BASE );
    
    negative = (n < 0);
    digits.assign(1, abs(n));
  }
  
  BigInteger( vector<digit> &dts, bool sign ) {
    negative = sign;
    digits = dts;
  }
  
  /* ��ʸ���������ʤ�����. ���������������Ȥ��ݾڤ���.
     ��Ƭ��̵�̤� 0 ��̵������. ������� regularize ��¹Ԥ��뤳��.
     ��Ƭ�� '-' ���դ��Ƥ�����Τ߽�������. '+' ����Ͻ������ʤ�.*/
  BigInteger( string n ) {
    assert( !n.empty() );
    
    negative = false;
    if ( n[0] == '-' ) negative = true, n = n.erase(n.begin());
    
    while ( n.size() % NDIGIT )
      n.insert(n.begin(), 1, '0');
    for ( int i = n.size()-NDIGIT; i >= 0; i -= NDIGIT )
      digits.push_back(atoi(n.substr(i, NDIGIT).c_str()));
  }
  
  /* ����ξ��ˤΤ���Ƭ�� '-' ���դ���.
     �����ξ��������դ��뤫�ɤ����� FRONT �ν�����˰�¸����.*/
  string toString() {
    char buffer[NDIGIT+1];
    string result;
    
    if ( negative ) result = "-";
    sprintf(buffer, FRONT, digits.back()), result += buffer;
    
    for ( int i = digits.size()-2; i >= 0; i-- )
      sprintf(buffer, FORMAT, digits[i]), result += buffer;
    return result;
  }
  
  int size() {
    return digits.size();
  }
  
  digit &operator [] ( int n ) {
    return digits[n];
  }
  
  bool sign() {
    return negative;
  }
  
  bool operator == ( BigInteger &O ) {
    return (compare(O, false) == EQUAL);
  }
  
  bool operator < ( BigInteger &O ) {
    return (compare(O, false) == LESS);
  }
  
  bool operator > ( BigInteger &O ) {
    return (compare(O, false) == GREATER);
  }
  
  BigInteger operator + ( BigInteger &O ) {
    if ( sign() == O.sign() )
      return add(*this, O, sign());
    else if ( compare(O, true) == LESS )
      return sub(O, *this, O.sign());
    else
      return sub(*this, O, sign());
  }
  
  BigInteger operator - ( BigInteger &O ) {
    if ( sign() != O.sign() )
      return add(*this, O, sign());
    else if ( compare(O, true) == LESS )
      return sub(O, *this, !O.sign());
    else
      return sub(*this, O, sign());
  }
  
  BigInteger operator * ( BigInteger &O ) {
    return mul(*this, O, sign() ^ O.sign());
  }
  
  pair<BigInteger, BigInteger> divmod( BigInteger &O ) {
    pair<BigInteger, BigInteger> result;
    
    result.second = BigInteger(digits, false);
    BigInteger denom = BigInteger(O.digits, false);
    div(result.first, result.second, denom);
    
    result.first.negative = sign() ^ O.sign();
    result.first.regularize();
    result.second.negative = sign() ^ O.sign();
    result.second.regularize();
    return result;
  }
  
 private:
  
  bool negative;
  vector<digit> digits;
  
  /* ignore �� true �ˤ��뤳�Ȥ�����̵�뤷����������Ӥ�Ԥ�. */
  int compare( BigInteger &O, bool ignore ) {
    if ( !ignore && (sign() != O.sign()) ) return (sign())? LESS : GREATER;
    
    const bool absolute = (ignore || !sign());
    if ( size() < O.size() ) return (absolute)? LESS : GREATER;
    if ( size() > O.size() ) return (absolute)? GREATER : LESS;
    
    for ( int i = size()-1; i >= 0; i-- ) {
      if ( digits[i] < O[i] ) return (absolute)? LESS : GREATER;
      if ( digits[i] > O[i] ) return (absolute)? GREATER : LESS;
    }
    return EQUAL;
  }
  
  void twice() {
    digits.push_back(0);
    
    digit carry = 0;
    for ( int i = 0; i < size(); i++ ) {
      digits[i] += digits[i] + carry;
      if ( digits[i] < BASE ) carry = 0;
      else carry = 1, digits[i] -= BASE;
    }
    regularize();
  }
  
  void increment() {
    digits.push_back(0);
    
    digit carry = 1;
    for ( int i = 0; carry > 0; i++ ) {
      digits[i] += carry;
      if ( digits[i] < BASE ) carry = 0;
      else carry = 1, digits[i] -= BASE;
    }
    regularize();
  }
  
  void regularize() {
    while ( digits.back() == 0 && digits.size() > 1 )
      digits.pop_back();
    if ( digits.size() == 1 && digits[0] == 0 ) negative = false;
  }
  
  static BigInteger add( BigInteger &a, BigInteger &b, bool sign ) {
    BigInteger result = BigInteger(a.digits, sign);
    
    result.digits.resize(max(a.size(), b.size()) + 1, 0);
    digit carry = 0;
    
    for ( int i = 0; i < result.size(); i++ ) {
      if ( i < b.size() ) result[i] += b[i] + carry;
      else result[i] += carry;
      
      if ( result[i] < BASE ) carry = 0;
      else carry = 1, result[i] -= BASE;
    }
    
    result.regularize();
    return result;
  }
  
  static BigInteger sub( BigInteger &a, BigInteger &b, bool sign ) {
    BigInteger result = BigInteger(a.digits, sign);
    
    assert(result.size() >= b.size());
    digit borrow = 0;
    
    for ( int i = 0; i < result.size(); i++ ) {
      if ( i < b.size() ) result[i] -= b[i] + borrow;
      else result[i] -= borrow;
      
      if ( result[i] >= 0 ) borrow = 0;
      else borrow = 1, result[i] += BASE;
    }
    
    result.regularize();
    return result;
  }
  
  static BigInteger mul( BigInteger &a, BigInteger &b, bool sign ) {
    BigInteger result;
    
    result.digits.resize(a.size() + b.size(), 0);
    result.negative = sign;
    
    for ( int i = 0; i < b.size(); i++ )
      for ( int j = 0; j < a.size(); j++ ) {
	digit carry = b[i] * a[j];
	for ( int k = i+j; carry > 0; k++ ) {
	  result[k] += carry;
	  if ( result[k] < BASE ) carry = 0;
	  else carry = result[k] / BASE, result[k] %= BASE;
	}
      }
    
    result.regularize();
    return result;
  }
  
  static void div( BigInteger &quot, BigInteger &rem, BigInteger &pow ) {
    if ( rem.compare(pow, true) == LESS ) return;
    
    BigInteger pow2 = pow; pow2.twice();
    div(quot, rem, pow2);
    
    quot.twice();
    if ( pow.compare(rem, true) <= EQUAL ) rem = rem - pow, quot.increment();
  }
  
};



string int2string( int n ) {
  char buffer[16];
  
  sprintf(buffer, "%d", n);
  return string(buffer);
}

int main() {
  for ( int i = 0; i < 50000; i++  ) {
    int a = rand() % 32000;
    int b = rand() % 32000;
    
    if ( rand() % 2 == 0 ) a *= (-1);
    if ( rand() % 2 == 0 ) b *= (-1);
    
    if ( b == 0 ) continue;
    
    int c = a / b;
    
    string as = int2string(a);
    string bs = int2string(b);
    string cs = int2string(c);
    
    BigInteger A = BigInteger(as);
    BigInteger B = BigInteger(bs);
    string result = A.divmod(B).first.toString();
    
    if ( result != cs ) {
      cout << "ERROR at " << a << " / " << b << endl;
      cout << "at " << A.toString() << " / " << B.toString() << endl;
      cout << "int: " << cs << endl;
      cout << "big: " << result << endl;
      break;
    }
  }
  
  return 0;
}



