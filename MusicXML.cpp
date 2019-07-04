

#include "MusicXML.h"


using namespace std;


void makeHeader(Composition *comp) {
	string filename = "jingle_bells.xml";
	ofstream outputfile(filename);
	outputfile 
		<< "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>" << endl
		<< "<!DOCTYPE score-partwise PUBLIC" << endl
		<< "\"-//Recordare//DTD MusicXML 3.1 Partwise//EN\"" << endl
		<< "\"http://www.musicxml.org/dtds/partwise.dtd\">" << endl
		<< "<score-partwise version=\"3.1\">" << endl
		<< "<part-list>" << endl
		<< "\t<score-part id=\"Right\"></score-part>" <<endl
		<< "\t<score-part id=\"Left\"></score-part>" << endl
		<< "</part-list>" << endl;

	outputfile << "<part id=\"Right\">" << endl;
	
	for (auto it : comp->parts) {
		partRight(outputfile, it);
	}
	outputfile << "  </part>" << endl;
	outputfile << "  <part id=\"Left\">" << endl;
	for (auto it : comp->parts) {
		partLeft(outputfile, it);
	}
	outputfile << "  </part>" << endl;
	
	outputfile << "</score-partwise>";
	outputfile.close();
}

void printMeasure(ofstream& output, Part* part, char lett, int num) {
	output
		<< "<measure>" << endl
		<< " <attributes>" << endl
		<< "  <divisions>2</divisions>" << endl
		<< "   <time>" << endl
		<< "    <beats>" << part->beat.first << "</beats>" << endl
		<< "    <beat-type>" << part->beat.second << "</beat-type>" << endl
		<< "   </time>" << endl
		<< "   <clef>" << endl
		<< "    <sign>"<< lett <<"</sign>" << endl
		<< "    <line>"<< num << "</line>" << endl
		<< "   </clef>" << endl
		<< " </attributes>" << endl;
}

void partLeft(ofstream &output, Part* part) {
	printMeasure(output, part, 'F', 4);
	vector<MusicSymbol*>::iterator it;
	for (it = part->left.begin(); it != part->left.end(); ++it) {
		if ((*it)->getMidi() == string("0")) {
			if (!(*it)->getInChord()) {
				int d;
				if ((*it)->getDuration() == 4)
					d = 2;
				else d = 1;
				output << "      <note>" << endl
					<< "        <rest/>" << endl
					<< "        <duration>" << d << "</duration>" << endl
					<< "      </note>"<<endl;
			}
		}
		else {
			if ((*it)->getMidi() == string("1")) {

			}
			else {
				if (!(*it)->getInChord()) {
					int d;
					if ((*it)->getDuration() == 4)
						d = 2;
					else d = 1;
					output << "      <note>" << endl
						<< "        <pitch>" << endl
						<< "          <step>" << ((Note*)(*it))->getLetter() << "</step>" << endl
						<< "          <octave>" << ((Note*)(*it))->getOctave() << "</octave>" << endl;
					if (((Note*)(*it))->getSharp())
						output << "          <alter>" << 1 << "</alter>" << endl;
					output << "        </pitch>"<< endl
						<< "        <duration>" << d << "</duration>" << endl
						<< "      </note>" << endl;
				}
			}
		}
		output << "    </measure>" << endl;
	}
	
}

void partRight(ofstream& output, Part* part) {
	printMeasure(output, part, 'G', 2);
	int notes = 0;
	vector<MusicSymbol*>::iterator it;
	for (it = part->right.begin(); it != part->right.end(); ++it) {
		if ((*it)->getMidi() == string("0")) {
			if (!(*it)->getInChord()) {
				int d;
				if ((*it)->getDuration() == 4)
					d = 2;
				else d = 1;
				output
					<< " <note>" << endl
					<< "  <rest/>" << endl
					<< " <duration>" << d << "</duration>" << endl;
				if ((*it)->isFirst()) {
					output << " <tie type=\"start\"/>" << endl;
				}
				if ((*it)->isSecond()) {
					output << " <tie type=\"end\"/>" << endl;
				}

				output << " </note>" << endl;
			}
		}
		else {
			if ((*it)->getMidi() == string("1")) {
				notes = 0;
			}
			else {
				if (!(*it)->getInChord()) {
					int d;
					if ((*it)->getDuration() == 4)
						d = 2;
					else d = 1;
					output 
						<< " <note>" << endl
						<< "  <pitch>" << endl
						<< "   <step>" << ((Note*)(*it))->getLetter() << "</step>" << endl
						<< "   <octave>" << ((Note*)(*it))->getOctave() << "</octave>" << endl;
					if (((Note*)(*it))->getSharp())
						output << "   <alter>" << 1 << "</alter>" << endl;
					output << "  </pitch>" << endl
						<< " <duration>" << d << "</duration>" << endl;
					if ((*it)->isFirst()) {
						output << " <tie type=\"start\"/>" << endl;
					}
					if ((*it)->isSecond()) {
						output << " <tie type=\"end\"/>" << endl;
					}
					output	<< " </note>" << endl;
				}
				else {
					int d;
					if ((*it)->getDuration() == 4)
						d = 2;
					else d = 1;
					output << " <note>" << endl;
					notes++;
					if (notes != 1) {
						output << "  <chord/>" << endl;
					}
					output 
						<< "  <pitch>" << endl
						<< "   <step>" << ((Note*)(*it))->getLetter() << "</step>" << endl
						<< "   <octave>" << ((Note*)(*it))->getOctave() << "</octave>" << endl;
					if (((Note*)(*it))->getSharp())
						output << "   <alter>" << 1 << "</alter>" << endl;
					output << "  </pitch>" << endl
						<< " <duration>" << d << "</duration>" << endl;
					if (notes == 1) {
						if ((*it)->isFirst()) {
							output << " <tie type=\"start\"/>" << endl;
						}
						if ((*it)->isSecond()) {
							output << " <tie type=\"end\"/>" << endl;
						}
					}
					output	<< " </note>" << endl;
				}
			}
		}
		output << "</measure>" << endl;
	}
}

