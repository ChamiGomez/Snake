//Program: Snake
//This file contains the main function of the Snake program, based on the C_Snake class

#include "C_Snake.h"
#include <iostream>
#include <conio.h>

int main(void) {
	C_Snake game;
	int a = 0;
	char move_val;
	do {
		Clear_Console();
		game.Output_Status(); //Output current status to screen
		move_val = Retrieve_Move(); //Retrieve move from user
		a = game.Move_Snake(move_val); //Perform move on snake
		//Perform move on non-snake components of game (apple or end game)
		switch (a) {
		case 1: exit(1); //Error
		case 2: //Snake hits wall or... (see below)
		case 3: //Snake hits itself (or snake hits wall for case a = 2)
			cout << "\n\nGame Over! You Lost!\n\n";
			exit(0); //Exit game successfully
		case 4: //Snake eats apple
			game.New_Apple_Coords(); //Generate new coordinates for apple
		/* case 0: continue; //Snake moves into new empty square - nothing to do*/
		}
	} while (game.snake_coords.size() < game.max_snake_length); //End when snake is at max length

	cout << "\n\nCongratulations! You win!\n\n"; //Output winning statement

	return 0; //Exit game successfully
}