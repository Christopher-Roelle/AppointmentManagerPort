#include "Contact.h"

//Invalid obj
Contact::Contact()
{
	this->contactID = "INVALID";
	this->firstName = "INVALID";
	this->lastName = "INVALID";
	this->phoneNumber = "INVALID";
	this->address = "INVALID";
}

//Constructor
Contact::Contact(const std::string& cid, const std::string& fn, const std::string& ln, const std::string& phone, const std::string& addr)
{
	//Validate the contact information
	if (cid.empty() || cid.length() > 10)
	{
		throw std::invalid_argument("Invalid contact ID - null or length is greater than 10");
	}
	else if (fn.empty() || fn.length() > 20)
	{
		throw std::invalid_argument("Invalid first name - null or length is greater than 20");
	}
	else if (ln.empty() || ln.length() > 20)
	{
		throw std::invalid_argument("Invalid last name - null or length is greater than 20");
	}
	else if (phone.empty() || phone.length() != 10)
	{
		throw std::invalid_argument("Invalid phone number - null or length is greater than 10");
	}
	else if (addr.empty() || addr.length() > 100)
	{
		throw std::invalid_argument("Invalid address - null or length is greater than 100");
	}

	//Passed all validation, insert the data into the Contact
	this->contactID = cid;
	this->firstName = fn;
	this->lastName = ln;
	this->phoneNumber = phone;
	this->address = addr;
};

//Getters
std::string Contact::GetContactID() const {
	return contactID;
}

std::string Contact::GetFirstName() const {
	return firstName;
}

std::string Contact::GetLastName() const {
	return lastName;
}

std::string Contact::GetPhoneNumber() const {
	return phoneNumber;
}

std::string Contact::GetAddress() const {
	return address;
}

//Setters
void Contact::SetContactID(const std::string& cid)
{
	throw std::invalid_argument("Contact ID cannot be changed!");
}

void Contact::SetFirstName(const std::string& fn)
{
	this->firstName = fn;
}

void Contact::SetLastName(const std::string& ln)
{
	this->lastName = ln;
}

void Contact::SetPhoneNumber(const std::string& phone)
{
	this->phoneNumber = phone;
}

void Contact::SetAddress(const std::string& addr)
{
	this->address = addr;
}
