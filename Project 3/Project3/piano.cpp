//
//  piano.cpp
//  Project 3
//
//  Created by Connor Kenny on 10/28/14.
//  Copyright (c) 2014 Connor Kenny. All rights reserved.
//

#include <iostream>
#include <string>
#include <cassert>
#include <cctype>
using namespace std;


//*************************************
//  translateNote
//*************************************

// Given an octave number, a note letter, and an accidental sign, return
// the character that the indicated note translates to if it is playable.
// Return a space character if it is not playable.
//
// First parameter:   the octave number (the integer 4 is the number of the
//                    octave that starts with middle C, for example).
// Second parameter:  an upper case note letter, 'A' through 'G'
// Third parameter:   '#', 'b', or ' ' (meaning no accidental sign)
//
// Examples:  translateNote(4, 'A', ' ') returns 'Q'
//            translateNote(4, 'A', '#') returns '%'
//            translateNote(4, 'H', ' ') returns ' '

char translateNote(int octave, char noteLetter, char accidentalSign)
{
    // This check is here solely to report a common CS 31 student error.
    if (octave > 9)
    {
        cerr << "********** translateNote was called with first argument = "
        << octave << endl;
    }
    
    // Convert Cb, C, C#/Db, D, D#/Eb, ..., B, B#
    //      to -1, 0,   1,   2,   3, ...,  11, 12
    
    int note;
    switch (noteLetter)
    {
        case 'C':  note =  0; break;
        case 'D':  note =  2; break;
        case 'E':  note =  4; break;
        case 'F':  note =  5; break;
        case 'G':  note =  7; break;
        case 'A':  note =  9; break;
        case 'B':  note = 11; break;
        default:   return ' ';
    }
    switch (accidentalSign)
    {
        case '#':  note++; break;
        case 'b':  note--; break;
        case ' ':  break;
        default:   return ' ';
    }
    
    // Convert ..., A#1, B1, C2, C#2, D2, ... to
    //         ..., -2,  -1, 0,   1,  2, ...
    
    int sequenceNumber = 12 * (octave - 2) + note;
    
    string keymap = "Z1X2CV3B4N5M,6.7/A8S9D0FG!H@JK#L$Q%WE^R&TY*U(I)OP";
    if (sequenceNumber < 0  ||  sequenceNumber >= keymap.size())
        return ' ';
    return keymap[sequenceNumber];
}



// This function returns true if its parameter is a well-formed tune, and false otherwise.
//
// Parameter: The string that you want to check to see if it is well formed
//
// A well-formed tune is a sequence of zero or more beats.
// Every character in a non-empty well-formed tune must be part of a beat
// (so, for example, C/G is not a well-formed tune because the G is not part of a beat,
// since every beat must end with a slash)
//
// Check each combination of letters, numbers and symbols that can make up a well-formed tune

