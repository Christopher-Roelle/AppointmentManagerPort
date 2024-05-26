#include "AppointmentService.h"

//Singleton Instance
AppointmentService& AppointmentService::GetInstance()
{
	static std::unique_ptr<AppointmentService> instance(new AppointmentService());
	return *instance;
}

//Constructor (Private)
AppointmentService::AppointmentService() {};

//Generates a NewUniqueID. I dont actually use this.
//Forgot I ported code for this, I could use this for the apt IDs, however I like my current iteration more atm.
std::string AppointmentService::NewUniqueID()
{
	//Seed the RNG on a device
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 15);

	//Place the hex value in the SS
	std::stringstream ss;
	ss << std::hex;

	//Generate a random 32-hex UUID to use as the ID (Close approx of what Java does with randomUUID()
	for (int i = 0; i < 32; ++i)
	{
		int randNum = dis(gen);
		char digit = randNum < 10 ? '0' + randNum : 'a' + randNum - 10;
		ss << digit;
	}

	//Set the uuid as the contents of ss
	std::string uuid = ss.str();

	//Substring the UID as the Unique ID
	return uuid.substr(0, std::min(uuid.length(), size_t(10)));
}

//Add appointment with just a patient ID
void AppointmentService::NewAppointment(std::string& cid)
{
	Appointment appt = Appointment::Appointment(cid);
	appointmentList.push_back(appt);
}

//Add appointment with appointment and patient ID
void AppointmentService::NewAppointment(std::string& id, std::string& cid)
{
	Appointment appt = Appointment::Appointment(id, cid);
	appointmentList.push_back(appt);
}

//Add appointment with appointment, patient ID and dateOfAppointment
void AppointmentService::NewAppointment(std::string& id, std::string& cid, std::chrono::system_clock::time_point date)
{
	Appointment appt = Appointment::Appointment(id, cid, date);
	appointmentList.push_back(appt);
}

//Add appointment with appointment, patient ID, dateOfAppointment and a description
void AppointmentService::NewAppointment(std::string& id, std::string& cid, std::chrono::system_clock::time_point date, std::string& desc)
{
	Appointment appt = Appointment::Appointment(id, cid, date, desc);
	appointmentList.push_back(appt);
}

//Delete appointment by ID
//TODO:: Figure out why uncommenting the erase causes a deleted function reference error....
//Implementation was ripped from ContactService, which does the same thing with 0 issue.
bool AppointmentService::DeleteAppointment(std::string& id)
{
	//Iterate over the vector, if the Appointment exists, delete it
	for (auto it = appointmentList.begin(); it != appointmentList.end(); ++it)
	{
		if (it->GetAppointmentID() == id)
		{
			//appointmentList.erase(it);
			return true;
		}
	}

	//No records
	return false;
}

//Calls the process to update the appointment's date.
//Was initially making the call directly to the apt object from the menu, but thought this was cleaner, and
//hoped it could resolve the bug where the time_point isnt updating even when the code succeeds and the params contain
//The proper data....
bool AppointmentService::UpdateAppointmentDate(std::string& id, std::chrono::system_clock::time_point date)
{
	Appointment apt = GetAppointmentByID(id);
	
	//Verify its valid
	if (apt.GetAppointmentID() == "INVALID")
	{
		std::cout << "Invalid appointment ID!" << std::endl;
		return false;
	}

	//Make the update
	apt.UpdateDate(date);
	return true;
}

//Getters
Appointment AppointmentService::GetAppointmentByID(std::string& id)
{
	if (GetListSize() == 0)
	{
		std::cout << "No appointments exist!\n" << std::endl;
		return Appointment();
	}

	ContactService& contactService = ContactService::GetInstance();

	for (Appointment apt : appointmentList)
	{
		if (apt.GetAppointmentID() == id)
		{			
			return apt;
		}
	}
}

//Calls PrintAppointment for all stored appointments
void AppointmentService::GetAllAppointments()
{
	//Check the list is not empty.
	if (GetListSize() == 0)
	{
		std::cout << "No appointments exist!\n" << std::endl;
		return;
	}

	//ContactService& contactService = ContactService::GetInstance();

	//Iterate the list, calling PrintAppointment
	for (Appointment apt : appointmentList)
	{
		apt.PrintAppointment();
	}
}

//Returns the number of stored appointments
int AppointmentService::GetListSize()
{
	return appointmentList.size();
}