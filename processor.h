#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <QDebug>

// номера операций над аргументами

#define NUM_SUM 1
#define NUM_SUB 2
#define NUM_MUL 3
#define NUM_DIV 4
#define NUM_SQR 5
#define NUM_REV 6


/*
    Класс Processor реализует процессор для рассчета операций и функций калькулятора
    Является шаблонным, в работе в качестве параметра шаблона использует PNum
*/
template<typename NumType>
class Processor
{
private:
    NumType Lop_res;                // левый операнд
    NumType Rop_res;                // правый операнд
    short int state;                // состояние процессора: 0 - операция НЕ установлена
                                    //                       иное число - указывает текущую операцию (см. выше)
    bool second_operand_defined;    // флаг; указывает, был ли введен второй операнд

public:
    Processor();

    void SetLop(const NumType& num) { Lop_res = num; }
    void SetRop(const NumType& num) { Rop_res = num; }

    void SetP(const short unsigned val) {
        Lop_res.SetP(val);
        Rop_res.SetP(val);
    }

    NumType GetLop() { return Lop_res; }
    NumType GetRop() { return Rop_res; }

    void setSecondOperandFlag(bool val) { second_operand_defined = val; }

    void ClearAll();
    void Execute();
    void ExecuteFunction(short int operation);
    void SetOperation(short int operation);
};

#endif // PROCESSOR_H

template<typename NumType>
Processor<NumType>::Processor() { // : Lop_res(0, 10, 7), Rop_res(0, 10, 7){
    state = 0;
}

/*
    Сбрасывает состояние процессора
*/
template<typename NumType>
void Processor<NumType>::ClearAll() {
    Lop_res = NumType();
    Rop_res = NumType();
    state = 0;
}

/*
    Вычисление операции процессора
    Результат вычисления - в левом операнде (Lop_res)
*/
template<typename NumType>
void Processor<NumType>::Execute() {
    NumType local_rop;
    // если второй аргумент (правый) определен
    if (second_operand_defined)
        // то он используется в качестве второго аргумента
        local_rop = Rop_res;
    else
        // иначе в качестве второго аргумента выступает левый операнд
        local_rop = Lop_res;


    switch(state) {
    case(NUM_SUM):
        Lop_res = Lop_res.Sum(local_rop);
        break;
    case(NUM_SUB):
        Lop_res = Lop_res.Sub(local_rop);
        break;
    case(NUM_MUL):
        Lop_res = Lop_res.Mul(local_rop);
        break;
    case(NUM_DIV):
        Lop_res = Lop_res.Div(local_rop);
        break;
    case(NUM_SQR):
        Lop_res = Lop_res.Sqr();
        break;
    case(NUM_REV):
        Lop_res = Lop_res.Rev();
        break;
    case(0):
        break;
    }
}

/*
    Вычисление функции
    Результат вычисления - в правом операнде (Rop_res)
*/
template<typename NumType>
void Processor<NumType>::ExecuteFunction(short int operation) {
    if (operation == NUM_SQR)
        Rop_res = Rop_res.Sqr();
    else if (operation == NUM_REV)
        Rop_res = Rop_res.Rev();
}

/*
    Функция устанавливает операцию процессора
    При этом в случае функций (SQR, REV) происходит мгновенное вычисление
*/
template<typename NumType>
void Processor<NumType>::SetOperation(short int operation) {
    state = operation;
    if (operation == NUM_SQR || operation == NUM_REV)
        ExecuteFunction(operation);
}
