// Name:				Maickel Siqueira
// Seneca Student ID:	129337192
// Seneca email:		msiqueira@myseneca.ca
// Date of completion:	2020-11-21
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iostream>
#include "Utilities.h"

char Utilities::m_delimiter = ',';

void Utilities::setFieldWidth(size_t newWidth)
{
	m_widthField = newWidth;
}
size_t Utilities::getFieldWidth() const
{
	return m_widthField;
}
void Utilities::setDelimiter(char newDelimiter)
{
	m_delimiter = newDelimiter;
}
char Utilities::getDelimiter()
{
	return m_delimiter;
}
std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more)
{
	std::string temp = str;
	int end_pos = temp.find(m_delimiter, next_pos);

	std::string token = "";
	if (more) {
		// if it didn't find new delimiter it is end of file
		more = end_pos != -1;
		token = temp.substr(next_pos, end_pos - next_pos);
		// check if it extracted any chars
		// if token is empty then it had missing data
		if (token.size() == 0 && more)
			throw "Invalid data\n";
		next_pos = end_pos + 1;
	}

	//sets biggest width
	if (token.size() > m_widthField)
		m_widthField = token.size();

	return token;
}