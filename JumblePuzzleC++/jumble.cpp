/*
 * jumble.cpp
 * This is my program to create a jumble puzzle. It creates the puzzle on the heap and implements
 * necessary function such as a destructor and a copy constructor as well as the assignment over-loader
 * so you don't get into problems when trying to make a copy of yourself and don't alias yourself
 * you assign to yourself.
 *
 * Note for Madiha: I created this program on a Mac as I was having problems with the caslab computers
 * trying to run my program on the eclipse installed in the labs. Please let me know if there are any
 * problems with the program because when I run this on my computer I do not get any problems.
 *
 *
 *  Created on: Nov 17, 2015
 *      Author: Katherine
 */


#include <cstdlib>
#include <iostream>
#include <string>
#include "jumble.h"

using namespace std;

/*constructor for JumblePuzzle class. Takes two parameters, the word to hide and
 * and the difficulty of the puzzle based on the length of the word and the difficulty
 * parameter.
 * Checks to see if the input parameters are acceptable and throws and exception if there aren't.
 * Generates a puzzle by calling makePuzzle()
 */
JumblePuzzle::JumblePuzzle(const string toHideParam1, const string difficultyParam2){
	int lengthWord = toHideParam1.length();
	if (lengthWord < 3 || lengthWord >10){
		throw BadJumbleException("Length of word is illegal.");

	}
	toHide = toHideParam1;
	if (difficultyParam2[0] == 'e' || difficultyParam2[0] == 'E'){

		difficulty = 2;
	}
	else if (difficultyParam2[0] == 'm' || difficultyParam2[0] == 'M'){
		cout << "I got here" << endl;
		difficulty = 3;
	}
	else if (difficultyParam2[0] == 'h' || difficultyParam2[0] == 'H'){
		difficulty = 4;
	}
	else{
		throw BadJumbleException("Not a recognized difficulty level");
	}

	size = lengthWord * difficulty;
	jumble = new charArrayPtr[size];
	for (int i = 0; i<size; i++){
		jumble[i] = new char[size];
	}
	int seed = static_cast<int>(time(NULL));
	srand(seed);

	makePuzzle();

}


/* Function fills the puzzle with random letters then generates a random row position
 * and col position to store the first letter. Then it tries to place the word in a random direction and
 * if it can't then it generates a new direction until it successfully places the whole word.
 */
void JumblePuzzle::makePuzzle(){
	bool flag = false;
	string directions = "nesw";
	//fill the jumble with random letters
	string letters = "abcdefghijklmnopqrstuvwxyz";
	for (int r = 0; r<size; r++){
		for (int c = 0; c<size; c++){
			jumble[r][c] = letters[rand() % 26];
		}
	}
	//generate a row and col pos to start the hidden word
	int colPosition = rand() % size;
	int rowPosition = rand() % size;

	colPos = colPosition;
	rowPos = rowPosition;
	jumble[rowPos][colPos] = toHide[0];

	//keep trying to fit the word while you haven't hid all of the words
	//characters.
	int stringIndex = 1;
	while (flag == false && stringIndex < toHide.length()){
		stringIndex = 1;
		direction = directions[rand() % 4];
		colPos = colPosition;
		rowPos = rowPosition;

		if (direction == 'n'){
			rowPos = rowPos -1;

			while (rowPos >= 0 && stringIndex < toHide.length()){

				jumble[rowPos][colPos] = toHide[stringIndex];
				rowPos = rowPos -1;
				stringIndex = stringIndex +1;
			}
		}
		else if (direction == 'e'){
			colPos = colPos + 1;
			while(colPos < size && stringIndex < toHide.length()){

				jumble[rowPos][colPos] = toHide[stringIndex];
				colPos = colPos + 1;
				stringIndex = stringIndex + 1;
			}
		}
		else if (direction == 'w'){
			colPos = colPos - 1;
			while (colPos >= 0 && stringIndex < toHide.length()){

				jumble[rowPos][colPos] = toHide[stringIndex];
				colPos = colPos - 1;
				stringIndex = stringIndex + 1;
			}
		}
		else if (direction == 's'){
			rowPos = rowPos + 1;
			while (rowPos < size && stringIndex < toHide.length()){

			jumble[rowPos][colPos] = toHide[stringIndex];
			rowPos = rowPos +1;
			stringIndex = stringIndex + 1;
			}

		}

	}
	colPos = colPosition;
	rowPos = rowPosition;

}

