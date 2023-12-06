//Program: Snake
//This file contains the C_Snake class declaration and the declarations of other input/output functions used in the program

#pragma once
#include <vector>

using namespace std;

class C_Snake {
public:
	const int box_height = 12, box_width = 22, start_snake_length = 3, max_snake_length = 15; //Start parameters
	vector<vector<int>> snake_coords; //Stores positions of each segment of snake
	vector<int> apple_coords; //Stores location of the apple

	C_Snake(); //Create intial game situation

	//Game mechanics and output functions
	int Move_Snake(const char move);
	void New_Apple_Coords();
	void Output_Status();
};

//Input/output functions
char Retrieve_Move(); //Retrieve move from user
void Clear_Console(); //Clears console (for aesthetics)