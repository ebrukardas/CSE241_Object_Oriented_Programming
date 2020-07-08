#include "ConnectFourAbstract.h"

//		CONSTRUCTOR
ConnectFourAbstract::ConnectFourAbstract(int c, int r){
	resize(c,r);
}

//		CONSTRUCTOR
ConnectFourAbstract::ConnectFourAbstract(string filename){
	resize(5,5);
	readFile(filename);
	fileOrCr=1;
}

//		ASSIGNMENT OPERATOR
ConnectFourAbstract& ConnectFourAbstract::operator=(const ConnectFourAbstract& other){

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
ConnectFourAbstract::ConnectFourAbstract(const ConnectFourAbstract& other){

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

//		DESTRUCTOR
ConnectFourAbstract::~ConnectFourAbstract(){
	for(int i=0; i<row; ++i)
		delete [] gameCells[i];
	delete [] gameCells;
	delete [] fullnessOfBoard;
}


void ConnectFourAbstract::playGame(){

// ASK TO BOARD SIZE
	string s="", t="";
	int w=0, h=0;
	do{
		cout << "Enter a board size width and height OR filename (.txt)\t--> ";
		cin >> s;
		if( s.size()>4 && (t=s.substr(s.size()-4)).compare(".txt") == 0 )
			break;

		w = stoi(s);
		cin >> h;
		cout << endl;
	}while( w<4 || h<4 );

//////////////////////////////////////////////////////////////////////////////
// Ask to choose competition will be against computer or another user
	player='P';
	do{
		cout << "Player | Computer\t--> ";
		cin >> player;
		cout << endl;
	}while( player != 'P' && player != 'C' );

	if(h!=0){
		resize(w, h);
	}else{
		readFile(s);
	}
	printBoard();
	cout << "------------------------------------------------\n\n";

}

bool ConnectFourAbstract::isEnd()const{
	int s=0, f =getWidth()*getHeight() ;
	for(int i=0; i<getWidth(); ++i)
		s+=getFullnessBoard(i);
	if( getWinnerPos(0,0) != -1 || s==f )
		return true;
	return false;
}




void ConnectFourAbstract::printBoard()const{

	cout << "BOARD IS:\n";
	
	for(char b='a';	b-'a'<getWidth(); ++b)
		cout << b << " " ;
	cout << endl;
	
	for(int i=0; i<getHeight(); ++i){
		for(int j=0; j<getWidth(); ++j)
			cout << gameCells[i][j].getContent() << " ";
		cout << endl;
	}

}

/*****************************************************************************
						READ & WRITE FILE FUNCTIONS
*****************************************************************************/

int ConnectFourAbstract::readFile( string filename ){

	if( filename.empty() ){
		cerr << "FILE NAME CANNOT BE EMPTY\n";
		return -1;
	}

	string line="", str ="";
	int kk=0, i=0, j=0, lenStr=0, tempRow=0, tempCol=0;
	ifstream tempRead, readFile;

	tempRead.open(filename);
	if( tempRead.is_open() ){
		while( getline(tempRead, line) ){
			++tempRow;
			tempCol = line.size();
		}
	}
	tempRead.close();

	line="";
	decltype(turn) tempPlayer = 'U';


	readFile.open(filename);
	if( readFile.is_open() ){
		if( getline(readFile, line) ){

// ****************************************************************************
// *******			TABLE HANDLING
// ****************************************************************************
			string *temp = new string[tempRow];
			temp[0]=line;
			for(i=1; getline(readFile,line); ++i){
				temp[i] = line;
			}

			resize(tempCol, tempRow);

			for(int r=0, i=0; r<tempRow; ++r )
				for(int c=0; c<tempCol; ++c){

					if( temp[r][c] == 'X' || temp[r][c] == 'O' ){
						gameCells[r][c].set( temp[r][c] );
						++i;
					}else if( temp[r][c] == '.' ){
						gameCells[r][c].set( temp[r][c] );
					}else if( temp[r][c] == '*' ){
						gameCells[r][c].set( temp[r][c] );
					}else if( temp[r][c] == ' ' ){
						gameCells[r][c].set( temp[r][c] );
					}else{
						cerr << "TABLE INCLUDE INVALID LETTER. X/O\n";
						return -1;
					}
				}

			for(int c=0; c<tempCol; ++c){
				fullnessOfBoard[c]=0;
				for(int r=0; r<tempRow; ++r ){
					if(gameCells[r][c].getContent()=='X' || 
						gameCells[r][c].getContent()=='O')
						++fullnessOfBoard[c];
				}
			}

			turn = tempPlayer;

			setHeight( tempRow );

			setWidth( tempCol );
			
			delete [] temp;
			
			cout << "FILE OPENED AND LOAD\n\n";
			printBoard();
			return i;
		}
		cerr << "FILE CANNOT BE EMPTY\n";
		return -1;

	}else{
		cerr << "FILE CANNOT OPENED\n";
		return -1;
	}

}



bool ConnectFourAbstract::writeFile( string filename, char players ){

	if( filename.empty() ){
		cerr << "FILE NAME CANNOT BE EMPTY\n";
		return false;
	}

	ofstream writeFilePtr;

	writeFilePtr.open(filename);
	if( writeFilePtr.is_open() ){

		for(int i=0; i<row; ++i){
			for(int j=0; j<column; ++j)
				writeFilePtr << gameCells[i][j].getContent();
			writeFilePtr << '\n';
		}
		cout << "FILE CREATED AND WROTE\n\n";
		writeFilePtr.close();
		return true;

	}else{
		cerr << "FILE CANNOT BE OPENED\n";
		return false;
	}

}


/****************************************************************************
 ****************************************************************************
							PRIVATE FUNCTIONS
 ****************************************************************************
 ***************************************************************************/

void ConnectFourAbstract::resize(int c, int r){

	setWidth(c);
	setHeight(r);

	gameCells = new Cell*[row];
	fullnessOfBoard = new int[column];
//	gameCells.resize(row);

	for(int i=0; i<column; ++i)
		fullnessOfBoard[i] = 0;

	for(int i=0; i<row; ++i){
		gameCells[i] = new Cell[column];
		for(int j=0; j<column; ++j){
			gameCells[i][j].set(i,j,'.');
		}
	}
}



int ConnectFourAbstract::enterPosition(  char userLetter ){
	auto temp=0;
	string f, f2;

	do{
//cout << temp << endl;
		getline(cin,f);
		cout << endl;
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
			}else{
				temp=-1;
			}
		}else if(f.size()==0){
			temp=-1;
		}
	}while( temp<0 || temp>=column || fullnessOfBoard[temp]==row ||
			gameCells[ row-1-fullnessOfBoard[temp] ][temp].getContent() == ' ');
	
	setLetter(userLetter, temp);
	return -2;
}

