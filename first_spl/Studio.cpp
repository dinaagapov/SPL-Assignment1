#include "Studio.h"
#include <fstream>
#include <sstream>
#include <cstring> 

using namespace std;

Studio::Studio() :open(false)
{
	
}

Studio::Studio(const std::string& configFilePath) : open(false)
{
	bool flag1 = false;  // flag1 true if we get to line # Number of trainers
	bool flag2 = false; // flag2 true if we get to line # Traines
	bool flag3 = false; // flag3 true if we get to line # Work Options
	int idW;
	int numberOfTrainers;
	std::ifstream file(configFilePath); 
	if (file.is_open())
	{
		std::string line;
		int idW = 0;
		while (getline(file, line))
		{
			if (!line.empty())
				continue;
			else if (line == "# Number of trainers")
				flag1 = true;
			else if (flag1) {
				numberOfTrainers = stoi(line); // converts to int
				flag1 = false;
			}
			else if (line == "# Traines")
				flag2 = true;
			else if (flag2)
			{
				std::vector<int> vect;
				std::stringstream ss(line);
				for (int i; ss >> i;) // removes all the commas - ','
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
				flag2 = false;
			}
			else if (line == "# Work Options")
				flag3 = true;
			else if (flag3)
			{
				vector<string> result;
				stringstream s_stream(line);
				while (s_stream.good())
				{
					string substr;
					getline(s_stream, substr, ',');
					result.push_back(substr);
					// NEED TO CONVERT STRING TO ENUM
					int enumType;
					if (result[3] == "Anaerobic")
						enumType = 1;
					else if (result[3] == "Mixed")
						enumType = 2;
					else
						enumType = 3;
					workout_options.push_back(Workout(idW, result[0], stoi(result[2]), WorkoutType(enumType)));
					idW = idW + 1;
				}
			}

		}
	}
}


void Studio::start()
{
	string input = "";
	open = true;
	std::cout << "Studio is now open" << std::endl;
	while (input != "closeAll")
	{
		cin >> input;
		BaseAction* action = configureTheAction(input);
		action->act(*this);
		actionsLog.push_back(action);
	}
	CloseAll* closeAll = new CloseAll();
	closeAll->act(*this);
	open = false;
}


int Studio::getNumOfTrainers() const
{
	return trainers.size();
}

Trainer* Studio::getTrainer(int tid)
{
	if (tid >= trainers.size())
		return nullptr;
	else
		return trainers[tid];

}
const std::vector<BaseAction*>& Studio::getActionsLog() const
{
	return actionsLog; 
}

std::vector<Workout>& Studio::getWorkoutOptions()
{
	return workout_options;

}

BaseAction* Studio::configureTheAction(std::string input)
{
	int id = 0;
	if (input.substr(0, 4) == "open")
	{
		string numOfTrainerString = input.substr(6, 1);
		int numOfTrainer = stoi(numOfTrainerString);
		string costumers = input.substr(7);
		vector<string> result;
		stringstream s_stream(costumers);
		while (s_stream.good()) // seperate the line to <name1>,<strategy1>
		{
			string substr;
			getline(s_stream, substr, ' ');
			result.push_back(substr);
		}
		string name = "";
		string type = "";
		bool findComma = false;
		std::vector<Customer*> customerList;
		// here we want to find the index of the comma in <name1>,<strategy1>
			for (int i = 0; i < result.size() && !findComma; i++)
			{
				int indexComma = 0;
				while (result[i].at(indexComma) != ',')
				{

					if (result[i].at(indexComma) == ',')
					{
						findComma = true;
						string name = result[i].substr(0, indexComma);
						string type = result[i].substr(indexComma + 1);
						Customer* customer = createCustomer(id, name, type);
						customerList.push_back(customer);
					}
					else
						indexComma++;
				}
				id++;

			}

			OpenTrainer* openTrainer = new OpenTrainer(numOfTrainer, customerList);
			return openTrainer;
	}

	else if (input.substr(0, 5) == "order")
	{
		string numOfTrainerString = input.substr(7, 1);
		int numOfTrainer = stoi(numOfTrainerString);
		Order* order = new Order(numOfTrainer);
		return order;

	}

	else if (input.substr(0, 4) == "move")
	{
		string numOfTrainerOriginString = input.substr(5, 1);
		string numOfTrainerDesString = input.substr(7, 1);
		string numOfCustomerString = input.substr(9, 1);
		int numOfTrainerOrigin = stoi(numOfTrainerOriginString);
		int numOfTrainerDes = stoi(numOfTrainerDesString);
		int numOfTrainerCustomer = stoi(numOfCustomerString);

		MoveCustomer* moveCustomer = new MoveCustomer(numOfTrainerOrigin,
			numOfTrainerDes, numOfTrainerCustomer);
		return moveCustomer;

	}

	else if (input.substr(0, 5) == "close")
	{
		string numOfTrainerString = input.substr(6, 1);
		int numOfTrainer = stoi(numOfTrainerString);
		Close* close = new Close(numOfTrainer);
		return close;
	}
	else if (input.substr(0, 6) == "status")
	{
		string numOfTrainerString = input.substr(7, 1);
		int numOfTrainer = stoi(numOfTrainerString);
		PrintTrainerStatus* printTrainerStatus = new PrintTrainerStatus(numOfTrainer);
		return printTrainerStatus;
	}

	else if (input.substr(0, 15) == "workout_options")
	{
	
		PrintWorkoutOptions* printWorkOutOptions = new PrintWorkoutOptions();
		return printWorkOutOptions;
	}
	else if (input.substr(0, 3) == "log")
	{
		PrintActionsLog* printActionsLog = new PrintActionsLog();
		return printActionsLog;
	}
	else if (input.substr(0, 6) == "backup")
	{
		BackupStudio* backup = new BackupStudio();
		return backup;
	}
	else if (input.substr(0, 7) == "restore") {
		RestoreStudio* restore = new RestoreStudio();
		return restore;
	
	}
}

Customer* Studio::createCustomer(int id, std::string name, std::string type)
{
	if (type == "swp") {
		SweatyCustomer* sweat = new SweatyCustomer(name, id);
		return sweat;
	}
	else if (type == "chp") {
		CheapCustomer* cheap = new CheapCustomer(name, id);
		return cheap;
	}
	else if (type == "mcl") {
		HeavyMuscleCustomer* muscle = new HeavyMuscleCustomer(name, id);
		return muscle;
	}
	else if (type == "fbd") {
		FullBodyCustomer* fullBody = new FullBodyCustomer(name, id);
		return fullBody;
	}
}


	