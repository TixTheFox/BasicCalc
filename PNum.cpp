#include "PNum.h"

/* КОНСТРУКТОРЫ */

/*
    Формирует PNum из:
        num - число, заданное в десятичной системе счисления
        p - система счисления числа
        c - точность
*/
PNum::PNum(double num, short unsigned int p, short unsigned int c) {
    if (p < 2 || p > 16)
        throw PNumException("p must be integer from 2 to 16");
    if (c <= 0)
        throw PNumException("c must be positive integer");

    this->p = p;
    this->c = c;
    this->num = num;
}

/*
    Формирует PNum из:
        num - число, заданное в своей системе счисления в виде строки
        p - система счисления числа
        c - точность
*/
PNum::PNum(const std::string& num, short unsigned int p,  short unsigned int c) {
    if (p < 2 || p > 16)
        throw PNumException("p must be integer from 2 to 16");
    if (c <= 0)
        throw PNumException("c must be positive integer");

    this->p = p;
    this->c = c;
    this->num = Converter::convert_pin_10(num, p);
}

/* МОДИФИКАТОРЫ ПОЛЕЙ */

void PNum::SetP(const short unsigned int p) {
    if (p < 2 || p > 16)
        throw PNumException("p must be integer from 2 to 16");
    this->p = p;
}
void PNum::SetAccuracy(const short unsigned int c) {
    if (c <= 0)
        throw PNumException("Accuracy('c') must be positive integer");
    this->c = c;
}


/* ОПЕРАЦИИ */

/*
    Возвращает результат сложения текущего PNum и other
*/
PNum PNum::Sum(const PNum& other) {
    if (other.p != p || other.c != c)
        throw PNumException("Other must have the same 'p' and accuracy('c')");
    return PNum(num + other.num, p, c);
}

/*
    Возвращает результат вычитания other из текущего PNum 
*/
PNum PNum::Sub(const PNum& other) {
    if (other.p != p || other.c != c)
        throw PNumException("Other must have the same 'p' and accuracy('c')");
    return PNum(num - other.num, p, c);
}

/*
    Возвращает результат умножения текущего PNum на other
*/
PNum PNum::Mul(const PNum& other) {
    if (other.p != p || other.c != c)
        throw PNumException("Other must have the same 'p' and accuracy('c')");
    return PNum(num * other.num, p, c);
}

/*
    Возвращает результат деления текущего PNum на other
*/
PNum PNum::Div(const PNum& other) {
    if (other.p != p || other.c != c)
        throw PNumException("Other must have the same 'p' and accuracy('c')");
    return PNum(num / other.num, p, c);
}

/*
    Возвращает обратное (1 / num) для текущего PNum
*/
PNum PNum::Rev() {
    if (fabs(num) < EPSILON)
        throw PNumException("Num is 0!");
    return PNum(1 / num, p, c);
}

/*
    Возвращает квадрат текущего PNum
*/
PNum PNum::Sqr() {
    return PNum(num * num, p, c);
}
