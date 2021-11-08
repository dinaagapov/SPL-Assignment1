#include "Studio.h"
#include <fstream>

Studio::Studio() :open(false)
{
	
}

Studio::Studio(const std::string& configFilePath):open(false)
{
}


void Studio::start()
{

	std::fstream newfile;
	newfile.open("ExmapleInput.txt", std::ios::out);
	if (newfile.is_open()) {   //checking whether the file is open
		std::string tp;
		open = true;
		std::cout << "Studio is now open" << std::endl;
		while (getline(newfile, tp))
		{
			if (tp == "# Number of trainers") {
				getline(newfile, tp);
				///

			}
			if (tp == "# Traines") {
				getline(newfile, tp);

				///

			}
			if (tp == "# Work Options") {
				getline(newfile, tp);
				///

			}
		}
		open = false;
		newfile.close();
	}
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
