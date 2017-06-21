// @author Yutaka Watanobe
// Backtracking with cutting back
#include<iostream>
#include<sstream>
#include<algorithm>
#include<cmath>
#define MAX 12

using namespace std;

class CakeShop{
    private:
    double cost[MAX][MAX]; // �P�[�L i �� �P�[�L j �Ƃ��������̃P�[�L i �̃R�X�g
    double possibleMin[MAX]; // �P�[�L i �����ɂ����܂�Ƃ��̍ŏ��l�i�\�Ȍ��菬�����l�j
    int buffer[MAX], size; // �P�[�L �̔��a��ۑ�
    bool used[MAX];
    double width;
    double manhattanDist; // ���̎��_�ł́A�c��̃P�[�L�̕K�v���̍ŏ��l�i�\�Ȍ��菬�����l�j

    public:
    void initialize(){
	for ( int i = 0; i < size; i++ ){
	    for ( int j = 0; j < size; j++ ){
		int r1 = buffer[i];
		int r2 = buffer[j];
		double base = sqrt((double)((r1+r2)*(r1+r2)-(r2-r1)*(r2-r1)));
		cost[i][j] = r1 * base/(r1+r2);
	    }
	}

	manhattanDist = 0;
	for ( int i = 0; i < size; i++ ){
	    double minDist = buffer[i];
	    for ( int j = 0; j < size; j++ ){
		if ( i == j ) continue;
		minDist = min( minDist, cost[i][j] );
	    }
	    possibleMin[i] = minDist * 2;
	    manhattanDist += minDist * 2;
	}

	for ( int i = 0; i < size; i++ ) used[i] = false;
    }

    bool recursive( int depth, double currentW, int pre  ){
	if ( currentW + manhattanDist + possibleMin[pre]/2 > width ) return false; 
	if ( depth == size ) return (currentW + buffer[pre] <= width);

	for ( int i = 0; i < size; i++ ){
	    if ( used[i] ) continue;
	    tryCake(i);
	    if ( recursive( depth+1, currentW + cost[pre][i] + cost[i][pre], i ) ) return true;
	    backCake(i);
	}

	return false;
    }
    
    bool judge(){
	initialize();
	for ( int start = 0; start < size; start++ ){
	    tryCake(start);
	    if ( recursive( 1, (double)buffer[start], start) ) return true;
	    backCake(start);
	}
	return false;
    }

    void tryCake(int current){
	used[current] = true;
	manhattanDist -= possibleMin[current];
    }

    void backCake(int current){
	used[current] = false;
	manhattanDist += possibleMin[current];
    }

    void simulate(){
	if ( judge() ) cout << "OK" << endl;
	else cout << "NA" << endl;
    }

    bool input(){
	size = 0;
	int r;
	string line; char ch;
	getline(cin, line);
	if ( cin.eof() ) return false;
	stringstream ss( line );
	ss >> width;
	while ( ss >> r ){
	    buffer[size++] = r;
	}
	return true;
    }
};

main(){
    CakeShop cakeShop;
    while ( cakeShop.input() ) cakeShop.simulate();
}



