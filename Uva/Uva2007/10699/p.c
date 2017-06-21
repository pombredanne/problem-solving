// factorize

#include<iostream>
#include<set>
using namespace std;

/*
 * �ǰ���ʬ�� version 1 (Factorization)
 * x�ΰ�����vector<int>������롣�����ǿ��ǤϤʤ��Τ�����ʤ���
 * �׷�: �ʤ�
 */
void factorize(set<int> &v, int x){
  v.clear();
  if(x<2) return;

  for(; !(x&1); x>>=1) v.insert(2);
  for(; x%3==0; x/=3) v.insert(3);

  for(int p=5, b=1; x/p>=p; b=-b, p+=3+b){
    for(; x%p==0; x/=p) v.insert(p);
  }
  
  if(x>1) v.insert(x);
}

main(){
  int n;
  while ( cin >> n ) {
    if ( n == 0 ) break;
    set<int> v;
    factorize(v, n);
    cout << n << " : " << v.size() << endl;
  }

}
