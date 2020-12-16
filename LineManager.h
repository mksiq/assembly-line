// Name:				Maickel Siqueira
// Seneca Student ID:	129337192
// Seneca email:		msiqueira@myseneca.ca
// Date of completion:	2020-11-21
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef LINEMANAGER_H
#define LINEMANAGER_H

#include <vector>
#include "Workstation.h"

class LineManager
{
	std::vector<Workstation*> AssemblyLine;
	std::deque<CustomerOrder> ToBeFilled;
	std::deque<CustomerOrder> Completed;
	unsigned int m_cntCustomerOrder;
	Workstation* getFirstStation() const ;
public:
	LineManager(const std::string& fileName, std::vector<Workstation*>& workstations, std::vector<CustomerOrder>& orders);
	bool run(std::ostream& os);
	void displayCompletedOrders(std::ostream& os) const;
	void displayStations() const;
	void displayStationsSorted() const;
};

#endif
