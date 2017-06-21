#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define Infinity	9999
#define Unreachable	0
#define BufferLength	1024
#define InputFile	"pipeline.txt"

typedef struct {
    int included;
    int length;
    int vertex;
  } Vertex;

int **makeMatrix(int *pSize, int *pNumSpa)
{
  char line[BufferLength];
  int size, numSpa, numDst, x, i, j;
  int **distMatrix;
  FILE *fp;

  if ((fp=fopen(InputFile,"r")) == NULL)  {
    printf("%s does not exist\n",InputFile);
    exit(1);
  }
  /* �����ο����϶�ο������� */
  fgets(line,BufferLength,fp);
  *pNumSpa = numSpa = atoi(strtok(line," \t"));
  numDst = atoi(strtok(NULL," \t"));

  /* ��Υ����γ��� */
  *pSize = size = numSpa + numDst;
  if ((distMatrix = (int **)malloc(sizeof(int *)*size)) == NULL)  {
    printf("insufficient memory\n");
    exit(1);
  }
  for (i=0; i<size; ++i)  {
    if ((distMatrix[i] = (int *)malloc(sizeof(int)*size)) == NULL)  {
      printf("insufficient memory\n");
      exit(1);
    }
  }

  /* ����������϶�ؤε�Υ������ */
  for (i=0; i<numSpa; ++i)  {
    for (j=0; j<numSpa; ++j)
      distMatrix[i][j] = Infinity;
    fgets(line,BufferLength,fp);
    distMatrix[i][numSpa] = 
      (x=atoi(strtok(line," \t"))) == Unreachable ? Infinity : x;
    for (j=numSpa+1; j<size; ++j)
      distMatrix[i][j] = 
        (x=atoi(strtok(NULL," \t"))) == Unreachable ? Infinity : x;
  }

  /* ���϶�֤ε�Υ������ */
  for (i=numSpa; i<size; ++i)  {
    distMatrix[i][i] = Infinity;
    if (i+1 != size)  {
      fgets(line,BufferLength,fp);
      distMatrix[i][i+1] = 
        (x=atoi(strtok(line," \t"))) == Unreachable ? Infinity : x;
      for (j=i+2; j<size; ++j)
        distMatrix[i][j] = 
          (x=atoi(strtok(NULL," \t"))) == Unreachable ? Infinity : x;
    }
  }
  fclose(fp);

  /* �оι���ˤ��� */
  for (i=0; i<size; ++i)
    for (j=i+1; j<size; ++j)
      distMatrix[j][i] = distMatrix[i][j];

  return distMatrix;
}


int getMinimumSpanningForest(int num, int size, 
                             int **distance, Vertex *vertex, int **result)
{
  int length = 0;
  int minimumLength, minimumIndex;
  int i;

  while (num++ != size)  {
    minimumLength = Infinity;
    for (i=0; i<size; ++i)  {
      if (!vertex[i].included && vertex[i].length < minimumLength)  {
        minimumLength = vertex[i].length;
        minimumIndex = i;
      }
    }
    length += minimumLength;
    vertex[minimumIndex].included = 1;
    result[minimumIndex][vertex[minimumIndex].vertex] = 1;
    result[vertex[minimumIndex].vertex][minimumIndex] = 1;
    for (i=0; i<size; ++i)
      if (!vertex[i].included && distance[i][minimumIndex] < vertex[i].length) {
        vertex[i].length = distance[i][minimumIndex];
        vertex[i].vertex = minimumIndex;
      }
  }
  return length;
}

main()
{
  int size, spa, length = 0;
  int **distance = makeMatrix(&size,&spa);
  int **result;
  Vertex *vertex;
  int i, j;

  /* ĺ���ν���γ��ݤȽ���� */
  if ((vertex=(Vertex *)malloc(sizeof(Vertex)*size)) == NULL)  {
    printf("insufficient memory\n");
    exit(1);
  }
  for (i=0; i<spa; ++i)
    vertex[i].included = 1;	// ������ĺ���򿹤˲ä���
  for (i=spa; i<size; ++i)  {
    vertex[i].included = 0;	// �϶��ĺ���ϲä��ʤ�
    vertex[i].length = Infinity;
  }

  /* ����ɽ�����ܹ���γ��ݤȽ���� */
  if ((result=(int **)malloc(sizeof(int *)*size)) == NULL)  {
    printf("insufficient memory\n");
    exit(1);
  }
  for (i=0; i<size; ++i)  {
    if ((result[i]=(int *)malloc(sizeof(int)*size)) == NULL)  {
      printf("insufficient memory\n");
      exit(1);
    }
    for (j=0; j<size; ++j)
      result[i][j] = 0;
  }

  /* �������ܤ���ĺ���Τ�����û���դ���� */
  for (i=spa; i<size; ++i)
    for (j=0; j<spa; ++j)
      if (distance[i][j] < vertex[i].length)  {
        vertex[i].length = distance[i][j];
        vertex[i].vertex = j;
      }

  /* �Ǿ�������� */
  length = getMinimumSpanningForest(spa,size,distance,vertex,result);

  /* ��̤ν��� */
  printf("%d\n",length);
}
  







