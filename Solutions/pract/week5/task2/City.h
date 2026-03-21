#pragma once
class City
{
private:
	char* name;
	long population;

	void copyFrom(const City& other);
	void free();

public:
	City();
	City(const char* name, long population);
	City(const City& other);
	City& operator=(const City& other);
	~City();
};

