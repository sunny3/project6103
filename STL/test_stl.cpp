#include <stdio.h>
#include <iostream>
#include <cassert>
#include "pch.h"
#include "Header_stl.h"
#include "test_stl.h"

using namespace std;

bool Station::station_exist(string name, int time, float depth, float a_stream) {
	if (this->name == name && this->time == time && this->a_stream == a_stream && this->depth == depth) { //прегруженное в стандартной библиотеке == проверяет строки на равенство
		return true;
	}
	else {
		return false;
	}
}

void test_station() {
	Station m1 = Station("Щелковская", 0, 200, 50);
	if (m1.station_exist("Щелковская", 0, 200, 50)) {
		std::cout << "Station 1 exists\n"; //"Станция 1 существует"
	}
	Station m2 = Station("Первомайская", 5, 200, 48);
	if (m2.station_exist("Первомайская", 5, 200, 48)) {
		std::cout << "Station 2 exists\n"; //"Станция 2 существует"
	}
	Station m3 = Station("test", 3, 300, 64);
	if (m2 > m1) {
		std::cout << "Station 2 has a time longer then station 1\n"; //"Станция 2 больше станции 1"
	}
	if (m2 == m2) {
		std::cout << "Station 2 has equal time to station 2\n"; //"Станция 2 равна станции 2"
	}
	if (m1 < m2) {
		std::cout << "Station 1 has a time smaller then station 2\n"; //"Станция 1 меньше станции 2"
	}
	m1.stream_change(52);
	int b = m1.get_a_stream();
	std::cout << "The value of a_stream for station 1 is " << b << "\n";
}

void test_transfer_station() {

	string e1[] = { "as", "fg","hj", "bf" };
	int size_of_e1 = 4;
	string e2[] = { "as", "fg","hj", "bf", "gh" };
	int size_of_e2 = 5;
	string e3[] = { "as", "fg","hj", "bf", "gh", "hjl" };
	int size_of_e3 = 6;
	Transfer_station *t1 = Transfer_station::init("Курская", 50, 200, 50, e1, size_of_e1);
	Transfer_station *t2 = Transfer_station::init("Курская", 50, 200, 50, e2, size_of_e2);
	Transfer_station *t3 = Transfer_station::init("Курская", 50, 200, 50, e3, size_of_e3);
	(*t1).printT();
	cout << "\n";
	(*t2).printT();
	cout << "\n";
	delete(t1);
	delete(t2);
	delete(t3);
}

/*list<unique_ptr<Station>> test_copying() {
	list<unique_ptr<Station>> green;
	unique_ptr<Station> s1(new Station("Театральная", 0, 200, 50));
	unique_ptr<Station> s2 (new Station("Тверская", 5, 200, 48));
	green.push_front();
	green->add_station(&m2);
	return green;
} */

void test_metro_line() {
	shared_ptr<Station> s1(new Station("Tversjay", 0, 200, 50));
	shared_ptr<Station> s2(new Station("Тeatralnaya", 5, 200, 48));
	shared_ptr<Station> s3(new Station("Ziablikogo", 3, 100, 20));
	string e1[] = { "Kurskay", "Oktyabrskay","Test" };
	int size_of_e1 = 3;
	shared_ptr<Station> t1(new Transfer_station("Mayakovskay", 50, 200, 50, e1, size_of_e1));
	//create a list
	cout << "Now we create a metro line. At first we will try with unvalid element,\nat second with valid.\nWe will print all the punctors of metro lines\n";
	list<shared_ptr<Station>> *ptr_metro_line = Metro_line(s2); //try to create not valid list.
	cout << "1) first punctor: " << ptr_metro_line << "\n";

	//assert(!ptr_metro_line);

	ptr_metro_line = Metro_line(s1); //try to create valid list.
	cout << "2) second punctor: " << ptr_metro_line << "\n";

	//assert(ptr_metro_line);

	list<shared_ptr<Station>> metro_line = *ptr_metro_line;
	//add stations
	cout << "Now we will add stations\n";
	cout << "correct values of the test: 1)1 2)0 3)1\n";
	cout << "real test values:\n";

	cout << "1)" << add_station(metro_line, s2) << "\n";
	cout << "2)" << add_station(metro_line, s3) << "\n";
	cout << "3)" << add_station(metro_line, t1) << "\n";

	/*assert(add_station(metro_line, s2));
	assert(!add_station(metro_line, s3));
	assert(add_station(metro_line, t1));
	*/

	//print all stations
	print_metro_line(metro_line);
	cout << "\n";
	delete ptr_metro_line; 
}