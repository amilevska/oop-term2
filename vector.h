#pragma once

#include"container.h"

#include<vector>

template<typename T>
class Vector :public ContainerImp<T> {
	std::vector<T> set;
public:
	
	T* find(const T& val) override {
		auto it = std::find(set.begin(), set.end(), val);
		if (it == set.end()) {
			return nullptr;
		}
		return &(*it);
	}

	void insert(const T& val) override {
		set.push_back(val);
	}

	void erase(const T& val) override {
		set.erase(std::find(set.begin(), set.end(), val));
	}

	int count(const T& val) const override {
		return std::count(set.begin(), set.end(), val);
	}

	bool isEmpty() const override {
		return set.empty();
	}

	int size() const override {
		return set.size();
	}
};
