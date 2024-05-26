#ifndef CONTACTSERVICE_H
#define CONTACTSERVICE_H

#include "Contact.h"
#include <vector>
#include <memory>
#include <iostream>

//Header for the service that manages the Contacts
class ContactService
{
private:
	//List of all the contacts stored
	std::vector<Contact> listOfContacts;

	//Constructor (Singleton)
	ContactService();

public:
	static ContactService& GetInstance();

	//Removing copy constructor/assignment
	ContactService(const ContactService&) = delete;
	void operator=(const ContactService&) = delete;

	//Methods
	bool AddContact(std::string& cid, std::string& fn, std::string& ln, std::string& phone, std::string& addr);
	bool DeleteContact(std::string& cid);
	bool UpdateContact(std::string& cid, std::string& fn, std::string& ln, std::string& phone, std::string& addr);

	//Getters
	int GetListSize() const;
	Contact GetContactByID(std::string& cid) const;
	void DisplayAllContacts() const;
};

#endif // !CONTACTSERVICE_H
