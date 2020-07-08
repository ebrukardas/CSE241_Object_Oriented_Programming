#include "ConnectFourPlus.h"

ConnectFourPlus::ConnectFourPlus(int c, int r)
				:ConnectFourAbstract(c,r){}

ConnectFourPlus::ConnectFourPlus()
				:ConnectFourPlus(5,5){}

ConnectFourPlus::ConnectFourPlus(string filename)
				:ConnectFourAbstract(filename){}


//		ASSIGNMENT OPERATOR
ConnectFourPlus& ConnectFourPlus::operator=(const ConnectFourPlus& other){

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
ConnectFourPlus::ConnectFourPlus(const ConnectFourPlus& other){

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

/*
//		DESTRUCTOR
ConnectFourPlus::~ConnectFourPlus(){
	for(int i=0; i<row; ++i)
		delete [] gameCells[i];
	delete [] gameCells;
	delete [] fullnessOfBoard;
}
*/



void ConnectFourPlus::workingCond(){

//	ConnectFourPlus c;
	playGame();
	game(player);

}

// player is a person/computer
void ConnectFourPlus::game( char player ){
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


bool ConnectFourPlus::controlBoard(char target){
	int t[2] = {0,0};
	int column=0;
//cout << "CONTROLBOARD\n";
cout << "";
	t[0]=controlVertical(target);
	t[1]=controlHorizontal(target);
//cout << t[0] << "/" << t[1] << "/" << t[2] << "/" << t[3] << endl;
	for(int i=0; i<2; ++i){
		if( t[i]==-1 ){
			return true;
		}
	}
	return false;
}

int ConnectFourPlus::findPosition(char rival){ // rakip

	int c=0, r=0, index=-1;
	int arr[2]={0,0};

	for(c=0; c<column; ++c){
		for(r=row-1; r>1; --r){
			arr[0] = controlHorizontal(rival);
			arr[1] = controlVertical(rival);

			for( int i=0; i<2; ++i)
				if( arr[i]!=-2 )
					index=arr[i];
		}
	}
	return index;
}

bool ConnectFourPlus::play(){

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
bool ConnectFourPlus::play(char cellPosition){

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


int ConnectFourPlus::controlHorizontal(char target){ //yatay

	int flag = 0, returnVal=-2, tempReturn=-1;
	for(int c=0; c<column; ++c){
		for( int r=row-1, i=0;	i<fullnessOfBoard[c] && r>=0;	--r, ++i ){
			flag=0;
			tempReturn = -1;
			if( gameCells[r][c].getContent()==target ){
				for(int j=0;	j<4 && c+j<column;	++j){
					if( target == gameCells[r][c+j].getContent() ){	//İLK ELEM HEDEFSE
						++flag;
					}else if( tempReturn==-1 && fullnessOfBoard[c+j]+1==row-r ){
						tempReturn = c+j;
					}
				}
			}
			if(flag==4){							// there is 4 letters
				for(int m=0, d=c; m<4; ++m, ++d){
					winner[m][0]=r;
					winner[m][1]=d;
				}
				return -1;
			}else if( flag==3 ){						// there is 3 letters
				if( tempReturn==-1 ){
					if( fullnessOfBoard[c-1]+1==row-r )
						returnVal = c-1;
				}else{
					returnVal = tempReturn;
				}
			}
			else if( flag==2 && returnVal==-2 ){		// there is 2 letters
				if( tempReturn==-1 ){
					if( fullnessOfBoard[c-1]+1==row-r && c>0)
						returnVal = c-1;
				}else{
					returnVal = tempReturn;
				}
			}
			
/*
	3letter and 2 letter are seperated because i want to check 
	if there is 3 letter, that index should be returned first. 
	If there is not, then 2 letter index should be returned
*/
		}

	}
	return returnVal;
}

int ConnectFourPlus::controlVertical(char target){ //dikey
	int flag = 0, returnVal=-2, three=-1;

	for(int c=0; c<column; ++c){
		for( int i=fullnessOfBoard[c], r=row-1;		i>=2;	--i, --r ){
			flag=0;
			for(int j=0; j<4 && r-j>=0; ++j)
				if( target == gameCells[r-j][c].getContent() )
					++flag;					
			if(flag==4){											// 4 letters
				for(int m=0, f=r;	m<4;	++m, --f){
					winner[m][0]=f;
					winner[m][1]=c;
				}
				return -1;
			}
			else if( flag==3 && row-r+2==fullnessOfBoard[c] && three==-1 ){		// 3 letters
				returnVal = c;
				three = 0;
			}else if( flag==2 && row-r+1==fullnessOfBoard[c] 
						&& returnVal==-2 && three==-1){	// 2 letters
				returnVal= c;
			}
		}
	}
	return returnVal;
}
