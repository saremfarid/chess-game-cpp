#include<iostream>
#include<cstring>
#include<string>
#include<iomanip>
#include<cctype>// for character clarification and transformation
#include<limits>//finding range boundaries
using namespace std;
enum Color {
	white,black
};
class Piece {
	Color color;
	char symbol;
	int rows, columns;

public:
	Piece(Color c, char s, int r, int col) :color(c), symbol(s), rows(r), columns(col){}
virtual	~Piece() {

	}
	// we gonna make pure virtual function and making the class abstract for polymorphism
virtual bool isvalidmove(int rows,int columns,Piece*board[8][8])const = 0;// now every class mold this class according to its own rule

// setters and getters
void setcolor(Color c) {
	color = c;
}
Color getcolor() const {
	return color;
}
void setsymbol(char s) {
	symbol = s;
}
char getsymbol() const{
	return symbol;
}
void setrowscoulmns(int r,int c) {
	rows = r;
	columns = c;
}
int getrows()const {
	return rows;
}
int getcolumns()const {
	return columns;
}

};
// no starting from the pawn

class Pawn:public Piece {
public:
	Pawn(Color c, int r, int columns) :Piece(c,(c == white ? 'P':'p'), r, columns) {}
	// actually we are giving symbol to pawn if it is white and if it is not
	string getname()const {
		return "Pawn";
	}
	// pawn moves one square and can move only forward and for the first it can move 2 swuare
	bool isvalidmove(int ro, int col, Piece* board[8][8])const override {
		// current position
		int currentR = getrows();
		int currentC = getcolumns();

		int direction = (getcolor() == white ? -1 : 1);// beacause we are designing the chess game where the white moves down and black moves up
		int startRow = (getcolor() == black ? 1 : 6);//white moving down and black moving up

		//row and column difference
		int rowdif = ro - currentR;
		int columndif = col - currentC;

		// for finding is the place empty
		if (columndif == 0) {
			// for single step mover
			if ((rowdif == direction) && (board[ro][col] = nullptr)) {
				return true;
			}
			// for first moving the two square
			if (rowdif == 2 * direction && currentR == startRow) {
				return true;
			}
			// for diagonally movement  and checking if it is on next column
			else if (abs(columndif) == 1 && rowdif == direction) {
				if (board[ro][col] != nullptr && board[ro][col]->getcolor() != getcolor()) {
					return true;
				}
			}
		}
			return false;
		
	}

};
class Rook :public Piece {
public:
	Rook(Color c, int r, int columns) :Piece(c, (c == white ? 'R' : 'r'), r, columns) {}

	string getname()const {
		return "Rook";
	}
	// Rook moves in the same row and in the same column
	bool isvalidmove(int ro, int col, Piece* board[8][8])const override {
		// check for the straight row or column
		if ((ro != getrows()) && (col != getcolumns())) {
			return  false;
		}
		int steprow = (ro == getrows()) ? 0 : (ro > getrows() ? 1 : -1);//1  is moving down and -1 is moving up
		int stepcolumns = (col == getcolumns()) ? 0 : (col > getcolumns()) ? 1 : -1;

		int checkrow = getrows() + steprow;
		int checkcolumn = getcolumns() + stepcolumns;
		 // a loop gonna check whether there is blockage or not
		
		while (checkrow != ro || checkcolumn != col) {


			if (board[checkrow][checkcolumn] != nullptr) {
				return false;// path is blocked
			}
			checkrow = checkrow + steprow;
			checkcolumn += stepcolumns;

		}

		if (board[ro][col] != nullptr && board[ro][col]->getcolor() == getcolor()) {
			return false;
		}
		return true;
	}


};
class knight :public Piece {
public:
	knight(Color c, int r, int columns) :Piece(c, (c == white ? 'K' : 'k'), r, columns) {}

	string getname()const {
		return "KNIGHT";
	}
	bool isvalidmove(int ro, int col, Piece* board[8][8])const override {
		int rowdiff = abs(ro - getrows());
		int columnsdif = abs(col - getcolumns());// for not having in the
		bool Lshape = (rowdiff == 2 && columnsdif == 1) || (rowdiff == 1 && columnsdif == 2);
		if (!Lshape) {
			return false;
		}


		if (board[ro][col] != nullptr && board[ro][col]->getcolor() == getcolor()) {
			return false;
		}
		return true;


	}


};
class Bishop :public Piece {
public:
	Bishop(Color c, int r, int columns) :Piece(c, (c == white ? 'B' : 'b'), r, columns) {}
	string getname()const {
		return "Bishop";

	}

