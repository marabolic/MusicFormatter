#pragma once
class Duration
{
private:
	double num;
public:
	Duration(double num) {
		this->num = num;
	}

	void setD(double num) {
		this->num = num;
	}
	double getNum()
	{
		return num;
	}

};

