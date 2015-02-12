///////////////////////////////////////
///
///	\file		UtilLib.cpp
///	\author		J. Caleb Wherry
///	\date		2/11/2015
///	\brief		Implementation for UtilLib.h
///
///	\notes
///		1. Prime factors routine modified from: http://www.geeksforgeeks.org/print-all-prime-factors-of-a-given-number/
///
///////////////////////////////////////


//
// Local includes:
//
#include "UtilsLib.h"


//
// Compiler includes:
//
//...


//
// Namespaces:
//
using namespace std;


//
// Main library namespace:
//
namespace utils
{

    // Parse application name:
    string parseApplicationName (
        const char* inPath
    )
    {
        string appFullPath = string(inPath);

		// Get eveything after the last '\' or '/' encountered:
        return appFullPath.substr(appFullPath.find_last_of("/\\") + 1);
    }


    // Convert string to int64_t:
    std::tuple<bool, int64_t> convertStrToLL (
        const string& inStr
    )
    {
        // Save current state of errno since it could have already been set:
        auto saved_errno = errno;

        // Our return tuple is made up of two items, if the conversion failed and the converted value:
        bool conversionFailed = false;
        int64_t convertedNumber = 0;

        // Convert string to int64_t (using base10):
        convertedNumber = strtoll(inStr.c_str(), nullptr, 10);

        // If the above conversion is outside of the range for an int64_t, then errno will be set to ERANGE so we skip it.
		//	Also, since there is not a good way to tell the difference between a failed conversion and converting
		//	the number string "0" (or any variant of that string that reduces to "0"), we assume that a return 
		//	convertedNumber == 0 means the conversion failed.
        if ((errno == ERANGE) || (convertedNumber == 0)) conversionFailed = true;

        // Restore errno state to what it was before we started messing with it:
        errno = saved_errno;

        // Return tuple of needed values:
        return make_tuple(conversionFailed, convertedNumber);
    }


    //
    // Calculate prime factors:
    //	Note: Modified solution from http://www.geeksforgeeks.org/print-all-prime-factors-of-a-given-number/
    //
    vector<uint64_t> calculatePrimeFactors (
        uint64_t numberToFactor
    )
    {
		// Vector to hold our prime factors in:
        vector<uint64_t> primeFactors;

        // Save the number of 2s that divide n:
        while ((numberToFactor % 2) == 0)
        {
            primeFactors.push_back(2);
            numberToFactor /= 2;
        }

        // n must be odd at this point. So we can skip one element per iteration, going no further than
		//	sqrt(numberToFactor) since going further would lead to a number bigger than numberToFactor
		//	when squared.
        for (uint64_t i = 3; i <= sqrt(numberToFactor); i = i + 2)
        {
            // While i divides n, save i and divide n:
            while ((numberToFactor % i) == 0)
            {
                primeFactors.push_back(i);
                numberToFactor /= i;
            }
        }

        // This condition is to handle the case whien n is a prime number greater than 2:
        if (numberToFactor > 2)
        {
            primeFactors.push_back(numberToFactor);
        }

        // Give ownership of primeFactors vector back to calling scope:
        //	Note: Modern compilers use RVO so no copy of this vector should happen.
        return primeFactors;
    }

} // namespace utils