	bool isvalidmove(int ro, int col, Piece* board[8][8])const override {

		int rowdiff = abs(ro - getrows());
		int columnsdif = abs(col - getcolumns());

		if (rowdiff != columnsdif || rowdiff == 0) {
			return false;
		}
		// for diagonally movement
		int steprow =  (ro > getrows() ? 1 : -1);//1  is moving down and -1 is moving up
		int stepcolumns =  (col > getcolumns() ? 1 : -1);
		// we are actually searching for obstacles
		int checkR = getrows() +steprow;
		int checkC = getcolumns() + stepcolumns;

		while (checkR != ro && checkC != col) {
			if (board[checkR][checkC] != nullptr) {
				return false;
				//there is some obstruction
			}
			 checkR = checkR + steprow;
			 checkC += stepcolumns;
		}


		if (board[ro][col] != nullptr && board[ro][col]->getcolor() == getcolor()) {
			return false;
		}
		return true;


	}

};
class Queen :public Piece {
public:
	Queen(Color c, int r, int columns) :Piece(c, (c == white ? 'Q' : 'q'), r, columns) {}
	string getname()const {
		return "Queen";

	}
	// Queen is the only piece which can move to everywhere even in the enemy lines to kill them
	bool isvalidmove(int ro, int col, Piece* board[8][8])const override {

		int rowdiff = abs(ro - getrows());
		int columnsdif = abs(col - getcolumns());

		// first we have to check the rook and the  BIshop move

		bool Rookmove = (getrows() == ro || getcolumns() == col);
		bool bishopmove = (rowdiff == columnsdif && rowdiff != 0);

		if (!Rookmove && !bishopmove) {
			return false;// because the move is invalid and they are moving neither staraight nor diagoanl 
		}
		// obsrtuctionn checking going on
		int steprow = (ro == getrows()) ? 0 : (ro > getrows() ? 1 : -1);//1  is moving down and -1 is moving up
		int stepcolumns = (col == getcolumns()) ? 0 : (col > getcolumns()) ? 1 : -1;

		int checkrow = getrows() + steprow;
		int checkcolumn = getcolumns() + stepcolumns;

		while (checkrow != ro || checkcolumn != col) {
			if (board[checkrow][checkcolumn] != nullptr) {
				
					return false;
					//there is some obstruction
				}
			checkrow += steprow;
			checkcolumn += stepcolumns;
			}
		// knowing that whether it reaches the destination or not

		if (board[ro][col] != nullptr && board[ro][col]->getcolor() == getcolor()) {
			return false;
		}
		return true;

		}

	
};
class King :public Piece {

public:
	King(Color c, int r, int columns) :Piece(c, (c == white ? 'K' : 'k'), r, columns) {}
	string getname()const {
		return "KING";

	}
	// king only can move only a  square if it is empty and if not it is unable to move

	bool isvalidmove(int ro, int col, Piece* board[8][8])const override {
		int rowdiff = abs(ro - getrows());
		int columnsdif = abs(col - getcolumns());

		if ((rowdiff <= 1 && columnsdif <= 1) && !(rowdiff == 0 && columnsdif == 0)) {
			// can move to 
			if (board[ro][col] == nullptr || board[ro][col]->getcolor() != getcolor()) {
				return true;
			}
		}

		return false;
	}

};
class Board {
	Piece* board[8][8];

public:
	Board() {
		// Initialize the grid with null pointers
		for (int i = 0; i < 8; ++i) {
			for (int j = 0; j < 8; ++j) {
				board[i][j] = nullptr;
			}
		}
		setupBoard();
	}

	~Board() {
		for (int i = 0; i < 8; ++i) {
			for (int j = 0; j < 8; ++j) {
				delete board[i][j];
			}
		}
	}

