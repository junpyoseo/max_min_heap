// ============================================================================
// File: main.cpp
// ============================================================================
// This is a test driver for the CMaxMinHeap class.
// ============================================================================

#include    <iostream>
#include    <cstdlib>
using namespace std;
#include    "personinfo.h"
#include    "cmaxminheap.h"

// constants
const   int NUM_PATIENTS = 7;


// ==== main ==================================================================
//
// ============================================================================

int     main()
{
    CMaxMinHeap<PersonInfo<int>>      myHeap;

    PersonInfo<int>                   patients[NUM_PATIENTS] =
                                { {147,          // weight
                                   67,          // height
                                   21,          // age
                                   "Iron Man",  //name
                                   1            // priority
                                  },            // end of first patient    [0]
                                  {155, 66, 45, "Black Widow", 5},      // [1]
                                  {232, 78, 84, "Captian America", 10}, // [2]
                                  {284, 69, 45, "Thor", 7},             // [3]
                                  {215, 75, 45, "Clint Barton", 15},    // [4]
                                  {270, 53, 45, "Hulk", 20},            // [5]
                                  {183, 71, 45, "Nick Fury", 13}        // [6]
                                };
    int                               index;


    // insert some patients into the heap (the heap defaults to 5 but we are
    // inserting 7 (so it will grow automatically...)

    for (index = 0; index < NUM_PATIENTS; ++index)
    {
        try
        {
            // exception handing here
            myHeap.Insert(patients[index]);

        }
        catch (CMaxMinHeapException&)
        {
            cerr << "Error inserting " << patients[index] << endl;
            exit(EXIT_FAILURE);
        }
        catch (...)
        {
            cerr << "Default catch for adding patient "
                 << patients[index] << endl;
            exit(EXIT_FAILURE);
        }
    }


    // removing all patients and then some...
    cout << "Removing all patients: " << endl;
    for (index = 0; index < NUM_PATIENTS; ++index)
    {
        PersonInfo<int> temp = myHeap.PeekTop();
        try
        {
            // print out patients name

            std::cout<< temp << endl;
            myHeap.Remove(temp);
        }
        catch (CMaxMinHeapException&)
        {
            cerr << "Error removing patient... " << temp << endl;
            exit(EXIT_FAILURE);
        }
        catch (...)
        {
            cerr << "Default catch for removing patient "
                 << temp << endl;
            exit(EXIT_FAILURE);
        }
    }

    return 0;

}  // end of "main"



