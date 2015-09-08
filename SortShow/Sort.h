#include <iostream>
#include <algorithm>
#include <stack>
#pragma once
template<class T>
class Sort
{
private:
	class Node
	{
	public:
		T value = -1;
		int index = -1;
		Node& operator=(Node n) 
		{
			value = n.value;
			if (index != -1 && n.index != -1)
			{
				myCashList->AddTail(index);
				myCashList->AddTail(n.value);
			}
			return *this;
		}
	};
	static CList<T>* myCashList;
	Node *sortData;
	void getData(T[], int);
	void swap(int, int);
	void copyList(CList<T>*);

	void MergeSort(Node*, int, int);
	void MergeAarry(Node*, int, int, int);

	void MaxInHeap(Node*, int);

	void qsort(Node*, int, int);
	
	void RadixSort(Node *,int ,int);

	static bool compare(Node, Node);
public:
	Sort();
	~Sort();
	long STL_Sort(T[], int, CList<T>*);
	long Bubble(T[], int, CList<T>*);
	long STL_StableSort(T[], int, CList<T>*);
	long Select(T[], int, CList<T>*);
	long Insert(T[], int, CList<T>*);
	long Shell(T[], int, CList<T>*);
	long Quick(T[], int, CList<T>*);
	long Heap(T[], int, CList<T>*);
	long Merge(T[], int, CList<T>*);
	long Radix(T[], int, CList<T>*);
	long Cocktail(T[], int, CList<T>*);
	
};

