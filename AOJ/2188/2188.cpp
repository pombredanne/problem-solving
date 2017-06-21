#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

static string name[20] = {"yotta", "zetta", "exa", "peta", "tera", "giga", "mega", "kilo", "hecto", "deca", "deci", "centi", "milli", "micro", "nano", "pico", "femto", "ato", "zepto", "yocto"};
static int T[20] = {24, 21, 18, 15, 12, 9, 6, 3, 2, 1, -1, -2, -3, -6, -9, -12, -15, -18, -21, -24};
bool isW(string n){
  for ( int i = 0; i < 20; i++ )
    if ( name[i] == n ) return true;
  return false;
}

int getW(string pre){
  for ( int i = 0; i < 20; i++ ){
    if ( name[i] == pre )  return T[i];
  }
}

int normalize(string &base, int w){
  if ( base.find('.') == string::npos) base += '.';
  int p = base.find('.');
  for ( int i = p; i >=2; i-- ) { swap(base[i], base[i-1]); w++;}
  while( base[0] == '0' ){
    base.erase(base.begin());
    swap(base[0], base[1]);
    w--;
  }
  if ( base[base.size()-1] == '.' ) base.erase(base.end()-1);
  return w;
}

void compute(){
  string base, unit;
  int w = 0;
  cin >> base >> unit;
  if ( isW(unit) ) { w = getW(unit); cin >> unit; }
  w = normalize(base, w);
  cout << base << " * 10^" << w << " " << unit << endl;
}

main(){
  int tcase; cin >> tcase;
  for ( int i = 0; i < tcase; i++ ) compute();
}
