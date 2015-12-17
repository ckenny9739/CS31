//
//  match.cpp
//  Project 5
//
//  Created by Connor Kenny on 11/15/14.
//  Copyright (c) 2014 Connor Kenny. All rights reserved.
//

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cassert>
#include <cctype>
#include <cstring>

using namespace std;

const int MAX_WORD_LENGTH = 20;
const int MAX_DOC_LENGTH = 200;

int standardizeRules(int distance[], char word1[][MAX_WORD_LENGTH+1], char word2[][MAX_WORD_LENGTH+1],int nRules);
int determineQuality(const int distance[], const char word1[][MAX_WORD_LENGTH+1], const char word2[][MAX_WORD_LENGTH+1], int nRules, const char document[]);
void swap(char a[], char b[]);

int main()
{
    /*
     const int TEST1_NCRITERIA = 4;
     int test1dist[TEST1_NCRITERIA] = {
     2,           4,          1,           13
     };
     char test1w1[TEST1_NCRITERIA][MAX_WORD_LENGTH+1] = {
     "mad",       "deranged", "nefarious", "have"
     };
     char test1w2[TEST1_NCRITERIA][MAX_WORD_LENGTH+1] = {
     "scientist", "robot",    "plot",      "mad"
     };
     
     const int TEST2_NCRITERIA = 6;
     int test2dist[TEST2_NCRITERIA] = {
     2,           4,          1,           13,           5,          0
     };
     char test2w1[TEST2_NCRITERIA][MAX_WORD_LENGTH+1] = {
     "mad",       "deranged", "nefarious", "have",     "SCIENTIST",     "dog"
     };
     char test2w2[TEST2_NCRITERIA][MAX_WORD_LENGTH+1] = {
     "scientist", "rob3ot",    "",      "mad",        "mad",        "cat"
     };
     
     const int TEST3_NCRITERIA = 5;
     int test3dist[TEST3_NCRITERIA] = {
     1,           2,          1,           4,           -1
     };
     char test3w1[TEST3_NCRITERIA][MAX_WORD_LENGTH+1] = {
     "mad",       "mad",          "scientist",       "have",    "hi"
     };
     char test3w2[TEST3_NCRITERIA][MAX_WORD_LENGTH+1] = {
     "scientist", "scientist",    "mad",      "mad",          "bye"
     };
     
     assert(standardizeRules(test1dist, test1w1, test1w2, TEST1_NCRITERIA) == 4); // regular
     assert(standardizeRules(test2dist, test2w1, test2w2, TEST2_NCRITERIA) == 3); // !alpha + repeat + empty, distance = 0
     assert(standardizeRules(test3dist, test3w1, test3w2, TEST3_NCRITERIA) == 2); // multiple repeats + same distance, negative distance
     
     assert(determineQuality(test1dist, test1w1, test1w2, TEST1_NCRITERIA,
     "The mad UCLA scientist unleashed a deranged evil giant robot.") == 2);
     assert(determineQuality(test1dist, test1w1, test1w2, TEST1_NCRITERIA,
     "The mad UCLA scientist unleashed    a deranged robot.") == 2);
     assert(determineQuality(test1dist, test1w1, test1w2, TEST1_NCRITERIA,
     "**** 2014 ****") == 0);
     assert(determineQuality(test1dist, test1w1, test1w2, TEST1_NCRITERIA,
     "  That plot is NEFARIOUS!") == 1);
     assert(determineQuality(test1dist, test1w1, test1w2, TEST1_NCRITERIA,
     "deranged deranged robot deranged robot robot") == 1);
     assert(determineQuality(test1dist, test1w1, test1w2, TEST1_NCRITERIA,
     "Two mad scientists suffer from deranged-robot fever.") == 0);
     */
    
    const int TEST0_NCRITERIA = 4;
    int test0dist[TEST0_NCRITERIA] = {
        2,           4,          1,           13
    };
    char test0w1[TEST0_NCRITERIA][MAX_WORD_LENGTH+1] = {
        "mad",       "swag", "nefarious", "have"
    };
    char test0w2[TEST0_NCRITERIA][MAX_WORD_LENGTH+1] = {
        "scientist", "deranged",    "plot",      "mad"
    };
    
    
    assert(standardizeRules(test0dist, test0w1, test0w2, TEST0_NCRITERIA)==4);
    
    const int TEST2_NCRITERIA = 4;
    int test2dist[TEST2_NCRITERIA] = {
        2,           	4,          	1,           	13
    };
    char test2w1[TEST2_NCRITERIA][MAX_WORD_LENGTH+1] = {
        "mad",       "half-witted", "nefaRIous", "have"
    };
    char test2w2[TEST2_NCRITERIA][MAX_WORD_LENGTH+1] = {
        "scientist", "guy",    "plot",      "MaD"
    };
    
    assert(standardizeRules(test2dist, test2w1, test2w2, TEST2_NCRITERIA)==3);
    
    const int TEST3_NCRITERIA = 4;
    int test3dist[TEST3_NCRITERIA] = {
        2,           	1,          	1,           	13
    };
    char test3w1[TEST3_NCRITERIA][MAX_WORD_LENGTH+1] = {
        "mad",       "PLOT", "nefarious", "scientist"
    };
    char test3w2[TEST3_NCRITERIA][MAX_WORD_LENGTH+1] = {
        "scientist", "NEFARIOUS",    "plot",      "mad"
    };
    
    assert(standardizeRules(test3dist,test3w1,test3w2,TEST3_NCRITERIA) == 2);
    
    const int TEST4_NCRITERIA = 4;
    int test4dist[TEST4_NCRITERIA] = {
        -3,           	4,          	1,           	13
    };
    char test4w1[TEST4_NCRITERIA][MAX_WORD_LENGTH+1] = {
        "mad",       "half-witted", "nefari#$us", "have"
    };
    char test4w2[TEST4_NCRITERIA][MAX_WORD_LENGTH+1] = {
        "scientist", "guy",    "plot",      "mad"
    };
    
    assert(standardizeRules(test4dist,test4w1,test4w2,TEST4_NCRITERIA) == 1);
    
    const int TEST5_NCRITERIA = 4;
    int test5dist[TEST5_NCRITERIA] = {
        3,           	4,          	1,           	13
    };
    char test5w1[TEST5_NCRITERIA][MAX_WORD_LENGTH+1] = {
        "",       "half-witted", "nefari#$us", "have"
    };
    char test5w2[TEST5_NCRITERIA][MAX_WORD_LENGTH+1] = {
        "scientist", "guy",    "plot",      ""
    };
    
    assert(standardizeRules(test5dist,test5w1,test5w2,TEST5_NCRITERIA) == 0);
    
    const int TEST6_NCRITERIA = 4;
    int test6dist[TEST6_NCRITERIA] = {
        12,           	4,          	1,           	13
    };
    char test6w1[TEST6_NCRITERIA][MAX_WORD_LENGTH+1] = {
        "mad",       "half-witted", "nefari#$us", "have"
    };
    char test6w2[TEST6_NCRITERIA][MAX_WORD_LENGTH+1] = {
        "mad", "guy",    "plot",      "mad"
    };
    
    assert(standardizeRules(test6dist,test6w1,test6w2,TEST6_NCRITERIA) == 2);
    
    const int TEST7_NCRITERIA = 4;
    int test7dist[TEST7_NCRITERIA] = {
        123455,           	4,          	1,           	13
    };
    char test7w1[TEST7_NCRITERIA][MAX_WORD_LENGTH+1] = {
        "mad",       "asdfghjklmnbvcxzqwer", "nefari#$us", "have"
    };
    char test7w2[TEST7_NCRITERIA][MAX_WORD_LENGTH+1] = {
        "scientist", "guy",    "plot",      "chicken"
    };
    
    assert(standardizeRules(test7dist,test7w1,test7w2,TEST7_NCRITERIA) == 3);
    
    const int TEST1_NCRITERIA = 5;
    int test1dist[TEST1_NCRITERIA] = {
        2,           4,          1,           13 ,  3
    };
    char test1w1[TEST1_NCRITERIA][MAX_WORD_LENGTH+1] = {
        "mad",       "deranged", "nefarious", "have", "deranged"
    };
    char test1w2[TEST1_NCRITERIA][MAX_WORD_LENGTH+1] = {
        "scientist", "robot",    "plot",      "mad", "deranged"
    };
    
    assert(determineQuality(test1dist, test1w1, test1w2, TEST1_NCRITERIA,
                            "The mad UCLA scientist unleashed a deranged evil giant robot.") == 2);
    assert(determineQuality(test1dist, test1w1, test1w2, TEST1_NCRITERIA,
                            "The mad UCLA scientist unleashed    a deranged robot.") == 2);
    assert(determineQuality(test1dist, test1w1, test1w2, TEST1_NCRITERIA,
                            "**** 2014 ****") == 0);
    assert(determineQuality(test1dist, test1w1, test1w2, TEST1_NCRITERIA,
                            "deranged deranged robot deranged robot robot") == 2);
    assert(determineQuality(test1dist, test1w1, test1w2, TEST1_NCRITERIA,
                            "Two mad scientists suffer from deranged-robot fever.") == 0);
    assert(determineQuality(test1dist, test1w1, test1w2, TEST1_NCRITERIA,
                            "") == 0);
    assert(determineQuality(test1dist, test1w1, test1w2, TEST1_NCRITERIA,
                            "deranged deranged deranged deranged deranged") == 1);
    assert(determineQuality(test1dist, test1w1, test1w2, TEST1_NCRITERIA,
                            "The deranged robot.") == 1);
    assert(determineQuality(test1dist, test1w1, test1w2, TEST1_NCRITERIA,
                            "that is a Very Nefarious:: plot!!") == 1);
    assert(determineQuality(test1dist, test1w1, test1w2, TEST1_NCRITERIA,
                            "The mad UCLA       $scientist unle@asheD a deranged robot.") == 2);
    assert(determineQuality(test1dist, test1w1, test1w2, TEST1_NCRITERIA,
                            "  That plot: NEFARIOUS!") == 1);
    
    cout << "All tests succeeded" << endl;
    
    
}

