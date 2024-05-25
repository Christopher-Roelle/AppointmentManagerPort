#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include <string>
#include <chrono>
#include <iostream>
#include <stdexcept>

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
	Appointment(std::string& cid);
	Appointment(std::string& id, std::string& cid);
	Appointment(std::string& id, std::string& cid, std::chrono::system_clock::time_point date);
	Appointment(std::string& id, std::string& cid, std::chrono::system_clock::time_point date, std::string& desc);

	//Methods
	void UpdateAppointmentID(std::string& id);
	void UpdateDate(std::chrono::system_clock::time_point date);
	void UpdateDesc(std::string& newDesc);

	//Getters
	std::string GetAppointmentID() const;
	std::string GetContactID() const;
	std::chrono::system_clock::time_point GetDateOfAppointment() const;
	std::string GetDescription() const;

	//Helpers
	bool IsValidDate(std::chrono::system_clock::time_point date, bool displayMessage);
};

#endif // !APPOINTMENT_H
