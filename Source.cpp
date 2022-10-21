#include <iostream>  
#include <string>  
#include <cstdlib>
#include <conio.h>
#include "Clock.h"

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
using namespace std;

// Lindsey Stoughton
// CS 210 Programming Languages
// October 11th, 2022
// Project 1


/**
 * Formats a number as 2 digits, with a leading 0 if needed
 * This method can be useful when converting a time like 9 hours, 12 minutes and 3 seconds to "09:12:03"
 * It's a good building block to help you get that part right and not have to repeat code
 *
 * @param n number to format, assumed between 0 and 59, inclusive
 * @return two digit string representation of number
 */
string twoDigitString(unsigned int n) {
    // Numbers between 10 and 59 are converted to a string
    // Numbers from 0 to 9 receive a "O" tacked onto the front of the string
    // Returns the two digit string representation of n
    if (n < 10) {
        string x = to_string(n);
        x.insert(0, "0");
        return x;
    }
    else {
        string x = to_string(n);
        return x;
    }
}

/**
 * Returns a string of length n, each character a c.
 * For example, nCharString(5, '*') should return "*****"
 *
 * @param n string length, >=0
 * @return string of n c's
 */
string nCharString(size_t n, char c) {
    // Initializes string and appends character c for length n digits
    string str;
    str.append(n, c);
    return str;
}

/**
 * Formats the time in military format
 *
 * @param h, hours 0 to 23
 * @param m, minutes 0 to 59
 * @param s, seconds 0 to 59
 *
 * @return hh:mm:ss
 */
string formatTime24(unsigned int h, unsigned int m, unsigned int s) {
    return twoDigitString(h) + ":" + twoDigitString(m) + ":" + twoDigitString(s);
}

/**
 * Formats the time in am/pm format
 *
 * @param h, hours 0 to 23
 * @param m, minutes 0 to 59
 * @param s, seconds 0 to 59
 *
 * @return hh:mm:ss A M or hh:mm:ss P M where hh is between 01 and 12, inclusive
 */
string formatTime12(unsigned int h, unsigned int m, unsigned int s) {
    string timestamp;

    if (h == 0) {
        h = 12;
        timestamp = "A M";
    }
    else if (h < 12) {
        timestamp = "A M";
    }
    else if (h == 12) {
        timestamp = "P M";
    }
    else {
        h = h - 12;
        timestamp = "P M";
    }
    return twoDigitString(h) + ":" + twoDigitString(m) + ":" + twoDigitString(s) + " " + timestamp;
}

/**
 * Prints menu
 *
 * @param *strings[], nonempty array of choices
 * @param numStrings, number of strings in array
 * @param width, width of each line, will be comfortably bigger than the longest string
 *
 */
void printMenu(const char *strings[], unsigned int numStrings, unsigned char width) {
    // first print width *'s followed by an endl
    cout << nCharString(width, '*') << endl;
    /** Next, for each string s in the array:
     * cout a star, a space, the item Number a space a hyphen another space, s,
     * and enough spaces to get to a length of width - 1 (enough will depend on the length of the current menu item).
     * Close the line with a star and an endl. The goal is that the stars on the right align with each other and each line
     * has the same width, passed in as a parameter.
     * Skip a line after each line except the last line
     */
    string lineText;

    for (int i = 1; i <= numStrings; i++) {
        lineText = "* " + to_string(i) + " - " + strings[i - 1];
        cout << lineText << nCharString(width - lineText.size() - 1, ' ') << "*" << endl;

        if (i < numStrings) {
            cout << endl;
        }
    }
    // outside the loop print another width *s followed by an endl
    cout << nCharString(width, '*') << endl;
}

