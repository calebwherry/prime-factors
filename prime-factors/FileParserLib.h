///////////////////////////////////////
///
///	\file		FileParserLib.h
///	\author		J. Caleb Wherry
///	\date		2/11/2015
///	\brief		FileParserLib library header
///
///	\notes
///		1. FileParser helper library for RAII file IO classes.
///
///////////////////////////////////////


//
// Include guards:
//
#ifndef FILE_PARSER_LIB_H
#define	FILE_PARSER_LIB_H


//
// Local includes:
//
//...


//
// Compiler includes:
//
#include <iostream>
#include <vector>
#include <string>
#include <fstream>


//
// Namespaces:
//
////


//
// Main library namespace:
//
namespace file_parser
{

    /// RAII FileParser class:
    class FileParser
    {
    public:

        /// Default constructor:
        FileParser() = delete;

        /// Custom constructor:
        explicit FileParser(
            const std::string& inFileName		///< File name of file to open
        );

        // Destructor:
        ~FileParser();


        //
        // Member functions:
        //

		/// Get name of file.
		std::string getFileName() { return fileName; }

        /// Get the contents of the file stored in a vector, (each entry is a line).
        std::vector<std::string> getContents() { return contents; }

    private:

        //
        // Member variables:
        //
        std::ifstream file;
        const std::string fileName;
        std::vector<std::string> contents;


        //
        // Member functions:
        //

        /// Parse the input file:
        void parseFile();

    };

} // namespace file_parser

#endif // FILE_PARSER_LIB_H