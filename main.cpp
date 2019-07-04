

#include "Chord.h"
#include "Note.h"
#include <map>
#include "Pause.h"
#include <functional>
#include "Part.h"
#include "midi.h"
#include "Composition.h"
#include "MusicXML.h"

using namespace std;

std::map<string, string> noteKey;
map<string, int> noteMidi;


void convertMidi(vector<MusicSymbol*> right, vector<MusicSymbol*> left, vector<int> *melody,vector<int> *bass,vector<int> *mrhythm,vector<int> *brhythm) {
	vector<MusicSymbol*>::iterator itR = right.begin();
	vector<MusicSymbol*>::iterator itL = left.begin();
	map<string, int>::iterator itMap;

	for (itR = right.begin(), itL = left.begin(); itL != left.end() || itR != right.end(); ++itR, ++itL) {
		if ((*itR)->getMidi() == string("1") || (*itL)->getMidi() == string("1")) {
			melody->push_back(1);
			bass->push_back(1);
			mrhythm->push_back(3);
			brhythm->push_back(3);
			continue;
		}
		else {
			if ((*itR)->getMidi() == string("0") && (*itL)->getMidi() == string("0")) {
				melody->push_back(0);
				bass->push_back(0);
			}
			else {
				if ((*itR)->getMidi() == string("0")) {
					melody->push_back(0);
					for (itMap = noteMidi.begin(); itMap != noteMidi.end(); ++itMap)
						if ((*itL)->getMidi() == itMap->first) {
							bass->push_back(itMap->second);
							break;
						}
				}
				else {
					if ((*itL)->getMidi() == string("0")) {
						bass->push_back(0);
						for (itMap = noteMidi.begin(); itMap != noteMidi.end(); ++itMap)
							if ((*itR)->getMidi() == itMap->first) {
								melody->push_back(itMap->second);
								break;
							}
					}
					else {
						for (itMap = noteMidi.begin(); itMap != noteMidi.end(); ++itMap)
							if ((*itL)->getMidi() == itMap->first) {
								bass->push_back(itMap->second);
								break;
							}
						for (itMap = noteMidi.begin(); itMap != noteMidi.end(); ++itMap)
							if ((*itR)->getMidi() == itMap->first) {
								melody->push_back(itMap->second);
								break;
							}
					}
				}
			}
		}



		if ((*itR)->getDuration() == 4) {
			if ((*itR)->getInChord() && (*itR)->getMidi() == string("0")) {
				mrhythm->push_back(3);
				brhythm->push_back(2);
			}
			else {
				if ((*itL)->getInChord() && (*itL)->getMidi() == string("0")) {
					mrhythm->push_back(2);
					brhythm->push_back(3);
				}
				else {
					mrhythm->push_back(2);
					brhythm->push_back(2);
				}
			}
		}
		else {
			if ((*itR)->isFirst()) {
				if ((*itR)->getInChord() && (*itR)->getMidi() == string("0")) {
					mrhythm->push_back(3);
					brhythm->push_back(2);
				}
				else {
					if ((*itL)->getInChord() && (*itL)->getMidi() == string("0")) {
						mrhythm->push_back(2);
						brhythm->push_back(3);
					}
					else {
						mrhythm->push_back(2);
						brhythm->push_back(2);
					}
				}
			}
			else {
				if ((*itR)->isSecond()) {
					mrhythm->push_back(3); //svira se prethodna dugo
					brhythm->push_back(3);
				}
				else {
					if ((*itR)->getInChord() && (*itR)->getMidi() == string("0")) {
						mrhythm->push_back(3);
						brhythm->push_back(1);
					}
					else {
						if ((*itL)->getInChord() && (*itR)->getMidi() == string("0")) {
							mrhythm->push_back(1);
							brhythm->push_back(3);
						}
						else {
							mrhythm->push_back(1);
							brhythm->push_back(1);
						}
					}
				}
			}
		}
	}
	/*for (itR = right.begin(); itR != right.end(); ++itR, ++itL) {
		if ((*itR)->getMidi() == string("0") && (*itL)->getMidi() != string("1")) {
			melody->push_back(0);
		}
		else {
			if ((*itR)->getMidi() == string("1")) {
				melody->push_back(1);
			}
			else {
				for (itMap = noteMidi.begin(); itMap != noteMidi.end(); ++itMap)
				{
					if ((*itR)->getMidi() == itMap->first) {
						melody->push_back(itMap->second);
						break;
					}
				}
			}
		}
		if ((*itR)->getDuration() == 4)
			mrhythm->push_back(2);
		else
			mrhythm->push_back(1);
	}

	itR = right.begin();

	for (itL = left.begin(); itL != left.end(); ++itL, ++itR) {
		if ((*itL)->getMidi() == string("0") && (*itR)->getMidi() != string("1")) {
			bass->push_back(0);
		}
		else {
			if ((*itL)->getMidi() == string("1")) {
				bass->push_back(1);
			}
			else {
				for (itMap = noteMidi.begin(); itMap != noteMidi.end(); ++itMap) {
					if ((*itL)->getMidi() == itMap->first) {
						bass->push_back(itMap->second);
						break;
					}
				}
			}
		}
		
		if ((*itL)->getDuration() == 4)
			brhythm->push_back(2);
		else
			brhythm->push_back(1);
	}*/
}

