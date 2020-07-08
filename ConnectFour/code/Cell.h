#ifndef CELL_H
#define CELL_H

#include <iostream>
using namespace std;

class Cell{

	public:

		Cell(int rowN, int colN, char value);
		Cell(int rowN, int colN );
		Cell();

		void set(int r, int c, char v);
		void set(char v);

		inline char getContent()const{//;
			return content;
		}
		inline int getRow()const{//;
			return row;
		}
		char getColumn()const;

		friend istream& operator>>(istream& in, Cell& obj);
		friend ostream& operator<<(ostream& out, const Cell& obj);

		Cell& operator++();
		Cell operator++(int);

		bool operator==(const Cell& other)const;
		/*	!= operator
		 *	row, column and content will be compared
		 *	returns true if rows, columns and contents are not same, else false
		*/
		inline bool operator!=(const Cell& other)const{//;
			return !(*this == other);}

	private:

		int column;
		int row;
		char content;

};

#endif //CELL_H
