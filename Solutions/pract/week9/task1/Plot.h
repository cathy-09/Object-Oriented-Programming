#pragma once
#include "Crop.h"

class Plot 
{
private:
    static int nextId;
    int id;
    double width;
    double height;
    Crop cropType;

public:
    Plot();
    Plot(double width, double height, Crop crop);

    int getId() const;
    double getWidth() const;
    double getHeight() const;
    Crop getCropType() const;

    void setWidth(double w);
    void setHeight(double h);

    void sow(Crop crop);
    void reap();
};