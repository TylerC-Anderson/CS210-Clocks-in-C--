#ifndef CLOCKSHELPER_H
#define CLOCKSHELPER_H

/*
* ClocksHelper Header file, guarded against multiple header references
*/

#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>

std::string displayClock12(int& hours24,int minutes, int seconds);
std::string displayClock24(int& hours24, int minutes, int seconds);

void clockSideBySide(std::string clock1, std::string clock2);
void calcTime(int& hours24, int& minutes, int& seconds);

void displayMenu();
void choiceResult(int input, int& currHours, int& currMinutes, int& currSeconds);
std::string calcPadding(const std::string& inputString, size_t padSize = 16, char paddedChar = ' ');

#endif
