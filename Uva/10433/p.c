// @JUDGE_ID:  17051CA  10433  C++
// @begin_of_source_code
#include<stdio.h>
#include<iostream>
#include<cstdio>
#include<vector>
#include<string>
#include<bitset>
#include<cassert>

using namespace std;

/** $BB?G\D9@0?t$N4pAC$rJQ99$9$k>l9g$K$O0J2<$N(B
 *  $B#5$D$N9`L\$rE,@Z$KD4@0$9$k$3$H(B
 */
typedef int digit;

#define BASE 10000
#define NDIGIT 4
#define FRONT "%d"
#define FORMAT "%04d"

class BigInteger{
 public:
  /* $B=i4|2=$O(B BASE $BL$K~$N?t$G9T$&$3$H(B */
  /* $B$3$N@)Ls$r<i$k8B$j$O9bB.$J=i4|2=$rJ]>Z(B */
  BigInteger( digit n = 0 ){
    assert( n < BASE);
    digits.assign(1, n);
  }

  BigInteger( vector<digit> &dts){
    digits = dts;
  }

  /* $B6uJ8;zNs$rF~$l$J$$$3$H!#?t;z$O@5$7$$$3$H$rJ]>Z$9$k(B */
  /* $BId9g$O=hM}$7$J$$(B!! */
  BigInteger( string n ){
    assert( !n.empty() );

    /* $B7e?t$rB7$($k(B */
    while( n.size() % NDIGIT ){
      n.insert(n.begin(), 1, '0');
      for ( int i = n.size()-NDIGIT; i >= 0; i -= NDIGIT ){
	digits.push_back(atoi(n.substr(i, NDIGIT).c_str()));
      }
    }
  }

  string toString() const {
    string result;
    char buffer[NDIGIT+1];

    /* $B@hF,$KM>J,$J#0$rIU$1$J$$(B */
    sprintf(buffer, FRONT, digits.back()), result = buffer;

    /* NDIGI $B$K$h$C$FJQ2=;I$;$?$$$,!"(Bsprintf $B$G%U%)!<%^%C%H$r(B */
    /* $B:n$k<j4V$r$+$1$k$h$j$O=$@5$7$?J}$,NI$$(B */
    for ( int i = digits.size()-2; i >= 0; i--){
      sprintf(buffer, FORMAT, digits[i]), result += buffer;
    }
    return result;
  }

  int size() const{
    return digits.size();
  }
  
  const digit &operator [] (int n) const {
    return digits[n];
  }

  bool operator == ( const BigInteger &O ) const {
    if( size() != O.size() ) return false;
    
    for( int i = 0; i < size(); i++ ){
      if ( digits[i] != O[i] ) return false;
    }
    return true;
  }

  bool operator < ( const BigInteger &O ) const {
    if ( size() < O.size() ) return true;
    if ( size() > O.size() ) return false;

    for( int i = size()-1; i >= 0; i-- ){
      if( digits[i] < O[i] ) return true;
      if( digits[i] > O[i] ) return false;
    }
    return false;
  }

  bool operator > ( const BigInteger &O ) const {
    if( size() > O.size() ) return true;
    if( size() < O.size() ) return false;

    for( int i = size()-1; i >= 0; i--){
      if ( digits[i] > O[i] ) return true;
      if ( digits[i] < O[i] ) return false;
    }
    return false;
  }

  void operator += ( const BigInteger &O ){
    digits.resize(max(size(), O.size()) +1, 0);
    
    for( int i = 0; i < O.size(); i++ ) add(O[i], i, digits);
    regularize();
  }

  void operator -= ( const BigInteger &O){
    assert( size() >= O.size() );

    for(int i = 0;  i < O.size(); i++ ) sub(O[i], i, digits);
    regularize();
  }

  void operator *= ( const BigInteger &O){
    vector<digit> dts;

    dts.resize(size() + O.size() +1, 0);
    for(int i=0; i<size(); i++){
      for(int j=0;  j<O.size(); j++) mul(digits[i] * O[j], i+j, dts);
    }
    digits = dts;
    regularize();
  }

  void operator /= ( const BigInteger &O ){
    BigInteger rem = BigInteger(digits);

    *this = BigInteger(0);
    div(*this, rem, O); /* $BM>$j$O(B rem $B$K3JG<$5$l$F$$$k(B */
  }

  void operator ^= ( int exponent ){
    BigInteger p = *this;
    bitset<32> bits = exponent;
    
    assert(exponent >= 0);
    *this = BigInteger(1);
    for(int i=0; bits.any(); i++){
      if(bits[i]) *this *= p;
      bits[i] = false, p *= p;
    }
  }

 private:

  vector<digit> digits;
  
  void add( digit num, int order, vector<digit> &dts ){
    dts[order] += num;

    for( int i = order; i < dts.size(); i++ ){
      if ( dts[i] < BASE ) break;
      dts[i+1]++;
      dts[i] -= BASE;
    }
  }

  void sub( digit num, int order, vector<digit> &dts ){
    dts[order] -= num;

    for ( int i = order; i < dts.size()-1; i++ ){
      if ( dts[i] >= 0) break;
      dts[i+1]--;
      dts[i] += BASE;
    }
  }

  void mul( digit num, int order, vector<digit> &dts ){
    dts[order] += num;

    for ( int i = order; i < dts.size(); i++ ){
      if ( dts[i] < BASE ) break;
      dts[i+1] += dts[i] / BASE;
      dts[i] %= BASE;
    }
  }
  
  void div( BigInteger &quot, BigInteger &rem, const BigInteger &pow ){
    if ( rem < pow ) return ;

    BigInteger pow2 = pow; pow2.twice();
    div(quot, rem, pow2);

    quot.twice();
    if ( !(pow > rem) ) rem -= pow, quot.increment();
  }

  void twice() {
    digits.push_back(0);
    for ( int i = digits.size()-1; i >= 0; i--) add(digits[i], i, digits);
    regularize();
  }

  void increment(){
    digits.push_back(0);
    add(1, 0, digits);
    regularize();
  }

  void regularize(){
    while ( digits.back() == 0 && digits.size() > 1){
      digits.pop_back();
    }
  }
};

class AutomorphicNumbers{
 public:
  string input, output;

  bool read(){
    return( cin >> input );
  }

  void work(){
    BigInteger a = BigInteger( input );
    a *= a;
    output = a.toString();

    if ( output.substr( output.size() - input.size(), input.size() ) ==
	 input ){
      cout << "Automorphic number of " << input.size() << "-digit." << endl;
    } else{
      cout << "Not an Automorphic number." << endl;
    }
  }

};

main(){
  AutomorphicNumbers AN;

  while ( AN.read() ){
    AN.work();
  }
}

// @end_of_source_code