void ConnectFourAbstract::setLetter(char userLetter, int column){
	int f = row-1-fullnessOfBoard[column];
	if(f!=-1){
		gameCells[f][column].set(userLetter);
		++fullnessOfBoard[column];

	}else{
		cerr << "SET ERROR!\n";
	}
}



/*****************************************************************************/
/********************** 	SETTERS & GETTERS	******************************/
/*****************************************************************************/

void ConnectFourAbstract::setWidth(int val){
	if(val<=0){
		cerr << "WIDTH CANNOT BE NEGATIVE OR ZERO!\n";
		exit(1);
	}else
		column = val;
}

void ConnectFourAbstract::setHeight(int val){
	if(val<=0){
		cerr << "HEIGHT CANNOT BE NEGATIVE OR ZERO!\n";
		exit(1);
	}else
		row = val;
}

void ConnectFourAbstract::setFullnessBoard(int index,  int val){
	if(val<0 || val>row || index<0 || index>=column)
		cerr << "INVALID INPUT SET FULLNESS OF BOARD!\n";
	else
		fullnessOfBoard[index] = val;
}

/*****************************************************************************/
/*****************************************************************************/

//	getWidth & getHeight functions are inline functions in header file

int ConnectFourAbstract::getFullnessBoard(int index) const{
	if(index<0 || index>=column)
		cerr << "INVALID INDEX FOR GET FULLNESS OF BOARD\n";
	else
		return fullnessOfBoard[index];
	return -1;

}

int ConnectFourAbstract::getWinnerPos(const int ind1, const int ind2)const{

	if( ind1<0 || ind1>=4 || ind2<0 || ind2>=4 )
		cerr << "INVALID INDEX FOR GET WINNER POSITION\n";
	else
		return winner[ind1][ind2];
	return -1;

}


