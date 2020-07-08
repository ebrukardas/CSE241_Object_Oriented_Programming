#include "ConnectFourPlusUndo.h"

ConnectFourPlusUndo::ConnectFourPlusUndo(int c, int r)
				:ConnectFourPlus(c,r){

	entered = new int[row*column];
	enteredSize = 0;

}

ConnectFourPlusUndo::ConnectFourPlusUndo()
				:ConnectFourPlusUndo(5,5){}

ConnectFourPlusUndo::ConnectFourPlusUndo(string filename)
				:ConnectFourPlus(filename){

	entered = new int[row*column];
	enteredSize = 0;

}


//		ASSIGNMENT OPERATOR
ConnectFourPlusUndo& ConnectFourPlusUndo::operator=(const ConnectFourPlusUndo& other){

	if(this!=&other){
		row=other.row;
		column = other.column;
		enteredSize=other.enteredSize;
		for(int i=0; i<row; ++i)
			delete[] gameCells[i];
		delete[] gameCells;
		delete[] fullnessOfBoard;
		delete[] entered;
		
		
		gameCells = new Cell*[row];
		fullnessOfBoard = new int[column];
		entered = new int[row*column];

		for(int i=0; i<column; ++i){
			fullnessOfBoard[i] = other.fullnessOfBoard[i];
			entered[i] = other.entered[i];
		}

		for(int i=0; i<row; ++i){
			gameCells[i] = new Cell[column];
			for(int j=0; j<column; ++j){
				gameCells[i][j].set(i,j,(other.gameCells[i][j]).getContent());
			}
		}

	}
	return *this;

}

//		COPY CONSTRUCTOR
ConnectFourPlusUndo::ConnectFourPlusUndo(const ConnectFourPlusUndo& other){

	row=other.row;
	column = other.column;
	enteredSize = other.enteredSize;
	for(int i=0; i<row; ++i)
		delete[] gameCells[i];
	delete[] gameCells;
	delete[] fullnessOfBoard;
	delete[] entered;
		
	gameCells = new Cell*[row];
	fullnessOfBoard = new int[column];
	entered = new int[row*column];

	for(int i=0; i<column; ++i){
		fullnessOfBoard[i] = other.fullnessOfBoard[i];
		entered[i]=other.entered[i];
	}
	for(int i=0; i<row; ++i){
		gameCells[i] = new Cell[column];
		for(int j=0; j<column; ++j){
			gameCells[i][j].set(i,j,(other.gameCells[i][j]).getContent());
		}
	}
}



int ConnectFourPlusUndo::enterPosition(  char userLetter ){
	auto temp=0;
	string f, f2;

	do{
//cout << temp << endl;
		getline(cin,f);
		cout << endl;
		cout << f << endl;
		if( cin.fail() ){
			exit(1);
		}else if( f.size() ==1 )
			temp = f[0]-'A';
		else if( f.size()>=4 ){
			if( f.substr(0,4) == "SAVE" && f[4]==' '){
				writeFile( f.substr(5, f.size()-1), turn );
				temp=-1;
			}else if(f.substr(0,4) == "LOAD" && f[4]==' '){
				int tt = readFile( f.substr(5, f.size()-1) );
				if(tt==-1)
					temp=-1;
				else
					return tt;
			}else if(f.substr(0,4) == "UNDO" ){
				undo();
				temp=-1;
			}else{
				temp=-1;
			}
		}else if(f.size()==0){
			temp=-1;
		}

	}while( temp<0 || temp>=column || fullnessOfBoard[temp]==row ||
			gameCells[ row-1-fullnessOfBoard[temp] ][temp].getContent() == ' ' );
	
	setLetter(userLetter, temp);
	return -2;
}

void ConnectFourPlusUndo::setLetter(char userLetter, int column){
	int f = row-1-fullnessOfBoard[column];
	if(f!=-1){
		gameCells[f][column].set(userLetter);
		++fullnessOfBoard[column];
		entered[enteredSize] = column;
		++enteredSize;

	}else{
		cerr << "SET ERROR!\n";
	}
}

bool ConnectFourPlusUndo::undo(){

	if( enteredSize<2 ){
		cerr << "There is nothing to do for UNDO\n";
		return false;
	}

	int c1=entered[enteredSize-1] ,c2=entered[enteredSize-2];

	gameCells[ row-fullnessOfBoard[c1] ][c1].set('.');
	gameCells[ row-fullnessOfBoard[c2] ][c2].set('.');
	--fullnessOfBoard[c1];
	--fullnessOfBoard[c2];

	entered[enteredSize-1] = -1;
	entered[enteredSize-2] = -1;
	enteredSize-=2;
cout << endl;printBoard();
	return true;
}


void ConnectFourPlusUndo::workingCond(){

	playGame();
	game(getPlayer());

}

bool ConnectFourPlusUndo::play(){

//COMPUTER PLAY
	int block = findPosition(firstUser), win = findPosition(secondUser), ind=0;

	if(win>0 && fullnessOfBoard[win]<row){
		ind = win;
	}else if(block>0 && fullnessOfBoard[block]<row){
		ind = block;
	}else{
		ind = -1;
		for(int h=0; h<row; ++h){
			if(gameCells[fullnessOfBoard[h]][h].getContent()==secondUser 
				&& fullnessOfBoard[h]<row-1){
				ind = h;
			}else if(fullnessOfBoard[h]<row-1 && ind==-1 && fullnessOfBoard[column]<row){
				ind = column/2;
			}else{
				for(int k=0; k<getWidth(); ++k){
					if( fullnessOfBoard[k]<row ){
						ind=k;
						break;
					}
				}
			}
		}
	}
	char t = static_cast<char> (ind) + 65;			// to show computer input as character
	cout << "Computer input --> " << t << endl << endl;
	setLetter(secondUser, ind);
	if( controlBoard(secondUser)  && isEnd()){
		cout << "\n------------------------------------------------\n\n";
		for(int d=0; d<4; ++d)
			gameCells[ winner[d][0] ][ winner[d][1] ].set('o');
		printBoard();
		return true;
	}
	return false;
}


// user turn
bool ConnectFourPlusUndo::play(char cellPosition){

	char userLetter;
	if(turn=='U')
		userLetter = 'X';
	else
		userLetter = 'O';
	if( controlBoard(userLetter )  && isEnd() ){
		cout << "\n------------------------------------------------\n\n";
		for(int d=0; d<4; ++d)
			gameCells[ winner[d][0] ][ winner[d][1] ].set(userLetter+32);
		printBoard();
		return true;
	}
	return false;
}

