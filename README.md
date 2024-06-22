# AppointmentManagerPort - Enhancement of CS-320-R1875
 Port of CS-320-R1875 from Java to C++

## Table of Contents
- [About](#about)
- [Enhancements](#enhancements)
- [Prerequisites](#prerequisites)
- [Building](#building)
- [Usage](#usage)

## About
Originally written for demonstration of Java Unit tests, I took this project and ported it to C++, as well as expanded its functionality to be a usable Appointment Manager.

## Enhancements
- Native C++ code that can be compiled to any architecture with compiler support.
- Added an entry point to the code in the form of a menu.
- Implemented support for Creating, Reading, Updating and Deleting Patient Contacts and Appointments from the menu.

## Prerequisites
- Visual Studio IDE (Or C++ Compiler)
- C++ 14 Compiler
- Git/Github for Desktop (Or Site Clone)

## Building
A pre-compiled x64 version is available.
If you want to compile yourself, please follow the below steps:
1. Clone this repository
    ```bash
    git clone https://github.com/Christopher-Roelle/AppointmentManagerPort.git
    ```
2. Navigate to project directory root
3. Open AppointmentManagerPort.sln
4. Change Build to 'Release' and Architecture to desired (i.e. x64, x86, ARM)
5. Click Build (Ctrl+F5)

# Usage
After downloading the pre-compiled version or compiling from the source, either run the executable via the .exe or run the following Command Line:
```bash
cd -INSERT PATH HERE-
./AppointmentManagerPort.exe
```