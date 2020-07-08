#ifndef CONNECTFOURPLUSUNDO_H
#define CONNECTFOURPLUSUNDO_H

#include "ConnectFourPlus.h"

class ConnectFourPlusUndo : public ConnectFourPlus{

	public:

		ConnectFourPlusUndo(int c, int r);
		ConnectFourPlusUndo();
		ConnectFourPlusUndo(string filename);

		ConnectFourPlusUndo& operator=(const ConnectFourPlusUndo& other);
		ConnectFourPlusUndo(const ConnectFourPlusUndo& other);


		void workingCond();

	protected:

		int* entered;
		int enteredSize;
		
		bool undo();

		bool play();
		bool play(char cellPosition);

		void setLetter(char userLetter, int column);
		int enterPosition(  char userLetter );

};

#endif // CONNECTFOURPLUSUNDO_H
