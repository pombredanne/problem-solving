// @JUDGE_ID:  17051CA  10110  C++
// @begin_of_source_code
#include<stdio.h>
#include<math.h>
#include<iostream>
/* ���� */
/* �������2��Ǥ��뤫Ƚ�ꤹ��Ф褤 */

main(){
  long long a;
  long long sq;
  double t;
  while(1){ 
    cin >> a;
    if( a == 0 ) return 0;
    sq = (long long)sqrt((double)a);
    if( a == sq*sq){
      printf("yes\n");
    }else{
      printf("no\n");
    }
  }
  return 0;
}
// @end_of_source_code
