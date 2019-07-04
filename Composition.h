#pragma once
#include "Part.h"
#include <iostream>
#include <vector>


class Composition
{
private:
	
	std::vector<Part*>::iterator temp;
public:
	std::vector<Part*> parts;
	Composition();

	void writePart(std::vector<Part>::iterator temp);
	void writeComp();

	std::vector<Part*>::iterator nextPart();
	std::vector<Part*>::iterator prevPart();

	void addPart(Part *part);
	
};

