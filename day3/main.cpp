#include "config.cpp"
#include <sstream>
#include <fstream>
#include <algorithm>

void grep(ifstream* file, string& path, string& pattern, bool& caseInsensitive);
void grep_file(string& path, Config& config);

int main(int argc, char *argv[])
{
	Config config;
	config.patch(argc, argv);

	for (int i = 0; i < config.files.size(); i++)
	{
		grep_file(config.files[i], config);
	}
}

void grep(ifstream* file, string& path, string& pattern, bool& caseInsensitive)
{
	string line;
	int lineNumber = 0;

	while (getline(*file, line))
	{
		lineNumber++;
		bool matched;

		if (caseInsensitive)
		{
			string lowerPattern = pattern;

			transform(line.begin(), line.end(), line.begin(), ::tolower);
			transform(lowerPattern.begin(), lowerPattern.end(), lowerPattern.begin(), ::tolower);

			matched = line.find(lowerPattern) != string::npos;
		}
		else {
			matched = line.find(pattern) != string::npos;
		}

		if (matched)
		{
			cout << path << '(' << lineNumber << "): " << line << endl;
		}
	}
}

void grep_file(string& path, Config& config)
{
	ifstream file(path);

	if (!file.is_open())
	{
		cout << "Could not open file: '" << path << '\'';
		exit(1);
	}

	grep(&file, path, config.pattern, config.caseInsensitive);
}