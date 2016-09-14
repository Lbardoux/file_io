/**
 * @brief This file provides some simple functions to read files with
 * the *stream libraries from C++ standard
 * @example example.cpp
 * @author MTLCRBN
 * @version 1.0
 */
#ifndef FILE_IO_HPP_INCLUDED
#define FILE_IO_HPP_INCLUDED

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#if defined(__GNUC__) && !defined(NONNULL)
	//! @brief USAGE : void func_name(args) NONNULL((index0, index1, etc))
	#define NONNULL(argNumbers) __attribute__((nonnull (argNumbers)))
#else
	#define NONNULL(argNumbers)
#endif

#ifndef DECLSPEC
	#if defined(__WIN32__) || defined(__WINRT__)
		#define DECLSPEC __declspec(dllexport)
	#else
		#if defined(__GNUC__) && __GNUC__ >= 4
			#define DECLSPEC __attribute__((visibility("default")))
		#elif defined(__GNUC__) && __GNUC__ >= 2
			#define DECLSPEC __declspec(dllexport)
		#else
			#define DECLSPEC
		#endif
	#endif
#endif


/**
 * @brief An input file wrapper class.
 * 
 * You could use it with a fstream or an ifstream.
 * It doesn't not make sense to try with a ofstream.
 */
template<typename FileType=std::ifstream>
class File final
{
	private:
		FileType file;
	
	public:
		//! @brief This function is forbidden
		File(void) = delete;
		
		/**
		 * @brief The only constructor, which open \a fname.
		 * @param[in] fname The path to the file you want to open, relative or absolute
		 * @throw std::string If this function was unable to open \a fname.
		 */
		File(const std::string &fname)
		{
			this->file.open(fname.c_str());
			if (!this->file.good())
			{
				throw std::string("Error while opening ") + fname;
			}
		}
		
		//! @brief Close the internal file.
		~File(void)
		{
			this->file.close();
		}
		
		/**
		 * @brief Try to get a Container of TypeValueToRead from a single line of the internal file.
		 * @code
		 * 
		 * @endcode
		 * @throw std::string When there is no more line to read.
		 * @return An empty container if the line doesn't contain the required value type, a full vector otherwise.
		 */
		template<typename TypeValueToRead, template<typename...> class Container=std::vector>
		Container<TypeValueToRead> readFromLine(void)
		{
			std::string line;
			Container<TypeValueToRead> container;
			if (!std::getline(this->file, line))
			{
				throw std::string("No more line to read !");
			}
			std::stringstream s(line);
			TypeValueToRead value;
			while (s >> value)
			{
				container.push_back(value);
			}
			return container;
		}
		
		//! @return the internal file as a reference.
		FileType& getFile(void)
		{
			return this->file;
		}
	
};

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
DECLSPEC std::string& getFullNameOfFile(const std::string &nameFromRoot, const char *const argv0, std::string &out) NONNULL((2));



#endif
