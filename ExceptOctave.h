#pragma once
#include <iostream>
#include <string>
using namespace std;
class ExceptOctave {
	friend ostream& operator<<(ostream& it, const ExceptOctave&) {
		return it << "Ne moze se promeniti ruka!";
	}
};