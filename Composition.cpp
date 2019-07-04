#include "Composition.h"



Composition::Composition()
{
	temp = parts.begin();
}

void Composition::writePart(std::vector<Part>::iterator temp) {
	
		cout << "|";
		for (auto itR : temp->right) {
			cout << itR->getMidi() << " ";
		}
		cout << "|" << endl;

		cout << "|";
		for (auto itL : temp->left) {
			cout << itL->getMidi() << " ";
		}
		cout << "|" << endl;
	
}

void Composition::writeComp()
{
	bool one = false;
	for (auto it : parts) {
		cout << "|";
		for (auto itR : it->right) {
			if (itR->getMidi() != "1" && !one)
				cout << itR->getMidi() << " ";
			else {
				if (!one) one = true;
				else {
					if (itR->getMidi() != "1") {
						cout << itR->getMidi();
					}
					else {
						one = false;
						cout << " ";
					}
				}
			}
		}
		cout << "|" << endl;

		one = false;
		cout << "|";
		for (auto itL : it->left) {
			if (itL->getMidi() != "1" && !one)
				cout << itL->getMidi() << " ";
			else {
				if (!one) one = true;
				else {
					if (itL->getMidi() != "1") {
						cout << itL->getMidi();
					}
					else {
						one = false;
						cout << " ";
					}
				}
			}
		}
		cout << "|" << endl << endl;
	}
}

std::vector<Part*>::iterator Composition::nextPart() {
	temp = temp++;
	return temp;
}

std::vector<Part*>::iterator Composition::prevPart() {
	temp = temp--;
	return temp;
}

void Composition::addPart(Part* part) {
	parts.push_back(part);
}