/*
 Swaps two c strings, a and b
 */

void swap(char a[], char b[])
{
    char temp[MAX_WORD_LENGTH+1];
    strcpy(temp, a);
    strcpy(a, b);
    strcpy(b, temp);
}


/*
 We say that a collection of match rules is in standard form if
 
 Every distance is positive.
 Every word is at least one letter long and contains no characters other than lower case letters.
 No two match rules in the collection have both the same w1 words and the same w2 words, in either order. (For example, if one rule has "mad" as its w1 word and "scientist" as its w2 word, then no other rule has "mad" as its w1 word and "scientist" as its w2 word, and no other rule has "scientist" as its w1 word and "mad" as its w2 word.)
 
 */

int standardizeRules(int distance[], char word1[][MAX_WORD_LENGTH+1], char word2[][MAX_WORD_LENGTH+1],int nRules)
{
    if (nRules <= 0)
        return 0;
    
    int lastPos = nRules - 1;                       // Also serves as counter for standardized rules
    for (int i = 0; i <= lastPos; i++)
    {
        bool needSwap = false;                      // set to true if need to swap
        
        if (distance[i] < 0 || word1[i][0] == '\0' || word2[i][0] == '\0')
        {
            needSwap = true;
        }
        
        for (int k = 0; k < strlen(word1[i]); k++)          // Set letters to lower case + remove if needed
        {
            if (!isalpha(word1[i][k]))                      // Only check for empty cstring
            {
                needSwap = true;
                break;
            }
            word1[i][k] = tolower(word1[i][k]);
        }
        
        for (int k = 0; k < strlen(word2[i]); k++)
        {
            if (!isalpha(word2[i][k]))
            {
                needSwap = true;
                break;
            }
            word2[i][k] = tolower(word2[i][k]);
        }
        
        if (needSwap == true)
        {
            swap(word1[i], word1[lastPos]);                     // Remove from standardized rules
            swap(word2[i], word2[lastPos]);
            swap(distance[i], distance[lastPos]);
            i--;
            lastPos--;
        }
    }
    
    for (int i = 0; i <= lastPos; i++)
    {
        for (int j = i+1; j <= lastPos; j++)
        {
            if ((strcmp(word1[i],word1[j]) == 0 && strcmp(word2[i],word2[j]) == 0) || (strcmp(word1[i],word2[j]) == 0 && strcmp(word2[i],word1[j]) == 0)) // Check when word1 has multiple of same value
            {
                if (distance[i] < distance[j])
                {
                    swap(word1[i], word1[lastPos]);             // Remove from standardized rules
                    swap(word2[i], word2[lastPos]);
                    swap(distance[i], distance[lastPos]);
                }
                else
                {
                    swap(word1[j], word1[lastPos]);             // Remove from standardized rules
                    swap(word2[j], word2[lastPos]);
                    swap(distance[j], distance[lastPos]);
                }
                i--;
                lastPos--;
                break;                                          // Only swap once
            }
        }
    }
    return lastPos + 1;                                         // Returns number of standard rules
}