template<class T>
Sort<T>::Sort()
{
	myCashList = new CList<int>();
}
template<class T>
Sort<T>::~Sort()
{
	if (sortData != NULL)
	{
		delete[] sortData;
	}
}
template<class T>
CList<int>* Sort<T>::myCashList;
template<class T>
void Sort<T>::getData(T data[], int size)
{
	if (sortData != NULL)
	{
		delete[] sortData;
	}
	sortData = new Node[size];
	for (int i = 0; i < size; i++)
	{
		sortData[i].value = data[i];
		sortData[i].index = i;
	}
}
template<class T>
void Sort<T>::swap(int i, int j)
{
	std::stack<Node>stack;
	stack.push(sortData[i]);
	stack.push(sortData[j]);
	sortData[i] = stack.top();
	stack.pop();
	sortData[j] = stack.top();
}
template<class T>
void Sort<T>::copyList(CList<T>*outCash)
{
	POSITION pos = myCashList->GetHeadPosition();
	while (pos != NULL)
	{
		int d = myCashList->GetNext(pos);
		outCash->AddTail(d);
	}
	myCashList->RemoveAll();
}
template<class T>
long Sort<T>::STL_Sort(T data[], int size, CList<T>* cash)
{
	getData(data, size);

	long begin_Time = GetTickCount();

	std::sort(sortData, sortData + size, compare);

	long end_Time = GetTickCount();

	copyList(cash);

	return end_Time - begin_Time;

}
template<class T>
bool Sort<T>::compare(Node a, Node b)
{
	if (a.value < b.value)
	{
		return true;
	}
	return false;
}
template<class T>
long Sort<T>::Bubble(T data[], int size, CList<T> *cash)
{
	getData(data, size);

	long begin_Time = GetTickCount();
	for (int i = 0; i < size; i++)
	{
		for (int j = size - 1; j >i; j--)
		{
			if (sortData[i].value > sortData[j].value)
			{
				swap(i, j);
			}
		}
	}
	long end_Time = GetTickCount();

	copyList(cash);

	return end_Time - begin_Time;
}
template<class T>
long Sort<T>::STL_StableSort(T data[], int size, CList<T> *cash)
{
	getData(data, size);

	long begin_Time = GetTickCount();

	std::stable_sort(sortData, sortData + size, compare);

	long end_Time = GetTickCount();

	copyList(cash);

	return end_Time - begin_Time;

}
template<class T>
long Sort<T>::Select(T data[], int size, CList<T>*cash)
{
	getData(data, size);

	long begin_Time = GetTickCount();

	int temp;
	int pos;
	for (int i = 0; i < size; i++)
	{
		temp = sortData[i].value;
		pos = i;
		for (int j = i + 1; j < size; j++)
		{
			if (sortData[j].value < temp)
			{
				temp = sortData[j].value;
				pos = j;
			}
		}
		swap(i, pos);
	}

	long end_Time = GetTickCount();

	copyList(cash);

	return end_Time - begin_Time;
}
template<class T>
long Sort<T>::Insert(T data[], int size, CList<T>*cash)
{
	getData(data, size);

	long begin_Time = GetTickCount();

	int temp;
	int pos;
	for (int i = 1; i < size; i++)
	{
		temp = sortData[i].value;
		pos = i - 1;
		while (pos >= 0 && temp < sortData[pos].value)
		{
			sortData[pos + 1] = sortData[pos];
			pos--;
		}
		Node node;
		node.index = sortData[i].index;
		node.value = temp;
		sortData[pos + 1] = node;
	}

	long end_Time = GetTickCount();

	copyList(cash);

	return end_Time - begin_Time;
}
template<class T>
long Sort<T>::Shell(T data[], int size, CList<T>*cash)
{
	getData(data, size);

	long begin_Time = GetTickCount();

	int temp, pos;
	int d = size;
	do
	{
		d = d / 3 + 1;
		for (int i = d; i < size; i++)
		{
			temp = sortData[i].value;
			pos = i - d;
			while (pos >= 0 && temp<sortData[pos].value)
			{
				sortData[pos + d] = sortData[pos];
				pos -= d;
			}
			Node node;
			node.index = sortData[i].index;
			node.value = temp;
			sortData[pos + d] = node;
		}
	} while (d>1);

	long end_Time = GetTickCount();

	copyList(cash);

	return end_Time - begin_Time;
}
template<class T>
long Sort<T>::Quick(T data[], int size, CList<T>*cash)
{
	getData(data, size);

	long begin_Time = GetTickCount();

	qsort(sortData, 0, size - 1);

	long end_Time = GetTickCount();

	copyList(cash);

	return end_Time - begin_Time;
}
template<class T>
void Sort<T>::qsort(Node*data, int left, int right)
{
	int i, j;
	int mid;
	i = left;
	j = right;
	mid = data[(left + right) / 2].value;
	do
	{
		while (data[i].value < mid && i < right)
		{
			i++;
		}
		while (data[j].value > mid && j > left)
		{
			j--;
		}
		if (i <= j)
		{
			swap(i, j);
			i++;
			j--;
		}
	} while (i <= j);

	if (left < j)
	{
		qsort(data, left, j);
	}
	if (right>i)
	{
		qsort(data, i, right);
	}
}
template<class T>
long Sort<T>::Heap(T data[], int size, CList<T>*cash)
{
	getData(data, size);

	long begin_Time = GetTickCount();

	for (int j = size; j > 0; j--)
	{
		MaxInHeap(sortData, j);
		swap(0, j - 1);
	}

	long end_Time = GetTickCount();

	copyList(cash);

	return end_Time - begin_Time;
}
template<class T>
void Sort<T>::MaxInHeap(Node*data, int size)
{
	for (int j = size - 1; j > 0; j--)
	{
		int parent = j / 2;
		int child = j;
		if (j < size - 1 && data[j].value < data[j + 1].value)
		{
			child++;
		}
		if (data[child].value > data[parent].value)
		{
			swap(child, parent);
		}
	}
}
template<class T>
long Sort<T>::Merge(T data[], int size, CList<T>*cash)
{
	getData(data, size);

	long begin_Time = GetTickCount();

	MergeSort(sortData, 0, size - 1);

	long end_Time = GetTickCount();

	copyList(cash);

	return end_Time - begin_Time;
}
template<class T>
void Sort<T>::MergeSort(Node*data, int begin, int end)
{
	int mid;
	if (begin < end)
	{
		mid = (begin + end) / 2;
		MergeSort(data, begin, mid);
		MergeSort(data, mid + 1, end);
		MergeAarry(data, begin, mid, end);
	}
}
template<class T>
void Sort<T>::MergeAarry(Node*data, int p, int q, int r)
{
	int n1, n2, i, j, k;
	Node *left = NULL, *right = NULL;
	n1 = q - p + 1;
	n2 = r - q;

	left = (Node*)malloc(sizeof(Node)*n1);
	right = (Node*)malloc(sizeof(Node)*n2);

	for (int i = 0; i < n1; i++)
	{
		left[i].value = data[p + i].value;
		left[i].index = data[p + i].index;
	}
	for (int j = 0; j < n2; j++)
	{
		right[j].value = data[q + 1 + j].value;
		right[j].index = data[q + 1 + j].index;
	}
	i = 0;
	j = 0;
	k = p;
	while (i < n1 && j < n2)
	{
		if (left[i].value <= right[j].value)
		{
			data[k++] = left[i++];
		}
		else
		{
			data[k++] = right[j++];
		}
	}
	for (; i < n1; i++)
	{
		data[k++] = left[i];
	}
	for (; j < n2; j++)
	{
		data[k++] = right[j];
	}
	delete[]left;
	delete[]right;

}
template<class T>
long Sort<T>::Radix(T data[], int size, CList<T>*cash)
{
	getData(data, size);

	long begin_Time = GetTickCount();

	int max = -1, loops = 1;
	for (int i = 0; i < size; i++)
	{
		if (sortData[i].value>max)
		{
			max = sortData[i].value;
		}
	}
	while (max > 0)
	{
		loops++;
		max /= 10;
	}

	for (int l = 1; l <= loops; l++)
	{
		RadixSort(sortData, size, l);
	}

	long end_Time = GetTickCount();

	copyList(cash);

	return end_Time - begin_Time;
}
template<class T>
void Sort<T>::RadixSort(Node *data, int size, int loop)
{
	int bucket[10][10001] = {};
	int temp = (int)pow(10, loop - 1);
	for (int i = 0; i < size; i++)
	{
		int row_index = (data[i].value / temp) % 10;

		for (int j = 0; j < 10001; j++)
		{
			if (bucket[row_index][j] == NULL)
			{
				bucket[row_index][j] = data[i].value;
				break;
			}
		}
	}
	int k = 0;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10001; j++)
		{
			if (bucket[i][j] != NULL)
			{
				Node n;
				n.value = bucket[i][j];
				n.index = k;
				data[k] = n;
				k++;
				bucket[i][j] = NULL;
			}
			else break;
		}

	}
}
template<class T>
long Sort<T>::Cocktail(T data[], int size, CList<T>*cash)
{
	getData(data, size);

	long begin_Time = GetTickCount();

	for (int i = 0; i < size / 2; i++)
	{
		for (int j = i; j < size - i - 1; j++)
		{
			if (sortData[j].value > sortData[j + 1].value)
			{
				swap(j + 1, j);
			}
		}
		for (int j = size - (i + 1); j>i; j--)
		{
			if (sortData[j].value < sortData[j - 1].value)
			{
				swap(j, j - 1);
			}
		}
	}

	long end_Time = GetTickCount();

	copyList(cash);

	return end_Time - begin_Time;
}