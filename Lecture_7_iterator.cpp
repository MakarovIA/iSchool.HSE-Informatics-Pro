#include <iostream>
#include <algorithm>
#include <vector>

class node { // каждый узер содержит значение и указатель на следующий узел
public:
	node(int x) {
		number = x;
		next = nullptr;
	}

	void setNext(node * n) {
		next = n;
	}

	node * getNext() {
		return next;
	}

	int& num() {
		return number;
	}

private:
	int number;
	node * next;
};

class iterator { // данный итератор - очень ограничен в функциональности для наглядности из-за чего он не будет совместим с некоторыми функциями
public:
	iterator(node * d) {
		data = d;
	}

	bool operator!=(iterator other) { // сравнение двух итераторов
		return data != other.data;
	}

	bool operator==(iterator other) { // сравнение двух итераторов
		return data == other.data;
	}

	iterator operator++(int a) {	 // сдвиг итератора
		data = data->getNext();
		return *this;
	}

	iterator operator++() {	 // сдвиг итератора
		data = data->getNext();
		return *this;
	}

	int& operator*() { // получения значения
		return data->num();
	}
private:
	node * data;
};

class line { // линия содержит первый и последнй узел цепочки
public:
	line() {
		start = nullptr;
		finish = nullptr;
	}
	~line() {
		while(start) {
			node * e = start;
			start = start->getNext();
			delete e;
		}
	}

	void push_back(int a) {
		if(start) {
			finish->setNext(new node(a));
			finish = finish->getNext();
		} else {
			start = new node(a);
			finish = start;
		}
	}

	iterator begin() {
		return iterator(start);
	}

	iterator end() {
		return iterator(nullptr);
	}

private:
	node * start;
	node * finish;
};

int main() {
	std::vector<int> v({2, 4, 9, 7, 5, 1, 3, 5, 7});
	line l;
	for(int i = 0; i < v.size(); i++) {
		l.push_back(v[i]);
	}
	for(auto it = l.begin(); it != l.end(); it++) {
		std::cout << *it << ' ';
	}
	std::cout << std::endl;
	std::cout << *std::max_element(l.begin(), l.end()) << std::endl;
	std::cout << *std::min_element(l.begin(), l.end()) << std::endl;

	std::vector<int> w;
	std::transform(l.begin(), l.end(), std::back_inserter(w), [](int x){return x*x;});
	for(auto it = w.begin(); it != w.end(); it++) {
		std::cout << *it << ' ';
	}
	std::cout << std::endl;
	return 0;
}
