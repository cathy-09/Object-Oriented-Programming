#define _CRT_SECURE_NO_WARNINGS
#include "Farmer.h"
#include <iostream>

void Farmer::copyFrom(const Farmer& other) 
{
    nameSize = other.nameSize;
    name = new char[nameSize + 1];
    strcpy(name, other.name);

    plotSize = other.plotSize;
    plots = new Plot * [plotSize];
    for (size_t i = 0; i < plotSize; i++)
    {
        plots[i] = other.plots[i];
    }
}

void Farmer::free() 
{
    delete[] name;
    delete[] plots;
}

Farmer::Farmer(const char* n, size_t ns, Plot** p, size_t ps) : nameSize(ns), plotSize(ps) 
{
    name = new char[nameSize + 1];
    strcpy(name, n);
    plots = new Plot * [plotSize];
    for (size_t i = 0; i < plotSize; i++)
    {
        plots[i] = p[i];
    }
}

Farmer::Farmer(const Farmer& other) 
{ 
    copyFrom(other); 
}

Farmer& Farmer::operator=(const Farmer& other) 
{
    if (this != &other) 
    {
        free();
        copyFrom(other);
    }
    return *this;
}

Farmer::~Farmer() 
{
    free(); 
}

void Farmer::addPlot(Plot* plot) 
{
    Plot** newPlots = new Plot * [plotSize + 1];
    for (size_t i = 0; i < plotSize; i++)
    {
        newPlots[i] = plots[i];
    }
    newPlots[plotSize] = plot;
    delete[] plots;
    plots = newPlots;
    plotSize++;
}

void Farmer::printField() const 
{
    for (size_t i = 0; i < plotSize; i++) 
    {
        std::cout << "Plot " << plots[i]->getId() << ": ";
        switch (plots[i]->getCropType()) 
        {
        case Crop::WHEAT:   
            std::cout << "Wheat" << std::endl;
            break;
        case Crop::BARLEY:  
            std::cout << "Barley" << std::endl;
            break;
        case Crop::CORN:   
            std::cout << "Corn" << std::endl;
            break;
        case Crop::NOTHING: 
            std::cout << "Nothing" << std::endl;
            break;
        }
    }
}