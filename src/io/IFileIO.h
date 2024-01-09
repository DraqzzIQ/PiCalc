#pragma once

class IFileIO
{
	virtual void read_file(std::string key) = 0;
	virtual void write_file(std::string key) = 0;
};