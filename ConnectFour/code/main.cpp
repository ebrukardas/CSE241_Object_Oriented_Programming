#include <iostream>
using namespace std;
#include "ConnectFourPlus.h"
#include "ConnectFourDiagonal.h"
#include "ConnectFourPlusUndo.h"


int main(){

	string v="";
	do{
		cout << "Enter game mode (P/D/U)\t--> ";
		cin >> v;
		cout << endl;
	}while( v[0]!='P' && v[0]!='D' && v[0]!='U' && v.size()!=1 );
	
	if(v[0]=='P'){
		ConnectFourPlus obj;
		obj.workingCond();
	}else if(v[0]=='D'){
		ConnectFourDiagonal obj;
		obj.workingCond();
	}else if(v[0]=='U'){
		ConnectFourPlusUndo obj;
		obj.workingCond();
	}
	
}