//Accessor method for the attribute jumble. It returns a copy of the current jumble
//prevent aliasing.
charArrayPtr* JumblePuzzle::getJumble() const{

	//initialize empty 2d array.
	charArrayPtr* newjumble =  new charArrayPtr[size];
	for (int i = 0; i<size; i++){
		newjumble[i] = new char[size];
	}
	for (int t = 0; t<size; t++){
		for (int j = 0; j<size; j++){
			newjumble[t][j] = jumble[t][j];
		}
	}
	return newjumble;

}

//Assignment operator overloading. This deletes the current attribute jumble in memory
//and creates a new jumble with values from object rhs. It assigns the current object's jumble
//attribute to the new jumble created.
JumblePuzzle& JumblePuzzle::operator=(const JumblePuzzle& rhs){
	if (this != &rhs){
		for (int i = 0; i<size; i++){
			delete[] jumble[i];
		}
		delete[] jumble;
		jumble = NULL;
		charArrayPtr* newjumble = new charArrayPtr[rhs.getSize()];
		charArrayPtr* oldJumble = rhs.getJumble();
		for (int j = 0; j<rhs.getSize(); j++){
			newjumble[j] = new char[rhs.getSize()];
		}

		for (int t = 0; t<rhs.getSize(); t++){
			for (int k = 0; k< rhs.getSize(); k++){
				newjumble[t][k] = oldJumble[t][k];
			}
		}
		size = rhs.getSize();
		jumble = newjumble;
	}

	return *this;

}

//destructor
/*
 * Deletes the current attribute jumble in memory, it is the only attribute stored on the heap.
 */
JumblePuzzle::~JumblePuzzle(){
	for (int i = 0; i<size; i++){
		delete[] jumble[i];
	}
	delete[] jumble;
	jumble = NULL;
}

//Accessor for the size of the jumble puzzle.
int JumblePuzzle::getSize() const{
	return size;
}

//copy constructor
/*
 * Creates a new jumble with values from the jumble from inputPuzzle. It assigns this to
 * the current jumble in memory.
 */
JumblePuzzle::JumblePuzzle(const JumblePuzzle& inputPuzzle){

	size = inputPuzzle.getSize();
	charArrayPtr* oldJumble = inputPuzzle.getJumble();
	charArrayPtr* newjumble = new charArrayPtr[inputPuzzle.getSize()];
	for (int i = 0; i< inputPuzzle.getSize(); i++){
		newjumble[i] = new char[inputPuzzle.getSize()];
	}

	//need to fill puzzle
	for (int t = 0; t < inputPuzzle.getSize(); t++){
		for (int k = 0; k < inputPuzzle.getSize(); k++){
			newjumble[t][k] = oldJumble[t][k];
		}
	}
	jumble = newjumble;
}

//Accessor for col position of hidden word.
int JumblePuzzle::getColPos() const{
	return colPos;
}

//Accessor for direction of hidden word.
char JumblePuzzle::getDirection() const{
	return direction;
}

//Accessor for row position of hidden word.
int JumblePuzzle::getRowPos() const{
	return rowPos;
}

//Accessor for difficulty of puzzle.
int JumblePuzzle::getDifficulty() const{
	return difficulty;
}

//Exception class constructor.
BadJumbleException::BadJumbleException(const string& m) : message(m) {}

string BadJumbleException::what() const{
	return message;
}



