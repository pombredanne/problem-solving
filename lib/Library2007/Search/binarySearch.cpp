#include<iostream>
using namespace std;

#define MAX 10000
#define NOT_FOUND (-1)

int binarySearch( int data[], int size, int key ){
    int mid, left, right;
    left = 0; // ���[
    right = size; // �E�[ + 1

    while ( left < right ){
	mid = ( left + right ) / 2; // �^�񒆂̃C���f�b�N�X�����߂�
	if ( data[mid] == key ) return mid; // �ړI�̒l�𔭌�
	else if ( key < data[mid] ) right = mid; // �O��������
	else left = mid + 1; // �㔼������
    }

    return NOT_FOUND; // �ړI�̒l���Ȃ�����
}

int main(void){
  int size, data[MAX], key;
  
  cin >> size;
  for ( int i = 0; i < size; i++ ) cin >> data[i];
  cin >> key;

  int result = binarySearch(data, size, key);
  if ( result == NOT_FOUND ) cout << "not found. " << endl;
  else cout << result << endl;

  return 0;
}
