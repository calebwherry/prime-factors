///////////////////////////////////////
///
///	\file		UtilsLibTests.cpp
///	\author		J. Caleb Wherry
///	\date		2/11/2015
///	\brief		UtilsLib unit tests
///
///	\notes
///		1. Even though this testing framework is specific to Visual Studio, all tests have
///			been created with portability in mind so that the details could easily be
///			transferred and work in a different testing framework.
///////////////////////////////////////


//
// Test & VS includes:
//
#include "stdafx.h"
#include "CppUnitTest.h"


//
// Local includes:
//
#include "../prime-factors/UtilsLib.h"


//
// Compiler includes:
//
#include <string>
#include <tuple>
#include <vector>


//
// Namspaces:
//
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
namespace u = utils;


//
// Test namespace:
//
namespace primefactorstests
{
	TEST_CLASS(UtilsLibTests)
	{
	private:

		//
		// Variables to use in tests:
		//
		const char* emptyPath = "";
		const char* windowsPath = "C:\\test\\one\\two\\three.exe";
		const char* unixPath = "/test/one/two/three";
		string testString;

	public:


		//
		// Initilization run BEFORE each TEST_METHOD:
		//
		TEST_METHOD_INITIALIZE(TestMethodInitialize)
		{
			// Nothing to do.
		}


		//
		// Cleanup run AFTER each TEST_METHOD:
		//
		TEST_METHOD_CLEANUP(TestMethodCleanUp)
		{
			// Nothing to do.
		}


		//
		// Test parsing of empty path:
		//
		TEST_METHOD(EmptyPath)
		{
			string appName = u::parseApplicationName(emptyPath);

			testString = "";
			Assert::AreEqual(testString, appName);
		}


		//
		// Test parsing of windows-style path:
		//
		TEST_METHOD(WindowsStylePath)
		{
			string appName = u::parseApplicationName(windowsPath);

			testString = "three.exe";
			Assert::AreEqual(testString, appName);
		}


		//
		// Test parsing of unix-style path:
		//
		TEST_METHOD(UnixStylePath)
		{
			string appName = u::parseApplicationName(unixPath);

			testString = "three";
			Assert::AreEqual(testString, appName);
		}


		//
		// Test converting "0" string to int64_t:
		//	Note: Edge case for the convertStrToLL routine that fails but is perfectly
		//			valid. Since the underlying routines make it hard to deal with this
		//			case, we assume that returning 0 as a convertedNumber is classified
		//			as a fail.
		//
		TEST_METHOD(ConvertStrToLL_0)
		{
			bool conversionFailed = false;
			int64_t convertedNumber = 0;

			// Convert number:
			tie(conversionFailed, convertedNumber) = u::convertStrToLL("0");

			Assert::AreEqual(conversionFailed, true);
			Assert::AreEqual(string("0"), to_string(convertedNumber));
		}


		//
		// Test converting "1" string to int64_t:
		//
		TEST_METHOD(ConvertStrToLL_1)
		{
			bool conversionFailed = false;
			int64_t convertedNumber = 0;

			// Convert number:
			tie(conversionFailed, convertedNumber) = u::convertStrToLL("1");

			Assert::AreEqual(conversionFailed, false);
			Assert::AreEqual(string("1"), to_string(convertedNumber));
		}


		//
		// Test converting "000087298756945" string to int64_t:
		//
		TEST_METHOD(ConvertStrToLL_000087298756945)
		{
			bool conversionFailed = false;
			int64_t convertedNumber = 0;

			// Convert number:
			tie(conversionFailed, convertedNumber) = u::convertStrToLL("000087298756945");

			Assert::AreEqual(conversionFailed, false);
			Assert::AreEqual(string("87298756945"), to_string(convertedNumber));
		}


		//
		// Test converting "8729875694597648957389475839743459" string to int64_t:
		//
		TEST_METHOD(ConvertStrToLL_Overflow)
		{
			bool conversionFailed = false;
			int64_t convertedNumber = 0;

			// Convert number:
			tie(conversionFailed, convertedNumber) = u::convertStrToLL("8729875694597648957389475839743459");

			Assert::AreEqual(conversionFailed, true);
		}


		//
		// Test converting "I am not a number." string to int64_t:
		//
		TEST_METHOD(ConvertStrToLL_NonNumber)
		{
			bool conversionFailed = false;
			int64_t convertedNumber = 0;

			// Convert number:
			tie(conversionFailed, convertedNumber) = u::convertStrToLL("I am not a number.");

			Assert::AreEqual(true, conversionFailed);
			Assert::AreEqual(to_string(0ll), to_string(convertedNumber));
		}


		//
		// Test converting "0x3" string to int64_t:
		//
		TEST_METHOD(ConvertStrToLL_Hex)
		{
			bool conversionFailed = false;
			int64_t convertedNumber = 0;

			// Convert number:
			tie(conversionFailed, convertedNumber) = u::convertStrToLL("0x3");

			Assert::AreEqual(true, conversionFailed);
			Assert::AreEqual(to_string(0ll), to_string(convertedNumber));
		}


		//
		// Test calculating prime factors of 1:
		//	Note: 1, by definition, has zero prime factors.
		//
		TEST_METHOD(PrimeFactorsOf_1)
		{
			// Calculate prime factors:
			auto& primeFactors = u::calculatePrimeFactors(1);
			vector<uint64_t> actualPrimeFactors = {};

			// Make sure sizes are the same:
			Assert::AreEqual(actualPrimeFactors.size(), primeFactors.size());

			// Loop through and test all factors:
			for (uint32_t i = 0; i < primeFactors.size(); ++i)
			{
				Assert::AreEqual(actualPrimeFactors[i], primeFactors[i]);
			}
		}


		//
		// Test calculating prime factors of 2:
		//	Note: prime
		//
		TEST_METHOD(PrimeFactorsOf_2)
		{
			// Calculate prime factors:
			auto& primeFactors = u::calculatePrimeFactors(2);
			vector<uint64_t> actualPrimeFactors = {2};

			// Make sure sizes are the same:
			Assert::AreEqual(actualPrimeFactors.size(), primeFactors.size());

			// Loop through and test all factors:
			for (uint32_t i = 0; i < primeFactors.size(); ++i)
			{
				Assert::AreEqual(actualPrimeFactors[i], primeFactors[i]);
			}
		}


		//
		// Test calculating prime factors of 3:
		//	Note: prime
		//
		TEST_METHOD(PrimeFactorsOf_3)
		{
			// Calculate prime factors:
			auto& primeFactors = u::calculatePrimeFactors(3);
			vector<uint64_t> actualPrimeFactors = {3};

			// Make sure sizes are the same:
			Assert::AreEqual(actualPrimeFactors.size(), primeFactors.size());

			// Loop through and test all factors:
			for (uint32_t i = 0; i < primeFactors.size(); ++i)
			{
				Assert::AreEqual(actualPrimeFactors[i], primeFactors[i]);
			}
		}


		//
		// Test calculating prime factors of 4:
		//
		TEST_METHOD(PrimeFactorsOf_4)
		{
			// Calculate prime factors:
			auto& primeFactors = u::calculatePrimeFactors(4);
			vector<uint64_t> actualPrimeFactors = { 2, 2 };

			// Make sure sizes are the same:
			Assert::AreEqual(actualPrimeFactors.size(), primeFactors.size());

			// Loop through and test all factors:
			for (uint32_t i = 0; i < primeFactors.size(); ++i)
			{
				Assert::AreEqual(actualPrimeFactors[i], primeFactors[i]);
			}
		}


		//
		// Test calculating prime factors of 455:
		//
		TEST_METHOD(PrimeFactorsOf_455)
		{
			// Calculate prime factors:
			auto& primeFactors = u::calculatePrimeFactors(455);
			vector<uint64_t> actualPrimeFactors = { 5, 7, 13 };

			// Make sure sizes are the same:
			Assert::AreEqual(actualPrimeFactors.size(), primeFactors.size());

			// Loop through and test all factors:
			for (uint32_t i = 0; i < primeFactors.size(); ++i)
			{
				Assert::AreEqual(actualPrimeFactors[i], primeFactors[i]);
			}
		}


		//
		// Test calculating prime factors of 5915587277:
		//	Note: prime
		//
		TEST_METHOD(PrimeFactorsOf_5915587277)
		{
			// Calculate prime factors:
			auto& primeFactors = u::calculatePrimeFactors(5915587277);
			vector<uint64_t> actualPrimeFactors = { 5915587277 };

			// Make sure sizes are the same:
			Assert::AreEqual(actualPrimeFactors.size(), primeFactors.size());

			// Loop through and test all factors:
			for (uint32_t i = 0; i < primeFactors.size(); ++i)
			{
				Assert::AreEqual(actualPrimeFactors[i], primeFactors[i]);
			}
		}

	};
}