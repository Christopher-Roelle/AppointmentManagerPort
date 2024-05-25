#ifndef APPOINTMENTSERVICE_H
#define APPOINTMENTSERVICE_H

#include "Appointment.h"
#include <vector>
#include <memory>
#include <string>
#include <iostream>
#include <sstream>
#include <chrono>
#include <iomanip>
#include <random>
#include "ContactService.h"

class AppointmentService
{
private:
	std::vector<Appointment> appointmentList;

	std::string NewUniqueID();

public:
	void NewAppointment(std::string& cid);
	void NewAppointment(std::string& id, std::string& cid);
	void NewAppointment(std::string& id, std::string& cid, std::chrono::system_clock::time_point date);
	void NewAppointment(std::string& id, std::string& cid, std::chrono::system_clock::time_point date, std::string& desc);

	bool DeleteAppointment(std::string& id);

	//Getters
	void GetAppointmentByID(std::string& id);
	void GetAllAppointments();

	int GetListSize();

};

#endif // !APPOINTMENTSERVICE_H