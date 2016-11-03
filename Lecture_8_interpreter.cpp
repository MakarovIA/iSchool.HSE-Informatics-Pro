#include <iostream>
#include <string>
#include <map>
#include <cmath>
#include <sstream>

class Handler;

class Interpreter {
public:
    Interpreter();
    ~Interpreter();
    void run(std::string code); // Реализуем данные фукнции после объявление обработчиков, так как
    // иначе они не будут о них ничего знать

    std::stringstream codeStream; // тоже самое, что и std::cin \ std::cout, точно чтение происходит из строки а не с клавиатуры
    std::map<std::string, int> variables; // множество всех переменных
    std::map<std::string, Handler*> handlers; // множество всех обработчиков
};


class Handler { // общий предок для обработчиков
public:
    Handler(Interpreter * inter) {
        interpretator = inter;
    }
    virtual void handle() {}

    std::pair<std::string, int> getAgruments() { // считать оба аргумента - общая функция для двух обработчиков
        std::string target, value;
        interpretator->codeStream >> target >> value;
        if(value[0] >= '0' and value[0] <= '9') { // если просто число
            return std::make_pair(target, std::stoi(value));
        } else { // если переменная
            return std::make_pair(target, interpretator->variables[value]);
        }
    };
protected: // секция protected аналогична private, но все ее содержимое будет доступно наследникам
    Interpreter * interpretator;
};

class SetHandler : public Handler { // обработчик установки значения переменной
public:
    SetHandler(Interpreter *inter) : Handler(inter) /*конструктор родителя*/ {} // конструктор необходимо прописать явно
    // однако не обязательно его еще реализовывать - достаточно вызвать конструктор родителя.

    virtual void handle() {
        auto args = getAgruments();
        interpretator->variables[args.first] = args.second;
    }
};

class AddHandler : public Handler {
public:
    AddHandler(Interpreter *inter) : Handler(inter) {}

    virtual void handle() {
        auto args = getAgruments();
        interpretator->variables[args.first] += args.second;
    }
};

class SubHandler : public Handler {
public:
    SubHandler(Interpreter *inter) : Handler(inter) {}

    virtual void handle() {
        auto args = getAgruments();
        interpretator->variables[args.first] -= args.second;
    }
};

class MultHandler : public Handler {
public:
    MultHandler(Interpreter *inter) : Handler(inter) {}

    virtual void handle()  {
        auto args = getAgruments();
        interpretator->variables[args.first] *= args.second;
    }
};

class DivHandler : public Handler {
public:
    DivHandler(Interpreter *inter) : Handler(inter) {}

    virtual void handle() {
        auto args = getAgruments();
        interpretator->variables[args.first] /= args.second;
    }
};

class PowHandler : public Handler { // возведение в степень
public:
    PowHandler(Interpreter *inter) : Handler(inter) {}

    virtual void handle() {
        auto args = getAgruments();
        interpretator->variables[args.first] = (int)pow(interpretator->variables[args.first], args.second);
    }
};

class PrintHandler : public Handler { // печать на экран
public:
    PrintHandler(Interpreter *inter) : Handler(inter) {}

    virtual void handle() {
        std::string variables, current;
        std::getline(interpretator->codeStream, variables);
        std::stringstream ss;
        ss << variables;
        while(ss >> current) {
            if(current[0] >= '0' and current[0] <= '9') std::cout << current << ' '; // Если просто число
            else std::cout << interpretator->variables[current] << ' '; // Если переменная
        }
        std::cout << std::endl;
    }
};

Interpreter::Interpreter() {
    handlers["set"] = new SetHandler(this); // установка соотвествующий обработчкиков для операций
    handlers["add"] = new AddHandler(this);
    handlers["subl"] = new SubHandler(this);
    handlers["mult"] = new MultHandler(this);
    handlers["div"] = new DivHandler(this);
    handlers["pow"] = new PowHandler(this);
    handlers["print"] = new PrintHandler(this);
}

Interpreter::~Interpreter() {
    for(auto h : handlers) {
        delete h.second; // по окончанию, необходимо освбодить память
    }
}

void Interpreter::run(std::string code) {
    codeStream.str(code);
    std::string command;
    while(codeStream >> command) { // считываем все комманды в коде
        handlers[command]->handle(); // для соответствующей команды вызываем соответствующий обработчик
    }
    std::stringstream().swap(codeStream); // очищаем ввод
}

int main() {
    Interpreter Inter;

    std::string hello = "print 42";

    Inter.run(hello);

    std::string adding = "\
set a 10 \n \
set b 20 \n \
add a b \n \
print a b \n \
";
    Inter.run(adding);

    std::string code = "\
set a 10 \n\
set b 20 \n \
set c 1 \n \
mult c a \n \
mult c b \n \
\
set k c \n \
div k 10 \n \
pow k 5 \n \
\
set abcd k \n \
div abcd 2 \n \
div abcd a \n \
\
set f 0 \n \
subl f a \n \
subl f b \n \
\
set summ 0 \n \
add summ a \n \
add summ b \n \
add summ c \n \
add summ k \n \
add summ f \n \
\
print a b c k f summ \n \
";
    Inter.run(code);
    return 0;
}
