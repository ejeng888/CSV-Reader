#include <cpplinq.hpp>
#include <iostream>
#include "../../std_lib_facilities.h"

using namespace cpplinq;

struct employee {
	string id;
	string city;
	string name;

	employee(string id = "", string name = "", string city = "")
		:id(move(id)), name(move(name)), city(move(city))
	{
	}
};

void print(vector<employee> test_vector) {

	auto result = from(test_vector)
		>> where([](employee const & e) {return e.city == "Toronto"; })
		>> orderby_ascending([](employee const & e) {return e.name; })
		>> select([](employee const & e) {return e.name; })
		>> to_vector();

	for (int i = 0; i != result.size(); ++i) {
		cout << result[i] << "\n";
	}
}

int main()
{
	string line, columnName;
	ifstream MyFile("C:\\Users\\ejeng\\source\\repos\\csvTest\\Employees.csv");

	vector<employee> employee_vector;

	int iline = 0;
	int icount = 0;
	string arr[3];
	while (getline(MyFile, line)) {
		stringstream ss(line);
		icount = 0;
		while (getline(ss, columnName, '|') && iline > 0)
		{
			//cout << columnName;
			arr[icount] = columnName;

			if (icount == 2)
			{
				employee_vector.push_back({ arr[0], arr[1], arr[2] });				
			}
			icount++;
			
		}
		iline++;
	}

	print(employee_vector);

	MyFile.close();
}


