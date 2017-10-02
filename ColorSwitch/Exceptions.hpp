#pragma once
#include <exception>
#include <string>
#include <iostream>

class Exception : std::exception 
{
	std::string m_errorMessage;
public:
	std::string getMessage() { return m_errorMessage; }
	Exception(std::string exceptionMessage) : m_errorMessage{ exceptionMessage } { }
};

class FieNoutFoundException : Exception
{
public:
	FieNoutFoundException(std::string file) : Exception("File not found: " + file) { }
};