bool isTuneWellFormed(string tune)
{
    
    if ( tune.size() == 0)                  // Empty string returns true
        return true;
    
    for (int i = 0; i != tune.size(); i++)  // Go through entire string ( Example )
    {
        if (tune[i] == 'A' || tune[i] == 'B' || tune[i] == 'C' ||tune[i] == 'D' ||tune[i] == 'E' || tune[i] == 'F' || tune[i] == 'G')
                                            // Check for note letter ( A )
        {
            if ( tune[i+1] == '#' || tune[i+1] == 'b')  // Check for accidental sign after letter ( A# )
            {
                
                if ( isdigit(tune[i+2]) )   // Check for digit after accidental sign ( A#5 )
                {
                    if ( tune[i+3] == '/')  // Check slash for end beat - continue after slash ( A#5/ )
                    {
                        i += 3;
                        continue;
                    }
                    else if (tune[i+3] == 'A' || tune[i+3] == 'B' || tune[i+3] == 'C' ||tune[i+3] == 'D' ||tune[i+3] == 'E' || tune[i+3] == 'F' || tune[i+3] == 'G')
                                    // Check for another note letter ( A#5A )
                    {
                        i += 2;     // only += 2, instead of += 3 because we want it to start on this letter
                                    // not the next character like the usual cases
                        continue;
                    }
                    else            // not in correct form ( A#51 )
                    {
                        return false;
                    }
                    
                }
                
                else if ( tune[i+2] == '/') // Check Slash for end beat - continue after slash ( A#/ )
                {
                    i += 2;
                    continue;
                }
                
                else if (tune[i+2] == 'A' || tune[i+2] == 'B' || tune[i+2] == 'C' ||tune[i+2] == 'D' ||tune[i+2] == 'E' || tune[i+2] == 'F' || tune[i+2] == 'G')
                                    // Check for note letter ( A#A )
                {
                    i += 1;         // only += 1, instead of 2 because want it to start on this letter
                                    // not the next character like the usual cases
                    continue;
                }
                
                else                // not in correct form  ( A#b )
                {
                    return false;
                }
                
            }
            
            else if ( isdigit(tune[i+1]) ) // Check for digit ( A3 )
            {
                if ( tune[i+2] == '/')     // Check slash for end beat - continue after slash ( A3/ )
                {
                    i += 2;
                    continue;
                }
                
                else if (tune[i+2] == 'A' || tune[i+2] == 'B' || tune[i+2] == 'C' ||tune[i+2] == 'D' ||tune[i+2] == 'E' || tune[i+2] == 'F' || tune[i+2] == 'G')
                                    // Check for another note letter ( A3A )
                {
                    i +=1;          // only += 1, instead of 2 because want it to start on this letter
                                    // not the next character like the usual cases
                    continue;
                }
                
                else                // not in correct form  ( A3- )
                {
                    return false;
                }
                
            }
            
            else if ( tune[i+1] == '/') // Check Slash for end beat ( A/ )
            {
                continue;
            }
            
            else if (tune[i+1] == 'A' || tune[i+1] == 'B' || tune[i+1] == 'C' ||tune[i+1] == 'D' ||tune[i+1] == 'E' || tune[i+1] == 'F' || tune[i+1] == 'G')
                                    // Check for another note letter ( AA )
            {
                continue;           // no changing i because want it to start on this letter
                                    // not the next character like the usual cases
            }
            
            else                    // not in the correct form ( A* )
            {
                return false;
            }
            
        }
        
        else if ( tune[i] == '/')   // Check Slash for end beat ( / )
        {
            continue;
        }
        
        else
            return false;           // Check for incorrect character at beginning, or after '/'
        
    }
    return true;                    // Well Formed
}



// Checks to see if tune is playable

bool isPlayable(string tune, int& badBeat)
{
    if (!isTuneWellFormed(tune))        // Automatically not playable if not well-formed
    {
        return false;
    }
    
    int beatCount = 1;              // Start at the first beat
    
    for (int i = 0; i != tune.size(); i++)
    {
        if ( tune [i] == '/' )      // At end of each beat, increase beatCount
            beatCount++;
        
        if (isdigit(tune[i]) && tune[i] == '2' && tune[i-1] == 'b' && tune[i-2] == 'C') // For Cb2
        {
            badBeat = beatCount;    // Set badBeat if not playable
            return false;
        }
        
        else if (isdigit(tune[i]) && tune[i] == '6' && tune[i-1] == 'b' && tune[i-2] == 'C') // For Cb6
            continue;
        
        else if (isdigit(tune[i]) && tune[i] == '6' && tune[i-1] == 'C') // For C6
            continue;
        
        else if (isdigit(tune[i]) && tune[i] == '1' && tune[i-1] == '#' && tune[i-2] == 'B') // For B#1
            continue;
        
        else if (isdigit(tune[i]) && ( tune[i] < '2' || tune[i] > '5'))
        {
            badBeat = beatCount;    // Set badBeat if not playable
            return false;
        }
        
    }
    
    return true;                    // Playable
}



