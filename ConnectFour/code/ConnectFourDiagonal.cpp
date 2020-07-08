#include "ConnectFourDiagonal.h"

ConnectFourDiagonal::ConnectFourDiagonal(int c, int r)
				:ConnectFourAbstract(c,r){}

ConnectFourDiagonal::ConnectFourDiagonal()
				:ConnectFourDiagonal(5,5){}

ConnectFourDiagonal::ConnectFourDiagonal(string filename)
				:ConnectFourAbstract(filename){}


//		ASSIGNMENT OPERATOR
ConnectFourDiagonal& ConnectFourDiagonal::operator=(const ConnectFourDiagonal& other){

	if(this!=&other){
		row=other.row;
		column = other.column;
		for(int i=0; i<row; ++i)
			delete[] gameCells[i];
		delete[] gameCells;
		delete[] fullnessOfBoard;
		
		
		gameCells = new Cell*[row];
		fullnessOfBoard = new int[column];

		for(int i=0; i<column; ++i)
			fullnessOfBoard[i] = other.fullnessOfBoard[i];

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
ConnectFourDiagonal::ConnectFourDiagonal(const ConnectFourDiagonal& other){

	row=other.row;
	column = other.column;
	for(int i=0; i<row; ++i)
		delete[] gameCells[i];
	delete[] gameCells;
	delete[] fullnessOfBoard;
		
	gameCells = new Cell*[row];
	fullnessOfBoard = new int[column];

	for(int i=0; i<column; ++i)
		fullnessOfBoard[i] = other.fullnessOfBoard[i];

	for(int i=0; i<row; ++i){
		gameCells[i] = new Cell[column];
		for(int j=0; j<column; ++j){
			gameCells[i][j].set(i,j,(other.gameCells[i][j]).getContent());
		}
	}
}

void ConnectFourDiagonal::workingCond(){

	playGame();
	game(getPlayer());

}


void ConnectFourDiagonal::game( char player ){
	auto s = 0, tt=0, flag=0;
	turn='U';
	while(tt==0){
		if(s!=0){
			if(s%2==0)
				turn = 'U';
			else
				turn = 'P';
		}
		for( flag = getWidth()*getHeight()-s; flag>0 ; --flag ){
			if(turn=='U'){
				s=enterPosition( firstUser );
				if( s!=-2 )
					break;
				else{
					if( play(s) ){
						flag=-1;
						tt=1;
					}
				}
				turn='P';
			}else{
				if(player=='P'){							// USER PLAY
					s = enterPosition( secondUser ) ;
					if( s!=-2 )								// file read
						break;
					else{
						if( play(s) ){
							flag=-1;
							tt=1;
						}
					}
				}else if(player=='C'){						// COMPUTER PLAY
					if( play() ){
						flag=-1;
						tt=1;
					}
				}
				turn = 'U';
			}
			printBoard();
			if(flag==1){			
				flag =-1;
			}
		}
		if(flag<0){
			break;
		}
	}
}



bool ConnectFourDiagonal::controlBoard(char target){
	int t[2] = {0,0};
	int column=0;
//cout << "CONTROLBOARD\n";
cout << "";
	t[0]=rightCross(target);
	t[1]=leftCross(target);

//cout << t[0] << "/" << t[1] << "/" << t[2] << "/" << t[3] << endl;
	for(int i=0; i<2; ++i){
		if( t[i]==-1 ){
			return true;
		}
	}
	return false;
}

int ConnectFourDiagonal::findPosition(char rival){ // rakip

	int c=0, r=0, index=-1;
	int arr[2]={0,0};

	for(c=0; c<column; ++c){
		for(r=row-1; r>1; --r){
			arr[0] = leftCross(rival);
			arr[1] = rightCross(rival);

			for( int i=0; i<2; ++i)
				if( arr[i]!=-2 )
					index=arr[i];
		}
	}
	return index;
}

bool ConnectFourDiagonal::play(){

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
bool ConnectFourDiagonal::play(char cellPosition){

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



/*
	HELPER FUNCTIONS:
	
	If there is 3 legal letters, functions return index+30 because
	functions also return 2 legal letters to block or win. This is how
	I seperate them. (XX.X / OOO. vs)
	If 4 letters found, 
	it directly returns the value to report there is a winning


*/

int ConnectFourDiagonal::rightCross(char target){
//cout << "GİRDİ\n";
	int flag = 0, returnVal=-2, tempReturn=-1;;
	for( int c=0; c<column; ++c ){
		for( int r=row-1, k=0;	k<fullnessOfBoard[c];	--r, ++k ){
			if( gameCells[r][c].getContent()==target && c+3<column && 
				(fullnessOfBoard[c+1] > 1 || fullnessOfBoard[c+2] > 2 || 
				fullnessOfBoard[c+3] > 3 ) ){

				flag=0;
				for( int i=0;	i<4 && r-i>0 && c+i<column;		++i )
					if( gameCells[r-i][c+i].getContent() == target )
						++flag;
					else if(tempReturn==-1)
						tempReturn=c+i;
				if(flag==4){												// found 4
					for(int m=0, f=r, d=c;	m<4;	++m, --f, ++d){
						winner[m][0]=f;
						winner[m][1]=d;
					}
					return -1;
				}else if(flag==3){											// found 3
					if( c-1>=0 && fullnessOfBoard[c]-2==fullnessOfBoard[c-1]
						&& fullnessOfBoard[c-1]>=0 ){
						returnVal= c-1;
					}else if( c+3<column && fullnessOfBoard[c+2]==fullnessOfBoard[c+3] ){
						returnVal= c+3;
					}else if(tempReturn!=-1)
						returnVal = tempReturn;
				}else if( flag==2 && returnVal==-2 ){						// found 2
					if( c-1>=0 && r<row-1
						&& fullnessOfBoard[c]==fullnessOfBoard[c-1]+2 ){
						returnVal= c-1;
					}else if( c+2<column && fullnessOfBoard[c+1]==fullnessOfBoard[c+2] ){
						returnVal= c+2;
					}else if(tempReturn!=-1)
						returnVal = tempReturn;
				}
			}
		}
	}
	return returnVal;
}



int ConnectFourDiagonal::leftCross( char target ){
	int flag = 0, returnVal=-2, tempReturn = -1;
	for( int c=1; c<column; ++c ){
		for( int r=row-1, k=0; k<fullnessOfBoard[c]; --r, ++k ){
			if( gameCells[r][c].getContent()==target ){
				flag=0;

				for(int i=0;	i<4 && c-i>=0 && r-i>=0;	++i){
					if( target == gameCells[r-i][c-i].getContent() )
						++flag;
					else if(tempReturn==-1 && gameCells[r-i][c-i].getContent()=='.')
						tempReturn = c-i;
				}
				if(flag==4){						// found 4
					for(int m=0, f=r, d=c; m<4; ++m, --f, --d){
						winner[m][0]=f;
						winner[m][1]=d;
					}
					return -1;
				}else if(flag==3){				// found 3 letters
					if( c-3>=0 && fullnessOfBoard[c-3]==fullnessOfBoard[c-2])
						returnVal= c-3;
					else if(c+1<column && row-1-r-1==fullnessOfBoard[c+1])
						returnVal= c+1;
					else if(tempReturn!=-1)
						returnVal = tempReturn;
				}else if(flag==2 && c-2>=0 && c+1<column-1 && returnVal==-2){	// found 2 letters
					if(fullnessOfBoard[c-2]==fullnessOfBoard[c-1] &&
						fullnessOfBoard[c-2]!=row ){
						returnVal= c-2;
					}else if( c+1<column && fullnessOfBoard[c]-1==fullnessOfBoard[c+1] &&
							fullnessOfBoard[c]!=1){
						returnVal= c+1;
					}else if(tempReturn!=-1)
						returnVal = tempReturn;
				}
			}
		}
	}
	return returnVal;
}
