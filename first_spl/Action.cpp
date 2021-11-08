#include "Action.h"
//test
BaseAction::BaseAction()
{
}

ActionStatus BaseAction::getStatus() const
{
	return ActionStatus();
}

void BaseAction::complete()
{
}

void BaseAction::error(std::string errorMsg)
{
}

std::string BaseAction::getErrorMsg() const
{
	return std::string();
}

OpenTrainer::OpenTrainer(int id, std::vector<Customer*>& customersList)
{
}

void OpenTrainer::act(Studio& studio)
{
}

std::string OpenTrainer::toString() const
{
	return std::string();
}

Order::Order(int id)
{
	return new Order();
}

void Order::act(Studio& studio)
{
}

std::string Order::toString() const
{
	return std::string();
}

MoveCustomer::MoveCustomer(int src, int dst, int customerId)
{
}

void MoveCustomer::act(Studio& studio)
{
}

std::string MoveCustomer::toString() const
{
	return std::string();
}

Close::Close(int id)
{
}

void Close::act(Studio& studio)
{
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
}

std::string PrintWorkoutOptions::toString() const
{
	return std::string();
}

PrintTrainerStatus::PrintTrainerStatus(int id)
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
