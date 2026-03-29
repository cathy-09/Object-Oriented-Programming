#include <iostream>
#include "HexColourCode.h"

int main()
{
	HexColourCode c1("#FF0000");
	HexColourCode c2("#00FF00");
	HexColourCode c3("#FF0000");

	cout << "c1 = " << c1 << endl;
	cout << "c2 = " << c2 << endl;

	if (c1 == c3)
	{
		cout << "c1 == c3: t" << endl;
	}
	else
	{
		cout << "c1 == c3: f" << endl;
	}

	if ((c2 <=> c1) < 0)
	{
		cout << "c2 < c1: t" << endl;
	}
	else
	{
		cout << "c2 < c1: f" << endl;
	}

	HexColourCode bad2("ZZZZZZ");
	cout << "Bad code defaults to: " << bad2 << endl;

	HexColourCode bad3("#GGG000");
	bad3.setCode("not_a_code");
}