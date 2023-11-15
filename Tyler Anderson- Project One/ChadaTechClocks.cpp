#include "ClocksHelper.h"

/*
*   Chada Tech Clock Update: ISO 8601 compliance
*   Developer: Tyler C Anderson
*   Developed on: November 11,2023
* 
*   Purpose:
*     To update the clocks our clients see when they use the
*     website in accordance with ISO 8601 standard. Displays
*     time in both the 12- and 24-hour formats simultaneously.
* 
*   Files used as dependencies:
*        ClocksHelper.cpp and ClocksHelper.h, the helper source
*           file and its header file, respectively.
* 
*     PLEASE NOTE: Prototype, only accepts user inputs
*     and does not yet keep time. 
*/


int main() {
	/*
	 * main() makes calls to other programs and directs user i/o.
	 */
	
	// Initialization
	int hours = 0;
	int minutes = 0;
	int seconds = 0;

	// Prints user input prompt for the initial time before starting the loop
	std::cout << "What time would you like to start with? Separate hours" << std::endl;
	std::cout << "minutes and seconds with spaces and as a 24-hour clock" << std::endl;
	std::cout << "please. Example: inputting 13 34 56  would be" << std::endl;
	std::cout << "01:34:56 P M in 12-hour time, or 13:34:56 in 24-hour" << std::endl;
	std::cout << "time." << std::endl << "    < ";
	std::cin >> hours;
	std::cin >> minutes;
	std::cin >> seconds;

	// Converts user time to appropriate time if out of denomination's bounds
	calcTime(hours, minutes, seconds);

	int userInput = -1;    // Just to start the loop and prep for input.

	// This is the menu loop. Displays the clocks and menu, then accept user
	// input and sends the data accordingly
	while (userInput != 4) {

		// Displays the clock side by side
		clockSideBySide(displayClock12(hours, minutes, seconds),
			displayClock24(hours, minutes, seconds));

		// Puts the finishing character on the above clocks 
		// then adds a new line
		std::cout << '*' << std::endl;

		// Display user's menu, then accept input
		displayMenu();
		std::cin >> userInput;

		// If the user sends the quit signal, don't do anything
		// further but restart the loop, which will end the program.
		if (userInput == 4) {
			continue;
		}

		// Calculates the time as appropriate based on the user's choice.
		choiceResult(userInput, hours, minutes, seconds);
		calcTime(hours, minutes, seconds);
	}

	return 0;
}