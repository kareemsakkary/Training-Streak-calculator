#include<iostream>
#include <fstream>
using namespace std;


int main()
{
	string str;
	ifstream Myfile;
	ofstream Output;
	// Names will be printed into the champions file  , You dant have to create it , it will be automatically created
	Output.open("Champions.txt");

	// Put the copied text in the Generate File >> You have to create it manually 
	Myfile.open("Generate.txt");
	while (!Myfile.eof())
	{

		getline(Myfile, str);



		if (str.find("Daily problem solved") != string::npos)
		{
			string name;
			int spaces = 0;
			for (int i = 10; i < str.length(); i++)
			{
				if (str[i] == ':')
				{
					break;
				}

				if (isalpha(str[i]))
				{
					name += str[i];

					if (str[i + 1] == ' ')
					{
						name += ' ';
					}

				}
			}
			Output << name + "\n";
		}
	}
}




