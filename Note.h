#pragma once
#include "MusicSymbol.h"
#include "ExceptOctave.h"
#include  <string>
using namespace std;

class Note : public MusicSymbol {
private:
	char letter;
	int octave;
	bool sharp;

public:
	Note(Duration d, char letter = 'c', int octave = 4, bool sharp = false) : MusicSymbol(d) {
		this->letter = letter;
		this->octave = octave;
		this->sharp = sharp;
	}
	Note* thisNote() { return this; }
	void setMidi() override
	{
		string s="";
		s += letter;
		if (sharp) s += string("#");
		s += std::to_string(octave);
		midi = s;
	}

	char getLetter() const { return letter; }
	int getOctave() const { return octave; }
	bool getSharp() const { return sharp; }


	void setLetter(char let) { letter = let; }
	void setOctave(int oct) { 
		if ((this->octave > 3 && oct > 3) || (this->octave < 3 && oct < 3))
			octave = oct; 
		if ((this->octave > 3 && oct < 3) || (this->octave < 3 && oct > 3))
			throw ExceptOctave();
	}
	void setSharp(bool shp) { sharp = shp; }


	void setArgs (char letter, int octave, const string &sharp) {
		if (sharp.empty())
			this->sharp = false;
		else this->sharp = true;
		this->letter = letter;
		this->octave = octave;
	}
};

