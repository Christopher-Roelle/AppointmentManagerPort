#include "Appointment.h"

//Error Appointment, used to determine if no Appointment exists
Appointment::Appointment()
{
	appointmentID = "INVALID";
	contactID = "INVALID";
	dateOfAppointment = std::chrono::system_clock::now();
	description = "INVALID";
}

//Differing constructors for the Appointment Class
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
//Updates teh appointment ID to a value
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

//Used to reschedule an appointment.
//TODO:: Currently bugged. The time_point object passes properly, however the member variable will not change....
//May have something to do with the AppointmentService's list's reference? Not sure...
void Appointment::UpdateDate(const std::chrono::system_clock::time_point &date)
{
	//Debug
	//std::time_t time = std::chrono::system_clock::to_time_t(date);
	//std::tm tm;
	//localtime_s(&tm, &time);
	//std::cout << "Received: " << std::put_time(&tm, "%Y-%m-%d");

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

//Updates the description for an appointment.
//Currently not in-use anywhere, as it was never used in Java code.
//TODO::Add Main Menu item for doing this if there is time.
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

//Prints out the appointment's details, including the linked Patient's name.
void Appointment::PrintAppointment()
{
	//Get the contactID from the apt object, and get a reference to the contact obj.
	std::string cid = GetContactID();
	Contact c = ContactService::GetInstance().GetContactByID(cid);

	//Convert the time_point into a ss object to output to the CLI
	std::time_t time = std::chrono::system_clock::to_time_t(GetDateOfAppointment());
	std::tm tm;
	localtime_s(&tm, &time);
	std::stringstream dos;
	dos << std::put_time(&tm, "%Y-%m-%d");

	//Print the Appointment's details to CLI
	std::cout << "\n";
	std::cout << "ID: " << GetAppointmentID() << "\n";
	std::cout << "Patient Name: " << c.GetFullName() << "\n";
	std::cout << "Date of Service: " << dos.str() << "\n";
	std::cout << "Description: " << GetDescription() << "\n" << std::endl;
}

//Helper
//Checks if a date is valid. Year cant be past 1900 or 2100.
//Months obviously cannot be 0 or 13, and day between 1 and 31.
//TODO::Handle day variations for months.
bool Appointment::IsValidDate(std::chrono::system_clock::time_point date, bool displayMessage)
{
	//Convert the time_point to a tm struct that we can compare against.
	std::time_t now_time = std::chrono::system_clock::to_time_t(date);
	std::tm now_tm;
	
	localtime_s(&now_tm, &now_time);

	int year = now_tm.tm_year + 1900; //Years since 1900
	int month = now_tm.tm_mon + 1; //Months since Jan (0-index)
	int day = now_tm.tm_mday; //Day of the month

	//Actual check if valid. If this catches, then the date is invalid.
	if (year < 1900 || year > 2100 || month < 1 || month > 12 || day < 1 || day > 31)
	{
		if (displayMessage) { std::cout << "Invalid date format, using today's date." << std::endl; }
		return false;
	}

	//Date was valid
	return true;
}