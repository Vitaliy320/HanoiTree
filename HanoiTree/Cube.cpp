#include "Cube.h"

Cube::Cube() {
	length_ = 1.0;
	size = 1;
}

Cube::Cube(int s) {
	size = s;
	length_ = 1.0;
}

double Cube::getVolume() {
	return length_ * length_ * length_;
}

double Cube::getSurfaceArea() {
	return 6 * length_ * length_;
}

void Cube::setLength(double length) {
	length_ = length;
	Cube::getVolume();
}

double* Cube::getLengthReference() {
	return &length_;
}

bool Cube::compareWithCube(Cube cubeToCompare) {
	return this->getLength() == cubeToCompare.getLength() && this->size == cubeToCompare.size;
}

double Cube::getLength() {
	return length_;
}