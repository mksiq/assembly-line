// Name:				Maickel Siqueira
// Seneca Student ID:	129337192
// Seneca email:		msiqueira@myseneca.ca
// Date of completion:	2020-11-21
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.t

#include "Workstation.h"

Workstation::Workstation(const std::string& record) : Station(record)
{
	m_pNextStation = nullptr;
}

void Workstation::runProcess(std::ostream& os)
{
	if (m_orders.size() != 0) 
		m_orders.front().fillItem(*this, os);
}

bool Workstation::moveOrder()
{
	if (m_orders.size() > 0 && m_orders.front().isItemFilled(this->getItemName())) {
		if (m_pNextStation) {
			*m_pNextStation += std::move(m_orders.front());
			m_orders.pop_front();
		}
		return true;
	}
	return false;
}

void Workstation::setNextStation(Station& station)
{
	m_pNextStation = dynamic_cast<Workstation*>(&station);
}

const Workstation* Workstation::getNextStation() const
{
	return m_pNextStation;
}
bool Workstation::getIfCompleted(CustomerOrder& order)
{
///if the order at the front of the queue is completed, this function removes
// from the queue, places it in the parameter and returns true; otherwise
// returns false. If the CustomerOrder queue is empty, returns false.
	if (m_orders.size() > 0 && m_orders.front().isOrderFilled()) {
		order = std::move(m_orders.front());
		m_orders.pop_front();		
		return true;
	}
	return false;
}

void Workstation::display(std::ostream& os) const
{
	os << getItemName() << " --> ";
	if (m_pNextStation)
		os << m_pNextStation->getItemName();
	else
		os << "END OF LINE";
	os << std::endl;		
}

Workstation& Workstation::operator+=(CustomerOrder&& order)
{
	m_orders.push_back(std::move(order));
	return *this;
}
