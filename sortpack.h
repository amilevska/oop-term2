#pragma once
#ifndef _SortPack_h_
#define _SortPack_h_

#include <iostream>
#include<random>
#include<ctime>
#include<vector>
class ArrayOfItems;
class SortedItems;
class IntToSort;
class SortPack
{
	ArrayOfItems * items;
public:
	SortPack(){};
	void bubble();
	void insert();
	void select();
	void quick();
	void shell();
	void show();
	void attach(ArrayOfItems& items) {
		this->items = &items;
	}
	void swap(SortedItems& a, SortedItems& b);
	ArrayOfItems& getItems() {
		return *items;
	}
private:
	void q_sort(int first, int last);
	int partition(int first, int last);
};

class SortedItems
{
public:
	virtual bool operator<(const SortedItems&) const = 0;
	virtual void showItem() = 0;
	virtual int getValue() const = 0;
	virtual void setValue(int) = 0;
};
class IntToSort : public SortedItems
{
	int value;
public:
	IntToSort() {};
	IntToSort(int i) :value(i) {};
	bool operator<(const SortedItems& it) const;
	bool operator==(const SortedItems& it) const {
		return value == it.getValue();
	}
	void showItem();
	int getValue() const;
	void setValue(int);
};

class ArrayOfItems
{
public:
	virtual SortedItems& operator[](int) = 0;
	virtual void fill() = 0;
	virtual void show() = 0;
	virtual int size() = 0;
};

class ArrayOfInt :public ArrayOfItems
{
	std::vector<IntToSort> arrayToSort;
public:
	ArrayOfInt(int n) :arrayToSort(n) {}
	ArrayOfInt(std::initializer_list<IntToSort> initList)
		: arrayToSort{ initList } {}
	SortedItems& operator[](int);
	void fill();
	void show();
	bool operator==(const ArrayOfInt& arr) {
		if (arrayToSort.size() != arr.arrayToSort.size()) return false;
		for (int i = 0; i < arrayToSort.size(); i++) {
			if (!(arrayToSort[i] == arr.arrayToSort[i])) return false;
		}
		return true;
	}

	int size() {
		return arrayToSort.size();
	}
};

#endif