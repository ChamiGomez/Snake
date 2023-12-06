//Program: Snake
//This file contains the constructor to the C_Snake class to setup the game

#include "C_Snake.h"

C_Snake::C_Snake(void){
	//Calculate startpoint for mouth of snake
	int start_x = box_width / 2;
	int start_y = box_height / 2;

	//Input snake coordinates
	snake_coords.resize(start_snake_length);
	for (int i = 0; i < start_snake_length; i++) {
		snake_coords[i].push_back(start_x - i);
		snake_coords[i].push_back(start_y);
	}

	New_Apple_Coords(); //Create new apple coordinates
}