#pragma once
#include <vector>

#define EXPORT __declspec(dllexport)

using namespace std;

__interface EXPORT IQueue
{
	void create(int size);
	bool add(int value);
	int get();
	bool del();
};


class PriorQueue : public IQueue
{
private:
	vector<int> _tree;
	int _size;
public:
	void create(int size) { _size = size; }
	bool add(int value);
	void orderTree(int i);
	bool del();
	int get() { return _tree[0]; }
};


extern "C"
{
	__declspec(dllexport) IQueue* GetIQueue();
}
