#include <iostream>
#include <algorithm>

class LVector {
public: // публичная секция - тут лежат функции, которые могут быть вызваны у объекта
  LVector() { // конструктор - функция вызывается при создании объекта
    size = 0; // задать начальные параметры
    dataSize = 0;
    delta = 4;
    reallocate(false);
  }

  LVector(int len) {
    size = len;
    delta = 4;
    dataSize = int(len / delta) * delta + delta;
    reallocate(false);
  }

  LVector(int len, int num) {
    size = len;
    delta = 4;
    dataSize = int(len / delta) * delta + delta;
    reallocate(false);
    for(int i = 0; i < size; i++) {
        data[i] = num;
    }
  }

  ~LVector() { // деструктор - вызывается при уничтожении объекта (например конец программы)
    delete[] data; // очистить память
  }

  void push_back(int elem) { // добавить элемент в конец
    if(dataSize == size) {
      reallocate(true);
    }
    data[size] = elem;
    size += 1;
  }


  int &operator [] (const int index) { // перегружаем [] для записи. Использование v[0] = 6;
    return data[index];
  }
    
  const int &operator [] (const int index) const { // перегружаем [] для чтения. Использование a = v[0]
    return data[index]; // используем const для гарании того, что данные не будут изменены при чтении
  }

  int getSize() { // узнать размер массива
    return size;
  }

  int * begin() { // итератор на начало
    return data;
  }

  int * end() { // итератор на конец
    return data + size;
  }
    
  LVector & operator = (LVector &other) { // перегружаем оператор копирования. Пример: LVector a; a = b;
      delete[] data;
      size = other.getSize();
      delta = 4;
      dataSize = int(size / delta) * delta + delta;
      reallocate(false);
      for(int i = 0; i < other.getSize(); i++) {
          data[i] = other[i];
      }
  } // Если не перегрузить этот метод, то после присваивание оба вектора будут работать с одним и тем же массивом

private: // приватная зона - данные +  фукнции, которые нельзя вызывать извне
  void reallocate(bool copy) { // выделяем новое местро для хранения
    dataSize = dataSize+delta;
    int * newdata = new int[dataSize];
    if(copy) {
        for(int i = 0; i < size; i++) {
            newdata[i] = data[i];
        }
        delete[] data;
    }
    data = newdata;
  }

  // данные объекта
  int * data; // указатель на данные
  int size; // количество элементов
  int dataSize; // количество выделенных ячеек
  int delta; // количество выделяемых новых ячеек
};

int main() {
  LVector h;
  h.push_back(3);
  h.push_back(6);
  h.push_back(9);
  h.push_back(12);
  h.push_back(51);
  h.push_back(21);

  for(int i = 0; i < h.getSize(); i++) {
    std::cout << h[i] << ' ';
  }

  std::cout << std::endl;

  LVector hh(7);
  for(auto it = hh.begin(); it != hh.end(); it++) {
    std::cout << *it << ' ';
  }

  std::cout << std::endl;

  LVector hhh(7, 4);
  for(auto it = hhh.begin(); it != hhh.end(); it++) {
    std::cout << *it << ' ';
  }

  std::cout << std::endl;

  std::sort(h.begin(), h.end(), [](int a, int b){return a > b;});

  for(auto it = h.begin(); it != h.end(); it++) {
    std::cout << *it << ' ';
  }

  std::cout << std::endl;
    
  LVector heh;
  heh = hhh;
  for(auto it = heh.begin(); it != heh.end(); it++) {
      std::cout << *it << ' ';
  }

  return 0;
}
/*
Вывод

3 6 9 12 51 21 
0 0 0 0 0 0 0 
4 4 4 4 4 4 4 
51 21 12 9 6 3
4 4 4 4 4 4 4 
*/
