// @JUDGE_ID:  17051CA  10497  C++
// @begin_of_source_code
/* �׻� �� ¿��Ĺ �� Dynamic Programming 
 * �٥�ޤ�� F(n) = sum k=0 -> n  (-1)^k*nCk(n-k)!
 *                 = sum k=0 -> n  (-1)^k*n!/k!
 * �����򤤤� F(n+1) = (n+1)F(n) + (-1)^n+1
 * --> DP */
#include<iostream>
#include<cstdio>
#include<vector>
#include<string>
#include<bitset>
#include<cassert>

using namespace std;

/** ¿��Ĺ�����δ��ä��ѹ�������ˤϰʲ���
 *  ���Ĥι��ܤ�Ŭ�ڤ�Ĵ�����뤳��
 */
typedef int digit;

#define BASE 10000
#define NDIGIT 4
#define FRONT "%d"
#define FORMAT "%04d"

class BigInteger{
 public:
  /* ������� BASE ̤���ο��ǹԤ����� */
  /* �����������¤�Ϲ�®�ʽ�������ݾ� */
  BigInteger( digit n = 0 ){
    assert( n < BASE);
    digits.assign(1, n);
  }

  BigInteger( vector<digit> &dts){
    digits = dts;
  }

  /* ��ʸ���������ʤ����ȡ����������������Ȥ��ݾڤ��� */
  /* ���Ͻ������ʤ�!! */
  BigInteger( string n ){
    assert( !n.empty() );

    /* �����·���� */
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

    /* ��Ƭ��;ʬ�ʣ����դ��ʤ� */
    sprintf(buffer, FRONT, digits.back()), result = buffer;

    /* NDIGI �ˤ�ä��Ѳ��ɤ���������sprintf �ǥե����ޥåȤ� */
    /* ����֤򤫤�����Ͻ������������ɤ� */
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
    div(*this, rem, O); /* ;��� rem �˳�Ǽ����Ƥ��� */
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

string line;
string F[801];
int x;

void init(){

  F[0] = "0";
  F[1] = "0";
  F[2] = "1";
  BigInteger f = BigInteger(0);
  BigInteger one = BigInteger(1);
  for(int n=1; n<=800; n++){
    F[n] = f.toString();
    const BigInteger next = BigInteger(n+1);
    f *= next;
    if ( (n+1) % 2 == 0 ) f += one;
    else f -= one;
  }
}


int read(){
  cin >> x;
  if(x==-1) return false;
  return true;
}

void work(){
  cout << F[x] << endl;
}

main(){
  init();
  while(read()) work();
}
// @end_of_source_code
