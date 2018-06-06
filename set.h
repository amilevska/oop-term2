#pragma once
#include"container.h"

template<typename T, template<typename> typename C>
class Set :public Container<T, C> {
public:

	T* find(const T& val) override{
		return impl->find(val);
	}

	void insert(const T& val) override {
		if (impl->count(val) == 0) {
			impl->insert(val);
		}
	}

	void erase(const T& val) override {
		if (impl->count(val) > 0) {
			impl->erase(val);
		}
	}

	int count(const T& val) const override {
		return impl->count(val);
	}

	bool isEmpty() const override {
		return impl->isEmpty();
	}

	int size() const override {
		return impl->size();
	}
};