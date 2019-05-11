#include <stdio.h>
#include <assert.h>
#include "pch.h"
#include "test_stl.h"

int main()
{
	test_station();


	test_metro_line();
	//return 0;

	test_transfer_station();



	/*bool flag = 1; - Недоработанная клиентская часть. Не надо смотреть этот код.
	string name;
	unsigned int time;
	unsigned int depth;
	unsigned int a_stream;
	string e[5];
	int type;
	Metro_line *blue = nullptr;
	cout << "\n\nEnter the parametrs of the station you want to add in line\n";
	while (flag) {
		cout << "enter the type of the station (transfer(0) or normal(1))";
		cin >> type;
		cout << "enter station's name:\n";
		getline(cin, name);
		cout << "enter station's time:\n";
		cin >> time;
		cout << "enter station's depth:\n";
		cin >> depth;
		cout << "enter station's a_stream:\n";
		cin >> a_stream;
		if (type) {
			//Station m1 = Station(name, time, depth, a_stream);
			if (blue == nullptr) {
				blue = Metro_line::init(new Station(name, time, depth, a_stream));
			}
			else
				blue->add_station(new Station(name, time, depth, a_stream));
		}
		else {
			cout << "enter an array of the stations, which are related to this transfer station :\n";
			for (int i = 0; i < 5; i++)
				getline(cin, e[i]);
			if (blue == nullptr) {
				blue = Metro_line::init(new Transfer_station(name, time, depth, a_stream, e));
			}
			else
				blue->add_station(new Transfer_station(name, time, depth, a_stream, e));
		}
		cout << "Do you want to continue?(yes - 1, no - 0)";
		cin >> flag;
	}
	*/
	return 0;

}