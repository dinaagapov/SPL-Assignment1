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
	return trainers.size(); // fix
}

Trainer* Studio::getTrainer(int tid)
{
	auto iter = trainers.begin();
	for (; iter != trainers.end(); iter++)
	{
		if ((*iter)->id == tid)
			return *iter;
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
