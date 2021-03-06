// Name:				Maickel Siqueira
// Seneca Student ID:	129337192
// Seneca email:		msiqueira@myseneca.ca
// Date of completion:	2020-11-12
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef CUSTOMERORDER_H
#define CUSTOMERORDER_H

#include <string>
// Name:				Maickel Siqueira
// Seneca Student ID:	129337192
// Seneca email:		msiqueira@myseneca.ca
// Date of completion:	2020-11-21
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "Station.h"

struct Item
{
	std::string m_itemName;
	unsigned int m_serialNumber = 0;
	bool m_isFilled = false;
	Item(const std::string& src) : m_itemName(src)
	{
	};
};

class CustomerOrder
{
	std::string m_name;
	std::string m_product;
	unsigned int m_cntItem;
	Item** m_lstItem;
	static size_t m_widthField;
public:
	CustomerOrder();
	CustomerOrder(const std::string& record);
	CustomerOrder(const CustomerOrder& source);
	CustomerOrder(CustomerOrder&& source) noexcept;
	~CustomerOrder();
	CustomerOrder& operator=(const CustomerOrder& source) = delete;
	CustomerOrder& operator=(CustomerOrder&& source) noexcept;
	bool isOrderFilled() const;
	bool isItemFilled(const std::string& itemName) const;
	void fillItem(Station& station, std::ostream& os);
	void display(std::ostream& os) const;
};

#endif // !CUSTOMERORDER_H
