#include<iostream>
using namespace std;

main(){
    char n;
    int b, r, g, c, s, t;
    while(1){
	cin >> b >> r >> g >> c >> s >> t;
	if ( b == 0 && r == 0 && g== 0 && c == 0 && s == 0 && t == 0) break;
	int nb = b*5 + r*3; // $B%\!<%J%9%2!<%`$N?t(B
	int no = t - nb;    // $BDL>o%2!<%`$N?t(B
	int cur = 100;
	int result = cur + 15*b + 15*r + 15*nb + 7*g + 2*c - 3*(no-s) - 2*nb;
	cout << result << endl;
    }
}
