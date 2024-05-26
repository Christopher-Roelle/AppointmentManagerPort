#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include <string>
#include <chrono>
#include <iostream>
#include <stdexcept>
#include <format>
#include <ctime>
#include <iomanip>
#include <sstream>
#include "ContactService.h"

//Header for the Appointment Class
class Appointment
{
private:
	static constexpr size_t APPOINTMENT_ID_LENGTH = 10;
	static constexpr size_t APPOINTMENT_DESC_LENGTH = 50;
	const std::string INITIALIZER = "INITIAL";
	
	std::string appointmentID;
	std::string contactID;
	std::chrono::system_clock::time_point dateOfAppointment;
	std::string description;

public:
	//Error Constructor
	Appointment();

	Appointment(std::string& cid);
	Appointment(std::string& id, std::string& cid);
	Appointment(std::string& id, std::string& cid, std::chrono::system_clock::time_point date);
	Appointment(std::string& id, std::string& cid, std::chrono::system_clock::time_point date, std::string& desc);

	//Methods
	void UpdateAppointmentID(std::string& id);
	void UpdateDate(const std::chrono::system_clock::time_point &date);
	void UpdateDesc(std::string& newDesc);

	//Getters
	std::string GetAppointmentID() const;
	std::string GetContactID() const;
	std::chrono::system_clock::time_point GetDateOfAppointment() const;
	std::string GetDescription() const;

	void PrintAppointment();

	//Helpers
	bool IsValidDate(std::chrono::system_clock::time_point date, bool displayMessage);
};

#endif // !APPOINTMENT_H
