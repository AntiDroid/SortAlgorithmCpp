#include "stdafx.h"
#include "Person.h"
#include "Functions.cpp"
#include <omp.h>

double sort(bool r) {

	if (r)
		std::cout << "\nRECURSIVE\n";
	else
		std::cout << "\nNORMAL\n";
	std::cout << "\t...sorting...\n";

	double start = omp_get_wtime();

	if (r)
		Person::getPersonen() = sorting_functions::mergeSort(Person::getPersonen());
	else
		sorting_functions::selectionSort(Person::getPersonen());

	std::cout << "\tfinished\n\n";

	return (int)((omp_get_wtime()-start)*1000);
}

int main()
{
	const std::string mode[] = { "worst", "avg", "best" };
	const bool recursive = true;
	int count = 0;

	do {

		std::cout << "How many entries should be used?\n";
		std::cin >> count;

		//Fully empty cin buffer
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		if (count < 2)
			continue;

		Person::getPersonen().reserve(count);

		double* rec = new double[3];
		double* normal = new double[3];

		for (int i = 0; i < 3; i++) {

			Person::readAndSetUp(mode[i], count);
			rec[i] = sort(recursive);

			Person::readAndSetUp(mode[1], count);
			normal[i] = sort(!recursive);
		}

		std::cout << "\n\n\n\n\n\t  Recursive  \t  Normal\n";
		std::cout << "       ----------------------------\n";
		std::cout << mode[0] << "\t\t" << rec[0] << "ms\t     " << normal[0] << "ms\n";
		std::cout << "\n" << mode[1] << "\t\t" << rec[1] << "ms\t     " << normal[1] << "ms\n";
		std::cout << "\n" << mode[2] << "\t\t" << rec[2] << "ms\t     " << normal[2] << "ms\n";
		std::cout << "       ----------------------------\n";
		std::cout << "\nItems: " << count << "\n\n\n";

		delete[] rec;
		delete[] normal;

	} while (true);

    return 0;
}