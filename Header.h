#ifndef Header_H
#define Header_H
#include <string>
#include <iostream>
#include <cstring>

using namespace std;
class Station
{
private:
	string name; //��� �������
	unsigned int time; //����� � ���� �� ��������� ������� � �������
	unsigned int depth; //������� ��������� ������� � ������
	unsigned int a_stream; //������� ������������ �������������� � "�������/������"
public:
	Station(string name, unsigned int time, unsigned int depth, unsigned int a_stream) :
		name(name), time(time), depth(depth), a_stream(a_stream) {} //��������� ������������ ����� ����� ��������, ����� ��� ������ - unsigned int
	
	/*
		Station(string a, unsigned int b, float c, float d): name(a), time(b), depth(c), a_stream(d) {} //- ������� ����������� ������, � ����� ������ float. �������� � ���, ��� float ����� ���� �������������, ��� ��������� �����������.

		friend Station * newStation(string a, unsigned int b, float c, float d){// ������� newStation, ������� ���������� ��������� �� ������ ������, ���� ������ ��� ����� ������� (��� float'� ������������), ���� ��� - �� nullptr
			Station *p = nullptr;
			if (c>0&&d>0)
			{
				p = new Station(a, b, c, d); //- ���� ��� ��, ��������� ������� �����������
			}
			return p;
		}
	*/
	void stream_change  (unsigned int curr_stream) {
		this->a_stream = curr_stream; //����������� ��������� ���������������
	}
	friend bool operator>(const Station &c1, const Station &c2){
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
	bool station_exist(string name, int time, float depth, float a_stream); //�������� �� ��, ��� � ��������� ����� ������ ����� ��� ������ ��� ��������
	
	virtual void print() { 
		cout << "\n---------" << "\n Station's name: " << name << "\n Station's type: standart station" << "\n time: " << time << "\n Depth: " << depth << "\n Average stream: " << a_stream << "\n---------\n";
	} //�������, ������� �������� ���������� � ����� ���� �������

	virtual Station * copy() {
		Station *c = new Station(name, time, depth, a_stream); 
		return c; //������� ��������� ����� ������ ���� �������
	}
};

class Transfer_station :
	public Station
{
	string stations[5]; //- ������ �����
	int length_of_arr;
public:
	Transfer_station(string name, int time, float depth, float a_stream, string st_arr[], int length_of_st_arr):Station(name, time, depth, a_stream){
		int i = 0;
		length_of_arr = length_of_st_arr;
		for (; i < length_of_st_arr; i++)
			stations[i] = st_arr[i];
	}

	bool add_station(string station) {
		if ((length_of_arr + 1)>5) {
			return false;
		}
		printf("%d",length_of_arr);
		length_of_arr++;
		stations[length_of_arr-1] = station;
		return true;
	}


	static Transfer_station * init(string name, int time, float depth, float a_stream, string st_arr[], int length_of_st_arr) {
		if (length_of_st_arr>5) {
			printf("wrong length of array, you should send the array witn length < 5\n");
			return nullptr;
		}
		Transfer_station *tr_st = new Transfer_station(name, time, depth, a_stream, st_arr, length_of_st_arr);
		return tr_st;
	} 

	void printT() {
		int i=0;
		for (; i < length_of_arr; i++)
			cout << stations[i] <<" "; 
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

struct metro_elem {
	Station *s;
	struct metro_elem *next;
	struct metro_elem *prev;
};

class Metro_line {
private:
	metro_elem *head; //������ ������� ������
	metro_elem *tail; //��������� ������� ������
	int length; //���������� ��������� ������
public: 
		Metro_line(Station *s1){
			metro_elem *h = new metro_elem;
			h->prev = nullptr;
			h->next = nullptr;
			Station *c = s1->copy();
			h->s = c;
			head = h;
			tail = h;
			length = 1;
		};
		static Metro_line * init(Station *s2){
			if (s2 == nullptr) {
				return nullptr;
			}
			if (s2->get_time() != 0){ //����� ������ ������� ������ - ��������� �������. ��������� ������� �������� ������� �������� � ���� �� ����� ����. 
				cout<<"The first station must have time=0\n";
				return nullptr;
			}
			Metro_line *m1 = new Metro_line(s2);
			return m1;
		}

		metro_elem * add_station(Station *curr) { 
			if (curr == nullptr) {
				return nullptr;
			}
			metro_elem *p;
			if (tail->s->get_time() > curr->get_time()) { //��� ��� ���� ����� �� ���������, �� ����� �� ��������� ������� �� ������ ������� � �������� �����������
				cout<<"Travel time from the previous station is more than from the next one - the order is violated\n";
				return nullptr;
			}
			p = head;
			while (p) { //- �� ������ ���� ���� ������� � ����������� ��������� � ����� Metro_line. ������� ������, ��� ��������� �������, ������� �������� �� ��� �������
				if ((p->s)->get_name() == curr->get_name()) { //������������� � ����������� ���������� == ��������� ������ �� ���������
					cout<<"This station already exists\n";
					return nullptr;
				}
				else {
					p = p->next;
				}
			}
			//��� �������� ���������, ����� ���������

			p = new metro_elem;
			if (!p){
				cout << "There is no free memory to add new station, or something goes wrong in the system";
				return nullptr;
			}
			p->prev = tail;
			p->next = nullptr;
			//p->s = curr;
			Station *c = curr->copy();
			p->s = c;
			tail->next = p;
			tail = p;
			length++;
			return p;
		}
		~Metro_line() {
			metro_elem *temp;
			metro_elem *p = head;
			while (p) {
				temp = p;
				p = p->next;
				free(temp);
			}
		}

		int get_length() {
			return length;
		}

		metro_elem * get_head() {
			return head;
		}

		metro_elem * get_tail() {
			return tail;
		}

		void print_line() {
			metro_elem *p = head; 
			while (p) {
				Station *curr = p->s;
				if (!curr) {
					cout << "\nYou want to print an empty Metro_line, maybe there are some problems with copying of the objects\n";
				}
				curr->print();
				p = p->next;
			}
		} 
		
};


#endif // !Header_H




