#include<iostream>
#include"Skill.h"
#include<string.h>
using namespace std;

Skill::Skill(string n, string l) : name(n), level(l)
{
}

string Skill::getName()
{
	return name;
}

string Skill::getLevel()
{
	return level;
}

void Skill::setLevel(string l)
{
	level = l;
}

void Skill::setName(string n)
{
	name = n;
}
