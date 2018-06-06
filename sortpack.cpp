#include"sortpack.h"


bool IntToSort::operator<(const SortedItems & it) const
{
	if (this->value < it.getValue()) return true;
	return false;
}

void IntToSort::showItem()
{
	std::cout << value << " ";
}

int IntToSort::getValue() const{
	return value;
}

void IntToSort::setValue(int a)
{
	value = a;
}



SortedItems& ArrayOfInt::operator[](int i)
{
	return arrayToSort[i];
}


void ArrayOfInt::fill()
{
	std::mt19937 gen(time(0));
	std::uniform_int_distribution<> urd(0, 250);
	for (int i = 0; i < arrayToSort.size(); i++) {
		arrayToSort[i] = urd(gen);
	}
}

void ArrayOfInt::show()
{
	for (int i = 0; i < arrayToSort.size(); i++) {
		arrayToSort[i].showItem();
	}
}

void SortPack::swap(SortedItems& a, SortedItems& b) {
	int temp = a.getValue();
	a.setValue(b.getValue());
	b.setValue(temp);
}

void SortPack::bubble()
{
	int n = items->size();
	int newn = n;
	while (n != 0) {
		newn = 0;
		for (int i = 1; i < n; i++) {
			/*if (massive[i - 1] > massive[i]) {
				swap(massive[i - 1], massive[i]);
				newn = i;
			}*/

			if ((*items)[i] < (*items)[i - 1]) {
				swap((*items)[i - 1], (*items)[i]);
				newn = i;
			}
		}
		n = newn;
	}
}

void SortPack::insert()
{
	for (int j = 1; j < items->size(); j++) {
		int i = j;
		while (i > 0 && (*items)[i] < (*items)[i-1]) {
			swap((*items)[i], (*items)[i - 1]);
			i--;
		}
	}
}

void SortPack::select()
{
	int n = items->size();
	int min_index;
	for (int j = 0; j < n; j++) {
		min_index = j;
		for (int i = j; i < n; i++) {
			if ((*items)[i] < (*items)[min_index]) {
				min_index = i;
			}
		}
		if (j != min_index) {
			swap((*items)[min_index], (*items)[j]);
		}
	}
}


void SortPack::quick() {
	q_sort(0, items->size() - 1);
}

void SortPack::shell()
{
	int n = items->size();
	for (int gap = n / 2; gap > 0; gap /= 2)
	{
		for (int i = gap; i < n; i++)
		{
			int j;
			for (j = i; j >= gap; j -= gap) {
				if ((*items)[j] < (*items)[j - gap]) swap((*items)[j], (*items)[j - gap]);
				else break;
			}
		}
	}
}

void SortPack::show()
{
	items->show();
}

void SortPack::q_sort(int first, int last)
{
	int q;
	if (first < last) {
		q = partition(first, last);
		q_sort(first, q - 1);
		q_sort(q + 1, last);
	}
}

int SortPack::partition(int first, int last) {
	int r = last;
	int i = first;
	for (int j = first; j < last; j++) {
		if ((*items)[j] < (*items)[r]) {
			swap((*items)[i], (*items)[j]);
			i++;
		}
	}
	swap((*items)[i], (*items)[r]);
	return i;
}