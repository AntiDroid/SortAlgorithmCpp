#include "stdafx.h"
#include "Person.h"
#include <omp.h>

#include <stdio.h>

template <typename T> std::vector<T> splitVec(std::vector<T>& main, size_t from, size_t to) {

	std::vector<T>::const_iterator first = main.begin() + from;
	std::vector<T>::const_iterator last = main.begin() + to;
	std::vector<T> erg(first, last);

	return erg;
}

template <typename T> std::vector<T> merge(std::vector<T>& m1, std::vector<T>& m2) {

	unsigned int posA = 0, posB = 0;

	std::vector<T> erg;
	erg.reserve(m1.size()+m2.size());

	while (posA < m1.size() && posB < m2.size()) {
		if (m1[posA].compareTo(m2[posB]) <= 0) 
			erg.push_back(m1[posA++]);
		else 
			erg.push_back(m2[posB++]);
	}

	while (posA < m1.size())
		erg.push_back(m1[posA++]);

	while (posB < m2.size())
		erg.push_back(m2[posB++]);

	return erg;
}

template <typename T> std::vector<T> mergeSort(std::vector<T>& m) {

	if (m.size() > 1) {

		//Split pers into two equally sized vectors
		std::vector<T> p1(splitVec(m, 0, m.size()/2));
		std::vector<T> p2(splitVec(m, (m.size()/2), m.size()));

		return merge(mergeSort(p1), mergeSort(p2));
	}
	else
		return m;
}

template <typename T> void swap(std::vector<T>& a, size_t x, size_t y) {

	T temp = a[x];

	a[x] = a[y];
	a[y] = temp;
}

template <typename T> void selectionSort(std::vector<T>& ar) {

	for (size_t i = 0; i < ar.size() - 1; i++) {

		size_t min = i;
		for (size_t j = (i + 1); j < ar.size(); j++)
			if (ar[min].compareTo(ar[j]) == 1)
				min = j;
		
		swap(ar, i, min);
	}
}

double sort(bool r) {
	if (r)
		std::cout << "\nRECURSIVE\n";
	else
		std::cout << "\nNORMAL\n";
	std::cout << "sorting...\n";

	double start = omp_get_wtime();

	if (r)
		Person::getPersonen() = mergeSort(Person::getPersonen());
	else
		selectionSort(Person::getPersonen());

	std::cout << "finished\n\n";

	return (int)((omp_get_wtime()-start)*1000);
}

int main()
{
	std::string mode[] = { "worst", "avg", "best" };
	const bool recursive = true;
	int count = 0;

	std::cout << "How many entries should be used?\n";
	std::cin >> count;

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
	
	system("pause");

    return 0;
}