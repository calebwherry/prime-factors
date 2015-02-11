///////////////////////////////////////
///
///	\file		UtilLib.cpp
///	\author		J. Caleb Wherry
///	\date		2/11/2015
///	\brief		Implementation for UtilLib.h
///
///	\notes
///		1. Prime factors routine modified from: http://www.geeksforgeeks.org/print-all-prime-factors-of-a-given-number/
///		2. ...
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
		return appFullPath.substr(appFullPath.find_last_of("/\\") + 1);
	}


	// Convert string to int64_t:
	std::tuple<bool, int64_t> convertStrToLL (
		const string& inStr
	)
	{
		// Save current state of errno since it could have already been set:
		auto saved_errno = errno;

		// Our return tuple is made up of two items, if the conversion was successful and the converted value:
		bool conversionFailed = false;
		int64_t convertedNumber = 0;

		// Convert string to int64_t (using base10):
		errno = 0;
		convertedNumber = strtoll(inStr.c_str(), nullptr, 10);

		// If the above conversion is outside of the range, then errno will be set to ERANGE so we skip it.
		if (errno == ERANGE) conversionFailed = true;

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
		vector<uint64_t> primeFactors;

		// Print the number of 2s that divide n
		while (numberToFactor % 2 == 0)
		{
			primeFactors.push_back(2);
			numberToFactor = numberToFactor / 2;
		}

		// n must be odd at this point.  So we can skip one element (Note i = i +2)
		for (uint64_t i = 3; i <= sqrt(numberToFactor); i = i + 2)
		{
			// While i divides n, print i and divide n
			while (numberToFactor%i == 0)
			{
				primeFactors.push_back(i);
				numberToFactor = numberToFactor / i;
			}
		}

		// This condition is to handle the case whien n is a prime number
		// greater than 2
		if (numberToFactor > 2)
		{
			//primeFactors.push_back(1);
			primeFactors.push_back(numberToFactor);
		}

		// Give ownership of primeFactors vector back to calling scope:
		//	Note: Modern compilers use RVO so no copy of this vector should happen.
		return primeFactors;
	}

} // namespace utils