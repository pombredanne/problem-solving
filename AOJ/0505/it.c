#include<stdio.h>
#include<string.h>

int main(){
	int ba[101][2],n,m,i,j,c;
	
	while(0<=scanf("%d%d",&n,&m)){
		if(n==0 && m==0)break;
		
		//��Ū���ֹ�ȿͿ������
		memset(ba,0,sizeof(ba));
		
		
		//��Ū���ֹ������ȿͿ��׻�
		for(i=1;i<=n;i++){
			for(j=1;j<=m;j++){
				scanf("%d",&c);
				if(c==1)++ba[j][1];
				ba[j][0]=j;
			}
		}
		
		//�Ϳ��ǥ�����
		for(i=1;i<=m;i++){
			for(j=i;j<=m;j++){
				if(ba[j][1]>ba[i][1]){
					c=ba[j][1];
					ba[j][1]=ba[i][1];
					ba[i][1]=c;
					
					c=ba[j][0];
					ba[j][0]=ba[i][0];
					ba[i][0]=c;
				}
			}
		}
		
		//����
		for(i=1;i<=m;i++){
			printf("%d",ba[i][0]);
			if(i!=m)printf(" ");
		}
		printf("\n");
	}
	return 0;
}

