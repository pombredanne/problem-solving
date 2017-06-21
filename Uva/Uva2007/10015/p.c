// @JUDGE_ID:  17051CA  10015  C++
// @begin_of_source_code
/* �ǿ� ���ߥ�졼����� */
/* �������Υ���ȥ��ƥͥ������ */
#include<stdio.h>
#include<iostream>
#include<string>
#include<vector>

/* 
 * ����ȥ��ƥͥ����� version 1 (The sieve of Eratosthenes)
 * �Ķ��[3, x], x>=3, ��δ�����ǿ����ɤ�����vector<bool>������롣
 * primes[i] == true �� 2*i+3 ���ǿ��Ǥ��뤳�Ȥ�ɽ����
 * �׷�: �ʤ�
 */
void eratos(int x, bit_vector &primes){
  int i, j;
  
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
void eratos(int a, int b, vector<int> &p){
  bit_vector v;
  int i;
  
  if(a>b) swap(a, b);
  if(b<2) return;
  if(b==2){ p = vector<int>(1, 2); return; }
  
  eratos(b, v);
  
  if(a<=2){ p.push_back(2); a = 2; }
  for(i=(a-2)/2; i<=(b-3)/2; i++)
    if(v[i]) p.push_back(2*i+3);
}

int n;
vector<int> prime;

int read(){
  cin >> n;
  return n==0 ? false : true;
}

void init(){
  eratos(2, 35000, prime);
}

void work(){
  vector<int> v;
  v.resize(n);
  for(int i=0; i<n; i++) v[i] = i+1;

  int index = 0;
  int pos = 0;
  while(1){
    if(v.size()==1) break;
    pos = pos + prime[index++]-1;
    pos = pos%v.size();
    v.erase(v.begin()+pos);
  }

  cout << v[0] << endl;
}

main(){
  init();
  while(read()){
    work();
  }
}
// @end_of_source_code


