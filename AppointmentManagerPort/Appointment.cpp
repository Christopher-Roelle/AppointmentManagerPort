#include "Appointment.h"

Appointment::Appointment(std::string& cid)
{
	appointmentID = INITIALIZER;
	contactID = cid;
	dateOfAppointment = std::chrono::system_clock::now();
	description = INITIALIZER;
}

Appointment::Appointment(std::string& id, std::string& cid)
{
	UpdateAppointmentID(id);
	contactID = cid;
	dateOfAppointment = std::chrono::system_clock::now();
	description = INITIALIZER;
}

Appointment::Appointment(std::string& id, std::string& cid, std::chrono::system_clock::time_point date)
{
	UpdateAppointmentID(id);
	contactID = cid;
	dateOfAppointment = (IsValidDate(date, true)) ? date : std::chrono::system_clock::now();
	description = INITIALIZER;
}

Appointment::Appointment(std::string& id, std::string& cid, std::chrono::system_clock::time_point date, std::string& desc)
{
	UpdateAppointmentID(id);
	contactID = cid;
	dateOfAppointment = (IsValidDate(date, true)) ? date : std::chrono::system_clock::now();
	UpdateDesc(desc);
}

//Methods
void Appointment::UpdateAppointmentID(std::string& id)
{
	if (id.empty())
	{
		throw std::invalid_argument("Appointment ID cannot be null!");
	}
	else if (id.length() > APPOINTMENT_ID_LENGTH)
	{
		throw std::invalid_argument(("Appointment ID cannot exceed " + std::to_string(APPOINTMENT_ID_LENGTH) + " characters!"));
	}
	else {
		this->appointmentID = id;
	}
}

void Appointment::UpdateDate(std::chrono::system_clock::time_point date)
{
	if (!IsValidDate(date, false))
	{
		throw std::invalid_argument("Invalid date format!");
	} 
	else if (date < std::chrono::system_clock::now())
	{
		throw std::invalid_argument("Date cannot be in the past!");
	}
	else {
		this->dateOfAppointment = date;
	}
}

void Appointment::UpdateDesc(std::string& newDesc)
{
	if (newDesc.empty())
	{
		throw std::invalid_argument("Appointment description cannot be empty!");
	} 
	else if (newDesc.length() > APPOINTMENT_DESC_LENGTH)
	{
		throw std::invalid_argument(("Appointment description cannot exceed " + std::to_string(APPOINTMENT_DESC_LENGTH) + " characters!"));
	}
	else {
		this->description = newDesc;
	}
}

//Getters
std::string Appointment::GetAppointmentID() const
{
	return appointmentID;
}

std::string Appointment::GetContactID() const
{
	return contactID;
}

std::chrono::system_clock::time_point Appointment::GetDateOfAppointment() const
{
	return dateOfAppointment;
}

std::string Appointment::GetDescription() const
{
	return description;
}

//Helper
bool Appointment::IsValidDate(std::chrono::system_clock::time_point date, bool displayMessage)
{
	std::time_t now_time = std::chrono::system_clock::to_time_t(date);
	std::tm now_tm;
	
	localtime_s(&now_tm, &now_time);

	int year = now_tm.tm_year + 1900; //Years since 1900
	int month = now_tm.tm_mon + 1; //Months since Jan (0-index)
	int day = now_tm.tm_mday; //Day of the month

	if (year < 1900 || year > 2100 || month < 1 || month > 12 || day < 1 || day > 31)
	{
		if (displayMessage) { std::cout << "Invalid date format, using today's date." << std::endl; }
		return false;
	}

	return true;
}