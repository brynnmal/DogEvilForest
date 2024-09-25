
#include "Board.hpp"
#include "Dog.hpp"
#include <iostream>
#include <time.h>
#include <cstdlib>
using namespace std;


Board::Board(char diff, bool d){
	level = diff;
	debug = d;
	wallStrength = 6;
	InitAll();
}
Board::Board(bool d){
	level = 'e';
	debug = d;
	wallStrength = 6;
	InitAll();
}
Board::Board(char diff, string name, bool d) {
	level = diff;
	debug = d;
	mydog.name = name;
	wallStrength = 6;
	InitAll();
}
void Board::InitAll() {
	bool keepPlaying = true;

	while (keepPlaying) {
		cout << "What level of difficulty do you want (e, m, or h)?" << endl;
		char c;
		cin >> c;
		level = c;
		startx = rand() % size;
		starty = 0;
		endx = rand() % size;
		endy = size-1;

		mydog.x = starty;
		mydog.y = startx;
		boardConfig();
		addFood();
		addTraps();
		printBoard();
		playGame();

		cout << "Play again? " << endl;
		string s = "no";
		cin>>s;
		if (s == "yes" || s == "Yes" || s == "Y" || s == "y") {
			keepPlaying = true;
			mydog.reset();
		}
		else {
			cout <<"Thanks for playing!" << endl;
			keepPlaying = false;
		}
	}

}


void Board::printBoard() {
	for(int i = 0; i < size; i++) {
		cout << " -";
	}
	cout << endl;
	for (int i = 0; i < size; i++) {
		cout << "|";
		for(int j = 0; j < size; j++) {
			cout << board[i][j] << " ";
		}
		cout << "|";
		cout << endl;
	}
	for(int i = 0; i < size; i++) {
		cout << " -";
	}
	cout << endl;
	mydog.printDog();
}

void Board::boardConfig() {
	for(int i = 0; i < size; i++) {
		for(int j = 0; j < size; j++) {
			board[i][j] = ' ';
		}
	}
	int rows = rand() % 10;
	int columns = 10 - rows;
	for(int i = 0; i < columns; i++) {
		int wall = ((rand() % 9) * 2) + 1;
		int amount;
		if(level == 'e') {
			amount = 9;
		}else if(level == 'm') {
			amount = 13;
		}else if(level == 'h') {
			amount = 16;
		}
		for(int j = 0; j < amount; j++) {
			int y = rand() % 20;
			while(board[wall][y] != ' ') {
				y = rand() % 20;
			}
			board[y][wall] = '|';
		}
	}
	for(int i = 0; i < rows; i++) {
		int wall = ((rand() % 9) * 2) + 1;
		int amount;
		if(level == 'e') {
			amount = 9;
		}else if(level == 'm') {
			amount = 13;
		}else if(level == 'h') {
			amount = 16;
		}
		for(int j = 0; j < amount; j++) {
			int x = rand() % 20;
			// while(board[wall][x] != ' ') {
			// 	x = rand() % 20;
			// }
			board[wall][x] = '-';
		}
	}

	board[mydog.y][mydog.x] = 'D';
	board[endx][endy] = 'E';
	//(8 pts)
	//Instructions for writing boardConfig:
	/* this method and the moveDog method are probably the longest methods.
	 * This method first puts dummy values in every square (I used '+' - I just didn't want
	 * every square to have gibberish, so I chose a character I wasn't using for any other
	 * purpose and initialized every square to have that value).
	 * I then added my random horizontal and vertical walls.
	 *
	 * Here's how I did it the walls:
	 *
	 * I only placed walls in the odd numbered rows and columns (in other words, row one might
	 * have a row, but then row 2 would not, whereas row three could and row 4 could not.
	 * Same with columns (although you can have flexibility.
	 *
	 * I picked an odd row or column that did not already have a wall in it at all.
	 *
	 * I generated a total of 10 walls.

	 * For each wall, I picked randomly for vertical or horizontal (just rand() % 2 to get either
	 * 0 for vertical, 1 for horizontal.
	 *
	 * I set the easy version to have at most 9 squares in a row or column as a wall, the
	 * medium to have at most 13 squares as walls in a row or column, and the hard version to
	 * have at most 16 squares per row or column.(but you can play with this because sometimes
	 * the hard version was seriously hard!!!
	 *
	 * Let's say I randomly decided to place a wall in row 3.  I then randomly chose 9 squares in
	 * row 3 to be a wall (if it was the easy version, 13 if it was the medium, and 16 if it was
	 * the hard)
	 *
	 * So that's the walls.  Then I added the 'D' to the beginning square nad an 'E' to the end square.
	 *
	 *
	 */

}


