// AppointmentManagerPort.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <sstream>
#include "ContactService.h"

//Prototypes
void PrintHeader();
void MainMenu();
void PrintMainMenu();
void PatientMenu();
void PrintPatientMenu();
void AppointmentMenu();
void PrintAppointmentMenu();
void NewContact();
void UpdateContact();
void DeleteContact();
void DisplayContact();

//Helpers
int ParseIntFromInput(std::string input);

//Vars
std::string officeName = "Lakeland Medical Center";
std::string officeMoto = "Your number one care practitioner!";

ContactService& contactService = ContactService::GetInstance();

//State Machine
enum class STATE{
    StartUp,
    MainMenu,
    PatientMenu,
    AppointmentMenu,
    Exiting
};

STATE currentState = STATE::StartUp;

int main()
{
    //Primary loop, using StateMachine
    while (currentState != STATE::Exiting)
    {
        switch (currentState)
        {
        case STATE::StartUp:
            //Blank slate for startup.
            PrintHeader();
            currentState = STATE::MainMenu;
            break;
        case STATE::MainMenu:
            //Display MainMenu
            MainMenu();
            break;
        case STATE::PatientMenu:
            //Display the Patient Menu
            PatientMenu();
            break;
        case STATE::AppointmentMenu:
            //Display the Appointment Menu
            AppointmentMenu();
            break;
        case STATE::Exiting:
            //Shouldnt hit this, just because iteration would catch the exit and not loop.
            break;
        default:
            //Reset, something went awry
            std::cerr << "Uh-Oh, something went wrong, reverting back to startup!!" << std::endl;
            currentState = STATE::StartUp;
            break;
        }
    }

    std::cout << "Thank you for choosing " << officeName << "!" << std::endl;
}

//Prints the Main Menu header
void PrintHeader()
{
    std::string oName = "Welcome to " + officeName;
    
    //Determine which is longer, oName or officeMoto, set maxLen to that, then add 6 to it for padding
    int maxLen = (oName.length() > officeMoto.length()) ? oName.length() : officeMoto.length();
    maxLen += 6;

    //Build the frame
    for (int i = 0; i < maxLen; i++)
    {
        std::cout << "#";
    }
    std::cout << std::endl;
    std::cout << "|| " << oName << " ||" << std::endl;
    std::cout << "|| " << officeMoto << " ||" << std::endl;
    for (int i = 0; i < maxLen; i++)
    {
        std::cout << "#";
    }
    std::cout << "\n" << std::endl;
}

//Displays the main menu, and handles the MainMenu state.
void MainMenu() {
    PrintMainMenu();

    std::string input;
    int optionChosen = -1;

    //Prompt for input, store in input
    std::cout << "Directive: ";
    std::getline(std::cin, input);
    std::cout << std::endl;

    //Try a parse
    optionChosen = ParseIntFromInput(input);

    switch (optionChosen)
    {
    case 1:
        currentState = STATE::PatientMenu;
        break;
    case 2:
        currentState = STATE::AppointmentMenu;
        break;
    case 3:
        currentState = STATE::Exiting;
        break;
    default:
        std::cout << "Invalid Input!\n" << std::endl;
        break;
    }
}

//Prints the main menu's options
void PrintMainMenu()
{
    std::cout << "How may we assist you? (Enter one of the menu directives and press enter)" << std::endl;
    std::cout << "1) Patients" << std::endl;
    std::cout << "2) Appointments" << std::endl;
    std::cout << "3) Exit\n" << std::endl;
}

//Displays the Patient Menu
void PatientMenu() {
    PrintPatientMenu();

    std::string input;
    int optionChosen = -1;

    //Prompt for input, store in input
    std::cout << "Directive: ";
    std::getline(std::cin, input);
    std::cout << std::endl;

    //Try a parse
    optionChosen = ParseIntFromInput(input);

    switch (optionChosen)
    {
    case 1:
        //New
        NewContact();
        break;
    case 2:
        //Update
        UpdateContact();
        break;
    case 3:
        //Delete
        DeleteContact();
        break;
    case 4:
        //Display single contact
        DisplayContact();
        break;
    case 5:
        //Display all
        contactService.DisplayAllContacts();
        break;
    case 6:
        //Return back to Main Menu
        currentState = STATE::MainMenu;
        break;
    default:
        std::cout << "Invalid Input!\n" << std::endl;
        break;
    }
}

