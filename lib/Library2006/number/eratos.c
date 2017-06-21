/*************************
 * Eratos                *
 * @creator Akira Satou  *
 *************************/

#include "number.h"



/* 
 * ����ȥ��ƥͥ����� version 1 (The sieve of Eratosthenes)
 * �Ķ��[3, x], x>=3, ��δ�����ǿ����ɤ�����vector<bool>������롣
 * primes[i] == true �� 2*i+3 ���ǿ��Ǥ��뤳�Ȥ�ɽ����
 * �׷�: �ʤ�
 */
void eratos(ullong x, bit_vector &primes){
  ullong i, j;
  
  primes = bit_vector((x-1)/2, 1);
  
  for(i=3; i<=sqrt(x); i+=2)
    for(j=3; i*j<=x; j+=2)
      primes[(i*j-3)/2] = 0;
}

/*
 * ����ȥ��ƥͥ����� version 2 (The sieve of Eratosthenes)
 * �Ķ��[min(a, b), max(a, b)], a, b>0, ����ǿ���vector<ulong>������롣
 * �׷�: �ؿ� eratos (version 1)
 */
void eratos(ullong a, ullong b, vector<ullong> &p){
  bit_vector v;
  ullong i;
  
  if(a>b) swap(a, b);
  if(b<2) return;
  if(b==2){ p = vector<ullong>(1, 2); return; }
  
  eratos(b, v);
  
  if(a<=2){ p.push_back(2); a = 2; }
  for(i=(a-2)/2; i<=(b-3)/2; i++)
    if(v[i]) p.push_back(2*i+3);
}

/*
 * ����ȥ��ƥͥ����� version 3 (The sieve of Eratosthenes)
 * �Ķ��[min(a, b), max(a, b)], a, b>0, ����ǿ���ulong[]������롣
 * �׷�: �ؿ� eratos
 */
void eratos(ullong a, ullong b, ullong p[], ullong &p_size){
  bit_vector v;
  ullong i, j;

  if(a>b) swap(a, b);
  if(b<2) return;
  if(b==2){ p[0] = 2; return; }
  
  eratos(b, v);

  j = 0;
  if(a<=2){ p[j++] = 2; a = 2; }
  for(i=(a-2)/2; i<=(b-3)/2; i++){
    if(v[i]) p[j++] = 2*i+3;
  }

  p_size = j;
}
