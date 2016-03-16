#include "stdafx.h"
#include "Person.h"
#include <fstream>

std::vector<Person> Person::personen;

Person::Person(std::string& vn, std::string& nn)
{
	vorname = vn;
	nachname = nn;
}

Person::~Person()
{
}

void Person::setVorname(std::string& vn) {
	this->vorname = vn;
}

void Person::setNachname(std::string& nn) {
	this->nachname = nn;
}

std::string& Person::getVorname() {
	return this->vorname;
}

std::string& Person::getNachname() {
	return this->nachname;
}

void Person::setPersonen(std::vector<Person>& p) {
	Person::personen = p;
}
std::vector<Person>& Person::getPersonen() {
	return Person::personen;
}

std::string& Person::toString() {
	return "Vorname: " + vorname + "   \t\tNachname: " + nachname + "\n";
}

void Person::readAndSetUp(std::string& fileName, int& c) {

	std::ifstream reader;
	reader.open("c:/emp_" + fileName + ".csv");

	if (!reader.is_open()) {
		std::cout << "file couldn't be found\n\n";
		system("pause");
		exit(EXIT_FAILURE);
	}

	Person::personen.clear();

	std::string word1;
	std::string word2;

	reader >> word1;
	reader >> word2;

	for (int i = 0; (i < c) && reader.good(); i++){

		Person p(word1, word2);

		Person::personen.push_back(p);

		reader >> word1;
		reader >> word2;
	}
}

int Person::compareTo(Person& o) {

	const char *c1 = this->nachname.c_str();
	const char *c2 = o.nachname.c_str();

	const char *c3 = this->vorname.c_str();
	const char *c4 = o.vorname.c_str();

	int nn = _strcmpi(c1, c2);
	int vn = _strcmpi(c3, c4);

	if (nn == 0) {
		if (vn == 0) {
			return 0;
		}
		else if (vn > 0)
			return 1;

		else if (vn < 0)
			return -1;
	}
	else if (nn > 0)
		return 1;

	else if (nn < 0)
		return -1;

	return 0;
}
