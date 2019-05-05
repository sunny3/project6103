#include <stdio.h>
#include <assert.h>
#include "pch.h"
#include "Header.h"
#include "test.h"

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
}

Metro_line * test_copying() {
	Metro_line *green;
	Station m1 = Station("Театральная", 0, 200, 50);
	Station m2 = Station("Тверская", 5, 200, 48);
	green = Metro_line::init(&m1);
	green->add_station(&m2);
	return green;
}

void test_metro_line() {
	Station m1 = Station("Щелковская", 0, 200, 50);
	Station m2 = Station("Первомайская", 5, 200, 48);
	Station m3 = Station("test", 3, 300, 64);
	string e1[] = { "as", "fg","hj" };
	int size_of_e1 = 3;
	Transfer_station t1 = Transfer_station("Курская", 50, 200, 50, e1, size_of_e1);
	Metro_line *blue = Metro_line::init(&m2);
	blue = Metro_line::init(&m1);
	blue->add_station(&m2);
	cout << blue->get_length() << "\n";
	blue->add_station(&m3);
	cout << blue->get_length() << "\n";
	blue->add_station(&t1);
	cout << blue->get_length() << "\n";
	blue->add_station(&t1);
	cout << blue->get_length() << "\n";
	blue->print_line();
	std::cout << "\nTest has been comleted\n";
	Metro_line *green = test_copying();
	green->print_line();
}