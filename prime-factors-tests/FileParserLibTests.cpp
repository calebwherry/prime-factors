///////////////////////////////////////
///
///	\file		FileParserLibTests.cpp
///	\author		J. Caleb Wherry
///	\date		2/11/2015
///	\brief		FileParserLib unit tests
///
///	\notes:
///		1. Even though this testing framework is specific to Visual Studio, all tests have
///			been created with portability in mind so that the details could easily be
///			transferred and work in a different testing framework.
///
///////////////////////////////////////


//
// Test & VS includes:
//
#include "stdafx.h"
#include "CppUnitTest.h"


//
// File system seperator:
//	Note: We would not normally do this type of thing this way since boost::filesystem provides an
//			extremely well done API for handling this stuff. However, since we are not linking against 
//			Boost, this will do.
//
#if defined(WIN32) || defined(_WIN32)
const char PATH_SEPARATOR = '\\';
#else
const char PATH_SEPARATOR = '/';
#endif 


//
// Local includes:
//
#include "../prime-factors/FileParserLib.h"


//
// Compiler includes:
//
#include <string>
#include <memory>
#include <iostream>


//
// Namspaces:
//
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace fp = file_parser;
using namespace std;


//
// Test namespace:
//
namespace primefactorstests
{
	TEST_CLASS(FileParserLibTests)
	{
	private:

		//
		// Variables to use in tests:
		//
		const string emptyFileName = "";
		const string nonExistentFileName = "i_do_not_exist.awesome_ext";
		const string realFileName = std::string("..") + PATH_SEPARATOR + std::string("prime-factors") + PATH_SEPARATOR + std::string("test-data.txt");

		// Used to decouple object method tests from instantiation tests:
		unique_ptr<fp::FileParser> safeFileParser;

	public:


		//
		// Initilization run BEFORE each TEST_METHOD:
		//
		TEST_METHOD_INITIALIZE(TestMethodInitialize)
		{
			safeFileParser = make_unique<fp::FileParser>(realFileName);
		}


		//
		// Cleanup run AFTER each TEST_METHOD:
		//
		TEST_METHOD_CLEANUP(TestMethodCleanUp)
		{
			// Nothing to do.
		}


		//
		// Test empty file name:
		//
		TEST_METHOD(EmptyFileName)
		{
			try
			{
				fp::FileParser fileParser(emptyFileName);
			}
			catch (const std::exception& e)
			{
				// Correct exception, return.
				return;
			}
			catch (...)
			{
				// Wrong exception type was thrown, test failure:
				Assert::Fail(L"Exception thrown NOT derived from std::exception.", LINE_INFO());
			}
			
			// No exception was thrown, test failure:
			Assert::Fail(L"No exception for empty file name.", LINE_INFO());
		}
		

		//
		// Test non-existent file:
		//
		TEST_METHOD(NonExisitentFile)
		{
			try
			{
				fp::FileParser fileParser(nonExistentFileName);
			}
			catch (const std::exception& e)
			{
				// Correct exception, return.
				return;
			}
			catch (...)
			{
				// Wrong exception type was thrown, test failure:
				Assert::Fail(L"Exception thrown NOT derived from std::exception.", LINE_INFO());
			}

			// No exception was thrown, test failure:
			Assert::Fail(L"No exception for non-existent file name.", LINE_INFO());
		}


		//
		// Test opening existent file:
		//
		TEST_METHOD(OpenExisitentFile)
		{
			// Test existent file name:
			try
			{
				fp::FileParser fileParser(realFileName);
			}
			catch (const std::exception& e)
			{
				// Should be no exception:
				Assert::Fail(L"Exception thrown with correct file name.", LINE_INFO());
			}
			catch (...)
			{
				// Wrong exception type was thrown, test failure:
				Assert::Fail(L"Exception thrown NOT derived from std::exception.", LINE_INFO());
			}

			// No exception was thrown, test success:
			return;
		}


		//
		// Test getting name of existent file:
		//	Note: Using 'safe' parser here so that we can bypass testing exceptions that are handled by other tests.
		//
		TEST_METHOD(GetFileName)
		{
			// Check name of file from parser against given name:
			Assert::AreEqual(realFileName, safeFileParser->getFileName());
		}


		//
		// Test contents of opened existent file:
		//	Note: Using 'safe' parser here so that we can bypass testing exceptions that are handled by other tests.
		//
		TEST_METHOD(CheckFileContents)
		{
			// Get contents of file:
			auto& contents = safeFileParser->getContents();

			// Do some spot checks of values that came from file:
			Assert::AreEqual(string("#"),					contents[0]);
			Assert::AreEqual(string("10"),					contents[14]);
			Assert::AreEqual(string("dlfksdjf98y23rn2"),	contents[26]);
			Assert::AreEqual(string("3498"),				contents[41]);
			Assert::AreEqual(string("#@@@@!!!@#@@#W"),		contents[49]);
			Assert::AreEqual(string("P"),					contents[55]);
		}

	};
}