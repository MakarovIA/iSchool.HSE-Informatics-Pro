#include <iostream>

class IWorker { // буква I - от слова Interface. То есть данный класс сам по себе ничего не делает а только предоставляет
    // интерфейс для потомков
public:
    virtual void doWork(){}
    virtual int getId() { return -1; }
};

class Worker : public IWorker {
public:
    Worker(int id) {
        this->id = id;
    }
    virtual void doWork() {
        for(int i = 0; i < 5; i++) {
            std::cout << "Working ..." << std::endl;
            // Эмулируем серьезную работу
            // в реальной задаче, тут могут быть какие-то серьезные вычисление
            // отправка каких-нибудь данных
            // работы с сетью или что-то подобное
        }
    }

    virtual int getId() {
        return id;
    }

private:
    int id;
};

class LoggerDecorator : public IWorker { // логгер
public:
    LoggerDecorator(IWorker * worker) {
        this->worker = worker; // получаем ссылку на настоящего рабочего
    }

    virtual int getId() { // возвращаем id настоящего работника
        return worker->getId();
    }

    virtual void doWork() { // обрамляем работу реального работника логгированием
        std::cout << "[Log]: Worker with id " << worker->getId() << " start working." << std::endl;
        worker->doWork();
        std::cout << "[Log]: Worker with id " << worker->getId() << " finish working." << std::endl;
    }


private:
    IWorker * worker;
};

class BeautyDecorator : public IWorker { // еще один декоратор, который рисует красивые строчки до и после основной работы
public:
    BeautyDecorator(IWorker * worker) {
        this->worker = worker;
    }

    virtual void doWork()  {
        for(int i = 0; i < 60; i++) std::cout << '=';
        std::cout << std::endl;

        worker->doWork();

        for(int i = 0; i < 60; i++) std::cout << '=';
        std::cout << std::endl;
    }

    virtual int getId()  {
        return worker->getId();
    }


private:
    IWorker * worker;
};

int main() {
    IWorker * one = new Worker(1); // Обычный рабочий
    one->doWork();

    std::cout << std::endl;

    IWorker * two = new LoggerDecorator(new Worker(2)); // оборачиваем рабочего в логгер
    // принцип работы с обхектом two никак не поменялся
    // но при этом мы аккуратно добавили новую функциональность, не изменяя изначальный класс рабочего

    two->doWork(); // работаем но теперь с логгированием

    std::cout << std::endl;

    IWorker * three = new BeautyDecorator(new Worker(3)); // аналогично мы можем сделать и с Beauty
    three->doWork();

    std::cout << std::endl;

    // так как все классы - наследники IWorker, то со всеми ними мы можем работать одинаковым образом
    // То есть мы можем оборачивать в произвольное клоичество декораторов
    IWorker * four = new BeautyDecorator(new LoggerDecorator(new Worker(4)));

    four->doWork();

    std::cout << std::endl;

    IWorker * five = new LoggerDecorator(one); // можем оборачивать уже созданные классы, не обязательно создавать новые

    five->doWork();

    std::cout << std::endl;

    return 0;
}
