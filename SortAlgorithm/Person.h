#pragma once
#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>

class Person
{
public:

	std::string vorname, nachname;
	static std::vector<Person> personen;

	Person(std::string &vn, std::string &nn);
	~Person();

	std::string toString();
	int compareTo(Person &o);

	static void readAndSetUp(std::string &fileName, int &c);
};

