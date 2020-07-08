#ifndef CONNECTFOURDIAGONAL_H
#define CONNECTFOURDIAGONAL_H

#include "ConnectFourAbstract.h"

class ConnectFourDiagonal : public ConnectFourAbstract{

/*	HELPER FUNCTIONS
	check vertical, horizontal, right cross and left cross letters
	2-3-4 letters check for computer to block user or win game 
*/
	int rightCross(char target);
	int leftCross(char target);

	void game( char player );
	bool controlBoard(char target);
	int findPosition(char rival);

	public:

	bool play();
	bool play(char cellPosition);

	ConnectFourDiagonal(int c, int r);
	ConnectFourDiagonal();
	ConnectFourDiagonal(string filename);

	void workingCond();

	ConnectFourDiagonal& operator=(const ConnectFourDiagonal& other);
	ConnectFourDiagonal(const ConnectFourDiagonal& other);
	//~ConnectFourDiagonal();

};


#endif	//CONNECTFOURDIAGONAL_H
