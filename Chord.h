#pragma once
#include "MusicSymbol.h"
#include "Note.h"
#include <iterator>
#include "Pause.h"

class Chord :
	public MusicSymbol
{
private:
	
public:
	vector<Note> notes;
	Chord(Duration d) : MusicSymbol(d){ }

	void divide(std::vector<MusicSymbol*> *right, std::vector<MusicSymbol*> *left, Duration d);//proveri da li se menja vektor

	void addNote(Note n) {
		n.setInChord(true);
		notes.push_back(n);
	}

	void setMidi() {
		midi = "1";
	}
};

