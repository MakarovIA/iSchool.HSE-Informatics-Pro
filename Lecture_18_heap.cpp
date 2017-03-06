#include <iostream>
#include <vector>
#include <iterator>
#include <tuple>
#include <stdexcept>
#include <climits>

typedef std::vector<long>::iterator Iter;

class PriorityQueue {
public:
    PriorityQueue(){
        retrieve_iters();
    }

    long Max() {
        return *heap_begin;
    }

    long Top() { // берем самый приоритетный элемент
        if(array.size() == 0) {
            throw std::length_error("Queue is empty");
        }

        long maximum = *heap_begin;
        heap_end--;
        *heap_begin = *heap_end; // берем элемент с конца
        heapify(heap_begin); // восстанавливаем кучу

        array.erase(heap_end);
        retrieve_iters();

        return maximum;
    }

    void Insert(long k) { // вставляем ключ
        array.push_back(LONG_MIN);
        retrieve_iters();

        increase_key(heap_end-1, k);
    }

    bool empty() {
        return array.size() == 0;
    }
    
    void build_heap() { // построение кучи
        heap_end = array.end(); 
        for(Iter i = heap_begin + (heap_end-heap_begin)/2 + 1; i != heap_begin - 1; i--) {
            heapify(i); // идем по массиву и восстанавливаем кучу
        }
    }
    
    void setData(std::vector<long> v) {
        array = v;
        retrieve_iters();
    }
    
private:
    void retrieve_iters() { // функция для удобства. Восстанавливает значение итераторов
        heap_begin = array.begin();
        heap_end = array.end();
    }

    Iter left(Iter i) { // левый потомок
        Iter l = heap_begin + (i - heap_begin) * 2 + 1;
        return l >= heap_end ? heap_end : l;
    }

    Iter rigth(Iter i) { // правый потомок
        Iter r = heap_begin + (i - heap_begin) * 2 + 2;
        return r >= heap_end ? heap_end : r;
    }

    Iter parent(Iter i) { // родитель
        return heap_begin + (i - heap_begin - 1) / 2;
    }

    void increase_key(Iter e, long k) { // вспомагательная функция дла вставки
        if(k < *e) {
            throw std::invalid_argument("New key is lesser then current");
        }

        *e = k;
        while(e != heap_begin and *parent(e) < *e) {
            std::swap(*e, *parent(e));
            e = parent(e);
        }
    }

    void heapify(Iter e) { // основная функция для восстановления кучи
        Iter l = left(e), r = rigth(e); // берем потомков
        Iter largest; 
        if(l != heap_end and *l > *e) largest = l;
        else largest = e; // находим максимальный среди них

        if(r != heap_end and *r > *largest) largest = r;

        if(largest != e) { // если он больше чем тот, что в изначальной вершине
            std::swap(*e, *largest); // меняем их местами
            heapify(largest); // выполняем восстановление для потомка
        }
    }

    std::vector<long> array;
    Iter heap_begin;
    Iter heap_end;
};

int main() {
	PriorityQueue q;
	q.Insert(5);
	q.Insert(7);
	q.Insert(3);
	q.Insert(10);

	std::cout << q.Top() << std::endl;
	std::cout << q.Max() << std::endl;
	std::cout << q.Top() << std::endl;

	std::cout << "----" << std::endl;

	q.Insert(125);
	q.Insert(1);

	std::cout << "----" << std::endl;

	while(!q.empty()) {
	    std::cout << q.Top() << std::endl;
	}


	PriorityQueue p;
	p.setData(std::vector<long>({5, 2, 7, 9, 3, 1, 6, 8, 11}));
	p.build_heap();

	while(!p.empty()) {
	    std::cout << p.Top() << std::endl;
	}
	return 0;
}
