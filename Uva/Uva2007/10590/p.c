#include <iostream>
#include <cstdio>
#include <string>
#include <cassert>
#include <vector>
#include <algorithm>
#define MAX 5001

using namespace std;

typedef long long digit;

#define BASE 10000000000000000LL
#define NDIGIT 16
#define HEAD "%lld"
#define BODY "%016lld"

// NDIGIT * BUF_SIZE ����������Ǽ�Ǥ��뤳�Ȥˤʤ�.
// ������, �׻�����Ǥ��η���ʾ�ο������ꤹ���ǽ����
// ������ˤϤ⤦������;͵��������Ƽ�뤳��.
#define BUF_SIZE 10


class BigInteger {
public:

	// 0 �ǽ����.
	BigInteger() {
		reset();
	}

	// BASE ̤���ο��������ͤ��������륳�󥹥ȥ饯��.
	// ���¤ϸ�������, ʸ����ˤ���������ϤϤ뤫�˹�®�˹Ԥ���.
	BigInteger( digit n ) {
		assert( n < BASE );

		reset();
		digits[0] = n;
	}

	void clear() {
		reset();
	}

	// �û���Ԥ�.  �������֤Ϸ�̤η�����������㤹��.
	void add( const BigInteger &r ) {
		resize(max(size(), r.size()) + 1);

		for ( int i = 0, sz = r.size(); i < sz; i++ ) digits[i] += r[i];
		for ( int i = 0, sz = size(); i < sz; i++ )
			if ( digits[i] >= BASE ) digits[i] -= BASE, ++digits[i+1];
		normalize();
	}

	// �����ͤ�ʸ����Ȥ����֤�.  ��Ƭ�� leading 0 ���դ��ʤ�.
	// �������֤Ϸ���˴ؤ����������㤹��.  sprintf �ˤ����ͤ�ʸ���󲽤�Ԥ��Τ�,
	// Ʊ���ͤ��Ф��� toString ��¿�Ѥ�, �礭��̵�̤Ȥʤ�.  ���ѤǤ���ʤ��,
	// ʸ����ˤ�륭��å����ͤ�����.
	string toString() const {
		char buf[NDIGIT + 1];
		string result;

		sprintf(buf, HEAD, most()), result = buf;
		for ( int i = size() - 2; i >= 0; i-- )
			sprintf(buf, BODY, digits[i]), result += buf;
		return result;
	}

private:

	// resize �Τߤ�Ĵ������� vector �Ǥ� C ����Ǥ⤹����
	// �ڤ��ؤ�����ǽ�Ǥ���.  BigInteger �δ��׵�ǽ�Ϥ��٤�
	// ����ʹߤ� private �Ȥ���·���뤳��.  ndigit �� vector ��
	// �������κݤˤ��Ѥ���.  vector �� size �᥽�åɤ��٤�
	// ����.

	int ndigit;
	digit digits[BUF_SIZE];

	inline void reset() {
		ndigit = 0, resize(1);
		digits[0] = 0;
	}

	inline void resize( int size ) {
		assert( size < BUF_SIZE );
		if ( size <= ndigit )
			ndigit = size;
		else
			while ( ndigit < size ) digits[ndigit++] = 0;
	}

	inline int size() const {
		return ndigit;
	}

	inline const digit &operator [] ( int n ) const {
		return digits[n];
	}

	inline digit most() const {
		return digits[ndigit - 1];
	}

	inline digit least() const {
		return digits[0];
	}

	inline void normalize() {
		while ( !normalized() ) ndigit--;
	}

	inline bool normalized() {
		return (most() != 0 || ndigit == 1);
	}

};

BigInteger T[MAX + 1];

void init(){
  for ( int i = 0; i < MAX; i++ ){
    T[i].clear();
  }

  T[0] = BigInteger(1);

  for ( int j = 1; j < MAX; j++ ){
    for ( int i = 0; i < MAX; i++ ){
      if ( i + j > MAX ) break;
      T[i + j].add(T[i]);
    }
  }


}

main(){
  int n;

  init();

  while ( scanf("%d", &n) != EOF ){
    cout << T[n].toString() << endl;
  }
}

