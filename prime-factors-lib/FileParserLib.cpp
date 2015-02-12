///////////////////////////////////////
///
///	\file		FileParserLib.cpp
///	\author		J. Caleb Wherry
///	\date		2/11/2015
///	\brief		Implementation for FileParserLib.h
///
///	\notes
///		1. RAII guarantees that when the FileParser object goes out of scope, the destructor will be called
///			which will close the files the object controls.
///
///////////////////////////////////////


//
// Local includes:
//
#include "FileParserLib.h"


//
// Compiler includes:
//
#include <stdexcept>


//
// Namespaces:
//
using namespace std;


//
// Main library namespace:
//
namespace file_parser
{

	// FileParser constructor:
	FileParser::FileParser(
		const string& inFileName
		) : fileName(inFileName)
	{
		// Parse file:
		this->parseFile();
	}

	// FileParse destructor:
	FileParser::~FileParser()
	{
		file.close();
	}

	// Parse file contents:
	void FileParser::parseFile()
	{
		// Open file:
		file.open(fileName);

		// Check is file was opened incorrectly:
		if (!file.is_open())
		{
			throw runtime_error(string("Error: Problem(s) occured while trying to open the file: '") + fileName + string("'; aborting."));
		}

		// Read file line by line until end:
		string line = "";
		while (getline(file, line))
		{
			contents.push_back(line);
		}
	}

} // namespace file_parser