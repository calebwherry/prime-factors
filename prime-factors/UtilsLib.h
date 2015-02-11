///////////////////////////////////////
///
///	\file		UtilsLib.h
///	\author		J. Caleb Wherry
///	\date		2/11/2015
///	\brief		UtilsLib library header
///
///	\notes
///		1. ...
///
///////////////////////////////////////


//
// Include guards:
//
#ifndef UTILS_LIB_H
#define	UTILS_LIB_H


//
// Local includes:
//
// N/A


//
// Compiler includes:
//
#include <stdint.h>
#include <string>
#include <tuple>
#include <vector>


//
// Namespaces:
//
////


//
// Main library namespace:
//
namespace utils
{

	/// Function to get base name from given path.
	std::string parseApplicationName (
		const char* inPath							///< Pointer to char array with full path to parse
	);


	/// Convert string to int64_t.
	std::tuple<bool,int64_t> convertStrToLL (
		const std::string& inStr					///< String to convert to int64_t
	);


	/// Calculate prime factors of given number non-negative.
	std::vector<uint64_t> calculatePrimeFactors (
		uint64_t inNumberToFactor					///< Number to calculate prime factors of
	);

} // namespace utils

#endif // UTILS_LIB_H