/*
 
 If the parameter tune is playable, the function sets instructions
 to the translation of the tune, leaves badBeat unchanged, and returns 0.
 
 In all other cases, the function leaves instructions unchanged.
 
 If tune is not well-formed, the function leaves badBeat unchanged and returns 1.
 
 If tune is well-formed but not playable, badBeat is set to
 the number of the beat with the first unplayable note
 (where the first beat of the whole tune is number 1, the second is number 2, etc.),
 and the function returns 2.
 
 You must not assume that instructions and badBeat have any particular values
 at the time this function is entered.
 
 */


int translateTune(string tune, string& instructions, int& badBeat)
{
    
    //if playable, instructions -> translation, return 0
    if (isPlayable(tune, badBeat))
    {
        // Set base values
        int oct = 4;
        char letter = 'A';
        char accidental = ' ';
        int noteCount = 0;
        instructions = "";
        
        if (tune[0] == '/')                         // For first beat rests
            instructions += ' ';
        
        for (int i = 0; i != tune.size(); i++)
        {
            
            for (int j = i; j != tune.size(); j++)  // Count number of notes in beat
            {
                if (isupper(tune[j]))               // To disregard the 'b'
                {
                    noteCount++;
                }
                if (tune[j] == '/')
                {
                    break;
                }
            }
            
            if (noteCount > 1)          // for multiple note beats
            {
                instructions += '[';
            }
            
            for (int k = 0; k < noteCount; k++)
            {
                while (!isalpha(tune[i]))       // increase i to start at a letter
                    i++;

                if (isalpha(tune[i]))           //  Make sure tune[i] is a Letter to start
                {
                    letter = tune[i];
                
                    if (tune[i+1] == '#' || tune[i+1] == 'b')      // Letter - Accidental
                    {
                        accidental = tune[i+1];
                        
                        if (isdigit(tune[i+2]))  // Letter - Accidental - Digit
                        {
                            oct = tune[i+2] - '0'; // turns character in ASCII to corresponding int
                        }
                    }
                
                    if (isdigit(tune[i+1]))       // Letter - Digit
                    {
                        oct = tune[i+1] - '0'; // turns character in ASCII to corresponding int
                    }
                    
                    instructions += translateNote(oct, letter, accidental);
                    
                    i++; // Start on next character. Without this, the for loop would only increase k, not i
                }
                
                oct = 4;
                letter = 'A';
                accidental = ' ';

                
            }
            
                if (noteCount > 1)          // for multiple note beats
                {
                    instructions += ']';
                }
            
            noteCount = 0; // reset for future iterations
            
            if (tune[i] == '/' && tune[i+1] == '/')     // for rests
            {
                instructions += ' ';
                continue;
            }
        }
            
            return 0;
    }

        // if well-formed, but not playable, badBeat -> first unplayabale note, return 2
    else if (isTuneWellFormed(tune) && ! isPlayable(tune, badBeat))
    {
        return 2;       // badBeat is set when isTuneWellFormed is true, but isPlayable is false
    }
        
    else                //if not well-formed, return 1
    {
        return 1;
    }
        
}
    
int main()      // Test Program
{
        
    string t;
    for (;;)
    {
        cout << "Enter tune: ";
        getline(cin, t);
        if (t == "quit")
            break;
        int beat = 999;
        string inst = "xxx";
            
        cout << "isTuneWellFormed returns ";
        if (isTuneWellFormed(t))
            cout << "true" << endl;
        else
            cout << "false" << endl;
            
        cout << "isPlayable returns ";
        if (isPlayable(t, beat))
            cout << "true" << endl;
        else
            cout << "false" << endl;
            
        cout << "translateTune returns " << translateTune(t, inst, beat) << endl;
        cout << "badBeat = " << beat << endl << "instructions = " << inst << endl;
            
            
    }
}