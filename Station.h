// Name:				Maickel Siqueira
// Seneca Student ID:	129337192
// Seneca email:		msiqueira@myseneca.ca
// Date of completion:	2020-11-21
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef STATION_H
#define STATION_H
#include <string>

class Station
{
	size_t m_id;
	std::string m_name;
	std::string m_description;
	size_t m_nextSerial;
	size_t m_quantity;
	static size_t m_widthField;
	static size_t id_generator;
public:
	Station(const std::string& record);
	const std::string& getItemName() const;
	unsigned int getNextSerialNumber();
	unsigned int getQuantity() const;
	void updateQuantity();
	void display(std::ostream& os, bool full) const;
	virtual ~Station()
	{
	};
};
#endif // !STATION_H