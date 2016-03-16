#pragma once
#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>

class Person
{
private:

	std::string vorname, nachname;
	static std::vector<Person> personen;

public:

	Person(std::string& vn, std::string& nn);
	~Person();

	void setVorname(std::string& vn);
	void setNachname(std::string& nn);

	std::string& getVorname();
	std::string& getNachname();

	static void setPersonen(std::vector<Person>& p);
	static std::vector<Person>& getPersonen();

	std::string toString();
	int compareTo(Person& o);

	static void readAndSetUp(const std::string& fileName, int& c);
};

