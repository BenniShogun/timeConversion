// McElroy CS265 Week 5 assignment
// Time Conversion
// Professor Lusby, 09-Jan-22

// We begin by including the necessary header files
#include <iostream>
#include <iomanip>

// We use the standard namespace
using namespace std;

// We list the function prototypes for the functions used in the program. 
void menu(int& mode);
void takeTime(int& hours, int& minutes, bool& median, int mode);
void displayTime(int hours, int minutes, int mode, bool median);
void twelveToTwentyfour(int& hours, bool median);
void twentyfourToTwelve(int& hours, bool& median);
void badInput();

int main()
{
	// Here we declare the variables to be used within the main function. The integer values are initialized to values
	// that fall outside of the control conditions for the loops used within the program's functions. 
	int hours = 25;
	int minutes = 60;
	int mode = 0;
	bool median = false;

	// Here we start by calling the function menu that lets the user select the type of conversion they wish to 
	// perform. We pass the initialized value of the integer mode to the function. The reference variable will be 
	// changed by the function according to the user input. 
	menu(mode);

	// After the user selects the type of conversion, we call the function takeTime so the user can enter the number 
	// of hours and minutes. We use the reference variables hours and minutes and function type void since we are 
	// returning multiple values. We also pass the value of mode to the program to determine the type of input asked 
	// from the user and to use for the loop control condition for hours. The reference variable median is used
	// to allow the user to enter am or pm if necessary.
	takeTime(hours, minutes, median, mode);

	// After taking the time, we call the function displayTime, which will call the appropriate function to 
	// convert the time based on the user's selection and then output the results to the screen
	displayTime(hours, minutes, mode, median);
	
	
	return 0;
}

void menu(int& mode)
{
	
	do
	{
		// Here we add an output to let the user know that the integer they entered is invalid in case
		// they enter a value that doesn't match one of two options and doesn't trigger an input failure
		if (mode != 0)
			badInput();
		
		// We prompt the user to enter 1 or 2 depending on the desired time conversion. We attempt to
		// assign the input to mode after ignoring anything that might be in the input stream.
		cout << "Are you converting 12 to 24 hour, or 24 to 12 hour?\n"
			<< "\nEnter '1' for 12 to 24. Enter '2' for 24 to 12.\n" << endl;
		
		cin >> mode;

		// Here we check for an input failure. If the input fails the "mode" integer will be zero-initialized
		// which is fine because the loop control condition will still work.
		if (!cin)
			badInput();
		
	} while (mode != 1 && mode != 2);

	cout << endl;

	return;
}

void takeTime(int& hours,int& minutes, bool& median, int mode)
{
	// We use local variable within the function in place of the reference variables to protect against 
	// zero-initialization in case of input failure.
	int w = 0;
	int x = hours;
	int y = minutes;
	int z = mode;

	do
	{
		// Since we initialized the value of x to the value of hours, if the user enters an integer
		// that is outside the allowed range we will call the badInput function to display an error message
		// so the user can try again.
		if (x != hours)
			badInput();

		// We prompt the user to enter a number of hours according to the desired conversion type
		// We attempt to assign the value to x and ignore any input overflow from previous input.
		cout << "Enter the hours" << endl;
		if (z == 1)
			cout << "Between 0 and 12" << endl;
		else if(z == 2)
			cout << "Between 0 and 23" << endl;
		
		cin >> x;
	
		// Here we check for an input failure. If the input has failed, we call badInput to reset the stream
		// and set x equal to hours because a failure will zero-initialize the integer variable. 
		if (!cin)
		{
			badInput();
			x = hours;
		}
			
	// Our loop condition will check to see if the number entered for x is within the parameters of the desired
	// conversion type.
	} while (z == 1 && x > 12 || z == 2 && x > 23 || x < 0);

	do
	{
		// If y is any value other than the initialized value of minutes, the program will call badInput and display
		// an error message
		if (y != minutes)
			badInput();

		// We prompt the user to enter the number of minutes and attempt to assign the value to y. We ignore any 
		// input overflow from a previous user input.
		cout << "Enter the minutes\nBetween 0 and 59" << endl;

		
		cin >> y;

		// Here we check for an input failure. If the input has failed, we call badInput to reset the stream
		// and set y equal to minutes because a failure will zero-initialize the integer variable. 
		if (!cin)
		{
			badInput();
			y = minutes;
		}
			
	// Our loop condition checks for an appropriate value of y. Minutes must be between 0 and 59.
	} while (y < 0 || y > 59);

	// If the user is converting from 12 hour to 24 hour time, we allow them to select the median am or pm
	if (mode == 1)
	{
		do
		{
			if (w != 0)
				cout << "Invalid input. Try again.\n" << endl;
			
			cout << "Enter 1 for AM, or 2 for PM." << endl;

			cin.ignore(100, '\n');
			cin >> w;

			// If we have an input failure we call badInput. Since the variable will be zero-initialized
			// The loop control condition will take care of it.
			if (!cin)
				badInput();
		} while (w != 1 && w != 2);
		
	}

	// After the risk of zero-initialization has passed, we assign the values of our local variables to the reference 
	// variables. 
	hours = x;
	minutes = y;

	if (w == 2)
		median = true;

	cout << endl;

	return;
}

// This function converts from 12 to 24 hour time. If the median is true then the input was p.m. and we add 
// 12 hours to the variable hours. If the median is false then we also check to see if the hours are equal to 12
// because if so then the 24 hour output will have the value of 0 for hours. 
void twelveToTwentyfour(int& hours, bool median)
{
	if (median == true)
		hours = hours + 12;
	else if (hours == 12)
		hours = 0;
	

	return;
}

// This function will perform the conversion from 24 to 12 hours. This is done simply by checking whether
// the input hours is greater than 12 and then subtracting 12 from the hours and setting the median to true
// to output p.m. If the hours are less than 12 we leave the median set to false to output a.m.
void twentyfourToTwelve(int& hours, bool& median)
{
	if (hours > 12)
	{
		hours = hours - 12;
		median = true;
	}

	return;
}

void displayTime(int hours, int minutes, int mode, bool median)
{
	// We start by displaying the time entered by the user in the correct format. We use setw() and setfill()
	// to ensure that the format is 00:00 regardless of whether the hours and minutes are single or 
	// double digit
	cout << setw(2) << setfill('0') << hours << ":" << setw(2) << minutes;

	// Here we decide whether the median will be displayed after the user input time. If the input was 
	// 12 hour we will assign a.m. or p.m. depending on the selected median. If the input was 12 hour, we
	// take advantage of the loop condition to call the twelveToTwentyfour function to perform the conversion.
	if (mode == 1)
	{
		if (median == false)
			cout << " a.m.";
		else
			cout << " p.m.";

		twelveToTwentyfour(hours, median);
	}

	// If the user input was 24 hour we don't output a median and call the function 
	// twentyfourToTwelve to perform the conversion
	else
		twentyfourToTwelve(hours, median);

	// We finish the output by outputting the converted time using setw() for the correct output format
	// and then decide again whether or not to include the median in the output.
	cout << " is: " << setw(2) << hours << ":" << setw(2) << minutes;
	if (mode == 2)
	{
		if (median == false)
			cout << " a.m.";
		else
			cout << " p.m.";
	}
	cout << endl;

	return;
}

// We have set up a function called badInput to call whenever there is an input stream failure.
// If the input fails we clear the failure and ignore the rest of the input
void badInput()
{
	cout << "Invalid input. Try again\n" << endl;
	cin.clear();
	cin.ignore(100, '\n');
	return;
}
