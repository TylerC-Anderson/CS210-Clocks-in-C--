#include "ClocksHelper.h"

/*
* Function: displayClock12()
* Purpose: Displays the 12-hour clock with a border
* Parameters:
*     hours24: taken in as 24 hours. We adjust to the 12 hour equivalent within
*     minutes: minutes as input
*     seconds: seconds as input
*/
std::string displayClock12(int& hours24, int minutes, int seconds) {

	// This accounts for afternoon or morning based on hours24
	// and sets hours12 accordingly, as well as selecting AM or PM
	int hours12 = (hours24 > 12) ? hours24 - 12 : hours24;
	hours12 = (hours12 < 1) ? 12 : hours12;              // if the hour is midnight (or lower somehow) set it to 12 instead
	std::string amPM = (hours24 < 12) ? " A M" : " P M";

	// This displays a leading zero if the amount of the denomination is less than 10
	// then places result into a string for later use.
	std::string zeroedHours = (hours12 < 10) ? "0" + std::to_string(hours12) : std::to_string(hours12);
	std::string zeroedMinutes = (minutes < 10) ? "0" + std::to_string(minutes) : std::to_string(minutes);
	std::string zeroedSeconds = (seconds < 10) ? "0" + std::to_string(seconds) : std::to_string(seconds);

	// Strings we need, also has the clock formatted as 00:00:00
	std::string clockBorder(26, '*');
	std::string clock12("12-Hour Clock");
	std::string time12(zeroedHours + ":" + zeroedMinutes + ":" + zeroedSeconds);
	
	// calculates padding based on it's location relative to the border
	std::string clock12PaddedLeft = calcPadding(clock12, 19);
	std::string time12PaddedLeft = calcPadding(time12,14);
	std::string clock12PaddedRight = calcPadding(clock12, 18);
	std::string time12PaddedRight = calcPadding(time12,14);

	// the string we output to display
	std::string showTime12 = clockBorder + "\n"
		+ "*" + clock12PaddedLeft + clock12 + clock12PaddedRight + "*" + "\n"
		+ "*" + time12PaddedLeft + time12 + amPM + time12PaddedRight + "*" + "\n"
		+ clockBorder;

	return showTime12;
}

/*
* Function: displayClock24()
* Purpose: Displays the 24-hour clock with a border
* Parameters:
*     hours24: taken in as 24 hours
*     minutes: minutes as input
*     seconds: seconds as input
*/
std::string displayClock24(int& hours24, int minutes, int seconds) {
	
	// This displays a leading zero if the amount of the denomination is less than 10
	// then places result into a string for later use.
	std::string zeroedHours = (hours24 < 10) ? "0" + std::to_string(hours24) : std::to_string(hours24);
	std::string zeroedMinutes = (minutes < 10) ? "0" + std::to_string(minutes) : std::to_string(minutes);
	std::string zeroedSeconds = (seconds < 10) ? "0" + std::to_string(seconds) : std::to_string(seconds);

	// Strings we need, also has the clock formatted as 00:00:00
	std::string clockBorder(26, '*');
	std::string clock24("24-Hour Clock");
	std::string time24(zeroedHours + ":" + zeroedMinutes + ":" + zeroedSeconds);

	// calculates padding based on it's location relative to the border
	std::string clock24PaddedLeft = calcPadding(clock24, 19);
	std::string time24PaddedLeft = calcPadding(time24);
	std::string clock24PaddedRight = calcPadding(clock24, 18);
	std::string time24PaddedRight = calcPadding(time24);

	// the string we output to display
	std::string showTime24 = clockBorder + "\n"
		+ "*" + clock24PaddedLeft + clock24 + clock24PaddedRight + "*" + "\n"
		+ "*" + time24PaddedLeft + time24 + time24PaddedRight + "*" + "\n"
		+ clockBorder + "\n";

	return showTime24;
}

