#pragma once
#include <string>

class IFileHandler
{
	public:
	virtual void read_file(std::string key) = 0;
	virtual void write_file(std::string key) = 0;
};