//Prints the Patient menu
void PrintPatientMenu()
{
    std::cout << "Patient Management (Enter one of the menu directives and press enter)" << std::endl;
    std::cout << "1) New Patient" << std::endl;
    std::cout << "2) Update Patient" << std::endl;
    std::cout << "3) Delete Patient" << std::endl;
    std::cout << "4) Display a Patient" << std::endl;
    std::cout << "5) Display All Patients" << std::endl;
    std::cout << "6) Return to Main Menu\n" << std::endl;
}

//Display the Appointment Menu
void AppointmentMenu() {
    PrintAppointmentMenu();

    std::string input;
    int optionChosen = -1;

    //Prompt for input, store in input
    std::cout << "Directive: ";
    std::getline(std::cin, input);
    std::cout << std::endl;

    //Try a parse
    optionChosen = ParseIntFromInput(input);

    switch (optionChosen)
    {
    case 1:
        //New
        NewContact();
        break;
    case 2:
        //Update
        UpdateContact();
        break;
    case 3:
        //Delete
        DeleteContact();
        break;
    case 4:
        //Display all
        contactService.DisplayAllContacts();
        break;
    case 5:
        //Display all
        contactService.DisplayAllContacts();
        break;
    case 6:
        //Return back to Main Menu
        currentState = STATE::MainMenu;
        break;
    default:
        std::cout << "Invalid Input!\n" << std::endl;
        break;
    }
}

//Prints the Appointment menu
void PrintAppointmentMenu()
{
    std::cout << "Appointment Management (Enter one of the menu directives and press enter)" << std::endl;
    std::cout << "1) New Appointment" << std::endl;
    std::cout << "2) Reschedule Appointment" << std::endl;
    std::cout << "3) Cancel Appointment" << std::endl;
    std::cout << "4) Display an Appointment" << std::endl;
    std::cout << "5) Display All Appointments" << std::endl;
    std::cout << "6) Return to Main Menu\n" << std::endl;
}

//Takes in user input and attempts to have the contact service create a new Contact for the patient
void NewContact()
{
    bool valid = true;
    std::string contactID;
    std::string firstName;
    std::string lastName;
    std::string phoneNumber;
    std::string address;

    //Get the fields
    std::cout << "Patient First Name: ";
    std::getline(std::cin, firstName);

    std::cout << "Patient Last Name: ";
    std::getline(std::cin, lastName);

    std::cout << "Patient Phone Number: ";
    std::getline(std::cin, phoneNumber);

    std::cout << "Patient Address: ";
    std::getline(std::cin, address);

    std::cout << std::endl;

    //Validate the fields are not null and long enough
    if (firstName.empty() || firstName.length() < 3) 
    {
        std::cout << "First Name needs to be at least 3 characters!" << std::endl;
        valid = false;
    }

    if(lastName.empty() || lastName.length() < 2)
    {
        std::cout << "Last Name needs to be at least 2 characters!" << std::endl;
        valid = false;
    }

    if(phoneNumber.empty() || phoneNumber.length() != 10)
    {
        std::cout << "Phone Number needs to be 10 characters!" << std::endl;
        valid = false;
    }

    if (address.empty() || address.length() < 2) 
    {
        std::cout << "Address needs to be at least 2 characters!" << std::endl;
        valid = false;
    }

    if (!valid)
    {
        //For now return to previous menu. If there is time, I will provide better validation correction/backing out
        std::cout << std::endl;
        return;
    }
        
    //Generate a new contactID
    contactID = firstName.substr(0, 3) + lastName.substr(0, 2) + phoneNumber.substr(2, 3) + address.substr(0, 2);

    try
    {
        bool success = contactService.AddContact(contactID, firstName, lastName, phoneNumber, address);

        if (success)
        {
            std::cout << "Successfully added Patient Contact ID: " << contactID << "\n" << std::endl;
        }
        else
        {
            std::cout << "Failed to add Patient Contact ID: " << contactID << " -- already exists!\n" << std::endl;
        }
    }
    catch (const std::invalid_argument& e)
    {
        //Oops, something is wrong!
        std::cout << contactID << std::endl;
        std::cout << "Unable to add the patient. " << e.what() << "\n" << std::endl;
    }
}

