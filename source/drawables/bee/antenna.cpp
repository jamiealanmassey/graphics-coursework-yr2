#include "antenna.h"

Antenna::Antenna()
{
}

Antenna::~Antenna()
{
}

void Antenna::initialise()
{
	
}

void Antenna::draw()
{
	glPushMatrix();
	this->transform();
	glPopMatrix();
}

void Antenna::update()
{
}