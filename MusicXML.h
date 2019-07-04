#pragma once
#include "Composition.h"
#include "Part.h"
#include <iostream>
#include <fstream>

void makeHeader(Composition *comp);
void printMeasure(ofstream& output, Part* part, char lett, int num);
void partLeft(ofstream& output, Part* part);
void partRight(ofstream& output, Part* part);
