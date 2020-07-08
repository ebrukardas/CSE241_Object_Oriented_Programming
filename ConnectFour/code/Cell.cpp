#include "Cell.h"

/****************************************************************************/
/*******************	CONSTRUCTORS	*************************************/
/****************************************************************************/

Cell::Cell(int rowN, int colN, char value){
	if( colN<0 || rowN<0 || 
		( value!='X' && value!='O' && value!='.' ) ){

		cerr << "CELL CANNOT CREATED. YOUR INPUT OUT OF THE TABLE.\n";
		exit(1);
	}
	column = colN;
	row = rowN;
	content = value;
}

Cell::Cell(int rowN, int colN ):Cell(rowN, colN, '.'){}

Cell::Cell():Cell(0, 0, '.'){}

/****************************************************************************/
/***************************	SETTERS		*********************************/
/****************************************************************************/

void Cell::set(int r, int c, char v){
	if( r<0 || c<0 || ( v!='X' && v!='O' && v!='.' ) ){
		cerr << "CELL CANNOT SETTED. YOUR INPUT IS NOT VALID.\n";
		return;
	}
	column = c;
	row = r;
	content = v;
}

void Cell::set(char v){	content = v;	}

/****************************************************************************/
/***************************	GETTERS		*********************************/
/****************************************************************************/
//inline char Cell::getContent()const{	return content;		}
//inline int Cell::getRow()const{	return row;	}
char Cell::getColumn()const{	return (char)(column+65);	}
			

/****************************************************************************/
/***********************	OPERATORS	*************************************/
/****************************************************************************/
// ++(prefix), ++(postfix), == !=


/*	++ prefix operator
 *	empty will be X, X will be O, O will be empty(.)
 *	returns itself(with change)
*/
Cell& Cell::operator++(){
	if(content == '.')
		content = 'X';
	else if(content == 'X')
		content = 'O';
	if(content == 'O')
		content = '.';
	return *this;
}

/*	++ postfix operator
 *	empty will be X, X will be O, O will be empty(.)
 *	returns temporary object(without change), object will be changed
*/		
Cell Cell::operator++(int){
	Cell temp(row,column,content);
	if(content == '.')
		content = 'X';
	else if(content == 'X')
		content = 'O';
	else if(content == 'O')
		content = '.';
	return temp;
}

/*	>> operator
 *	row, column and content will be in the istream
 *	returns istream
*/
istream& operator>>(istream& in, Cell& obj){
	in >> obj.row >> obj.column >> obj.content;
	return in;
			
}

/*	<< operator
 *	row, column and content will be in the ostream
 *	returns ostream
*/		
ostream& operator<<(ostream& out, const Cell& obj){
	out << "[" << obj.getRow() << "][" << obj.getColumn() << "]=" 
		<< obj.getContent() ;
	return out;
}

/*	== operator
 *	row, column and content will be compared
 *	returns true if rows, columns and contents are same , else false
*/
bool Cell::operator==(const Cell& other)const{
	return (column==other.column && row==other.row &&
			content==other.content);
}

/*	!= operator
 *	row, column and content will be compared
 *	returns true if rows, columns and contents are not same, else false
*/	
/*inline bool Cell::operator!=(const Cell& other)const{
	return !(*this == other);
}*/

