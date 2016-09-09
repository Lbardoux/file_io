#include <cstdlib>
#include <iostream>

#include "file_io.hpp"


std::ifstream& openFileAsReadOnly(const std::string &fname, std::ifstream &file)
{
	file.open(fname.c_str(), std::ifstream::in);
	if (!file.good())
	{
		throw std::string("Error while opening ") + fname;
	}
	return file;
}

std::string& getFullNameOfFile(const std::string &nameFromRoot, const char *const argv0, std::string &out)
{
	// Here, i'm using NULL and free() because realpath called malloc()
	// In order to prevent issues, we better have to call free instead of delete.
	char *absolutePath = realpath(argv0, NULL);
	if (absolutePath == NULL)
	{
		throw std::string("Error while getting absolute path of ") + nameFromRoot;
	}
	out = std::string(absolutePath);
	free(absolutePath);
	out = out.substr(0, out.find_last_of("\\/")) + "/" + nameFromRoot;
	return out;
}
