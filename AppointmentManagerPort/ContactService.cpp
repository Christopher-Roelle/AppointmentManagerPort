#include "ContactService.h"

//Singleton Instance
ContactService& ContactService::GetInstance()
{
	static std::unique_ptr<ContactService> instance(new ContactService());
	return *instance;
}

//Constructor (Private)
ContactService::ContactService(){};

//Methods
//Checks if a contact already exists, if not, then we create a new Contact Object and insert if all data is good
bool ContactService::AddContact(std::string& cid, std::string& fn, std::string& ln, std::string& phone, std::string& addr)
{
	bool contactExists = false;

	//Loop through all contacts, if the contact matches, then set the flag
	for (Contact lc : listOfContacts)
	{
		if (lc.GetContactID() == cid)
		{
			//Contact exists, break from the loop
			return false;
		}
	}

	//Add the contact
	listOfContacts.push_back(Contact(cid, fn, ln, phone, addr));
	return true;

}

//Deletes a contact by the contactID
bool ContactService::DeleteContact(std::string& cid)
{
	//Iterate over the vector, if the contact exists, delete it
	for (auto it = listOfContacts.begin(); it != listOfContacts.end(); ++it)
	{
		//Check the passed cid against the contactID on the contact
		if (it->GetContactID() == cid)
		{
			//Matches, delete it from the list
			listOfContacts.erase(it);
			return true;
		}
	}

	//No Matches
	return false;
}

//Updates a contact based on its CID
bool ContactService::UpdateContact(std::string& cid, std::string& fn, std::string& ln, std::string& phone, std::string& addr)
{
	for (auto it = listOfContacts.begin(); it != listOfContacts.end(); ++it)
	{
		//Found the contact, lets validate, and set the new data.
		if (it->GetContactID() == cid)
		{
			//Validate the data, then set it
			if (!fn.empty() && !(fn.length() > 20) && !ln.empty() && !(ln.length() > 20) &&
				phone.length() == 10 && !addr.empty() && !(addr.length() > 100))
			{
				it->SetFirstName(fn);
				it->SetLastName(ln);
				it->SetPhoneNumber(phone);
				it->SetAddress(addr);

				return true;
			}

			//If we hit here, then the update failed due to invalid data
			return false;
		}
	}

	//No matches on contactID
	return false;
}

//Getters
int ContactService::GetListSize() const
{
	return listOfContacts.size();
}

//Return just one contact by its ID
Contact ContactService::GetContactByID(std::string& cid) const
{
	for (const auto& contact : listOfContacts)
	{
		if (contact.GetContactID() == cid)
		{
			return contact;
		}
	}

	std::cout << "No patients match that ID.\n" << std::endl;
	return Contact();
}

//Returns all contacts
void ContactService::DisplayAllContacts() const
{
	//Check the list is not empty
	if (GetListSize() == 0)
	{
		std::cout << "No contacts exist!\n" << std::endl;
		return;
	}

	//Call printContact for all stored contacts
	for (Contact c : listOfContacts)
	{
		c.PrintContact();
	}

	//New line for clean output
	std::cout << std::endl;
}