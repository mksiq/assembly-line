// Name:				Maickel Siqueira
// Seneca Student ID:	129337192
// Seneca email:		msiqueira@myseneca.ca
// Date of completion:	2020-11-21
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef WORKSTATION_H
#define WORKSTATION_H

#include <deque>
#include <iostream>
#include "CustomerOrder.h"
#include "Station.h"

class Workstation : public Station
{
	std::deque<CustomerOrder> m_orders;
	Workstation* m_pNextStation;
public:
	Workstation(const std::string& record);
	Workstation(const Workstation&) = delete;
	Workstation(Workstation&&) = delete;
	~Workstation(){}
	Workstation& operator=(Workstation&&) = delete;
	Workstation & operator=(const Workstation&) = delete;
	void runProcess(std::ostream& os);
	bool moveOrder();
	void setNextStation(Station& station);
	const Workstation* getNextStation() const;
	bool getIfCompleted(CustomerOrder& order);
	void display(std::ostream& os) const;
	Workstation& operator+=(CustomerOrder&&);
};

#endif // !WORKSTATION_H
