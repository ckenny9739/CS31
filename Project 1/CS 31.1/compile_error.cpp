// Code for Project 1
// Report poll results

#include <iostream>
// Error 1: Forgot using namespace std

int main()
{
    int numberSurveyed // Error 2: Forgot semicolon
    int forJerry;
    int forNeel;
    
    cout << "How many registered voters were surveyed? ";
    cin >> numberSurveyed;
    cout << "How many of them say they will vote for Jerry? ";
    cin >> forJerry;
    cout << "How many of them say they will vote for Neel? ";
    cin >> forNeel;
    
    double pctJerry = 100.0 * forJerry / numberSurveyed;
    double pctNeel = 100.0 * forNeel / numberSurveyed;
    
    cout.setf(ios::fixed);   // see pp. 30-31 in Savitch book
    cout.precision(1);
    
    cout << endl;
    cout << pctJerry << "% say they will vote for Jerry." << endl;
    cout << pctNeel << "% say they will vote for Neel." << endl;
    
    if (forJerry > forNeel)
        cout << "Jerry is predicted to win the election." << endl;
    else
        cout << "Neel is predicted to win the election." << endl;
}
