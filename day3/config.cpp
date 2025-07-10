#include <iostream>
#include <vector>

using namespace std;

struct Config {
	string pattern;
	vector<string> files;
	bool caseInsensitive;

	void patch(int argc, char* argv[])
	{
		if (argc < 3)
		{
			cout << "Usage: " << argv[0] << " pattern file(or files[-i])" << endl;
			exit(1);
		}

		caseInsensitive = false;
		vector<string> nonFlagArgs = {};

		for (int i = 1; i < argc; ++i)
		{
			string arg = argv[i];

			if (arg == "-i")
			{
				caseInsensitive = true;
			}
			else {
				nonFlagArgs.push_back(arg);
			}
		}

		if (nonFlagArgs.empty())
		{
			cout << "Error: Pattern not provided." << endl;
			exit(1);
		}

		pattern = nonFlagArgs[0];

		if (nonFlagArgs.size() < 2)
		{
			cout << "Error: No input files provided." << endl;
			exit(1);
		}

		files = vector<string>(nonFlagArgs.begin() + 1, nonFlagArgs.end());
	}
};