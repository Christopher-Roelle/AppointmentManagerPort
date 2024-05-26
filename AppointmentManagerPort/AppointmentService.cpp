#include "AppointmentService.h"

//Singleton Instance
AppointmentService& AppointmentService::GetInstance()
{
	static std::unique_ptr<AppointmentService> instance(new AppointmentService());
	return *instance;
}

//Constructor (Private)
AppointmentService::AppointmentService() {};

std::string AppointmentService::NewUniqueID()
{
	//Seed the RNG on a device
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 15);

	std::stringstream ss;
	ss << std::hex;

	//Generate a random 32-hex UUID to use as the ID (Close approx of what Java does with randomUUID()
	for (int i = 0; i < 32; ++i)
	{
		int randNum = dis(gen);
		char digit = randNum < 10 ? '0' + randNum : 'a' + randNum - 10;
		ss << digit;
	}

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

void AppointmentService::GetAllAppointments()
{
	if (GetListSize() == 0)
	{
		std::cout << "No appointments exist!\n" << std::endl;
		return;
	}

	ContactService& contactService = ContactService::GetInstance();

	for (Appointment apt : appointmentList)
	{
		apt.PrintAppointment();
	}
}

int AppointmentService::GetListSize()
{
	return appointmentList.size();
}