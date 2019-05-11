#ifndef Header_stl_H
#define Header_stl_H
#include <string>
#include <iostream>
#include <memory>
#include <list>

using namespace std;
class Station
{
private:
	string name;
	unsigned int time; //time, measured in minutes
	unsigned int depth; //depth, measured in meters
	unsigned int a_stream; //average stream, measured in people/minutes
public:
	Station(string name, unsigned int time, unsigned int depth, unsigned int a_stream) :
		name(name), time(time), depth(depth), a_stream(a_stream) {}
	void stream_change(unsigned int curr_stream) {
		this->a_stream = curr_stream; //registration of average stream changing
	}
	friend bool operator>(const Station &c1, const Station &c2) {
		return(c1.time > c2.time);
	}
	friend bool operator<(const Station &c1, const Station &c2) {
		return(c1.time < c2.time);
	}
	friend bool operator==(const Station &c1, const Station &c2) {
		return(c1.time == c2.time);
	}
	const string& get_name() const {
		return name;
	}

	int get_time() const {
		return(this->time);
	}
	float get_depth() const {
		return(this->depth);
	}
	float get_a_stream() const {
		return(this->a_stream);
	}
	bool station_exist(string name, int time, float depth, float a_stream); //method is needed for test.cpp

	virtual void print() {
		cout << "\n---------" << "\n Station's name: " << name << "\n Station's type: standart station" << "\n time: " << time << "\n Depth: " << depth << "\n Average stream: " << a_stream << "\n---------\n";
	} //print all information about the station (work for every type of the stations)

	virtual Station * copy() {
		Station *c = new Station(name, time, depth, a_stream);
		return c; //copy a station
	}
};

class Transfer_station :
	public Station
{
	string stations[5]; //- array of stations you can transfer to
	int length_of_arr;
public:
	Transfer_station(string name, int time, float depth, float a_stream, string st_arr[], int length_of_st_arr) :Station(name, time, depth, a_stream) {
		int i = 0;
		length_of_arr = length_of_st_arr;
		for (; i < length_of_st_arr; i++)
			stations[i] = st_arr[i];
	}

	bool add_station(string station) {
		if ((length_of_arr + 1) > 5) {
			return false;
		}
		printf("%d", length_of_arr);
		length_of_arr++;
		stations[length_of_arr - 1] = station;
		return true;
	}


	static Transfer_station * init(string name, int time, float depth, float a_stream, string st_arr[], int length_of_st_arr) {
		if (length_of_st_arr > 5) {
			printf("wrong length of array, you should send the array witn length < 5\n");
			return nullptr;
		}
		Transfer_station *tr_st = new Transfer_station(name, time, depth, a_stream, st_arr, length_of_st_arr);
		return tr_st;
	}

	void printT() {
		int i = 0;
		for (; i < length_of_arr; i++)
			cout << stations[i] << " ";
	}

	void print() {
		cout << "\n---------" << "\n Station's name: " << get_name() << "\n Station's type: transfer station" << "\n time: " << get_time() << "\n Depth: " << get_depth() << "\n Average stream: " << get_a_stream();
		cout << "\n List of stations you can transfer to: ";
		printT();
		cout << "\n---------\n";
	}

	Station * copy() {
		Station *c = new Transfer_station(get_name(), get_time(), get_depth(), get_a_stream(), stations, length_of_arr);
		return c;
	}
};

list<shared_ptr<Station>> * Metro_line(const shared_ptr<Station> &s) { //return a pointer on metro_line, then to use all methods you should dereference the pointer
	if (s->get_time() != 0) {
		cout << "The first station must have time=0\n";
		return nullptr;
	}
	list<shared_ptr<Station>> *ptr_metro_line = new list<shared_ptr<Station>>;
	(*ptr_metro_line).push_front(s);
	return ptr_metro_line;
}

bool add_station(list<shared_ptr<Station>> &lst, const shared_ptr<Station> &s) {
	Station *curr = s.get();
	int curr_time = curr->get_time();
	//time must rise, if we go along the list. check it
	if (lst.back()->get_time() > curr_time) {
		cout << "Travel time from the previous station is more than from the next one - the order is violated\n";
		return 0;
	}
	//no different stations with the same name are allowed. check it
	string curr_name = curr->get_name();
	for (auto i = lst.begin(); i != lst.end(); ++i) {
		curr = (*i).get();
		if (curr->get_name() == curr_name) {
			cout << "Travel time from the previous station is more than from the next one - the order is violated\n";
			return 0;
		}
	}
	//add valid station
	lst.push_back(s);
	return 1;
}

void print_metro_line(const list<shared_ptr<Station>> &lst) {
	Station *j;
	for (auto i = lst.begin(); i != lst.end(); ++i) {
		j = (*i).get();
		j->print();
	}

}


#endif // !Header_stl_H