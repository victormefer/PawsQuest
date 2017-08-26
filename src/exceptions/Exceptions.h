#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>

class TextureException : public std::exception
{
public:

	TextureException(std::string msg)
	{
		this->msg = msg;
	}

	virtual const char* what() const throw()
	{
		return msg.c_str();
	}

private:
	std::string msg;
};

class FileException : public std::exception
{
public:

	FileException(std::string msg)
	{
		this->msg = msg;
	}

	virtual const char* what() const throw()
	{
		return msg.c_str();
	}

private:
	std::string msg;
};


#endif