/**
* Display the clocks
*
* @param h, hours 0 to 23
* @param m, minutes 0 to 59
* @param s, seconds 0 to 59
*/
void displayClocks(unsigned int h, unsigned int m, unsigned int s) {
    // cout 27 stars + 3 spaces + 27 stars + endl
    // cout 1 star + 6 spaces + 12-HOUR CLOCK + 6 spaces + 1 star + 3 spaces
    // cout 1 star + 6 spaces + 24-HOUR CLOCK + 6 spaces + 1 star + endl
    // cout an endl for a blank line
    // cout 1 star + 6 spaces + formatTime12(h, m, s) + 7 spaces + 1 star + 3 spaces
    // cout 1 star + 8 spaces + formatTime24(h, m, s) + 9 spaces + 1 star + endl
    // cout 27 stars + 3 spaces + 27 stars + endl

    cout << nCharString(27, '*') << nCharString(3, ' ') << nCharString(27, '*') << endl;
    cout << "*      12-HOUR CLOCK      *   ";
    cout << "*      24-HOUR CLOCK      *" << endl;
    cout << endl;
    cout << "*      " << formatTime12(h, m, s) << "       *   ";
    cout << "*        " << formatTime24(h, m, s) << "         *" << endl;
    cout << nCharString(27, '*') << nCharString(3, ' ') << nCharString(27, '*') << endl;
    cout << flush; // Added flush
}

/**
 * Adds one hour
 */
void addOneHour(Clock& clock) {
    // If getHour() is between 0 and 22 inclusive, add 1 and setHour() to that
    // If getHour() is 23 the next value for hour is 0 so setHour() to that
    int hour = clock.getHour();

    if (hour >= 0 && hour <= 22) {
        clock.setHour(hour + 1);
    }
    else if (hour == 23) {
        clock.setHour(0);
    }
}

/**
 * Adds one minute
 */
void addOneMinute(Clock& clock) {
    // If getMinute() is between 0 and 58 inclusive, add 1 and setMinute() to the new value
    // If getMinute() is 59 the minutes must be set to 0 and you must call addOneHour()
    int minute = clock.getMinute();

    if (minute >= 0 && minute <= 58) {
        clock.setMinute(minute + 1);
    }
    else if (minute == 59) {
        clock.setMinute(0);
        addOneHour(clock);
    }
}

/**
 * Adds one second
 */
void addOneSecond(Clock& clock) {
    // If getSecond() is between 0 and 58 inclusive, add 1 and setSecond()
    // If getSecond() is 59, seconds wrap around to 0 and you need to call addOneMinute()
    int second = clock.getSecond();

    if (second >= 0 && second <= 58) {
        clock.setSecond(second + 1);
        //cout << second << flush;
    }
    else if (second == 59) {
        clock.setSecond(0);
        addOneMinute(clock);
    }
}

/**
 *  Evaluates user input into 4 choices
 *  1 to add one hour
 *  2 to add one minute
 *  3 to add one second
 *  4 to exit program
 *  Note: Enter does not need to be pressed, answer is cleared when read
 */
void mainMenu(Clock& clock, int userChoice) {
    int menuChoice = userChoice;

    switch (menuChoice) {
    case 1:
        addOneHour(clock);
        break;

    case 2:
        addOneMinute(clock);
        break;

    case 3:
        addOneSecond(clock);
        break;

    case 4:
        exit(0);
        break;
        
    default:
        cout << "Invalid choice" << endl;
        break;
    }
}

// Refreshes the display clocks and menu with updated time each second
// and checks for menu selection
void refreshDisplay(Clock& clock, const char* strings[], unsigned int numStrings, unsigned char width) {
    while (true) {
        displayClocks(clock.getHour(), clock.getMinute(), clock.getSecond());
        printMenu(strings, numStrings, width);
        
        // Detect when key is pressed and send it to mainMenu for evaluation
        if (_kbhit()) {
            int userInput= _getch();
                
            if (isdigit(userInput)) {
                int userChoice = (int)((char)userInput - '0');
                mainMenu(clock, userChoice);
                userChoice = 0; // Reset input
            }      
        }
        // Delay for one second to be added accurately
        Sleep(1000);
        addOneSecond(clock);
        // Clear screen to reprint current time
        system("cls");
    }   
}

int main() {
    // Instantiate clock object to hold time
    Clock clock(0,0,0);
    const int numStrings = 4;
    const char *strings[numStrings] = {"Add One Hour", "Add One Minute", "Add One Second", "Quit"};
    int width = 57;
    // Display updated clocks and menu, while taking input
    refreshDisplay(clock, strings, numStrings, width);
}