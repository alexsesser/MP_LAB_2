#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <chrono>
#include <algorithm>
#include <clocale> 
#include <stdio.h> 
#include <time.h> 
#include <iterator>
#include <map>
using namespace std;


class Passenger
{
public:
	//сравнение по полям – номер каюты, порт  назначения, ФИО
	string name;
	int cabin;
	int type; //0,1,2,3
	string port;
	Passenger() {}
	Passenger(string name, int cabin, int type, string port)
	{
		this->name = name;
		this->cabin = cabin;
		this->type = type;
		this->port = port;
	}
	bool operator < (Passenger& b)
	{
		if (this->name == b.name)
		{
			return true;
		}
		else
		{
			int res = this->name.compare(b.name);
			return res < 0;
		}
	}
	bool operator <= (Passenger& b)
	{
		if (this->name == b.name)
		{
			return true;
		}
		else
		{
			int res = this->name.compare(b.name);
			return res <= 0;
		}
	}

	bool operator > (Passenger& b)
	{
		if (this->name == b.name)
		{
			return true;
		}
		else
		{
			int res = this->name.compare(b.name);
			return res > 0;
		}
	}

	bool operator >= (Passenger& b)
	{
		if (this->name == b.name)
		{
			return true;
		}
		else
		{
			int res = this->name.compare(b.name);
			return res >= 0;
		}
	}
};



ostream& operator<<(ostream& out, const Passenger& passagir) {
	return out << passagir.name << ":" << passagir.cabin << "," << passagir.type << "-" << passagir.port;
}




template <class T> int BinSearch(vector<T> a, string key, int low, int high)
{
	if (low > high)
	{
		return -1;
	}
	int mid = (low + high) / 2;
	if (a[mid].name == key) {
		return mid;
	}
	if (a[mid].name < key) {
		BinSearch(a, key, mid + 1, high);
	}
	if (a[mid].name > key) {

		BinSearch(a, key, low, mid - 1);
	}
}

template <class T> int LinearSearch(vector<T>& a, int size, string key)
{
	for (int i = 0; i < size; i++) 
	{
		if (a[i].name == key) 
		{
			return i;
		}
	}
	return -1;
}

template<class T>
int partition(vector<T>& nums, int low, int high)
{
	int i = low - 1;
	//choosing pivot as last element 
	T pivot = nums[high];
	for (int j = low; j < high; j++)
	{
		if (nums[j] <= pivot)
		{
			i++;
			swap(nums[i], nums[j]);
		}
	}
	swap(nums[i + 1], nums[high]);
	return i + 1;
}

template<class T>
void quicksort(vector<T>& nums, int low, int high)
{
	if (low < high)
	{
		int pivot = partition(nums, low, high);
		quicksort(nums, low, pivot - 1);
		quicksort(nums, pivot + 1, high);

	}
}

//Passanger

ofstream out_d("D:/учёба/Методы програмирования/Metods_2/graph/ris_grahp.txt");


void handleFile(string fileName, int searchAlgo, string key) {
	string openPath = "D:/учёба/Методы програмирования/Metods_1/test/" + fileName;
	ifstream file(openPath);
	vector <Passenger> data;
	string line, field;
	while (getline(file, line))
	{
		stringstream ss(line);
		int i = 0;
		string name;
		int cabin;
		int type;
		string port;
		while (getline(ss, field, ','))
		{
			switch (i) {
			case 0:
				name = field;
				break;
			case 1:
				cabin = stoi(field);
				break;
			case 2:
				type = stoi(field);
				break;
			case 3:
				port = field;
				break;
			default:
				break;
			}
			++i;
		}
		Passenger pasn(name, cabin, type, port);
		data.push_back(pasn);
	}
	multimap<string, Passenger> tepl;
	auto begin = std::chrono::steady_clock::now();
	switch (searchAlgo)
	{
	case 1:
	{
		begin = std::chrono::steady_clock::now();
		LinearSearch(data, data.size(), key);
		break;
	}
	case 2:
	{
		sort(data.begin(), data.end());
		begin = std::chrono::steady_clock::now();
		BinSearch(data, key, 0, data.size() - 1);
		break;
	}
	case 3:
	{
		begin = std::chrono::steady_clock::now();
		quicksort(data, 0, data.size() - 1);
		BinSearch(data, key, 0, data.size() - 1);
		break;
	}
	case 4:
	{
		for (int i = 0; i < data.size(); i++)
		{
			tepl.insert(make_pair(data[i].name, data[i]));
		}
		begin = std::chrono::steady_clock::now();
		tepl.find(key);
		break;
	}
	default:
		break;
	}
	auto end = chrono::steady_clock::now();
	auto elapsed_ms = chrono::duration_cast<chrono::microseconds>(end - begin);
	cout << data.size() << "\t" << elapsed_ms.count() << endl;
	out_d << data.size() << "\t" << elapsed_ms.count() << endl;
}



