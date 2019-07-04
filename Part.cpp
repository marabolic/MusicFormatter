#include "Part.h"
#include "midi.h"

double Part::sum_ = 0;



void Part::writeNote()
{
	cout << (*temp)->getMidi() << endl;
}

void Part::choseHand()
{
	cout << "desna - 0,  leva - 1" << endl;
	int hand;
	cin >> hand;
	if (hand == 0) { //desna
		temp = right.begin();
	}
	else { //leva
		temp = left.begin();
	}
}

pair< vector<MusicSymbol*>::iterator, vector<MusicSymbol*>::iterator> Part::lastNote() // probolem ovde, vrati prazan akord, onaj prvi sto je midi 1
{
	std::vector<MusicSymbol*>::iterator lastL, lastR;
	for (std::vector<MusicSymbol*>::iterator l = left.begin(); l != left.end(); ++l) {
		if ((*l)->isFirst()) {
			lastL = l;
			break;
		}
	}

	for (std::vector<MusicSymbol*>::iterator r = right.begin(); r != right.end(); ++r) {
		if ((*r)->isFirst()) {
			lastR = r;
			break;
		}
	}
	return make_pair(lastL, lastR);
}

std::vector<MusicSymbol*>::iterator Part::nextNote() {
	temp = temp++;
	return temp;
}

std::vector<MusicSymbol*>::iterator Part::prevNote() {
	temp = temp--;
	return temp;
}


void Part::addChord(Chord *chord) {
	bool canSum = false;
	if (sum_ + 1 / chord->getDuration() <= beat.first / beat.second) {
		sum_ += 1 / chord->getDuration();
		canSum = true;
	}
	if (chord->getDuration() == 4.0 && beat.first / beat.second - sum_ == 0.125 && !canSum) {
		//split
		vector<Note>::iterator itr;
		Note* n;
		Duration d(8);
		Chord* ch = new Chord(d);
		ch->firstS();
		ch->setMidi();
		for (itr = chord->notes.begin(); itr != chord->notes.end(); ++itr) {
			n = new Note(d, itr->getLetter(), itr->getOctave(), itr->getSharp());
			n->firstS();
			n->setMidi();
			ch->addNote(*n);
		}
		splitted = true;
		sum_ = 0;
		partFull = true;
		
		ch->divide(&right, &left, d);
	}
	else {
		Duration d(4);
		chord->divide(&right, &left, d);

		if (sum_ == beat.first / beat.second) {
			sum_ = 0;
			partFull = true;
		}
	}
	
}

void Part::addNote(Note *note) {
	bool canSum= false;
	if (sum_ + 1 / note->getDuration() <= beat.first / beat.second) {
		sum_ += 1 / note->getDuration();
		canSum = true;
	}
	if (note->getDuration() == 4.0 && beat.first / beat.second - sum_ == 0.125 && !canSum) {
		//split
		Duration d(8);
		Note *n = new Note(d, note->getLetter(), note->getOctave(), note->getSharp());
		n->firstS();
		n->setMidi();
		if (note->getOctave() > 3) {
			right.push_back(n);
			Pause *pause = new Pause(d);
			pause->firstS();
			pause->setMidi();
			left.push_back(pause);
		}
		else {
			left.push_back(n);
			Pause *pause = new Pause(d);
			pause->firstS();
			pause->setMidi();
			right.push_back(pause);
		}
		splitted = true;
		sum_ = 0;
		partFull = true;
	}
	else
	{
		if (note->getOctave() > 3) {
			right.push_back(note);
			Duration d(note->getDuration());
			Pause *pause = new Pause(d);
			pause->setMidi();
			left.push_back(pause);
		}
		else {
			left.push_back(note);
			Duration d(note->getDuration());
			Pause *pause = new Pause(d);
			pause->setMidi();
			right.push_back(pause);
		}
		if (sum_ == beat.first / beat.second) {
			sum_ = 0;
			partFull = true;
		}
	}
}

void Part::addPause(Pause *pause)
{
	bool canSum = false;
	if (sum_ + 1 / pause->getDuration() <= beat.first / beat.second) {
		sum_ += 1 / pause->getDuration();
		canSum = true;
	}
	if (pause->getDuration() == 4.0 && beat.first / beat.second - sum_ == 0.125 && !canSum) {
		//split
		Duration d(8);
		Pause *p = new Pause(d);
		p->setMidi();
		p->firstS();
		left.push_back(p);
		right.push_back(p);
		splitted = true;
		partFull = true;
		sum_ = 0;
	}
	else {
		left.push_back(pause);
		right.push_back(pause);
		if (sum_ == beat.first / beat.second) {
			sum_ = 0;
			partFull = true;
		}
	}
}

//MusicSymbol* Part::get_symbol()
//{
//	
//}