#ifndef STUDIO_H_
#define STUDIO_H_

#include <vector>
#include <string>
#include "Workout.h"
#include "Trainer.h"
#include "Action.h"
#include "Workout.h"
#include "Customer.h"
#include "Action.h"
#include <fstream>


class Studio {
public:
    Studio();
    Studio(const std::string& configFilePath);
    void start();
    int getNumOfTrainers() const;
    Trainer* getTrainer(int tid);
    const std::vector<BaseAction*>& getActionsLog() const; // Return a reference to the history of actions
    std::vector<Workout>& getWorkoutOptions();
    BaseAction* configureTheAction(std::string input); // takes string and return the right action
    Customer* createCustomer(int id, std::string name, std::string type);

private:
    bool open;
    std::vector<Trainer*> trainers;
    std::vector<Workout> workout_options;
    std::vector<BaseAction*> actionsLog;
};

#endif