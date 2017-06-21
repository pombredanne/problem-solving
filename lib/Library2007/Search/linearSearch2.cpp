#include<iostream>
using namespace std;

#define MAX 10000
#define NOT_FOUND (-1)

int linearSearch( int data[], int size, int key ){
    int index = -1; // data[0]���猟�����J�n���邽��
    data[ size ] = key; // �ԕ����Z�b�g���� 

    while ( data[ ++index ] != key ); // �T������

    if ( index == size ) return NOT_FOUND; // �ԕ����@�\�����ꍇ 
    else return index; // �ړI�̒l�𔭌������ꍇ 
}

int main(void){
  int size, data[MAX], key;
  
  cin >> size;
  for ( int i = 0; i < size; i++ ) cin >> data[i];
  cin >> key;

  int result = linearSearch(data, size, key);
  if ( result == NOT_FOUND ) cout << "not found. " << endl;
  else cout << result << endl;

  return 0;
}
