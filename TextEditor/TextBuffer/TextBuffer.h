#pragma once

#include <string>

class TextBuffer
{
public:
	TextBuffer(std::string t) : text(t) {};
	std::string text;

	unsigned int length() { return text.length(); };
	std::string substr(unsigned int index, unsigned int size) { return text.substr(index, size); };
};

