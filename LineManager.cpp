// Name:				Maickel Siqueira
// Seneca Student ID:	129337192
// Seneca email:		msiqueira@myseneca.ca
// Date of completion:	2020-11-21
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <algorithm>
#include <fstream>
#include "LineManager.h"
#include "Utilities.h"

LineManager::LineManager(const std::string& fileName, std::vector<Workstation*>& workstations, std::vector<CustomerOrder>& orders)
{
	m_cntCustomerOrder = 0u;
	std::ifstream file(fileName);
	if (file) {
		for (size_t i = 0u; i < workstations.size(); ++i) {
			AssemblyLine.push_back(workstations[i]);
		}
		for (size_t i = 0u; i < orders.size(); ++i) {
			ToBeFilled.push_back(std::move(orders[i]));
		}
		m_cntCustomerOrder = orders.size();
		std::string record;
		Utilities util;
		while (std::getline(file, record)) {
			size_t next = 0;
			bool more = true;
			std::string firstStation = util.extractToken(record, next, more);
			std::string nextStation = util.extractToken(record, next, more);
			bool notFound = true;
			for (size_t i = 0u; i < AssemblyLine.size() && notFound; ++i) {
				if (AssemblyLine[i]->getItemName() == firstStation) {
					for (size_t j = 0u; j < AssemblyLine.size() && notFound; ++j) {
						if (AssemblyLine[j]->getItemName() == nextStation) {
							notFound = false;
							AssemblyLine[i]->setNextStation(*AssemblyLine[j]);						
						}
					}
				}
			}
		}
	}
	file.close();
}

bool LineManager::run(std::ostream& os)
{
	static size_t counter = 0u;
	os << "Line Manager Iteration: " << ++counter << "\n";

	Workstation* first = getFirstStation();
	if (ToBeFilled.size() > 0) {
		*first += std::move(ToBeFilled.front());
		ToBeFilled.pop_front();
	}

	// Loop through all stations on the assembly line and run one cycle of the station's process
	for (size_t i = 0u; i < AssemblyLine.size(); ++i)
		AssemblyLine[i]->runProcess(os);

	//Loop through all stations on the assembly lineand move the CustomerOrder objects down the line
	for (size_t i = 0u; i < AssemblyLine.size(); ++i) {
		AssemblyLine[i]->moveOrder();
		//Checks if completed, if so move to Completed deque
		CustomerOrder complete;
		if (AssemblyLine[i]->getIfCompleted(complete)) {
			Completed.push_back(std::move(complete));
		}
	}

	return m_cntCustomerOrder == Completed.size();
}

void LineManager::displayCompletedOrders(std::ostream& os) const
{
	std::for_each(Completed.begin(), Completed.end(), [&](const CustomerOrder& order)
		{
			order.display(os);
		});
}

void LineManager::displayStations() const
{
	std::for_each(AssemblyLine.begin(), AssemblyLine.end(), [&](Workstation* station)
		{
			station->display(std::cout);
		});
}

void LineManager::displayStationsSorted() const
{
	Workstation* first = getFirstStation();
	const Workstation* nextStation = first;
	while(nextStation) {
		nextStation->display(std::cout);
		nextStation = nextStation->getNextStation();
	}
}

Workstation* LineManager::getFirstStation() const
{
	// Finds the station that is not pointed by any other station
	Workstation* first = nullptr;
	bool found = false;
	for (size_t i = 0u; i < AssemblyLine.size() && !found; ++i) {
		bool hasPrevious = false;
		if (AssemblyLine[i]->getNextStation()) {
			for (size_t j = 0u; j < AssemblyLine.size() && !hasPrevious; ++j) {
				if (AssemblyLine[i]->getNextStation()) {
					if (AssemblyLine[j]->getNextStation() && AssemblyLine[i]->getItemName() == AssemblyLine[j]->getNextStation()->getItemName()) {
						hasPrevious = true;
					}
					if (!hasPrevious && j == AssemblyLine.size() - 1) {
						found = true;
						first = AssemblyLine[i];
					}
				}
			}
		}
		else {
			// if next station is nullptr then in case there is not a single station
			// So, it would not work for a single station Assembly line
			hasPrevious = true;
		}
	}
	return first;
}