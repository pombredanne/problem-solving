#include<iostream>
using namespace std;

int main(){
  int N, K, S[100], k;

  // �ƥ��ȥ��������������롼��
  while(1){
    cin >> N >> K;
    if ( N == 0 && K == 0 ) break;
    // S ���ɤ߹���
    for ( int i = 0; i < K; i++ ) cin >> S[i];
    // N �ͤε۷쵴�ˤĤ��ơ�S���鳺���������̤�����Ƥ���
    for ( int i = 0; i < N; i++ ){
      for ( int j = 0; j < K; j++ ){
	cin >> k;
	S[j] -=k;
      }
    }
    // S[i]����ˣ��ĤǤ�����ͤ������No
    bool ok = true;
    for ( int i = 0; i < K; i++ ) if ( S[i] < 0 ) ok = false;
    if ( ok ) cout << "Yes" << endl;
    else cout << "No" << endl;
    
  }
  return 0;
}
