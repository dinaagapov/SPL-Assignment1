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
	bool flag1 = false;
	bool flag2 = false;
	bool flag3 = false;
	int idW = 0;
	int numberOfTrainers;
	std::ifstream file(configFilePath);
	string clean = "";
	if (file.is_open())
	{
		std::string line;
		while (getline(file, line))
		{
			if (!line.empty())
				continue;
			else if (line == "# Number of trainers")
				flag1 = true;
			else if (flag1) {
				numberOfTrainers = stoi(line);
				flag1 = false;
			}
			else if (line == "# Traines")
				flag2 = true;
			else if (flag2)
			{
				std::vector<int> vect;
				std::stringstream ss(line);
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
					Workout workout(idW, result[0], stoi(result[2]), result[3]);
					workout_options.push_back(workout);
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
		configureTheAction(input)->act(*this);
		

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
		string costumers = input.substr(8);
		vector<string> result;
		stringstream s_stream(costumers);
		while (s_stream.good())
		{
			string substr;
			getline(s_stream, substr, ' ');
			result.push_back(substr);
		}
		string name = "";
		string type = "";
		bool findComma = false;
		std::vector<Customer*> customerList;
			for (int i = 0; i < result.size() && !findComma; i++)
			{
				int indexComma = 0;
				while (result[i].at(indexComma) != ',')
				{

					if (result[i].at(indexComma) == ',')
					{
						findComma = true;
						string name = result[i].substr(0, indexComma);
						string type = result[i].substr(indexComma + 1, result[i].size() - (indexComma + 1));
						Customer* customer = createCustomer(id, name, type);
						customerList.push_back(customer);
					}
					else
						indexComma++;
				}
				id++;

			}

			OpenTrainer* openTrainer = new OpenTrainer(numOfTrainer, customerList);
			openTrainer->act(*this);
			actionsLog.push_back(openTrainer);
	}

	else if (input.substr(0, 5) == "order")
	{
		string numOfTrainerString = input.substr(6, 1);
		int numOfTrainer = stoi(numOfTrainerString);
		Order* order = new Order(numOfTrainer);
		order->act(*this);
		actionsLog.push_back(order);

	}

	else if (input.substr(0, 13) == "move customer")
	{
		string numOfTrainerOriginString = input.substr(5, 1);
		string numOfTrainerDesString = input.substr(7, 1);
		string numOfCustomerString = input.substr(9, 1);
		int numOfTrainerOrigin = stoi(numOfTrainerOriginString);
		int numOfTrainerDes = stoi(numOfTrainerDesString);
		int numOfTrainerCustomer = stoi(numOfCustomerString);

		MoveCustomer* moveCustomer = new MoveCustomer(numOfTrainerOrigin,
			numOfTrainerDes, numOfTrainerCustomer);
		moveCustomer->act(*this);
		actionsLog.push_back(moveCustomer);

	}

	else if (input.substr(0, 5) == "close")
	{
		string numOfTrainerString = input.substr(6, 1);
		int numOfTrainer = stoi(numOfTrainerString);
		Close* close = new Close(numOfTrainer);
		close->act(*this);
		actionsLog.push_back(close);
	}
	else if (input.substr(0, 16) == "print Trainer Status")
	{
		string numOfTrainerString = input.substr(8, 1);
		int numOfTrainer = stoi(numOfTrainerString);
		PrintTrainerStatus* printTrainerStatus = new PrintTrainerStatus();
		printTrainerStatus->act(*this);
		actionsLog.push_back(printTrainerStatus);
	}

	else if (input.substr(0, 15) == "print workout options")
	{
		string numOfTrainerString = input.substr(15, 1);
		int numOfTrainer = stoi(numOfTrainerString);
		PrintWorkoutOptions* printWorkOutOptions = new PrintWorkoutOptions();
		printWorkOutOptions->act(*this);
		actionsLog.push_back(printWorkOutOptions);
	}
	else if (input.substr(0, 7) == "backup")
	{

		//not implemented
	}
	else if (input.substr(0, 8) == "restore")
	{
	//not implemented

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


	