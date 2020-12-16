// Name:				Maickel Siqueira
// Seneca Student ID:	129337192
// Seneca email:		msiqueira@myseneca.ca
// Date of completion:	2020-11-21
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include "CustomerOrder.h"
#include "Utilities.h"

size_t CustomerOrder::m_widthField = 0u;

CustomerOrder::CustomerOrder()
{
	m_name = "";
	m_product = "";
	m_cntItem = 0u;
	m_lstItem = nullptr;
}

CustomerOrder::CustomerOrder(const std::string& record) : CustomerOrder()
{
	size_t next = 0u;
	bool more = true;
	Utilities util;

	m_name = util.extractToken(record, next, more);

	if(more)
		m_product = util.extractToken(record, next, more);

	

	while(more) {
		Item** temp = new Item*[m_cntItem + 1];
		for (size_t i = 0u; i < m_cntItem; i++) {
			temp[i] = m_lstItem[i];
		}
		delete[] m_lstItem;
		m_lstItem = temp;
		m_lstItem[m_cntItem] = new Item(util.extractToken(record, next, more));

		m_widthField = m_widthField < m_lstItem[m_cntItem]->m_itemName.size() ?
												m_lstItem[m_cntItem]->m_itemName.size() : m_widthField;
		m_cntItem++;
	}	
}

CustomerOrder::CustomerOrder(const CustomerOrder& source) 
{
	throw "Invalid Operation";
}

CustomerOrder::CustomerOrder(CustomerOrder&& source) noexcept : CustomerOrder()
{
	*this = std::move(source);
}

CustomerOrder::~CustomerOrder()
{
	for (size_t i = 0; i < m_cntItem; i++)
		delete m_lstItem[i];

	delete[] m_lstItem;
}

CustomerOrder& CustomerOrder::operator=(CustomerOrder&& source) noexcept
{
	if (this != &source) {
		for (size_t i = 0; i < m_cntItem; i++)
			delete m_lstItem[i];

		delete[] m_lstItem;
		m_name = source.m_name;
		m_product = source.m_product;
		m_cntItem = source.m_cntItem;
		m_lstItem = source.m_lstItem;
		source.m_lstItem = nullptr;
		source.m_cntItem = 0u;
	}
	return *this;
}

bool CustomerOrder::isOrderFilled() const
{
	return std::all_of(m_lstItem, m_lstItem + m_cntItem,
		[=](Item* item){ return item->m_isFilled;});
}

bool CustomerOrder::isItemFilled(const std::string& itemName) const
{
	bool isFilled = true;
	std::for_each(m_lstItem, m_lstItem + m_cntItem,
		[&](const Item* item)
		{
			if (item->m_itemName == itemName) isFilled = item->m_isFilled;
		});
	return isFilled;
}

void CustomerOrder::fillItem(Station& station, std::ostream& os)
{
	std::transform(m_lstItem, m_lstItem + m_cntItem, m_lstItem, [&](Item* item)
		{
			if (item->m_itemName == station.getItemName()) {
				if(station.getQuantity() > 0){
					station.updateQuantity();
					item->m_serialNumber = station.getNextSerialNumber();
					item->m_isFilled = true;
					os.width(m_widthField-1);
					os << "Filled " << m_name << ", " << m_product << " [" << item->m_itemName << "]\n";
				}
				else {
					os << "Unable to fill " << m_name << ", " << m_product << "[" << item->m_itemName << "]\n";
				}				
			} 
			return item;
		});	
}

void CustomerOrder::display(std::ostream& os) const
{
	os << m_name << " - " << m_product << "\n";
	std::for_each(m_lstItem, m_lstItem + m_cntItem, [&](const Item* item)
		{
			os << "[" << std::setfill('0') << std::setw(6) << item->m_serialNumber << "] " <<
				std::setfill(' ') << std::setw(m_widthField) << std::left << item->m_itemName
				<< "     - " << std::right;
			if (item->m_isFilled)
				os << "FILLED\n";
			else
				os << "MISSING\n";
		});
}