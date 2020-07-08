#ifndef CONNECTFOURPLUS_H
#define CONNECTFOURPLUS_H

#include "ConnectFourAbstract.h"

class ConnectFourPlus : public ConnectFourAbstract{

/*	HELPER FUNCTIONS
	check vertical, horizontal, right cross and left cross letters
	2-3-4 letters check for computer to block user or win game 
*/
	protected:
		int controlHorizontal(char target); //yatay
		int controlVertical(char target); //yatay

		void game( char player );
		bool controlBoard(char target);
		int findPosition(char rival);

	public:

		ConnectFourPlus(int c, int r);
		ConnectFourPlus();
		ConnectFourPlus(string filename);

		void workingCond();

		bool play();
		bool play(char cellPosition);

		ConnectFourPlus& operator=(const ConnectFourPlus& other);
		ConnectFourPlus(const ConnectFourPlus& other);
		//~ConnectFourPlus();

};

#endif //CONNECTFOURPLUS_H