void UpdateContact()
{
    if (contactService.GetListSize() == 0)
    {
        std::cout << "No contacts exist!\n" << std::endl;
        return;
    }

    bool valid = true;
    std::string contactID;
    std::string firstName;
    std::string lastName;
    std::string phoneNumber;
    std::string address;

    //Get the fields
    std::cout << "Patient ID: ";
    std::getline(std::cin, contactID);

    std::cout << "Patient First Name: ";
    std::getline(std::cin, firstName);

    std::cout << "Patient Last Name: ";
    std::getline(std::cin, lastName);

    std::cout << "Patient Phone Number: ";
    std::getline(std::cin, phoneNumber);

    std::cout << "Patient Address: ";
    std::getline(std::cin, address);

    std::cout << std::endl;

    if (!valid)
    {
        //For now return to previous menu. If there is time, I will provide better validation correction/backing out
        std::cout << std::endl;
        return;
    }

    //Attempt the update
    try
    {
        bool success = contactService.UpdateContact(contactID, firstName, lastName, phoneNumber, address);

        if (success)
        {
            std::cout << "Successfully updated Patient Contact ID: " << contactID << "\n" << std::endl;
        }
        else
        {
            std::cout << "Failed to update Patient Contact ID: " << contactID << " -- does not exist or invalid data!\n" << std::endl;
        }
    }
    catch (const std::invalid_argument& e)
    {
        //Oops, something is wrong!
        std::cout << contactID << std::endl;
        std::cout << "Unable to update the patient. " << e.what() << "\n" << std::endl;
    }

}

void DeleteContact()
{
    if (contactService.GetListSize() == 0)
    {
        std::cout << "No contacts exist!\n" << std::endl;
        return;
    }

    std::string contactID;

    //Get the ID
    std::cout << "Patient ID: ";
    std::getline(std::cin, contactID);

    bool success = contactService.DeleteContact(contactID);

    if (success)
    {
        std::cout << "Successfully deleted Patient ID: " << contactID << "\n" << std::endl;
    }
    else
    {
        std::cout << "Failed to delete Patient ID: " << contactID << " -- does not exist!\n" << std::endl;
    }

}

void DisplayContact() {
    if (contactService.GetListSize() == 0)
    {
        std::cout << "No contacts exist!\n" << std::endl;
        return;
    }

    std::string contactID;

    //Get the ID
    std::cout << "Patient ID: ";
    std::getline(std::cin, contactID);

    Contact contact = contactService.GetContactByID(contactID);

    if (contact.GetContactID() != "INVALID")
    {
        std::cout << "\n";
        std::cout << "ID: " << contact.GetContactID() << "\n";
        std::cout << "First Name: " << contact.GetFirstName() << "\n";
        std::cout << "Last Name: " << contact.GetLastName() << "\n";
        std::cout << "Phone Number: " << contact.GetPhoneNumber() << "\n";
        std::cout << "Address: " << contact.GetAddress() << std::endl;
    }
}

//Parses an integer from a provided input string
int ParseIntFromInput(std::string input)
{
    //Create the string stream obj
    std::stringstream ss(input);
    int number = -1;

    //Attempt parse, return -1 if not valid
    if (ss >> number && ss.eof())
    {
        return number;
    }
    else {
        //Invalid int
        return -1;
    }
}
