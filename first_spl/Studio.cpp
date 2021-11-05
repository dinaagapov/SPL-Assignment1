#include "Studio.h"

Studio::Studio()
{
}

Studio::Studio(const std::string& configFilePath)
{

}


void Studio::start()
{

	std::cout << "Studio is now open" << std::endl;
}


int Studio::getNumOfTrainers() const
{
	return trainers.size();
}

Trainer* Studio::getTrainer(int tid)
{
	Trainer* tr = nullptr;
	bool found = false;
	for(int i = 0 ; i < trainers.size() && !found; i++)
	{
		 tr = (trainers)[i];
		 

	}
}
const std::vector<BaseAction*>& Studio::getActionsLog() const
{
	// TODO: insert return statement here
}

std::vector<Workout>& Studio::getWorkoutOptions()
{
	// TODO: insert return statement here
}
