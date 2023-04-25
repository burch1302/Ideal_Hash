#include<iostream>
#include<list>
#include<cstring>
using namespace std;

// Hash table to implamete 905, jimy

class HashTable {
private:
	static const int hashGroups = 10;//amount of lists
	//��� ����� �������� ����� ������� ����� ��������� � ���� ������� � �������� 
	//� ������ ���� ������ � ���� ���� , �� ���� ���� � �������� 
	list<pair<int, string>> table[hashGroups]; // list 1 , index 0 , list 2 index 1...

public:
	bool isEmpty() const;
	int hashFunc(int key);
	void insertItem(int key, string value);
	void removeItem(int key);
	string serchTable(int key);
	void printTable();

};

bool HashTable::isEmpty() const{
	int sum{};
	for (int i{}; i < hashGroups; i++) {
		sum += table[i].size();
	}

	if (!sum) {
		return true;
	}
	return false;
}

int HashTable::hashFunc(int key) {
	return key % hashGroups; //key: 905, in return , this function will spit out 5.
}

void HashTable::insertItem(int key, string value) {
	int hashValue = hashFunc(key);
	auto& cell = table[hashValue];
	auto bItr = begin(cell);
	bool keyExists = false;
	for (; bItr != end(cell); bItr++) {
		if (bItr->first == key) {
			keyExists = true;
			bItr->second = value;
			cout << "[WARNING] Key exists. Value replaced."<<endl;
			break;
		}
	}

	if (!keyExists) {
		cell.emplace_back(key, value);
	}
	return;
}

void HashTable::removeItem(int key) {
	int hashValue = hashFunc(key);
	auto& cell = table[hashValue];
	auto bItr = begin(cell);
	bool keyExists = false;
	for (; bItr != end(cell); bItr++) {
		if (bItr->first == key) {
			keyExists = true;
			bItr = cell.erase(bItr);
			cout << "[INFO] Item removed." << endl;
			break;
		}
	}

	if (!keyExists) {
		cout << "[WARNING] KEy not found.Pair not remove." << endl;
	}
	return;
	
}

void HashTable::printTable() {
	for (int i{}; i < hashGroups; i++) {
		if (table[i].size() == 0) continue;

		auto bItr = table[i].begin();
		for (; bItr != table[i].end(); bItr++) {
			cout << "[INFO] Key: "<<bItr->first<<"Value: "<<bItr->second<<endl;
		}
	}
	return;
}

int main() {
	HashTable HT;

	if (HT.isEmpty()) {
		cout << "Correct answe. Good job."<<endl;
	}
	else {
		cout << "oh oh oh. We need to chek out code!"<<endl;
	}

	HT.insertItem(905, "Danya");
	HT.insertItem(301, "Bob");
	HT.insertItem(407, "Pedro");
	HT.insertItem(332, "GubkaBob");
	HT.insertItem(553, "Sendi");
	HT.insertItem(553, "Squid");

	HT.printTable();

	HT.removeItem(407);
	HT.removeItem(100);

	if (HT.isEmpty()) {
		cout << "oh oh oh. We need to chek out code!" << endl;
	}
	else {
		cout << "Correct answer.GJ!" << endl;
	}

	return 0;
}