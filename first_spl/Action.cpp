#include "Action.h"



BaseAction::BaseAction()
{
}

ActionStatus BaseAction::getStatus() const
{
	return ActionStatus();
}

void BaseAction::complete()
{
	status = COMPLETED;
}

void BaseAction::error(std::string errorMsg)
{
	errorMsg = errorMsg;
	status = ERROR;
	std::cout <<"Error:"<< errorMsg << std::endl;
}

std::string BaseAction::getErrorMsg() const
{
	return errorMsg;
}

OpenTrainer::OpenTrainer(int id, std::vector<Customer*>& customersList):trainerId(id), customers(customersList)
{
	
}

void OpenTrainer::act(Studio& studio)
{
	if (studio.getNumOfTrainers() < trainerId || studio.getTrainer(trainerId)->isOpen())
		// I dont think we need to print it to the screen - we need to check about it
		std::cout << "Workout session does not exist or the trainer's workout session is already open" << std::endl	;
	Trainer* trainer = studio.getTrainer(trainerId);
	if (customers.size() + trainer->getCapacity() < trainer->getCustomers().size()) {
		trainer->openTrainer();
		for (int i = 0; i < customers.size(); i++)
			trainer->getCustomers().push_back(customers.at(i));
	}
	

}

std::string OpenTrainer::toString() const
{
	return "Trainer ";
}

Order::Order(int id) :trainerId(id)
{
}

void Order::act(Studio& studio)
{
	if (studio.getNumOfTrainers() < trainerId || studio.getTrainer(trainerId)->isOpen())
		std::cout << "error" << std::endl; // fixxxxx 
	else
	{
		Trainer* trainer = studio.getTrainer(trainerId);
		std::vector<Customer*> customers = trainer->getCustomers();
		for (int i = 0; i < customers.size(); i++) 
		{
			Customer* customer = customers.at(i);
			std::vector<int> result = customer->order(studio.getWorkoutOptions());
			std::cout << "order " << trainerId << std::endl;
			for (int j = 0; j < result.size(); j++)
				/// we should not print here
				std::cout << customer->getName() << " Is Doing " << studio.getWorkoutOptions().at(result.at(i)).getName() << std::endl;
		}
	}		
}

std::string Order::toString() const
{
	return std::string();
}

MoveCustomer::MoveCustomer(int src, int dst, int customerId):srcTrainer(src) , dstTrainer(dst), id(customerId)
{
	
}

void MoveCustomer::act(Studio& studio)
{
	//חסר בדיקת תקינות
	Trainer* trainerOrigin = studio.getTrainer(srcTrainer);
	Customer* customer = trainerOrigin->getCustomer(id);
	Trainer* trainerDst = studio.getTrainer(dstTrainer);
	trainerDst->addCustomer(customer);
	trainerOrigin->removeCustomer(id);
	std::vector<OrderPair>& orderList = trainerDst->getOrders();
	std::vector<OrderPair> toAdd;
	for (int i = 0; i < orderList.size(); i++) // moves the orders from trainerSrc to trainerDst
	{
		if (orderList.at(i).first == id) 
		{
			toAdd.push_back(OrderPair(orderList.at(i)));
			orderList.erase(orderList.begin() + i);
		}
	}
	if (trainerOrigin->getCustomers().size() == 0) // checks if the origin trainer has no customers 
		trainerOrigin->closeTrainer();


}

std::string MoveCustomer::toString() const
{
	return std::string();
}

Close::Close(int id):trainerId(id)
{

}

void Close::act(Studio& studio)
{
	//בדיקת תקינות
	Trainer* trainer = studio.getTrainer(trainerId);
	int salary = trainer->getSalary();
	// print the salary
	
	// open the trainer

}

std::string Close::toString() const
{
	return std::string();
}

CloseAll::CloseAll()
{
}

void CloseAll::act(Studio& studio)
{
}

std::string CloseAll::toString() const
{
	return std::string();
}

PrintWorkoutOptions::PrintWorkoutOptions()
{
}

void PrintWorkoutOptions::act(Studio& studio)
{
	std::vector<Workout> workouts = studio.getWorkoutOptions();
	for (int i = 0; i < workouts.size(); i++)
		std::cout << workouts[i].getName() << "," << workouts[i].getType() << "," << workouts[i].getPrice() << std::endl;
}

std::string PrintWorkoutOptions::toString() const
{
	return std::string();
}

PrintTrainerStatus::PrintTrainerStatus(int id):PrintTrainerStatus(id)
{
	
}

void PrintTrainerStatus::act(Studio& studio)
{
	
}

std::string PrintTrainerStatus::toString() const
{
	return std::string();
}

PrintActionsLog::PrintActionsLog()
{

}

void PrintActionsLog::act(Studio& studio)
{
}

std::string PrintActionsLog::toString() const
{
	return std::string();
}

RestoreStudio::RestoreStudio()
{
}

void RestoreStudio::act(Studio& studio)
{
}

std::string RestoreStudio::toString() const
{
	return std::string();
}

BackupStudio::BackupStudio()
{
}

void BackupStudio::act(Studio& studio)
{
}

std::string BackupStudio::toString() const
{
	return std::string();
}
