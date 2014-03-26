#include <iostream>
#include <fstream>
#include <string>

using namespace std;
int main(int argc, char** argv){
	std::fstream myfile;
	string line;
	myfile.open("test.txt");
	while(getline(myfile, line)){
		std::string::iterator end_pos = std::remove(line.begin(), line.end(), ' ');
		line.erase(end_pos, line.end());
		cout << line << "\n";
	}
	myfile.close();
	std::string num = "0.6";
	double temp = ::atof(num.c_str());
	cout << temp;
	return 0;
}