void readNote(char c, Note* note) {

	map<string, string>::iterator itr;
	for (itr = noteKey.begin(); itr != noteKey.end(); ++itr) {

		string s = "";
		s += c;
		if (itr->first == s) {
			string n = itr->second;
			//std::cout << "n: " << n << endl;
			//seckanje note
			regex rx("([a-zA-z]*)([#]*)([1-9]*).*");
			smatch result;
			if (regex_match(n, result, rx))
			{
				string let = result.str(1).c_str();
				string sharp = result.str(2);
				int oct = atoi(result.str(3).c_str());
				char letter = let[0];
				note->setArgs(letter, oct, sharp);
				note->setMidi();
				break;
				//std::cout << note->getLetter() << " "
					//<< note->getSharp() << " " << note->getOctave() << endl;
			}
		}
	}
}

Part * addSplitted(Part* part, double beats, double beatType) {
	std::vector<MusicSymbol*>::iterator lastL, lastR;
	tie(lastL, lastR) = part->lastNote();
	Part* newpart = new Part(beats, beatType);

	if ((*lastL)->getMidi() == string("0")) {  //ako je bila pauza
		Pause* p = new Pause((*lastL)->getDuration());
		p->setMidi();
		p->secondS();
		newpart->left.push_back(p);
	}
	else {
		if ((*lastL)->getMidi() == string("1")) { //ako je bio akord 
			lastL++;
			Chord *ch = new Chord((*lastL)->getDuration());
			ch->setMidi();
			ch->secondS();
			while ((*lastL)->getMidi() != string("1")) {
				if ((*lastL)->getMidi() == string("0")) {
					lastL++;
					continue;
				}
				Note* n = new Note((*lastL)->getDuration(), ((Note*)(*lastL))->getLetter(),
					((Note*)(*lastL))->getOctave(), ((Note*)(*lastL))->getSharp());
				n->secondS();
				n->setMidi();
				ch->addNote(*n);
				lastL++;
			}
			newpart->addChord(ch);
		}
		else {
			if ((*lastL)->getMidi() == string("0")) {
				lastL++;
			}
			else {
				Note* n = new Note((*lastL)->getDuration(), ((Note*)(*lastL))->getLetter(),
					((Note*)(*lastL))->getOctave(), ((Note*)(*lastL))->getSharp());
				n->secondS();
				n->setMidi();
				newpart->left.push_back(n);
			}
		}
	}

	if ((*lastR)->getMidi() == string("0")) {  //ako je bila pauza
		Pause* p = new Pause((*lastR)->getDuration());
		p->setMidi();
		p->secondS();
		newpart->right.push_back(p);
	}
	else {
		if ((*lastR)->getMidi() == string("1")) {  //akord
			lastR++;
			Chord *ch = new Chord((*lastR)->getDuration());
			ch->setMidi();
			ch->secondS();
			while ((*lastR)->getMidi() != string("1")) {
				if ((*lastR)->getMidi() == string("0")) {
					lastR++;
					continue;
				}
				Note* n = new Note((*lastR)->getDuration(), ((Note*)(*lastR))->getLetter(),
					((Note*)(*lastR))->getOctave(), ((Note*)(*lastR))->getSharp());
				n->secondS();
				n->setMidi();
				ch->addNote(*n);
				lastR++;
			}
			newpart->addChord(ch);
		}
		else {
			if ((*lastL)->getMidi() == string("0")) {
				lastL++;
			}
			else {
				Note* n = new Note((*lastR)->getDuration(), ((Note*)(*lastR))->getLetter(),
					((Note*)(*lastR))->getOctave(), ((Note*)(*lastR))->getSharp());
				n->secondS();
				n->setMidi();
				newpart->right.push_back(n);
			}
		}
	}
	
	//std::vector<MusicSymbol*>::iterator last;
	//last = lastL;
	//int done1 = 0;
	//while (!done1) {
	//	if ((*last)->getMidi() == string("0")) {

	//	}

	//	last = lastR;
	//	done1 = 1;
	//}


	return newpart;
}

