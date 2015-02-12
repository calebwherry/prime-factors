///////////////////////////////////////
///
///	\file		prime-factors.cpp
///	\author		J. Caleb Wherry
///	\date		2/11/2015
///	\brief		CmdLine program to read in a file and print out all prime factors of given integers per line.
///
///	\notes
///		1. Integers in input file can be from Z (all integers) but prime factors will only be generated for
///			integers in Z+ \ {1} (positive integers with 1 removed) only.
///		2. Prime factors will only be from Z+ \ {1}.
///		3. We chose to design this app by seperating the file IO from the prime factors generation. This leads to
///			a better ability to test the individual components and decouples the two activites making them completely
///			non-dependent. This also allows us to easily use RAII when dealing with file IO. However, this design
///			could potentially be a problem if the size of the input file becomes massive. Inlining the prime factor
///			generation with the file IO would allow for the processing of vey large files whereas we are currently limited
///			to the amount of data we can hold in the vector containing the file contents.
///     4. We chose to make one slight modification to the given requirements: the number that is being factored is output to
///         the console followed by a colon then a comma-separated list of the prime factors, not just the factors themselves.
///
///////////////////////////////////////


//
// Local includes:
//
#include "UtilsLib.h"
#include "FileParserLib.h"


//
// Compiler includes:
//
#include <exception>
#include <stdint.h>
#include <string>
#include <fstream>
#include <iostream>
#include <cerrno>


//
// Namespaces:
//
using namespace std;
namespace u  = utils;
namespace fp = file_parser;


//
// Function prototypes:
//

/// Function to print out prime factors in specific format given a vector.
void printPrimeFactors (
    uint64_t, 
    const vector<uint64_t>&
);


//
// Main:
//
int main(int argc, char* argv[]) try
{

    //
    // App name:
    //
    string appName = u::parseApplicationName(argv[0]);


    //
    // CLI output header:
    //
    for (uint64_t i = 0; i < appName.size(); ++i) cout << "=";
    cout << endl << appName << endl;
    for (uint64_t i = 0; i < appName.size(); ++i) cout << "=";
    cout << endl << endl
         << "<number>: <CSV of prime factors>" << endl
         << "--------------------------------" << endl;


    //
    // Check number of CLI options:
    //
    if (argc != 2)
    {
        // Throw exception since this application only accepts 1 argument:
        //		Note: We perform the 'minus 1' since argc includes the executable name we are running in its value.
        throw runtime_error(string("Error: '" + appName + "' takes only 1 CLI option, ") + to_string(argc-1) + string(" given; aborting."));
    }


    //
    // Use first CLI option and parse file to get contents:
    //
    string inFileName = string(argv[1]);
    fp::FileParser fileParser(inFileName);
    auto fileContents = fileParser.getContents();


    //
    // Iterate through all lines, convert, get prime factors, and print results to screen:
    //
    for (auto& line : fileContents)
    {
        // Convert string to int64_t:
        bool conversionFailed = false;
        int64_t numberToFactor = 0;
        tie(conversionFailed, numberToFactor) = u::convertStrToLL(line);

        // If the above returned conversionFailed == true, we skip. We also ignore everything below 2 here 
        // since 0 is the value returned from convertStrToLL if a conversion could not happen, 1 is not prime by 
        // definition, and we are only showing prime factors for non-negative integers.
        if (conversionFailed || (numberToFactor < 2)) continue;

        // Get prime factors of parsed number:
        auto primeFactors = u::calculatePrimeFactors(numberToFactor);

        // Print prime factors data:
        printPrimeFactors(numberToFactor, primeFactors);
    }


    //
    // CLI output footer:
    //
    cout << endl << endl << appName << ": finished." << endl << endl;


    //
    // No exceptions/errors/crashes, we are good to go:
    //
    return 0;

}
catch (const exception& e)
{
    // Catch std::exceptions and ones derived from it and show error message:
    cerr << endl << "Exception from main: " << endl
         << "\t" << e.what() << endl << endl;

    // Return non-zero exit code:
    return 1;
}
catch (...)
{
    // Unknown exception:
    //	Note: This should not happen since ALL exceptions should be either std::exception or derived from it. If it 
    //		   DOES happen though there is not much we can do since we don't have any RTTI for the exception, it
    //		   could be anything.
    cerr << "Unknown exception was thrown from main, this should not have happened. Seek help; aborting." << endl;

    // Return non-zero exit code:
    return 1;
}


//
// Function to print prime factors data:
//
void printPrimeFactors (
    uint64_t numberFactored,
    const vector<uint64_t>& primeFactors
)
{
    // Print out number that was factored:
    cout << numberFactored << ": ";

    // Print out all prime factors on the same line seperated by commas:
    bool firstCSVElement = true;
    for (auto& factor : primeFactors)
    {
        // Do not print trailing comma on first item, print it starting with the second item BEFORE
        //	printing the item.
        if (firstCSVElement)
        {
            cout << factor;
            firstCSVElement = false;
        }
        else
        {
            cout << ", " << factor;
        }
    }

    // Print newline so next iteration will be starting fresh:
    cout << endl;
}
