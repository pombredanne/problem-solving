/*��������N�ޤǤ��ǿ�����뤿��Ρ�C�ץ���� */
#include <stdio.h>
#include <math.h>

void main(){
  
  int i,j,limit,n,find;
  
  printf("���������ϡ�");
  scanf("%d",&n); /* �����ܡ��ɤ����¡�N)������ */
  
  for(i=2;i<=n;i++) {
    /*limit=sqrt(i);*/
    limit=i-1; /* limit=sqrt(i); */ /* ������limit��i-1 */
    find=1;
    for (j=2;j<=limit;j++){ /* ����J�ϣ�����limit�ޤ� */
      if (i%j==0) { /* ����ڤ줿���ǿ��ǤϤʤ��Τǣ£���뤹�� */
	find=0;
	break;
      }
    }
    if (find==1) { /* find�����Τޤޤʤ��ǿ� */
      printf("%d ",i);
    }
  }
  printf("\n"); 
}



