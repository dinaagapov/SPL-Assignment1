#include "Trainer.h"

Trainer::Trainer(int t_capacity):capacity(t_capacity)
{
}



int Trainer::getCapacity() const
{
	return capacity;
}

void Trainer::addCustomer(Customer* customer)
{
	
}

void Trainer::removeCustomer(int id)
{
}

Customer* Trainer::getCustomer(int id)
{
	return nullptr;
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
}

void Trainer::closeTrainer()
{
}

int Trainer::getSalary()
{
	return 0;
}

bool Trainer::isOpen()
{
	return false;
}
