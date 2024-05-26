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

//Header for the Service that manages the Appointments
class AppointmentService
{
private:
	std::vector<Appointment> appointmentList;

	std::string NewUniqueID();

	//Constructor (Singleton)
	AppointmentService();

public:
	static AppointmentService& GetInstance();

	//Removing copy constructor/assignment
	//AppointmentService(const AppointmentService&) = delete;
	//void operator=(const AppointmentService&) = delete;

	void NewAppointment(std::string& cid);
	void NewAppointment(std::string& id, std::string& cid);
	void NewAppointment(std::string& id, std::string& cid, std::chrono::system_clock::time_point date);
	void NewAppointment(std::string& id, std::string& cid, std::chrono::system_clock::time_point date, std::string& desc);

	bool DeleteAppointment(std::string& id);

	bool UpdateAppointmentDate(std::string& id, std::chrono::system_clock::time_point date);

	//Getters
	Appointment GetAppointmentByID(std::string& id);
	void GetAllAppointments();

	int GetListSize();

};

#endif // !APPOINTMENTSERVICE_H