#pragma once
#include<iostream>
using namespace std;

class Skill {
private:
	string skillName;	//like c++, java, python, etc
	string expertiseLevel; //beginer, advanced, etc

public:
	Skill(string, string);
	string getName();
	string getLevel();
	void setLevel(string);
	void setName(string);
};