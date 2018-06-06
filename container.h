#pragma once
#include<memory>

template<typename T>
class ContainerImp {
public:
	virtual ~ContainerImp(){}

	virtual T* find(const T& val) = 0;
	virtual void insert(const T& val) = 0;
	virtual void erase(const T& val) = 0;
	virtual int count(const T& val) const = 0;
	virtual bool isEmpty() const = 0;
	virtual int size() const = 0;
};


template<typename T, template<typename> typename C>
class Container {
protected:
	std::unique_ptr<ContainerImp<T>> impl;
public:
	Container() : impl{ new C<T>() } {}
	virtual ~Container(){}

	virtual T* find(const T& val) = 0;
	virtual void insert(const T& val) = 0;
	virtual void erase(const T& val) = 0;
	virtual int count(const T& val) const = 0;
	virtual bool isEmpty() const = 0;
	virtual int size()const  = 0;
};

