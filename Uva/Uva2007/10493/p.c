// @JUDGE_ID:  17051CA  10493  C++
// @begin_of_source_code
#include<stdio.h>
#include<iostream>
#include<string>
/* ���� */
/* H + M = H*N + 1 */
/* �����򤯤� H = (M-1)/(N-1) �Ȥʤ� */
/* �嵭H�������Ȥʤ�� H + M ��ǭ�ο��Ǥ��� */
/* ˹�Ҥ���Ĥλ��˸¤�, Multiple �Ǥ��� */
int H, N, M;

int read(){
  cin >> N >> M;
  if(N==0 && M==0) return 0;
  return 1;
}

void work(){
  cout << N << " " << M << " ";
  if(N==1 && M==1){
    cout << "Multiple" << endl;
    return;
  }
  if(N==1 && M!=1){
    cout << "Impossible" << endl;
    return;
  }

  if( (M-1)%(N-1)==0 ){
    cout << (M-1)/(N-1) + M << endl;
  }else{
    cout << "Impossible" << endl;
  }
}

main(){
  while(read()){
    work();
  }
}
// @end_of_source_code
