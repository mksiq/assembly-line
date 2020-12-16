// Name:				Maickel Siqueira
// Seneca Student ID:	129337192
// Seneca email:		msiqueira@myseneca.ca
// Date of completion:	2020-11-21
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iomanip>
#include "Station.h"
#include "Utilities.h"
size_t Station::m_widthField = 0u;
size_t Station::id_generator = 0u;

Station::Station(const std::string& record)
{
	size_t next = 0;
	bool more = true;
	Utilities util;

	m_name = util.extractToken(record, next, more);

	if(more)
		m_nextSerial = std::stoi(util.extractToken(record, next, more));
	if(more)
		m_quantity = std::stoi(util.extractToken(record, next, more));
	if(more)
		m_description = util.extractToken(record, next, more);

	m_widthField = m_widthField < m_name.size() ? m_name.size() : m_widthField;

	m_id = ++id_generator;
}
const std::string& Station::getItemName() const
{
	return m_name;
}
unsigned int Station::getNextSerialNumber()
{
	return m_nextSerial++;
}
unsigned int Station::getQuantity() const
{
	return m_quantity;
}
void Station::updateQuantity()
{
	if (m_quantity > 0) m_quantity--;
}
void Station::display(std::ostream& os, bool full) const
{
	os << "[" << std::setfill('0') << std::setw(3) << m_id << "] Item: " <<
		std::setfill(' ') << std::setw(m_widthField) << std::left << m_name
		<< " [" << std::right << std::setfill('0') << std::setw(6) <<
		m_nextSerial << "]" << std::setfill(' ');
	if (full) {
		os << " Quantity: " << std::setw(m_widthField) << std::left <<
			m_quantity << std::right << " Description: " << m_description;
	}
	os << "\n";
}