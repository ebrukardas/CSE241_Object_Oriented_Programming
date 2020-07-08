#ifndef CONNECTFOURABSTRACT_H
#define CONNECTFOURABSTRACT_H

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include "Cell.h"
using namespace std;

class ConnectFourAbstract{

	public:
/*****************************************************************************/
/************************** 	CONSTRUCTORS	******************************/
/*****************************************************************************/

		ConnectFourAbstract(int c, int r);

		ConnectFourAbstract(int squareBoard):
				ConnectFourAbstract(squareBoard,squareBoard){}

		ConnectFourAbstract():
				ConnectFourAbstract(5,5){}

		ConnectFourAbstract(string filename);

/*****************************		BIG TREE	******************************/

		ConnectFourAbstract& operator=(const ConnectFourAbstract& other);
		ConnectFourAbstract(const ConnectFourAbstract& other);
		~ConnectFourAbstract();


/****************************	NEED FUNCTIONS		**************************/

		void printBoard()const;												/**/
		void playGame();													/**/
		bool isEnd()const;													/**/
//		<int, int> currentWidthAndHeight();
		bool writeFile( string filename, char players );								/**/
		int readFile( string filename );												/**/

// playTurn adini play ile degistir
		// computer turn
		virtual bool play()=0;													/**/
		// user turn
		virtual bool play(char cellPosition)=0;									/**/


/******************************************************************************
 ******************************************************************************
 ******************************************************************************/

		virtual void workingCond()=0;




	protected:

/*****************************************************************************/
/********************** 	SETTERS & GETTERS	******************************/
/*****************************************************************************/

		void setWidth(int val);			// column
		void setHeight( int val);		// row
		void setFullnessBoard(int index,  int val);

		inline int getWidth() const{return column;}
		inline int getHeight() const{return row;}
		inline char getPlayer()const{return player;}

		int getFullnessBoard(int index) const;
		int getWinnerPos(const int ind1, const int ind2)const;

		//	Taking position and checks
		virtual int enterPosition(  char userLetter );
		virtual void setLetter(char userLetter, int column);

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

		/* finding position for computer to block user or win game */
		virtual int findPosition(char rival)=0; // rakip
		/* Whether found 4 or not */
		virtual bool controlBoard(char target)=0;
		virtual void game( char player )=0;

		void resize(int c, int r);

/*****************************************************************************/
/**********************		MEMBER VARIABLES	******************************/
/*****************************************************************************/

		int row;											//yükseklik row
		int column;											//genişlik column
		int* fullnessOfBoard;
		Cell **gameCells;

		int fileOrCr;
		int winner[4][2] = { {-1,-1},{-1,-1},{-1,-1},{-1,-1} };
		char firstUser='X', secondUser='O';
		char turn='U';
		char player='P';




};


#endif //CONNECTFOURABSTRACT_H