void read(string filename, Composition* comp, double beats, double beatType)
{
	std::ifstream file(filename);
	bool open = false, wasOpened = false;
	int countInnerSpaces = 0;
	vector<Note> inside;
	vector<int> *melody = new vector<int>, *bass = new vector<int>, *mrhyhm = new vector<int>, *brhythm = new vector<int>;
	Part *part = new Part(beats, beatType);
	Pause* pause; Note *note; Chord *chord;
	while (!file.eof()) {

		Duration d(-1);
		pause = new Pause(d); note = new Note(d); chord = new Chord(d);

		if (part->full()) {
			if (part->getSplitted()) {
				part = addSplitted(part, beats, beatType);
			}
			else
				part = new Part(beats, beatType);
		}
		
		char c = file.get();
		if (file.eof()) 
			break;
	

		switch (c) {
		case '[': open = true; break;
		case ']':
			open = false; //ovde provera da li su cetvrtine ili osmine
			if (countInnerSpaces != 0) { //bilo je razmaka: osmine jedna za drugom
				vector<Note>::iterator itr;
				Note* n;
				for (itr = inside.begin(); itr != inside.end(); ++itr) {
					n = new Note(*itr);
					n->setDur(8);
					n->setMidi();
					part->addNote(n);
				}
				inside.clear();
			}

			else {
				//nema razmaka, akord cetvrtina
				chord->setDur(4);
				chord->setMidi();
				vector<Note>::iterator itr;
				Note* n;
				for (itr = inside.begin(); itr != inside.end(); ++itr) {
					n = new Note(*itr);
					n->setDur(4);
					n->setMidi();
					chord->addNote(*n);
					//readNote(c, note);
				}
				part->addChord(chord);
				inside.clear();
			}
			break;
		case ' ':
			if (open == false) {
				pause->setDur(8);
				pause->setMidi();
				part->addPause(pause);
			}
			else { countInnerSpaces++; }
			break;
		case '|':
			pause->setDur(4);
			pause->setMidi();
			part->addPause(pause);
			break;
		case '\n': break;
		default:
			//cita notu

			if (open) {
				readNote(c, note);
				inside.push_back(*note);
			}
			else {
				note->setDur(4);
				readNote(c, note);
				part->addNote(note);
			}
		}
		if (part->full()) {
			convertMidi(part->right, part->left, melody, bass, mrhyhm, brhythm);
			comp->addPart(part);
			
		}

	}
	if (!part->full()) {
		convertMidi(part->right, part->left, melody, bass, mrhyhm, brhythm);
		comp->addPart(part);
		
	}
	file.close();
	//kraj nizova
	melody->push_back(-1);
	bass->push_back(-1);
	mrhyhm->push_back(-1);
	brhythm->push_back(-1);
	createMidi(*melody, *bass, *mrhyhm, *brhythm);
}

void mapNotes(std::string fileName) {

	std::ifstream file(fileName);
	string lineText;
	regex rx("([^,]*),([^,]*),([^,]*).*");

	while (getline(file, lineText))
	{
		smatch result;
		if (regex_match(lineText, result, rx))
		{
			string key = result.str(1);
			string note = result.str(2);
			int midiNum = atoi(result.str(3).c_str());

			noteMidi.insert(pair<string, int>(note, midiNum));
			//std::cout << key << " " << note;
			noteKey.insert(pair<string, string>(key, note));
		}
	}
	file.close();

	/*
	map<string, int>::iterator itr;
	std::cout << "\nThe map noteMidi is : \n";
	std::cout << "\tKEY\tELEMENT\n";
	for (itr = noteMidi.begin(); itr != noteMidi.end(); ++itr) {
		std::cout << '\t' << itr->first
			<< '\t' << itr->second << '\n';
	}
	std::cout << endl;

	map<string, string>::iterator itr1;
	std::cout << "\nThe map noteMidi is : \n";
	std::cout << "\tKEY\tELEMENT\n";
	for (itr1 = noteKey.begin(); itr1 != noteKey.end(); ++itr1) {
		std::cout << '\t' << itr1->first
			<< '\t' << itr1->second << '\n';
	}
	std::cout << endl;
	*/
}

void menu1()
{
	std::cout << "1. Putanja do falja za mapiranje" << endl
		 << "2. Putanja do fajla sa notama" << endl
		 << "3. Unesi beats i beatType " << endl
		 << "4. Eksportuj u Midi format" << endl
		<< "5 << Eksportuj u BMP format" << endl
		<< "6. Ekspirtuj u MusicXML fomrat" << endl
		<< "7. Iteriraj kroz taktove" << endl;
}

int main() {
	/*int command;
	cin >> command;
	string mapFilePath, inputFilePath;
	int beats, beatType;
	switch (command) {
	case 1: cin >> mapFilePath; mapNotes(mapFilePath); break;
	case 2: cin >> inputFilePath; break;
	case 3: cin >> beats >> beatType;
		if (beatType != 4 && beatType != 8)
			cout << "Greska: moze beatType da bude samo 4 ili 8" << endl;

	case 4:
	}*/

	string mapFilePath = "map.txt";
	//cin >> mapFilePath;
	mapNotes(mapFilePath);

	string inputFilePath = "jingle_bells.txt";
	int beats, beatType;
	cout << "unesi beats i beatType\n";
	cin >> beats >> beatType;
	Composition *comp = new Composition();
	read(inputFilePath, comp, beats, beatType);
	makeHeader(comp);
	comp->writeComp();
	system("PAUSE");
	return 0;
}
