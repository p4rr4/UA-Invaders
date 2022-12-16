#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

struct database {
	int punt;
	char name[5];
};

int main() {
	char name[5];
	int punt, i;
	char line[80];
	int count;
	char ch;
	count = 0;

	database datos;


	ofstream file;
	file.open("database.txt", ios::app);

	for (i=0;i<5;i++){
		cout << "Enter your name: ";
		cin >> name;
		cout << "Enter your points: ";
		cin>>punt;
		file << name << " " << punt << endl;
	}
	file.close();

	ifstream infile;
	infile.open("database.txt");

	infile.get(ch);

	while (infile) {
		if (ch=='\n'){
			count++;
		}
		infile.get(ch);
	}
	infile.close();

	ifstream datain;
	datain.open("database.txt", ios::in);

	for (i=0; i<count;i++){
		datain >> datos.name >> datos.punt;
		cout << datos.name << " " << datos.punt << endl;
	}


	//strcpy(name, "PAR");


	datain.close();


	return 0;
}