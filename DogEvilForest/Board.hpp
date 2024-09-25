/*
 * Board.hpp
 *
 *  Created on: Feb 25, 2021
 *      Author: 13027
 */

#ifndef BOARD_HPP_
#define BOARD_HPP_

#include <iostream>
#include <string.h>
#include "Dog.hpp"
using namespace std;

class Board {
	int size = 20;  //the square board's size
	char board[20][20]= {{'0','1','2','3','4','5','6','7','8','9','0','1','2','3','4','5','6','7','8','9'},
			{'1','2','3','4','5','6','7','8','9','0','1','2','3','4','5','6','7','8','9','0'},
			{'2','3','4','5','6','7','8','9','0','1','2','3','4','5','6','7','8','9','0','1'},
			{'3','4','5','6','7','8','9','0','1','2','3','4','5','6','7','8','9','0','1','2'},
			{'4','5','6','7','8','9','0','1','2','3','4','5','6','7','8','9','0','1','2','3'},
			{'5','6','7','8','9','0','1','2','3','4','5','6','7','8','9','0','1','2','3','4'},
			{'6','7','8','9','0','1','2','3','4','5','6','7','8','9','0','1','2','3','4','5'},
			{'7','8','9','0','1','2','3','4','5','6','7','8','9','0','1','2','3','4','5','6'},
			{'8','9','0','1','2','3','4','5','6','7','8','9','0','1','2','3','4','5','6','7'},
			{'9','0','1','2','3','4','5','6','7','8','9','0','1','2','3','4','5','6','7','8'},
			{'0','1','2','3','4','5','6','7','8','9','0','1','2','3','4','5','6','7','8','9'},
			{'1','2','3','4','5','6','7','8','9','0','1','2','3','4','5','6','7','8','9','0'},
			{'2','3','4','5','6','7','8','9','0','1','2','3','4','5','6','7','8','9','0','1'},
			{'3','4','5','6','7','8','9','0','1','2','3','4','5','6','7','8','9','0','1','2'},
			{'4','5','6','7','8','9','0','1','2','3','4','5','6','7','8','9','0','1','2','3'},
			{'5','6','7','8','9','0','1','2','3','4','5','6','7','8','9','0','1','2','3','4'},
			{'6','7','8','9','0','1','2','3','4','5','6','7','8','9','0','1','2','3','4','5'},
			{'7','8','9','0','1','2','3','4','5','6','7','8','9','0','1','2','3','4','5','6'},
			{'8','9','0','1','2','3','4','5','6','7','8','9','0','1','2','3','4','5','6','7'},
			{'9','0','1','2','3','4','5','6','7','8','9','0','1','2','3','4','5','6','7','8'}};
	//Note:  I gave the board initial values so you can test your printBoard method.  Normally you
	// wouldn�t need to do this.

	int wallStrength;  //the amount of strenght needed to take down part of the wall (6)
	int startx;  //Where the dog enters the board (randomly along the left side)
	int starty;  //again, the dog's y entrance to the board (0)
	int endx;  // THe goal location on the right side (random x value)
	int endy;  // will be size -1
	char level; //'e' for easy, 'm' for medium, 'h' for hard (user can input in the initAll() method)
	Dog mydog;  //the dog object that's moving through
	//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	//comment the above line in when you write your dog class!!!
	bool debug;
	//this is a boolean value that I used for debugging - so if it was true, and
	//I was in debug mode, I'd include a lot more print statements in each method
	//so I could see where I was and what was happening.  Then I could just switch
	//this to false and all the print statements would become invisible, but if I
	//moved on, I could always switch the debug print statemetns back on to see
	//what was happening in m code.
public:
	Board(char diff, string name, bool d);
	/* constructor - has as a parameter the level of difficulty, the name I'll give
	 * to my dog object, and whether debug mode is on or off
	 * This method calls the initAll method.
	 */
	Board(char diff, bool d);
	/* constructor - sets level of difficulty and the debug mode.  With this the
	 * dog constructor that doesn't require a name is called, so the default dog's
	 * name is fluffy (which is set in the dog's constructor)
	 * This method calls the initAll method.
	 */
	Board(bool d);
	/* for this constructor the level is set to be 'e' (which is the default), it calls
	 * the default dog constructor, and it calls the initAll method.
	 */
	void InitAll();
	/* (I'm giving you this one. )
	 * It loops for each playing of the game, continuing
	 * as long as the user enters "yes", "Yes","y", or "Y".  It asks the user and
	 * sets the level of difficulty.  It finds the start and end square that the
	 * dog must traverse, it calls boardConfig to configure the board, it calls
	 * printBoard to see the board, it calls addFood and addTraps. And then it calls
	 * the playGame method to start the game.  It loops to continuously reset everything
	 * and play another round of hte game for every time the user says they want to
	 * continue playing another round.
	 */
	void boardConfig();
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
	void printBoard();
	/* this method first uses the dog's printDog method to print out info about the dog, and then
	 * it prints out the board as follows:
	 *
	 * This method prints out hte board such that it looks like a board.  It prints a blank space
	 * for the dummy values (for squares that do not have food, traps, walls, the dog, and aren't the
	 * beginning or the ending.  Otherwise it prints out the character in the square.
	 * Note that I printed a border around the entire board so it was easier to look at, and, equally,
	 * I placed an -> arro (thats a minus and a greater than sign) in the border for where the
	 * beginning of the game was and where the end of the game was. E.g., this is what my starting
	 * printBoard printed: (Note this is after I called addFood and addTraps)
	 */
	//	 _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	//	|     F |                   | T           |
	//	->D  _ _  _   _   _ _     _ _ _ _     _ _ |
	//	|                               |         |
	//	|     F               T     |   |         |
	//	|   T   |                   | F |         |
	//	| _     | _ _ _ _ _ _ _   _ | _ _ _   _   |
	//	|       |     F             |             |
	//	| _ _   | _ _ _ _     F _ _ _ _ _ F   _ _ |
	//	|       |                       |         |
	//	| _ _ _ | _   _ _ _   _   _ _ _ _     _   |
	//	|       T       T               |         |
	//	| T _   |       _ _ _ _ _ _ _ F _ _ _ _ _ |
	//	|   F         F   F         |   |         |
	//	|     T |                   |   |       T |
	//	|             F             |   |         |
	//	|       | T           T     |   |       F |
	//	|                       F   |   |     F E ->
	//	|   _ _ | _ _ _ _ _ _ _   _ | _ |     _ _ |
	//	|       |           T   F   |   |   F     |
	//	|       |     F         F   |   |   T     |
	//	 _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _

