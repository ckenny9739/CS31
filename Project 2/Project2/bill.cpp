//
//  bill.cpp
//  CS 31 - Project 2
//
//  Created by Connor Kenny on 10/15/14.
//  Copyright (c) 2014 Connor Kenny. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;

int main()
{
    // GET THE USERS INFORMATION
    int minutes;
    cout << "Minutes used: ";
    cin >> minutes;
    cin.ignore(10000, '\n'); // Just in case user enters extra characters after the integer

    int messages;
    cout << "Text messages: ";
    cin >> messages;
    cin.ignore(10000, '\n'); // Just in case user enters extra characters after the integer
    
    string name;
    cout << "Customer name: ";
    getline(cin, name);
    
    int month;
    cout << "Month number (1=Jan, 2=Feb, etc.): ";
    cin >> month;
    
    // PRINT OUT 3 HYPHENS
    cout << "---" << endl;
    
    // CHECK FOR INCORRECT ENTRIES
    if (minutes < 0)
        cout << "The number of minutes used must be nonnegative." << endl;
    else if (messages < 0)
        cout << "The number of text messages must be nonnegative." << endl;
    else if (name == "")
        cout << "You must enter a customer name." << endl;
    else if (month < 1 || month > 12)
        cout << "The month number must be in the range 1 through 12." << endl;
    else // Only calculate bill if user enters information correctly
    {
    // CALCULATE THE BILL
    cout.setf(ios::fixed);
    cout.precision(2);
    
    double bill = 40.00; // Base bill
    if (minutes > 500)
        bill += (minutes - 500) * .45; // Extra Minutes
    
    
    if (messages > 400) // Extra Messages over 400
    {
        bill += (messages - 400) * .11;
        messages -= messages - 400; // Already paid for minutes over 400
    }
    
    if (messages > 200) // Extra Messages between 200 and 400
    {
        if (month >= 10 || month <= 5)
            bill += (messages - 200) * .03; // Regular
        else
            bill += (messages - 200) * .02; // Summer Sale
    }
    
    // PRINT OUT BILL
    cout << "The bill for " << name << " is $" << bill << endl;
    }
}
