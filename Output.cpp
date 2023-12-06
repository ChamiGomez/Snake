//Program: Snake
//This file contains the output functions of the Snake program, based on the C_Snake class

#include "C_Snake.h"
#include <iostream>

//Clear_Console uses compile-time if's
void Clear_Console(void) {
#if defined _WIN64
	system("cls");
#endif
}
/* Untested on other operating systems, but potential to be expanded...
void Clear_Console(void) {
#if defined (_WIN32) || (_WIN64) //Other windows systems
	system("cls");
#elif defined defined(__linux__) || (__LINUX__) || defined(__gnu_linux__) //linux systems
	system("clear");
#endif
}
*/

//Output current status of the game to screen
void C_Snake::Output_Status(void) {
	for (int y = 0; y < box_height; y++) { //For each row in game
		for (int x = 0; x < box_width; x++) { //For each column within the row
			bool snake_here = false;
			for (int i = 0; i < snake_coords.size(); i++) {
				if (x == snake_coords[i][0] && y == snake_coords[i][1]) { //If snake is here
					cout << "O"; //Output snake symbol
					snake_here = true;
					break;
				}
			}
			if (!snake_here) { //No snake here
				if (x == 0 || x == box_width - 1) { //Left or right wall
					cout << "\*"; //Output wall symbol
					continue;
				}
				else if (y == 0 || y == box_height - 1) { //Bottom or top wall
					cout << "\*"; //Output wall symbol
					continue;
				}
				else if (x == apple_coords[0] && y == apple_coords[1]) { //Apple is here
					cout << "A"; //Output apple symbol
					continue;
				}
				else cout << " "; //Empty space
			}
		}
		cout << endl;
	}
	cout << endl;
}