/*
 
 The first four parameters represent a set of match rules that this function is allowed to assume is in standard form. (In other words, it need not check this, and is allowed to not work correctly or even do something undefined if the set is not in standard form.) The last argument is a C string containing the entire text of a document. You are allowed to assume that no document is longer than 200 characters. (We guarantee we will not test your function with documents that exceed this limit.) The function must return the match quality of the document (i.e., the number of match rules that the document matches).
 
 */


int determineQuality(const int distance[], const char word1[][MAX_WORD_LENGTH+1], const char word2[][MAX_WORD_LENGTH+1], int nRules, const char document[])
{
    if (nRules <= 0 || strlen(document) == 0)                   // Check bad arguments
        return 0;
    int matches = 0;
    int cDocWord = 0;                                           // Go through cDoc
    char cDoc[MAX_DOC_LENGTH+1][MAX_DOC_LENGTH+1] = { "\0" };   // Max possible array, '0\' as first char
                                                                // in case no letters in document
    for (int docLetter = 0; docLetter < strlen(document); docLetter++)  // Putword in each element of cDoc
    {
        if (document[docLetter] == ' ')                   // Catch beginning with spaces and multiple spaces
            continue;
        int cDocLetter = 0;
        while (document[docLetter] != ' ')
        {
            cerr << "docLetter " << docLetter << endl;
            if (isalpha(document[docLetter]))
            {
                cerr << "document " << document[docLetter] << endl;
                cDoc[cDocWord][cDocLetter] = tolower(document[docLetter]);
                cDocLetter++;
            }
            else if (docLetter == strlen(document) - 1)         // Document ends on non alpha character
                break;
            docLetter++;
        }
        cerr << cDoc[cDocWord] << endl;
        cDoc[cDocWord][cDocLetter] = '\0';
        cDocWord++;
        cerr << "cDocWord: " << cDocWord << endl;
    }
    
    if(cDoc[0][0] == '\0')                          // cDoc is empty
        return 0;
    
    for (int i = 0; i < nRules; i++)                // Loop 1: One iteration per rule
    {
        if(distance[i] == 0)
        {
            continue;                               // Skip because distance 0 means no match
        }
        bool match = false;
        for (int j = 0; j < cDocWord; j++)             // Loop 2: One iteration per word in cDoc
        {
            if(strcmp(cDoc[j], word1[i]) == 0)
            {
                for (int k = 1; k <= distance[i]; k++)      // Loop 3: One iteration per number in distance
                {                                           // Don't compare word in same position
                    if(strcmp(cDoc[j+k],word2[i]) == 0)
                    {
                        match = true;
                        matches++;
                        break;                      // Get out of loop 3
                    }
                }
            }
            
            if (match == true)                      // Get out of loop 2
                break;
            
            if(strcmp(cDoc[j], word2[i]) == 0)
            {
                for (int k = 1; k <= distance[i]; k++)      // Loop 3: One iteration per number in distance
                {                                           // Don't compare word in same position
                    if(strcmp(cDoc[j+k],word1[i]) == 0)
                    {
                        match = true;
                        matches++;
                        break;                      // Get out of loop 3
                    }
                }
            }
            
            if (match == true)                      // Get out of loop 2
                break;
        }
    }
    
    return matches;
}

