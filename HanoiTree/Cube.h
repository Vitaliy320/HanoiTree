#pragma once

class Cube
{
public:
	int size;
	double getVolume();
	double getSurfaceArea();
	void setLength(double length);
	double* getLengthReference();
	double getLength();
	Cube();
	Cube(int s);
	bool compareWithCube(Cube cubeToCompare);
private:
	double length_;
};

