#pragma once
#include "Duration.h"
#include <iostream>
#include <string>
#include <regex>
#include <fstream>

class MusicSymbol
{
protected:
	Duration duration;
	std::string midi;
	bool inChord = false;
	bool firstSplit = false, secondSplit = false;
public:
	MusicSymbol(Duration d) : duration(d) {}
	void setDur(double d) {
		duration.setD(d);
	}
	double getDuration()
	{
		return duration.getNum();
	}
	virtual void setMidi() {}

	void firstS() { firstSplit = true; }
	void secondS() { secondSplit = true; }

	bool getInChord() const { return inChord; }
	void setInChord(bool in) { inChord = in; }

	bool isFirst() { return firstSplit; }
	bool isSecond() { return secondSplit; }


	std::string getMidi() { return midi; }

	/*friend std::ostream & operator << (std::ostream & os, const MusicSymbol *s)
	{
		
	}*/
};

