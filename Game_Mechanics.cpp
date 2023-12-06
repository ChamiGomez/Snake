//Program: Snake
//This file contains the input and game mechanics functions of the C_Snake class

#include "C_Snake.h"
#include <iostream>
#include <conio.h> //used for _getch()
#include <locale> //used for toupper() 
#include <time.h> //used for time() to provide a seed for random number generation
#include <cstdlib> //used for srand() and rand() for random number generation

//Retrieve move from user
char Retrieve_Move(void) {
	char move = 'x'; //Dummy initialisation
	do {
		cout << "Please enter your next move (W/A/S/D): ";
		move = _getch(); //Retrieve move
		if (toupper(move) != 'W' && toupper(move) != 'A' && toupper(move) != 'S' && toupper(move) != 'D') cout << "Invalid key entered!\n";
	} while (toupper(move) != 'W' && toupper(move) != 'A' && toupper(move) != 'S' && toupper(move) != 'D'); //Repeat until input is valid
	cout << endl << endl;
	return toupper(move); //Return valid move char
}

//Create new coordiantes for the apple the snake eats
void C_Snake::New_Apple_Coords(void) {
	//Generate list of empty-space coords available
	vector<vector<int>> empty_spaces;
	empty_spaces.resize(((box_height - 2) * (box_width - 2)) - snake_coords.size()); //Resize to contain space for everywhere inside playing field except where snake is
	int snake_occupied_spaces = 0;
	for (int y = 1; y < box_height - 1; y++) {
		for (int x = 1; x < box_width - 1; x++) {
			bool empty_cell = true;
			if (snake_occupied_spaces != snake_coords.size()) { //If there are still some potential snake coordinates not yet covered
				for (int i = 0; i < snake_coords.size(); i++) {
					if ((x == snake_coords[i][0]) && (y == snake_coords[i][1])) { //Check if this is a square containing the snake
						empty_cell = false;
						snake_occupied_spaces++;
						break;
					}
				}
			}
			if (empty_cell) { //If this is an empty cell (snake squares have been check or have already been passed)
				empty_spaces[(x - 1) + ((y - 1) * (box_width - 2)) - snake_occupied_spaces].push_back(x); //Insert x value in current index
				empty_spaces[(x - 1) + ((y - 1) * (box_width - 2)) - snake_occupied_spaces].push_back(y); //Insert y value in current index
			}
		}
	}

	//Randomly pick an empty cell for new apple location and store in apple_coords
	srand(time(0)); //Use current time as seed for random number generator
	int index = rand() % empty_spaces.size(); //Chose a random index within empty_spaces
	//Clear old apple location and store new one
	apple_coords.clear();
	apple_coords.push_back(empty_spaces[index][0]);
	apple_coords.push_back(empty_spaces[index][1]);
}

//Move snake using previously user-defined move
int C_Snake::Move_Snake(const char move) {
	vector<int> new_snake_mouth; //Create variable for the new snake's mouth outisde switch
	switch (move) {
	case 'W': //Player wants to move up
		if (snake_coords[0][1] == 1) return 2; //Snake will hit top wall after this move
		new_snake_mouth.push_back(snake_coords[0][0]); //Left-right is the same
		new_snake_mouth.push_back(snake_coords[0][1] - 1); //Up-down is 1 square further up
		for (int i = 1; i < snake_coords.size(); i++)
			if (snake_coords[i] == new_snake_mouth) return 3; //Snake hits itself
		if (new_snake_mouth == apple_coords) { //Apple is above
			snake_coords.insert(snake_coords.begin(), new_snake_mouth); //Snake eats apple above and grows in length by 1 (no pop_back() afterwards)
			return 4;
		}
		else { //Normal movement of snake to new empty location
			snake_coords.insert(snake_coords.begin(), new_snake_mouth); //Snake moves up
			snake_coords.pop_back(); //Last cell is vacated by snake
			return 0;
		}
	case 'A': //Player wants to move left
		if (snake_coords[0][0] == 1) return 2; //Snake will now hit left wall after this move
		new_snake_mouth.push_back(snake_coords[0][0] - 1); //Left-right is 1 square further left
		new_snake_mouth.push_back(snake_coords[0][1]); //Up-down is the same
		for (int i = 1; i < snake_coords.size(); i++)
			if (snake_coords[i] == new_snake_mouth) return 3; //Snake hits itself
		if (new_snake_mouth == apple_coords) { //Apple is to the left
			snake_coords.insert(snake_coords.begin(), new_snake_mouth); //Snake eats apple to the left and grows in length by 1 (no pop_back() afterwards)
			return 4;
		}
		else {
			snake_coords.insert(snake_coords.begin(), new_snake_mouth); //Snake moves left
			snake_coords.pop_back(); //Last cell is vacated by snake
			return 0;
		}
	case 'S': //Player wants to move down
		if (snake_coords[0][1] == box_height - 2) return 2; //Snake will now hit bottom wall after this move
		new_snake_mouth.push_back(snake_coords[0][0]); //Left-right is the same
		new_snake_mouth.push_back(snake_coords[0][1] + 1); //Up-down is 1 square further down
		for (int i = 1; i < snake_coords.size(); i++)
			if (snake_coords[i] == new_snake_mouth) return 3; //Snake hits itself
		if (new_snake_mouth == apple_coords) { //Apple is below
			snake_coords.insert(snake_coords.begin(), new_snake_mouth); //Snake eats apple below and grows in length by 1 (no pop_back() afterwards)
			return 4;
		}
		else {
			snake_coords.insert(snake_coords.begin(), new_snake_mouth); //Snake moves down
			snake_coords.pop_back(); //Last cell is vacated by snake
			return 0;
		}
	case 'D': //Player wants to move right
		if (snake_coords[0][0] == box_width - 2) return 2; //Snake will now right bottom wall after this move
		new_snake_mouth.push_back(snake_coords[0][0] + 1); //Left-right is 1 square further right
		new_snake_mouth.push_back(snake_coords[0][1]); //Up-down is the same
		for (int i = 1; i < snake_coords.size(); i++)
			if (snake_coords[i] == new_snake_mouth) return 3; //Snake hits itself
		if (new_snake_mouth == apple_coords) { //Apple is to the right
			snake_coords.insert(snake_coords.begin(), new_snake_mouth); //Snake eats apple to the right and grows in length by 1 (no pop_back() afterwards)
			return 4;
		}
		else {
			snake_coords.insert(snake_coords.begin(), new_snake_mouth); //Snake moves right
			snake_coords.pop_back(); //Last cell is vacated by snake
			return 0;
		}
	}
	//Return error value
	return 1; //Should never be triggered as input (const char move) is checked to be correct in Retrieve_Move()
}