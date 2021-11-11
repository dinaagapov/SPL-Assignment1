#include "Trainer.h"

Trainer::Trainer(int t_capacity) :capacity(t_capacity), open(false)
{
}



int Trainer::getCapacity() const
{
	return capacity;
}

void Trainer::addCustomer(Customer* customer)
{
	customersList.push_back(customer);
}

void Trainer::removeCustomer(int id)
{
	if (id < customersList.size()) {
		Customer* customer = customersList[id];
		customersList.erase(customersList.begin() + id);
		delete customer;
	}
	
}

Customer* Trainer::getCustomer(int id)
{
	auto iter = customersList.begin();
		for (; iter != customersList.end(); iter++)
		{
			if ((*iter)->getId() == id)
				return *iter;
		}
}

std::vector<Customer*>& Trainer::getCustomers()
{
	// TODO: insert return statement here
}

std::vector<OrderPair>& Trainer::getOrders()
{
	// TODO: insert return statement here
}

void Trainer::order(const int customer_id, const std::vector<int> workout_ids, const std::vector<Workout>& workout_options)
{
}

void Trainer::openTrainer()
{
	open = true;
}

void Trainer::closeTrainer()
{
	open = false;
}

int Trainer::getSalary()
{
	int salary = 0;
	auto iter = orderList.begin();
	for (; iter != orderList.end(); iter++)
	{
		salary = ((*iter).second.getPrice()) + salary;
	}
	return salary;
}
bool Trainer::isOpen()
{
	return open;
}
