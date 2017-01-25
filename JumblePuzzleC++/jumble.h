/*
 * jumble.h

 * Declarative file for jumble.cpp
 *  Created on: Nov 17, 2015
 *      Author: Katherine
 */
#include <string>
using namespace std;

typedef char* charArrayPtr;
class JumblePuzzle{
private:
	string toHide;			//hidden word
	int difficulty;			//difficulty of puzzle. This is an integer defined by either easy,hard, or medium
	int colPos;				//col position of hidden word.
	int rowPos;				//row position of hidden word.
	int size;				//overall size of the puzzle.
	charArrayPtr* jumble;	//this is how we store the puzzle. It is basically an array of arrays.
	void makePuzzle();		//method of making the puzzle.
	char direction;			//direction of hidden word either n,s,e, or w

public:
	~JumblePuzzle(); 							//destructor
	JumblePuzzle(const JumblePuzzle&); 			//copy constructor
	JumblePuzzle(const string, const string);	//constructor for JumblePuzzle class, two input parameters
	charArrayPtr* getJumble() const; 			//accessor for jumble attribute
	JumblePuzzle& operator=(const JumblePuzzle&); //assignment overloading for JumblePuzzle class
	int getSize() const;						//accessor for size of puzzle
	int getRowPos() const;						//accessor for row position of hidden word
	int getColPos() const;						//accessor for column position of hidden word
	char getDirection() const;					//accessor for direction of hidden word
	int getDifficulty() const;					//accessor for difficulty of puzzle.
};

class BadJumbleException{
private:
	string message;						//informative message to be displayed to users when exception is thrown.

public:
	BadJumbleException(const string&);	//constructor for exception class
	string what() const;				//method used to get exception message.

};


