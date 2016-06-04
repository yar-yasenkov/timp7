#include <windows.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

__interface IQueue
{
	void create(int size);
	bool add(int value);
	int get();
	bool del();
};

vector<string> split(const string &s, char delim);

int main(int argc, char* argv[])
{
	if (argc != 3)
		return 0;

	HINSTANCE hLib = LoadLibrary(argv[1]);
	if (!hLib)
	{
		cout << "Library is not found\n";
		return 0;
	}
	ifstream fin(argv[2]);
	if (!fin)
	{
		cout << "File is not found\n";
		return 0;
	}

	IQueue *(*getQueue)() = (IQueue *(*)())GetProcAddress(hLib, "GetIQueue");
	if (!getQueue)
		return 0;
	IQueue *pQueue = getQueue();
	if (!pQueue)
		return 0;
	string expression;
	getline(fin, expression);
	pQueue->create(stoi(expression));
	vector<string> expressions;
	int size;
	while (getline(fin, expression))
	{
		expressions = split(expression, ' ');
		size = expressions.size();
		if (size == 0)
			continue;
		if (expressions[0] == "add")
		{
			if (size != 2 || !pQueue->add(stoi(expressions[1])))
			{
				cout << "Cannot add value\n";
				return 0;
			}
		}
		else if (expressions[0] == "get")
		{
			if (size == 1)
				cout << pQueue->get() << endl;
			else
			{
				cout << "Cannot get value\n";
				return 0;
			}
		}
		else if (expressions[0] == "del")
		{
			if (size != 1 || !pQueue->del())
			{
				cout << "Cannot delete\n";
				return 0;
			}
		}
		else
		{
			cout << "Incorrect command in file\n";
			return 0;
		}
	}
	FreeLibrary(hLib);
	return 0;
}

vector<string> split(const string &s, char delim)
{
	vector<string> elems;
	stringstream ss(s);
	string item;

	while (getline(ss, item, delim))
		elems.push_back(item);

	return elems;
}
