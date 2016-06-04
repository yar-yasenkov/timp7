#pragma once

#define EXPORT __declspec(dllexport)

__interface EXPORT IQueue
{
	void create(int size);
	bool add(int value);
	int get();
	bool del();
};


class Queue : public IQueue
{
private:
	int* _array;
	int _head;
	int _tail;
	int _size;
	int _counter;
public:
	void create(int size);
	bool add(int value);
	int get();
	bool del();
};

extern "C"
{
	__declspec(dllexport) IQueue* GetIQueue();
}
