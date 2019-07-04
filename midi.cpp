
#include "midi.h"

int createMidi(const vector<int> &melody, const vector<int> &bass, const vector<int> &mrhythm, const vector<int> &brhythm) {
	MidiFile outputfile;
	outputfile.absoluteTicks();
	vector<uchar> midievent;
	midievent.resize(3);
	int tpq = 48;
	outputfile.setTicksPerQuarterNote(tpq);
	outputfile.addTrack(1);
	outputfile.addTempo(1, 0, 240);

	int i = 0;
	int actiontime = 0;
	midievent[2] = 64;
	while (melody[i] >= 0) { 
		if (melody[i] == 0) { //pauza
			if (mrhythm[i] != 3)
				actiontime += tpq / 2 * mrhythm[i];
		}
		else {
			if (melody[i] == 1) { //akord
				i++;
				int j = i;
				while (melody[j] != 1) {
					midievent[0] = 0x90;
					midievent[1] = melody[j];
					outputfile.addEvent(0, actiontime, midievent);
					j++;
				}
				if (mrhythm[i] != 3)
					actiontime += tpq / 2 * mrhythm[i];

				while (melody[i] != 1) {
					midievent[0] = 0x80;
					outputfile.addEvent(0, actiontime, midievent);
					i++;
				}
				
			}
			else { // nota
				midievent[0] = 0x90;
				midievent[1] = melody[i];
				outputfile.addEvent(0, actiontime, midievent);
				if (mrhythm[i] != 3)
					actiontime += tpq / 2 * mrhythm[i];
				midievent[0] = 0x80;
				outputfile.addEvent(0, actiontime, midievent);
			}
		}
		i++;
	}
	i = 0;
	actiontime = 0;
	while (bass[i] >= 0) {
		if (bass[i] == 0) { //pauza
			if (brhythm[i] != 3)
				actiontime += tpq / 2 * brhythm[i];
		}
		else {
			if (bass[i] == 1) { //akord
				i++;
				int j = i;
				while (bass[j] != 1) {
					midievent[0] = 0x90;
					midievent[1] = bass[j];
					outputfile.addEvent(0, actiontime, midievent);
					j++;
				}
				if (brhythm[i] != 3)
					actiontime += tpq / 2 * brhythm[i];
				while (bass[i] != 1) {
					midievent[0] = 0x80;
					outputfile.addEvent(0, actiontime, midievent);
					i++;
				}
			}
			else { // nota
				midievent[0] = 0x90;
				midievent[1] = bass[i];
				outputfile.addEvent(1, actiontime, midievent);
				if (brhythm[i] != 3)
					actiontime += tpq / 2 * brhythm[i];
				midievent[0] = 0x80;
				outputfile.addEvent(1, actiontime, midievent);
			}
		}
		i++;
	}
	outputfile.sortTracks();
	outputfile.write("jingle_bells.mid");
	return 0;
}