void Board::addFood() {
	int foodcount;
	if(level == 'e') {
		foodcount = size;
	}else if(level == 'm') {
		foodcount = size - 2;
	}else if(level == 'h') {
		foodcount = size - 4;
	}
	while(foodcount > 0) {
		int column = rand() % 20;
		int row = rand() % 20;
		if(board[column][row] == ' ') {
			foodcount -= 1;
			board[column][row] = 'F';
		}
	}
}

void Board::addTraps() {
	int trapcount;
	if(level == 'e') {
		trapcount = size - 6;
	}else if(level == 'm') {
		trapcount = size - 8;
	}else if(level == 'h') {
		trapcount = size - 10;
	}
	while(trapcount > 0) {
		int column = rand() % 20;
		int row = rand() % 20;
		if(board[column][row] == ' ') {
			trapcount -= 1;
			board[column][row] = 'T';
		}
	}
}


bool Board::moveDog(char c) {
	int newx = 0;
	int newy = 0;
	bool alive = true;
	if(c == 'u') {
		newy = -1;
	}else if(c == 'd') {
		newy = 1;
	}else if(c == 'l') {
		newx = -1;
	}else if(c == 'r') {
		newx = 1;
	}
	if(mydog.y + newy > 20 || mydog.y + newy < 0 || mydog.x + newx > 20 || mydog.x + newx < 0) {
		return true;
	}
	if(board[mydog.y + newy][mydog.x + newx] == '|' || board[mydog.y + newy][mydog.x + newx] == '-') {
		if(mydog.strength > 6) {
			string input;
			cout << "Do you want to knock down that wall?";
			cin >> input;
			if(input == "No" || input == "NO" || input == "no") {
				return mydog.changeStrength(-1);
			}
			alive = mydog.changeStrength(-6);
		}
	}
	board[mydog.y][mydog.x] = ' ';
	mydog.x += newx;
	mydog.y += newy;
	if(board[mydog.y][mydog.x] == 'E') {
		mydog.won();
		board[mydog.y][mydog.x] = 'D';
		return false;
	}
	if(board[mydog.y][mydog.x] == 'F') {
		int food = rand() % 17;
		alive = mydog.changeStrength(food);
		cout << mydog.name + " eats food! Gains " + to_string(food) + " strength!" << endl;
	}
	if(board[mydog.y][mydog.x] == 'T') {
		int trap = (rand() % 17) * -1;
		alive = mydog.changeStrength(trap);
		cout << "Its a trap! " + mydog.name + " loses " + to_string(trap) + " strength." << endl;
	}
	if(board[mydog.y][mydog.x] == ' ') {
		alive = mydog.changeStrength(-2);
	}
	board[mydog.y][mydog.x] = 'D';
	return alive;
	// (12 pts)
	//Instructions for moveDog
	/* This is a somewhat long method.
		 * First, it determines the new coordinats of the dog, based on teh direction in which the
		 * dog wants to move (based on what c holds - u is up, d is down, l is left, r is right).
		 *
		 * If the dog is at teh edge of the board, teh dog should not move
		 *
		 * If the dog moves over food, a random number between 2 and 17 is generated, and the
		 * dog's changeStrength method is used to increase the dog's strength by the random amount.
		 *
		 * If the dog moves over the end of the board, the dog's won method is called and false is
		 * returned from this method.
		 *
		 * If the dog moves over a Trap, a random number between 2 and 17 is generated and the dog's
		 * changeStrength method is called with that negative number.  (Note that the changeStrength
		 * method returns a boolean indicating whether the dog's strength has gone to 0 or less, and
		 * thus the dog has died and the game is over. That boolean value is returned from this method).
		 *
		 * If the dog moves over a wall, the method checks to see if the dog has enough strength to
		 * knock down the wall (I made it cost 6 strength points to knock down a wall).  If the dog
		 * has enough strength, the user is asked, "Do you want to knock down that wall?"  If the user
		 * responds "yes", then the wall is knocked down, the dog moves into that square, adn the dog's
		 * strength decreases by 6.  If the answer is "no", the dog loses 1 strength point, just because.
		 *
		 * If the dog moves into a blank square, the dog loses 2 strength points using the changeStrength
		 * method (which, again, will return false if the dog has lost all their strength and died.
		 *
		 * NOTE: I am not concerned with the precise rules here.  If you want to change the range of
		 * random numbers for food, if you are worried about whether you still lose 2 strength points for
		 * moving even though you gained points for moving over food - I'm leaving all that to your preference.
		 * I am concerned that you are using classes, objects, and object methods and accessing object
		 * fields correctly!
		 *
		 */

}


void Board::playGame() {
	bool play = true;
	while (play) {
		cout << "Move (u, d, l, r) "<<endl;
		char c;
		cin >> c;
		play = moveDog(c);
		printBoard();
	}


}


