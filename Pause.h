#pragma once

class Pause : public MusicSymbol {
private:
	
public:
	Pause(Duration d) : MusicSymbol(d) {}

	

	void setMidi() override{
		midi = string("0");
	}
};