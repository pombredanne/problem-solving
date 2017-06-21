// @JUDGE_ID:  17051CA  10145  C++
// @begin_of_source_code
/* ���ߥ�졼����� */
/* DBMS �Υ�å������ƥ���ۤ������� */

#include<stdio.h>
#include<iostream>
#include<string> 
#include<map>

#define GRANTED 1
#define BLOCKED 2

char m;
int t_id, i_id;

void work(){

  map<int, int> item_state;
  map<int, int> item_transaction;
  map<int, char> item_mode;
  map<int, int> transaction_state;
  map<int, int> multi; /* ��ͭ���Ƥ��뤫�ɤ��� */

  while(1){
    cin >> m ;
    if(m=='#') break;
    cin >> t_id >> i_id;

    /* trasaction ���֥�å�����Ƥ�����̵�� */
    if(transaction_state[t_id]==BLOCKED){ cout << "IGNORED" << endl; goto next;}

    if(m=='X'){ /* X ��å����ߤ� */
      if(item_state[i_id]==0 ){/* item ���ե꡼�ʤ� OK*/
	cout << "GRANTED" << endl;
	item_state[i_id] = GRANTED;
	item_transaction[i_id] = t_id;
	item_mode[i_id] = 'X';
      }else{/* ���Ǥ� item ��¸�� */
	/* ��ͭ����Ƥ��롢�ޤ��ϡ���ʬ�Υȥ�󥶥������Ǥʤ� */
	if(multi[i_id]!=0 || item_transaction[i_id]!=t_id){
	  transaction_state[t_id] = BLOCKED;
	  cout << "DENIED" << endl;
	}else{
	  cout << "GRANTED" << endl;
	  item_state[i_id] = GRANTED;
	  item_transaction[i_id] = t_id;
	  item_mode[i_id] = 'X';
	}
      }
    }else if(m=='S'){/* S ��å����ߤ� */
      if(item_mode[i_id]=='X'){ /* X ��å��������äƤ��� */
	/* ��ʬ�ʤ�OK �Ҿ� */
	if(item_transaction[i_id]==t_id){
	  cout << "GRANTED" << endl;
	}else{
	  cout << "DENIED" << endl;
	  transaction_state[t_id] = BLOCKED;
	}
      }else{
	/* S ��å��������äƤ��� */
	if(item_state[i_id]==0){
	  item_state[i_id] = GRANTED;
	  item_transaction[i_id] = t_id;
	}else if(item_transaction[i_id]!=t_id){
	  multi[i_id]++;
	}
	cout << "GRANTED" << endl;
      }
    }

  next:;
  }
}

main(){
  int testCase;
  cin >> testCase;
  for(int i=0; i<testCase; i++){
    if(i!=0) cout << endl;
    work();
  }
}
// @end_of_source_code