	void setupBoard() {
		// Black Pieces (Top - Row 0 and 1)
		board[0][0] = new Rook(black, 0, 0);
		board[0][1] = new knight(black, 0, 1);
		// Note: You need to make Bishop's constructor public in your code!
		// grid[0][2] = new Bishop(black, 0, 2); 
		board[0][3] = new Queen(black, 0, 3);
		board[0][4] = new King(black, 0, 4);
		// grid[0][5] = new Bishop(black, 0, 5);
		board[0][6] = new knight(black, 0, 6);
		board[0][7] = new Rook(black, 0, 7);
		for (int i = 0; i < 8; ++i) board[1][i] = new Pawn(black, 1, i);

		// White Pieces (Bottom - Row 6 and 7)
		for (int i = 0; i < 8; ++i) board[6][i] = new Pawn(white, 6, i);
		board[7][0] = new Rook(white, 7, 0);
		board[7][1] = new knight(white, 7, 1);
		// grid[7][2] = new Bishop(white, 7, 2);
		board[7][3] = new Queen(white, 7, 3);
		board[7][4] = new King(white, 7, 4);
		// grid[7][5] = new Bishop(white, 7, 5);
		board[7][6] = new knight(white, 7, 6);
		board[7][7] = new Rook(white, 7, 7);
	}

	void display() {
		cout << "   a b c d e f g h" << endl;
		cout << "  -----------------" << endl;
		for (int i = 0; i < 8; ++i) {
			cout << 8 - i << "| "; // Chess notation ranks
			for (int j = 0; j < 8; ++j) {
				if (board[i][j] == nullptr) {
					cout << ". ";
				}
				else {
					cout << board[i][j]->getsymbol() << " ";
				}
			}
			cout << "|" << 8 - i << endl;
		}
		cout << "  -----------------" << endl;
		cout << "   a b c d e f g h" << endl;
	}
	bool movePiece(int startR, int startC, int endR, int endC) {
		Piece* p = board[startR][startC];

		if (p == nullptr) {
			cout << "No piece at that position!" << endl;
			return false;
		}

		if (!p->isvalidmove(endR, endC, board)) {
			cout << "Invalid move!" << endl;
			return false;
		}

		if (wouldLeaveKingInCheck(startR, startC, endR, endC)) {
			cout << "Illegal! This move leaves your king in check!" << endl;
			return false;
		}

		// Move is fully legal — execute it
		if (board[endR][endC] != nullptr) {
			delete board[endR][endC];
		}
		board[endR][endC] = p;
		board[startR][startC] = nullptr;
		p->setrowscoulmns(endR, endC);

		// Warn opponent if they are now in check
		Color opponent = (p->getcolor() == white) ? black : white;
		if (isInCheck(opponent)) {
			cout << "Check!" << endl;
		}

		return true;
	}
	bool isUnderAttack(int r, int c, Color attackerColor) {

		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				Piece* p = board[i][j];  // Fix 1: added 'board'

				if (p != nullptr && p->getcolor() == attackerColor) {
					if (p->isvalidmove(r, c, board)) {
						return true;
					}
				}
			}
		}
		return false;
	}
	bool findKing(Color color, int& kingRow, int& kingCol) {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				Piece* p = board[i][j];
				if (p != nullptr && p->getcolor() == color && p->getsymbol() == (color == white ? 'K' : 'k')) {
					kingRow = i;
					kingCol = j;
					return true;
				}
			}
		}
		return false; // King not found (should never happen in a valid game)
	}
	bool isInCheck(Color color) {
		int kingRow = -1, kingCol = -1;

		//  Find the king's position
		if (!findKing(color, kingRow, kingCol)) {
			return false; // King not found (should never happen)
		}

		//  Check if any opponent piece can attack the king's position
		Color attackerColor = (color == white) ? black : white;
		return isUnderAttack(kingRow, kingCol, attackerColor);
	}
	bool wouldLeaveKingInCheck(int startR, int startC, int endR, int endC) {
		//we are gonna  Save the current state
		Piece* movingPiece = board[startR][startC];
		Piece* targetPiece = board[endR][endC];

		// then  Temporarily make the move
		board[endR][endC] = movingPiece;
		board[startR][startC] = nullptr;
		movingPiece->setrowscoulmns(endR, endC);

		// now Check if own king is in check after the move
		bool inCheck = isInCheck(movingPiece->getcolor());

		//  restore the move (restore original state)
		board[startR][startC] = movingPiece;
		board[endR][endC] = targetPiece;
		movingPiece->setrowscoulmns(startR, startC);

		return inCheck;
	}
	bool hasAnyLegalMove(Color color) {
    for (int startR = 0; startR < 8; startR++) {
        for (int startC = 0; startC < 8; startC++) {
            Piece* p = board[startR][startC];

            // Skip if no piece or wrong color
            if (p == nullptr || p->getcolor() != color) {
                continue;
            }

            // Try every possible destination on the board
            for (int endR = 0; endR < 8; endR++) {
                for (int endC = 0; endC < 8; endC++) {

                    // Skip same position
                    if (startR == endR && startC == endC) {
                        continue;
                    }

                    // Check if move is valid and doesn't leave king in check
                    if (p->isvalidmove(endR, endC, board) &&
                        !wouldLeaveKingInCheck(startR, startC, endR, endC)) {
                        return true; // At least one legal move exists
                    }
                }
            }
        }
    }
    return false; // No legal moves found
}

};

