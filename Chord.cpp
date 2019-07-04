#include "Chord.h"

void Chord::divide(std::vector<MusicSymbol*> *right, std::vector<MusicSymbol*> *left, Duration d) { //proveri da li se menja vektor

	bool leftExist = false, rightExist = false;
	std::vector<Note>::iterator it;
	Chord* start = new Chord(d), *stop = new Chord(d);
	if (this->isFirst()) {
		start->firstS();
		stop->firstS();
	}
	start->setMidi(); stop->setMidi();
	right->push_back(start);
	left->push_back(start);
	int countl = 0, countr = 0;

	for (it = notes.begin(); it != notes.end(); ++it) {
		if (it->getOctave() > 3) {
			right->push_back(it->thisNote());
			rightExist = true;
			countr++;
		}
		else {
			left->push_back(it->thisNote());
			leftExist = true;
			countl++;
		}
	}

	if (!rightExist) {
		Pause* pause;
		for (it = notes.begin(); it != notes.end(); ++it) {
			pause = new Pause(d);
			pause->setMidi();
			if (start->isFirst())
				pause->firstS();
			pause->setInChord(true);
			right->push_back(pause);
		}
	}
	else
		if (countr < countl) {
			Pause* pause;
			int num = countl - countr;
			while (num > 0) {
				pause = new Pause(d);
				pause->setMidi();
				if (start->isFirst())
					pause->firstS();
				pause->setInChord(true);
				right->push_back(pause);
				num--;
			}
		}
	if (!leftExist) {
		Pause* pause;
		for (it = notes.begin(); it != notes.end(); ++it) {
			pause = new Pause(d);
			if (start->isFirst())
				pause->firstS();
			pause->setMidi();
			pause->setInChord(true);
			left->push_back(pause);
		}
	}
	else 
		if (countr > countl) {
			Pause* pause;
			int num = countr - countl;
			while (num > 0) {
				pause = new Pause(d);
				if (start->isFirst())
					pause->firstS();
				pause->setMidi();
				pause->setInChord(true);
				left->push_back(pause);
				num--;
			}
		}

	

	right->push_back(stop);
	left->push_back(stop);

}