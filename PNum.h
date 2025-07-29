#ifndef PNUM_H
#define PNUM_H

#include <string>
#include <QDebug>
#include "utils/converter.h"

#define EPSILON 1e-7

class PNumException : public std::exception {
public:
    PNumException(std::string msg) : message(msg) {}

    const char *what() const noexcept override { return message.data(); }

private:
    std::string message;
};

/*
    Класс PNum реализует число в p-ичной системе счисления
*/
class PNum {
    private:
        double num;                 // число в десятичной системе счисления
        short unsigned int p;       // основание системы счисления
        short unsigned int c;       // точность - число знаков после запятой

    public:
        PNum(double num = 0, short unsigned int p = 10, short unsigned int c = 7);
        PNum(const std::string& num, short unsigned int p = 10, short unsigned int c = 7);

        double GetNumDouble() const { return num; }
        std::string GetNumString() const { return Converter::convert_10_pout(num, p, c); }

        short unsigned int GetP() const { return p; }
        short unsigned int GetAccuracy() const { return c; }
        void SetP(const short unsigned int p);
        void SetAccuracy(const short unsigned int c); 


        PNum Sum(const PNum& other);
        PNum Mul(const PNum& other);
        PNum Sub(const PNum& other);
        PNum Div(const PNum& other);
        PNum Rev();
        PNum Sqr();
};

#endif
