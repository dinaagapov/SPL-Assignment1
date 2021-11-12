#include "Customer.h"
#include<iostream>
#include<vector> // for vectors
#include<iterator> // for iterators
#include <algorithm>

Customer::Customer(std::string c_name, int c_id):name(c_name),id(c_id)
{
}

std::string Customer::getName() const
{
	return name;
}

int Customer::getId() const
{
	return id;
}




FullBodyCustomer::FullBodyCustomer(std::string name, int id) : Customer(name,id)
{

}

std::vector<int> FullBodyCustomer::order(const std::vector<Workout>& workout_options)
{
	int priceCardio = 0;
	int idCardio = -1;
	int priceMix = 0;
	int idMix = -1;
	int priceAna = 0;
	int idAna = -1;
	std::vector<int> output;
	auto iter = workout_options.begin();
	for (; iter != workout_options.end(); iter++)
	{
		if ((*iter).getType() == CARDIO &&(idCardio == -1 || ((*iter).getPrice() < priceCardio)))
		{
			priceCardio = ((*iter).getPrice());
			idCardio = ((*iter).getId());
		}
		else if ((*iter).getType() == MIXED && (idMix == -1 || ((*iter).getPrice() > priceMix)))
		{
			priceMix = ((*iter).getPrice());
			idMix = ((*iter).getId());
		}
		else if((*iter).getType() == CARDIO && (idAna == -1 || ((*iter).getPrice() < priceAna)))
		{
				priceAna = ((*iter).getPrice());
				idAna = ((*iter).getId());
		}
		
	}
	if (idCardio != -1)
		output.push_back(idCardio);
	if (idMix != -1)
		output.push_back(idMix);
	if (idAna!= -1)
		output.push_back(idAna);
	return output;
}
	


std::string FullBodyCustomer::toString() const
{
	return getName()+",fbd";;
}

HeavyMuscleCustomer::HeavyMuscleCustomer(std::string name, int id) : Customer(name, id)
{
}

std::vector<int> HeavyMuscleCustomer::order(const std::vector<Workout>& workout_options)
{
	// not sure it is good - I wanted to sort the vec by the price;
	std::sort(workout_options.begin(), workout_options.end()); 
	// reverse the vector to start from the most expensive
	reverse(workout_options.begin(), workout_options.end());

	std::vector<int> output;
	auto iter = workout_options.begin();
	for (; iter != workout_options.end(); iter++)
	{
		if ((*iter).getType() == ANAEROBIC)
		{
			output.push_back((*iter).getId());
		}
	}
	return output;
}



std::string HeavyMuscleCustomer::toString() const
{
	return getName()+ ",mcl";;
}

CheapCustomer::CheapCustomer(std::string name, int id) : Customer(name, id)
{
}

std::vector<int> CheapCustomer::order(const std::vector<Workout>& workout_options)
{
	std::sort(workout_options.begin(), workout_options.end());
	int minID = -1;
	int minPrice = -1;
	std::vector<int> output;
	auto iter = workout_options.begin();
	for (; iter != workout_options.end(); iter++)
	{
		if (minID == -1 || (*iter).getPrice() < minPrice)
		{
			minPrice = (*iter).getPrice();
			minID = (*iter).getId();
		}
	}
	output.push_back(minID);
	return output;
}

std::string CheapCustomer::toString() const
{
	return getName() + ",chp";
}

SweatyCustomer::SweatyCustomer(std::string name, int id) : Customer(name, id)
{
}

std::vector<int> SweatyCustomer::order(const std::vector<Workout>& workout_options)
{
	std::vector<int> output;
	auto iter = workout_options.begin();
	for (; iter != workout_options.end(); iter++)
	{
		if ((*iter).getType() == CARDIO)
		{
			output.push_back((*iter).getId());
		}
	}
	return output;
}

std::string SweatyCustomer::toString() const
{
	return getName() + ",swp";
}
