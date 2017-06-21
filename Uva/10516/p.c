// @JUDGE_ID:  17051CA  10516  C++
// @begin_of_source_code
/* Count the Trees - BigInteger */
#include<stdio.h>
#include<iostream>
#include<cstdio>
#include<vector>
#include<string>
#include<bitset>
#include<cassert>

#define for if ( false ); else for

int max(int a, int b) { return (a >= b)? a : b; }

using namespace std;

typedef int digit;

#define BASE 10000
#define NDIGIT 4
#define FRONT "%d"
#define FORMAT "%04d"

#define LESS (-1)
#define EQUAL 0
#define GREATER 1

class BigInteger {
public:

  BigInteger( digit n = 0 ) {
    assert( abs(n) < BASE );
    
    negative = (n < 0);
    digits.assign(1, abs(n));
  }
  
  BigInteger( vector<digit> &dts, bool sign ) {
    negative = sign;
    digits = dts;
  }
  
  BigInteger( string n ) {
    assert( !n.empty() );
    
    negative = false;
    if ( n[0] == '-' ) negative = true, n = n.erase(n.begin());
    
    while ( n.size() % NDIGIT )
      n.insert(n.begin(), 1, '0');
    for ( int i = n.size()-NDIGIT; i >= 0; i -= NDIGIT )
      digits.push_back(atoi(n.substr(i, NDIGIT).c_str()));
  }
  
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

BigInteger power(BigInteger x, int n){
  BigInteger tmp = BigInteger(1);

  if(n>0){
    tmp = power(x, n/2);
    if(n%2==0) tmp = tmp*tmp;
    else tmp = tmp*tmp*x;
  }

  return tmp;
}

int n, d;

int read(){
  cin >> n >> d;
  if ( n == 0 && d == 0) return 0;
  return 1;
}

BigInteger M[33][20];
BigInteger S[33][20];
bool T[33][20];

void init(){
  for ( int i = 0; i < 33; i++ ){
    fill ( T[i], T[i] + 20, false );
  }
}

void compute( int n, int d ){
  M[n][0] = BigInteger( 1 );
  M[n][1] = BigInteger( 1 );
  S[n][0] = BigInteger( 1 );
  S[n][1] = BigInteger( 2 );
  T[n][0] = true;
  T[n][1] = true;
  for ( int i = 2; i <= d; i++ ){
    BigInteger tmp = power( S[n][i-2], n );
    M[n][i] = power( S[n][i-1], n ) - tmp;
    T[n][i] = true;
    S[n][i] = S[n][i-1] + M[n][i];
  }
}

void work(){
  cout << n << " " << d << " ";
  if ( T[n][d] ){
    cout << M[n][d].toString() << endl;
  }else{
    compute( n, d );
    cout << M[n][d].toString() << endl;
  }
}

main(){
  init();
  while ( read() ){
    work();
  }
}
// @end_of_source_code
