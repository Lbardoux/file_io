/**
 * @brief This file provides some simple functions to read files with
 * the *stream libraries from C++ standard
 * @author MTLCRBN
 * @version 1.0
 */
#ifndef FILE_IO_HPP_INCLUDED
#define FILE_IO_HPP_INCLUDED

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#ifdef __GNUC__
	//! @brief USAGE : void func_name(args) NONNULL((index0, index1, etc))
	#define NONNULL(argNumbers) __attribute__((nonnull (argNumbers)))
#else
	#define NONNULL(argNumbers)
#endif

/**
 * @brief Open \a fname inside \a file.
 * You'll have to call the \b close() function by yourself when you're done, like this :
 * @code
 *	file.close();
 * @endcode
 *
 * @throw std::string If there is any issue while opening the \a fname
 * 
 * @param[in]  fname The name (relative or absolute) of the file you wanna open as read only.
 * @param[out] file  The ifstream (an inputFileStream) to store the content of \a fname.
 * @return A reference to \a file.
 */
std::ifstream& openFileAsReadOnly(const std::string &fname, std::ifstream &file);

/**
 * @brief Get the absolute name of \a nameFromRoot, using \a argv0, and storing the result
 * on \a out.
 * @throw std::string if an error occurs.
 * 
 * @param[in]  nameFromRoot Considering the root of your project tree, the relative path to get your file.
 * @param[in]  argv0        the first argument of the program (argv[0]).
 * @param[out] out          The storage place for the result.
 * @return A reference on \a out.
 */
std::string& getFullNameOfFile(const std::string &nameFromRoot, const char *const argv0, std::string &out) NONNULL((2));


/**
 * @brief Try to get a vector of TypeValueToRead from a single line of \a file.
 * An example below;
 * @code
 * try
 * {
 *  	readFromLine<int>(myFile);
 *  	// do stuff
 * }
 * catch(std::string &exception)
 * {
 *  	std::cout << "EOF" << std::endl;
 *  	myFile.close();
 * }
 * @endcode
 * @throw std::string When there is no more line to read.
 * @param[inout] file The opened as read only file to read.
 * @return An empty container if the line doesn't contain the required value type, a full vector otherwise.
 */
template<typename TypeValueToRead, template<typename...> typename Container>
Container<TypeValueToRead> readFromLine(std::ifstream &file)
{
	std::string line;
	Container<TypeValueToRead> container;
	if (!std::getline(file, line))
	{
		throw std::string("No more lines to read !");
	}
	std::stringstream s(line);
	TypeValueToRead value;
	while (s >> value)
	{
		container.push_back(value);
	}
	return container;
}


#endif
