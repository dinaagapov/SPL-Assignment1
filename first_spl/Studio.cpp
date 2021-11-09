#include "Studio.h"
#include <fstream>
#include <sstream>
using namespace std;

Studio::Studio() :open(false)
{
	
}

Studio::Studio(const std::string& configFilePath):open(false)
{
	std::fstream newfile;
	newfile.open(configFilePath, std::ios::out);
	if (newfile.is_open()) {   //checking whether the file is open
		std::string tp;

		while (getline(newfile, tp))
		{
			if (tp == "# Number of trainers") 
			{
				getline(newfile, tp);
				int numbersOfTrainers = stoi(tp);

			}
			if (tp == "# Traines")
			{
				std::vector<int> vect;

				std::stringstream ss(tp);

				for (int i; ss >> i;)
				{
					vect.push_back(i);
					if (ss.peek() == ',')
						ss.ignore();
				}

				for (std::size_t i = 0; i < vect.size(); i++)
				{
					Trainer* tr = new Trainer(vect[i]);
					trainers.push_back(tr);
				}
				
			}
			if (tp == "# Work Options")
			{
				getline(newfile, tp);
				/// missing
				
			}
		}
		newfile.close();
	}
}


void Studio::start()
{
	string input = "";
	open = true;
	std::cout << "Studio is now open" << std::endl;
	while (input != "closeAll")
	{
		// missing *arguments* for the constructors and the *act function *
		if (input == "open triner")
		{
			OpenTrainer* openTrainer = new OpenTrainer();
			openTrainer->act(*this);
		}

		else if (input == "order") 
		{
			Order* order = new Order();
			order->act(*this);
		}

		else if (input == "move customer") 
		{
			MoveCustomer* moveCustomer = new MoveCustomer();
			moveCustomer->act(*this);
		}

		else if (input == "close")
		{
			Close* close = new Close();
			close->act(*this);
		}
		else if (input == "print Trainer Status") 
		{
			PrintTrainerStatus* printTrainerStatus = new PrintTrainerStatus();
			printTrainerStatus->act(*this);
		}

		else if (input == "print workout options")
		{
			PrintWorkoutOptions* printWorkOutOptions = new PrintWorkoutOptions();
			printWorkOutOptions->act(*this);
		}

	}
	CloseAll();
	open = false;
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
	return workout_options;

}
