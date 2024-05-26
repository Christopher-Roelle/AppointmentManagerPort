#ifndef CONTACT_H
#define CONTACT_H

#include <string>
#include <stdexcept>
#include <iostream>

class Contact
{

private:
	std::string contactID;
	std::string firstName;
	std::string lastName;
	std::string phoneNumber;
	std::string address;

	//Was public in Java... Should just be omitted outright, but for sake of porting
	void SetContactID(const std::string& cid);

public:
	//Constructor
	Contact();
	Contact(const std::string& cid, const std::string& fn, const std::string& ln, const std::string& phone,	const std::string& addr);

	void PrintContact();

	//Getters
	std::string GetContactID() const;
	std::string GetFirstName() const;
	std::string GetLastName() const;
	std::string GetPhoneNumber() const;
	std::string GetAddress() const;
	std::string GetFullName() const;

	//Setters
	void SetFirstName(const std::string& fn);
	void SetLastName(const std::string& ln);
	void SetPhoneNumber(const std::string& phone);
	void SetAddress(const std::string& addr);
};

#endif