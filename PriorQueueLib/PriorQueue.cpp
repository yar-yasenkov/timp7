#include "PriorQueue.h"

IQueue * GetIQueue()
{
	return new PriorQueue();
}

bool PriorQueue::add(int value)
{
	if (_tree.size() == _size)
		return false;

	_tree.push_back(value);
	int i = _tree.size() - 1;
	int parent = (i - 1) / 2;

	while (i > 0 && _tree[parent] > _tree[i])
	{
		int temp = _tree[i];
		_tree[i] = _tree[parent];
		_tree[parent] = temp;
		i = parent;
		parent = (i - 1) / 2;
	}
	return true;
}

void PriorQueue::orderTree(int i)
{
	int leftChild;
	int rightChild;
	int leastChild;

	while (true)
	{
		leftChild = 2 * i + 1;
		rightChild = 2 * i + 2;
		leastChild = i;

		if (leftChild < _tree.size() && _tree[leftChild] < _tree[leastChild])
			leastChild = leftChild;

		if (rightChild < _tree.size() && _tree[rightChild] < _tree[leastChild])
			leastChild = rightChild;

		if (leastChild == i)
			break;

		int temp = _tree[i];
		_tree[i] = _tree[leastChild];
		_tree[leastChild] = temp;
		i = leastChild;
	}
}

bool PriorQueue::del()
{
	if (_tree.size() == 0)
		return false;
    int result = _tree[0];
	_tree[0] = _tree[_tree.size() - 1];
	_tree.erase(_tree.begin() + _tree.size() - 1);

	for (int i = _tree.size() / 2; i >= 0; i--)
		orderTree(i);
	return true;
}