	/* Note: Debug Mode:
	 *  The board class has a debug field.  For every example I showed you, I had the
	 * debug field set to true.
	 *
	 * When the debug field is set to true, the Traps are printed out.  This makes the game easier
	 * to test (and a lot easier to play).  However, if the debug mode is set to false, the Traps
	 * are not printed out unless the Dog steps on a trap, at which point they randomly lose points.
	 * So when not in debut mode, the printBoard prints "  " for every 'T' character on the board.
	 * When the game is in debug mode, though, the printBoard prints out the 'T'.
	 */

	void addFood();
	// /* this method randomly adds food around the board.  For easy, I added the field size
	//  * number of foods randomly around the board.  For medium, I added size-2 foods, and for
	//  * hard I added size-4 foods.  The amount of strength the dog gets when they eat (aka
	//  * move onto) the food is determined in the moveDog method.
	//  */
	void addTraps();
	// /* this method randomly adds traps around the board.  For easy I added size - 6 traps,
	//  * for medium, I added size - 8 traps, and for hard I added size - 10 traps.  Note: Traps are
	//  * only printed on the board when the game is in debug mode.  The amount of strength each trap
	//  * saps from the dog is determined in the moveDog method when the dog moves on a Trap.
	//  */
	 void playGame();
	// /* (I'm giving you this one)
	//  * this method loops for every move the dog makes.  It asks whether the user wants to move up,
	//  * down, left, or right.  It then calls the moveDog method with the character indicating which
	//  * way the dog should move, and then it calls the printBoard method.
	//  */
	bool moveDog(char c);
	// /* This is a somewhat long method.
	//  * First, it determines the new coordinats of the dog, based on teh direction in which the
	//  * dog wants to move (based on what c holds - u is up, d is down, l is left, r is right).
	//  *
	//  * If the dog is at teh edge of the board, teh dog should not move
	//  *
	//  * If the dog moves over food, a random number between 2 and 17 is generated, and the
	//  * dog's changeStrength method is used to increase the dog's strength by the random amount.
	//  *
	//  * If the dog moves over the end of the board, the dog's won method is called and false is
	//  * returned from this method.
	//  *
	//  * If the dog moves over a Trap, a random number between 2 and 17 is generated and the dog's
	//  * changeStrength method is called with that negative number.  (Note that the changeStrength
	//  * method returns a boolean indicating whether the dog's strength has gone to 0 or less, and
	//  * thus the dog has died and the game is over. That boolean value is returned from this method).
	//  *
	//  * If the dog moves over a wall, the method checks to see if the dog has enough strength to
	//  * knock down the wall (I made it cost 6 strength points to knock down a wall).  If the dog
	//  * has enough strength, the user is asked, "Do you want to knock down that wall?"  If the user
	//  * responds "yes", then the wall is knocked down, the dog moves into that square, adn the dog's
	//  * strength decreases by 6.  If the answer is "no", the dog loses 1 strength point, just because.
	//  *
	//  * If the dog moves into a blank square, the dog loses 2 strength points using the changeStrength
	//  * method (which, again, will return false if the dog has lost all their strength and died.
	//  *
	//  * NOTE: I am not concerned with the precise rules here.  If you want to change the range of
	//  * random numbers for food, if you are worried about whether you still lose 2 strength points for
	//  * moving even though you gained points for moving over food - I'm leaving that to your preference.
	//  * I am concerned that you are using classes, objects, and object methods and accessing object
	//  * fields correctly!
	//  *
	//  */

};



#endif /* BOARD_HPP_ */
