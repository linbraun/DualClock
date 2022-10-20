#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <istream>
using namespace std;

class CityTemps {
public:
	CityTemps() {
		cityName = "None";
		fahrenheitTemp = 0;
		celsiusTemp = 0;
	}
	void SetName(string name) {
		cityName = name;
	}
	void SetTemp(int fahrenheit) {
		fahrenheitTemp = fahrenheit;
		celsiusTemp = 5 * (fahrenheit - 32) / 9;
	}
	string GetName() {
		return cityName;
	}
	int GetFahrenheit() {
		return fahrenheitTemp;
	}
	int GetCelsius() {
		return celsiusTemp;
	}

private:
	string cityName;
	int fahrenheitTemp;
	int celsiusTemp;
};

void readFile(string readFileName, vector<CityTemps>& cityTempsList) {
	// Input file stream
	ifstream inFS;
	inFS.open(readFileName);
	string city;
	int temp;
	
	if (!inFS.is_open()) {
		// Do not proceed if file could not open
		cout << "Could not open file " << readFileName << endl;
	}
	else {
		cout << "Opening file " << readFileName << endl;

		while (!inFS.eof()) {
			// Read city name and temperature to class and list
			inFS >> city;
			inFS >> temp;

			CityTemps cityTemp;
			cityTemp.SetName(city);
			cityTemp.SetTemp(temp);

			cityTempsList.push_back(cityTemp);
		}
		// When done reading file, close file
		cout << "Closing file " << readFileName << endl;
		inFS.close();
	}
}

void writeFile(string writeFileName, vector<CityTemps>& cityTempsList) {
	ofstream outFS;
	outFS.open(writeFileName);
	int i = 0;

	if (!outFS.is_open()) {
		// Do not proceed if file could not open
		cout << "Could not open file " << writeFileName << endl;
	}
	else {
		cout << "Opening file " << writeFileName << endl;
		// Iterate through vector of city temps, writing to file
		for (i = 0; i < cityTempsList.size(); i++) {
			outFS << cityTempsList[i].GetName() << " " << cityTempsList[i].GetCelsius() << endl;	 
		}
		// When done reading file, close file
		cout << "Closing file " << writeFileName << endl;
		outFS.close();
	}
}

int main() {
	// Create vector of CityTemps objects
	vector<CityTemps> cityTempsList;

	// Open file and read from
	string readFileName = "FahrenheitTemperature.txt";
	readFile(readFileName, cityTempsList);
	
	// Create file and write to
	string writeFileName = "CelsiusTemperature.txt";
	writeFile(writeFileName, cityTempsList);

	return 0;
}