#include "Plot.h"

int Plot::nextId = 1;

Plot::Plot() : id(nextId++), width(50), height(50), cropType(Crop::NOTHING)
{

}

Plot::Plot(double width, double height, Crop crop) : id(nextId++), width(this->width), height(this->height), cropType(crop)
{

}

int Plot::getId() const 
{ 
	return id; 
}
double Plot::getWidth() const 
{
	return width;
}
double Plot::getHeight() const
{
	return height;
}
Crop Plot::getCropType() const 
{
	return cropType;
}

void Plot::setWidth(double w) 
{ 
	width = w; 
}
void Plot::setHeight(double h) 
{
	height = h; 
}

void Plot::sow(Crop crop) 
{ 
	cropType = crop; 
}

void Plot::reap() 
{
	cropType = Crop::NOTHING; 
}