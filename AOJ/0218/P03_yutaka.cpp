#include<iostream>
using namespace std;

char getClass(int m, int e, int j){
    if ( m == 100 || e == 100 || j == 100 ||
	 (m + e)/2 >= 90 || (m + e + j)/3 >= 80 ) return 'A';
    if ( (m + e + j)/3 >= 70 ||
	 (m + e + j)/3 >= 50 && m >= 80 || e >= 80 ) return 'B';
    return 'C';
}

int main(){
    int n, pm, pe, pj;
    while( cin >> n && n ){
	for ( int i = 0; i < n; i++ ){
	    cin >> pm >> pe >> pj;
	    cout << getClass(pm, pe, pj) << endl;
	}
    }
    return 0;
}

/*
$B@8EL$r?t3X!"1Q8l!"9q8l$NE@?t$+$i>r7o$K=>$C$F(BA$B!"(BB$B!"(BC$B$N%/%i%9$K?6$jJ,$1$kLdBj$G$9!#(B

$BEy2A1i;;!"Hf3S1i;;!"O@M}1i;;Ey$rMQ$$$F4JC1$J>r7oJ,4t$,5-=R$G$-$k$+$,Ld$o$l$F$$$^$9!#(B

$B#32JL\$=$l$>$l$NE@?t(B m, e, j $B$r0z?t$H$7$F!"%/%i%9$rI=$9J8;z$rJV$94X?t(B getClass()$B$r:n@.$7$^$9!#(BgetClass$B$OLdBjJ8$GM?$($i$l$?>r7o$K=>$C$F!"3:Ev$9$k%/%i%9$NJ8;z$rJV$7$^$9!#(B main$B4X?t$G$O$=$l$>$l$NE@?t(B pm, pe, pj$B$rFI$_9~$_(B getClass(pm, pe, pj)$B$r=PNO$7$^$9!#(B
 */
