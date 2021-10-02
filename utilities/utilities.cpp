#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <algorithm>

#include "../includes/constants.h"
#include "../includes/utilities.h"
using namespace std;
using namespace KP;

bool compareName(std::vector<KP::studentData> &allstudentData){
	int vecSize = allstudentData.size();
	return allstudentData[0].name < allstudentData[vecSize - 1].name;
}

bool compareFinal(std::vector<KP::studentData> &allstudentData){
	int vecSize = allstudentData.size();
	return allstudentData[0].finalgrade > allstudentData[vecSize - 1].finalgrade;
}


int readFile(std::string &file, std::vector<KP::studentData> &allstudentData){
	ifstream inputFile;
	inputFile.open(file);

	if(!inputFile.is_open()){
		return COULD_NOT_OPEN_FILE;
	}

	std::string line;
	std::string token1;
	std::string token2;
	studentData myStudentData;
	stringstream ss;
	while(!inputFile.eof()){
		getline(inputFile, line);
		ss.str(line);

		myStudentData.clear();

		getline(ss, myStudentData.name, SEPERATOR_CHAR);

		getline(ss, token1, SEPERATOR_CHAR);
		myStudentData.midterm1 = stringToInt(token1.c_str());

		getline(ss, token2, SEPERATOR_CHAR);
		myStudentData.midterm2 = stringToInt(token2.c_str());
	}
	inputFile.close();
	return SUCCESS;
}

int calculateFinalGrade(std::vector<KP::studentData> &allstudentData){

	if (allstudentData.size() == 0){
		return VECTOR_CONTAINS_NO_STUDENTS;
	}

	for (int i = 0; i < allstudentData.size(); i++){
		int avg = (allstudentData[i].midterm1 + allstudentData[i].midterm2)/2;
		allstudentData[i].finalgrade = avg;
	}
	return SUCCESS;
}

int writeFile(std::string &file, std::vector<KP::studentData> &allstudentData){
	ofstream outputFile;
	outputFile.open(file.c_str());

	if(!outputFile.is_open()){
		return COULD_NOT_OPEN_FILE;
	}
	for(int i = 0; i < allstudentData.size(); i++){
		continue;
		//no math for operator ofstream char and type studentData
		//outputFile << allstudentData[i] << endl;
	}
	outputFile.close();
	return SUCCESS;
}

int sortStudentData(std::vector<KP::studentData> &allstudentData,KP::SORT_TYPE st){

	if (allstudentData.size() == 0){
		return VECTOR_CONTAINS_NO_STUDENTS;
	}

	switch (st){
		case KP::NAME:
			sort(allstudentData.begin(), allstudentData.end(), compareName);
			break;

		case KP::FINAL_GRADE:
			sort(allstudentData.begin(), allstudentData.end(), compareFinal);
			break;
	}
	return SUCCESS;
}

//if you are debugging the file must be in the project parent directory
std::string DoubleToString(double Number) {
	std::ostringstream ss;
	ss << Number;
	return ss.str();
}

//if myString does not contain a string rep of number returns 0
//if int not large enough has undefined behaviour, 
//this is a very fragile function
//ex. string a="3";
//    int i = stringToInt(a.c_str()); //i contains 3
//    a="s";
//    i = stringToInt(a.c_str()); //i receives 0
int stringToInt(const char *myString) {
	return atoi(myString);
}

//if myString does not contain a string rep of number returns 0
//this is a very fragile function
//ex. string b="4.5";
//    double d = stringToDouble(b.c_str()); //d receives 4.5
double stringToDouble(const char *myString) {
	return atof(myString);
}