// сортировки а, в, е Сортировка выбором Сортировка простыми вставками Быстрая сортировка
int main()
{
	setlocale(LC_ALL, "Russian");
	cout << "Size" << "\t" << "Прямой поиск" << "\n";
	out_d << "Size" << "\t" << "Прямой поиск" << "\n";
	handleFile("test400.txt", 1, "qahcuckczcvu aitrtkzimtvc cymtrjs");
	handleFile("test800.txt", 1, "bygugwblg krwgopy m");
	handleFile("test4000.txt", 1, "pzsewtkhrwpc aisynksrl s");
	handleFile("test8000.txt", 1, "kvdgtoqbbazt amxlxvofmalh fdfhiakpv");
	handleFile("test40000.txt", 1, "lvlsneciihhga edbs ztyyttzg");
	handleFile("test80000.txt", 1, "iolao ixihcv yhdcre");
	handleFile("test120000.txt", 1, "ywmbfffplsqq srcfbcxpe fgca");
	cout << "Size" << "\t" << "Бинарный поиск" << "\n";
	out_d << "Size" << "\t" << "Бинарный поиск" << "\n";
	handleFile("test400.txt", 2, "qahcuckczcvu aitrtkzimtvc cymtrjs");
	handleFile("test800.txt", 2, "bygugwblg krwgopy m");
	handleFile("test4000.txt", 2, "pzsewtkhrwpc aisynksrl s");
	handleFile("test8000.txt", 2, "kvdgtoqbbazt amxlxvofmalh fdfhiakpv");
	handleFile("test40000.txt", 2, "lvlsneciihhga edbs ztyyttzg");
	handleFile("test80000.txt", 2, "iolao ixihcv yhdcre");
	handleFile("test120000.txt", 2, "ywmbfffplsqq srcfbcxpe fgca");
	cout << "Size" << "\t" << "Сортировка + бинарный поиск" << "\n";
	out_d << "Size" << "\t" << "Сортировка + бинарный поиск" << "\n";
	handleFile("test400.txt", 3, "qahcuckczcvu aitrtkzimtvc cymtrjs");
	handleFile("test800.txt", 3, "bygugwblg krwgopy m");
	handleFile("test4000.txt", 3, "pzsewtkhrwpc aisynksrl s");
	handleFile("test8000.txt", 3, "kvdgtoqbbazt amxlxvofmalh fdfhiakpv");
	handleFile("test40000.txt", 3, "lvlsneciihhga edbs ztyyttzg");
	handleFile("test80000.txt", 3, "iolao ixihcv yhdcre");
	handleFile("test120000.txt", 3, "ywmbfffplsqq srcfbcxpe fgca");
	cout << "Size" << "\t" << "Multimap" << "\n";
	out_d << "Size" << "\t" << "Multimap" << "\n";
	handleFile("test400.txt", 4, "qahcuckczcvu aitrtkzimtvc cymtrjs");
	handleFile("test800.txt", 4, "bygugwblg krwgopy m");
	handleFile("test4000.txt", 4, "pzsewtkhrwpc aisynksrl s");
	handleFile("test8000.txt", 4, "kvdgtoqbbazt amxlxvofmalh fdfhiakpv");
	handleFile("test40000.txt", 4, "lvlsneciihhga edbs ztyyttzg");
	handleFile("test80000.txt", 4, "iolao ixihcv yhdcre");
	handleFile("test120000.txt", 4, "ywmbfffplsqq srcfbcxpe fgca");
}