class Game {
private:
	Board board;        // Composition: Game contains a Board
	Color currentTurn;  // Whose turn it is

	/*
	 * printHeader:
	 *  Displays the game title banner.
	 */
	void printHeader() const {
		cout << "========================================\n";
		cout << "          CHESS GAME IN C++             \n";
		cout << "    NUCES Faisalabad-Chiniot Campus     \n";
		cout << "========================================\n";
		cout << "  Symbols:  K=King  Q=Queen  R=Rook\n";
		cout << "            B=Bishop  N=Knight  P=Pawn\n";
		cout << "  UPPER = WHITE    lower = BLACK\n";
		cout << "  Input format: e2 e4  (from to)\n";
		cout << "  Type 'quit' to exit the game.\n";
		cout << "========================================\n";
	}

	/*
	 * colorName:
	 *  Returns "WHITE" or "BLACK" string for display.
	 */
	string colorName(Color c) const {
		return (c == white) ? "WHITE" : "BLACK";
	}


	bool parseInput(const string& s, int& row, int& col) const {
		if (s.length() != 2) return false;

		char colChar = tolower(s[0]);
		char rowChar = s[1];

		if (colChar < 'a' || colChar > 'h') return false;
		if (rowChar < '1' || rowChar > '8') return false;

		col = colChar - 'a';          // 'a'=0 .. 'h'=7
		row = 8 - (rowChar - '0');    // '8'=row0 .. '1'=row7

		return true;
	}

public:
	/* Constructor – WHITE always moves first */
	Game() : currentTurn(white) {}

	
	void run() {
		printHeader();

		while (true) {
			board.display();

			// --- Check / Checkmate / Stalemate detection ---
			Color opponent = (currentTurn == white) ? black : white;

			// Stalemate: opponent has no legal moves but is NOT in check
			if (!board.hasAnyLegalMove(currentTurn)) {
				if (board.isInCheck(currentTurn)) {
					cout << "  *** CHECKMATE! "
						<< colorName(opponent) << " WINS! ***\n";
				}
				else {
					cout << "  *** STALEMATE! The game is a DRAW. ***\n";
				}
				break;
			}

			// Warn if current player is in check
			if (board.isInCheck(currentTurn)) {
				cout << "  *** " << colorName(currentTurn)
					<< " is in CHECK! ***\n";
			}

			// --- Prompt for move ---
			cout << "  " << colorName(currentTurn)
				<< "'s turn. Enter move (e.g., e2 e4): ";

			string from, to;
			cin >> from;

			if (from == "quit") {
				cout << "  Game ended. Goodbye!\n";
				break;
			}

			cin >> to;
			if (to == "quit") {
				cout << "  Game ended. Goodbye!\n";
				break;
			}

			int fromR, fromC, toR, toC;

			if (!parseInput(from, fromR, fromC)
				|| !parseInput(to, toR, toC)) {
				cout << "  [!] Invalid input format."
					" Use notation like: e2 e4\n";
				continue;
			}

			// --- Attempt the move ---
			if (board.movePiece(fromR, fromC, toR, toC)) {
				// Switch turn on success
				currentTurn = (currentTurn == white) ?black : white;
			}
		}
	}
};
int main() {
	Game game;
	game.run();
	return 0;
}
