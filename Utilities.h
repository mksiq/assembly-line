// Name:				Maickel Siqueira
// Seneca Student ID:	129337192
// Seneca email:		msiqueira@myseneca.ca
// Date of completion:	2020-11-21
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef UTILITIES_H
#define UTILITIES_H
#include <string>

class Utilities
{
	size_t m_widthField = 1;
	static char m_delimiter;
public:
	void setFieldWidth(size_t newWidth);
	size_t getFieldWidth() const;
	static void setDelimiter(char newDelimiter);
	static char getDelimiter();
	std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
};

#endif // ! SDDS_UTILITIES_H