/*
* Function: clockSideBySide()
* Purpose: Runs the 12- and 24-hour clocks through a loop to display them
*     side by side
* Parameters: two clocks to display as strings
*/
void clockSideBySide(std::string clock1, std::string clock2) {
	
	// Initialize interator for the second loop, j, out here 
	// so as to not reset its count each time. Using size_t in
	// each case because we are comparing to a sizeof operator
	// result, so this avoids memory overflow
	size_t j = 0;

	// Outer loop prints the first clock if it isn't time to
	// start printing the second clock.
	for (size_t i = 0; i < clock1.length(); ++i) { 

		// The cue to start the next clock printing is a newline
		// character, due to how the displayClock functions
		// needed to be written to be outputable
		if ((clock1.at(i) == '\n') || (i == clock1.length() - 1)) {

			// if the clock1 hasn't finished yet, print a 3 character-wide
			// space between clocks first. 
			if (i != clock1.length() - 1) {
				std::cout << "   ";
			}
			// if clock one has finished, print out the last border
			// character then add the space from above
			else {
				std::cout << "*   ";
			}

			// Inner loop is for printing out the second clock
			for (j; j < i; ++j) {

				// Check the next character ahead of the print
				// head, if it's a newline character, prepare
				// to exit this inner loop 
				if (clock2.at(j+1) == '\n') {	
					// move j up by one, print the last border
					// character then exit inner loop
					++j;
					std::cout << '*' << std::endl;
					continue;
				}
				else {
					std::cout << clock2.at(j);  // prints clock2 characters
				}
			}
		}
		else {
			std::cout << clock1.at(i);  // Prints clock1 if inner loop didn't trigger
		}
	}
}

/*
 * Function: calcTime()
 * Purpose: Calculates hours, minutes, and seconds
 *   over 23, 59, and 59 respectively, as a clock should
 * Parameters:
 *	 General Note - All parameters are passed by reference
 *      because this code is only ever going to be called
 *      when the time might need to be calculated. This way
 *      it's more readable both to implement the function 
 *      itself and to call it when needed.
 *   hours24 - hours inputted as the 24 hour format
 *   minutes - minutes inputted by user
 *   seconds - seconds inputted by user
 */
void calcTime(int& hours24, int& minutes, int& seconds) {

	/* Each of the blocks takes the time that's over the threshhold 
	 * value, adds one to its larger denomination, then subtracts
	 * the threshhold amount from the amount passed. Repeats addition
	 * until all values are less than their upper denomination
	 */
	
	while (seconds > 59) {
		++minutes;
		seconds -= 60;
	}
	while (minutes > 59) {
		++hours24;
		minutes -= 60;
	}
	while (hours24 > 23) {
		hours24 -= 24;
	};
}

/*
* Function: displayMenu()
* Purpose: Does what it says on the tin, displays what options user may take. 
* Parameters: N/A
*/
void displayMenu() {

	// Labeling our strings for better readability
	std::string menuBorder(26,'*');          // Sets menu border length, fills with *'s
	std::string addHour("1 - Add One Hour");
	std::string addMinute("2 - Add One Minute");
	std::string addSecond("3 - Add One Second");
	std::string exitSignal("4 - Exit Program");

	// Formats the strings and adds a border
	std::cout << menuBorder << std::endl;
	std::cout << "* " << std::setw(23) << std::left << addHour << "*" << std::endl;
	std::cout << "* " << std::setw(23) << std::left << addMinute << "*" << std::endl;
	std::cout << "* " << std::setw(23) << std::left << addSecond << "*" << std::endl;
	std::cout << "* " << std::setw(23) << std::left << exitSignal << "*" << std::endl;
	std::cout << menuBorder << std::endl << "  < ";	      // "  < " is to denote user's input
}

/*
* Function: Choice Result()
* Purpose: runs user input through a switch-case block to output the result
*    via the passed by reference hours, minutes, and seconds
*/
void choiceResult(int input, int& currHours, int& currMinutes, int&currSeconds) {

	switch (input) {
	case(1):
		++currHours;
		break;
	case(2):
		++currMinutes;
		break;
	case(3):
		++currSeconds;
		break;
	case(4):
	default:
		break;
	}

}

/*
* Function: calcPadding()
* Purpose: Calculates how much spacing to use for the inputString given
*    and optionally what character to use for the spacing.
* Parameters:
*    inputString: Passed by reference but labeled constant, for memory savings
*    padSize: How much total spacing should be in the output string
*    paddedChar: Optional, what character to use for padding. Default is a single 
*        white space.
*/
std::string calcPadding(std::string const& inputString, size_t padSize, char paddedChar) {

	if (inputString.size() < padSize) {    // Runs the calculation when the string is less than number of characters
		return std::string(padSize - inputString.size(), paddedChar);
	}
	else {                                // Returns empty if the string is at least as big as the padSize
		return "";
	}
}