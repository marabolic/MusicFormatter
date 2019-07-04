#pragma once
#include "MidiFile.h"
#include "MusicSymbol.h"
#include <iostream>
#include <vector>
using namespace std;
using namespace smf;

int createMidi(const vector<int> &melody,
	const vector<int> &bass, const vector<int> &mrhythm, const vector<int> &brhythm);