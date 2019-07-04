#pragma once

#include "Note.h"
#include "Chord.h"
#include "Pause.h"

#include <vector>


class Part {

private:
	bool note_pause = false; //note je true, pause je false, bitno samo ako je splitted = true
	bool splitted = false;
	bool partFull = false;
	
	static double sum_;

	std::vector<MusicSymbol*>::iterator temp;
public:
	std::pair<double, double> beat;
	std::vector<MusicSymbol*> right;
	std::vector<MusicSymbol*> left;
	Part(double beats, double beatType) {
		beat.first = beats;
		beat.second = beatType;
	}
	bool getSplitted() { return splitted; }
	void addChord(Chord*); 
	void addNote(Note*);
	void addPause(Pause*);

	//za iteriranje

	void writeNote();

	void choseHand(); 

	pair< vector<MusicSymbol*>::iterator, vector<MusicSymbol*>::iterator> lastNote();
	std::vector<MusicSymbol*>::iterator nextNote();
	std::vector<MusicSymbol*>::iterator prevNote();

	//

	bool full() { return partFull; }

};

