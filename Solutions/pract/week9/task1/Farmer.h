#include "Plot.h"

class Farmer 
{
private:
    char* name;
    size_t nameSize;
    Plot** plots;
    size_t plotSize;
    
    void copyFrom(const Farmer& other);
    void free();

public:
    Farmer(const char* name, size_t nameSize, Plot** plots, size_t plotSize);
    Farmer(const Farmer& other);
    Farmer& operator=(const Farmer& other);
    ~Farmer();

    void addPlot(Plot* plot);
    void printField() const;
};
