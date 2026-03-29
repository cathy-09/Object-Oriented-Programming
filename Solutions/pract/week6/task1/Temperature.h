#pragma once
class Temperature
{
private:
	int temperature;
	char system;
	static int toFahrenheit(int celsius);
	static int toCelsius(int fahrenheit);
	int asCelsius() const;
public:
	Temperature(int temperature, char system);
	int getTemperature() const;
	char getSystem() const;
	void setTemperature(int temperature);
	void setSystem(char system);
	bool operator==(const Temperature& other) const;
	bool operator<(const Temperature& other) const;
	bool operator!=(const Temperature& other) const;
	bool operator<=(const Temperature& other) const;
	bool operator>(const Temperature& other) const;
	bool operator>=(const Temperature& other) const;
	Temperature operator+(const Temperature& other) const;
	Temperature operator-(const Temperature& other) const;
	Temperature& operator+=(const Temperature& other);
	Temperature& operator-=(const Temperature& other);
};

