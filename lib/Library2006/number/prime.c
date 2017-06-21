/*************************
 * Prime                 *
 *************************/

#include <iostream>
#include <vector>
#include <cmath>

/*
 * ����С������
 * Solved 10394,
 */
bool prime[N+1];
void eratos( int n){

  fill(prime, prime+N, false);
  /* ������ǿ�����Ȥ��� */
  for ( int i = 3; i <= n; i += 2 ) prime[i] = true;
  prime[2] = true;
  
  /* �������Ǥʤ����������Ĥ� */
  for ( int i = 3, limit = (int)sqrt(n); i <= limit; i += 2 ) {
    if ( !prime[i] ) continue;
    
    for ( int j = i * i, k = i * 2; j <= n; j += k ) prime[j] = false;
  }
}
/**  ����ȥ��ƥͥ����� (Sieve of Eratosthenes) 
 * 
 *  ����: 
 *    0 .. n ���ϰϤ��ǿ�ɽ����� 
 *  �Ȥ���: 
 *    �ǿ�ɽ����¸���� vector<int> ���Ϥ����ȡ����̳��ݤϴؿ����Ԥ�. 
*/
void eratos( int n, vector<int> &p ) {
  p.assign(n + 1, false);
  
  /* ������ǿ�����Ȥ��� */
  for ( int i = 3; i <= n; i += 2 ) p[i] = true;
  p[2] = true;
  
  /* �������Ǥʤ����������Ĥ� */
  for ( int i = 3, limit = (int)sqrt(n); i <= limit; i += 2 ) {
    if ( !p[i] ) continue;
    
    for ( int j = i * i, k = i * 2; j <= n; j += k ) p[j] = false;
  }
}


/*  �ǿ�Ƚ�� */

/*  ���� */
/*    Ϳ����줿��Ǥʤ����� n ���ǿ����ɤ���Ƚ�ꤹ��. */
/*    ¿�����ǿ��ˤĤ��ƹԤ��ȸ�Ψ�������Τ��ǿ�ɽ���뤳��. */

bool isprime( int n ) {
  if ( n == 0 || n == 1 ) return false;
  
  /* 2 �� 3 �ǳ���ڤ�ʤ��������å� */
  if ( n == 2 || n == 3 ) return true;
  if ( n % 2 == 0 || n % 3 == 0 ) return false;
  
  /* ¾���ǿ�����ǳ���ڤ�ʤ��������å� */
  for ( int i = 5, b = 1, limit = (int)sqrt(n); i <= limit; b = -b, i += 3 + b )
    if ( n % i == 0 ) return false;
  
  return true;
}


int main() {
  vector<int> prime;
  
  /*  0 .. 100000 ���ǿ�ɽ�����*/
  eratos(100000, prime);
  
  /* �ǿ�ɽ���ǿ�Ƚ��η�̤������������ڤ���(���ںѤ�)*/
  for ( int i = 0; i <= 100000; i++ )
    if ( isprime(i) != prime[i] ) cout << "ERROR!! : " << i << endl;
  
  return 0;
}
