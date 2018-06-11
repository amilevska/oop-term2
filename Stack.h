#pragma once
#include<string>
#include<iostream>
#include<memory>

template<typename T>
class Stack {
private:
	std::unique_ptr<T[]> stack;
	int top;
	int size;
public:
	Stack() {
		size = 100;
		try {
			stack = std::unique_ptr<T[]>(new T[size]);
		}
		catch (std::bad_alloc& exception) {
			std::cerr << "bad_alloc was caught " << exception.what() << std::endl;
		}
		top = -1;
	};
	Stack(int your_size) {
		size = your_size;
		try {
			stack = std::unique_ptr<T[]>(new T[size]);
		}
		catch (std::bad_alloc& exception) {
			std::cerr << "bad_alloc was caught " << exception.what() << std::endl;
		}
		top = -1;
	};
	void push(T data) {
		if (top >= size - 1) {
			throw std::out_of_range("Stack is full");
		}
		++top;
		this->stack[top] = data;
	}
	T read() {
		if (top < 0) {
			throw std::out_of_range("Stack is empty");
		}
		return stack[top];
	}
	void pop() {
		if (top < 0) {
			throw std::out_of_range("Stack is empty");
		}
		--top;
	}
	std::unique_ptr<T[]> get_array() {
		return std::move(stack);
	}
	int get_top() {
		return top;
	}
	int get_size() {
		return size;
	}
	void print_array() {
		if (top == -1) {
			std::cout << "Stack is empty\n";
		}
		for (int i = 0; i <= top; i++) {
			std::cout << stack[i] << " ";
		}
		std::cout << "\n";
	}
};



