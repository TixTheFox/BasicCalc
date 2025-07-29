#ifndef PNUM_EDITOR_H
#define PNUM_EDITOR_H

#include <string>
#include "PNum.h"

/*
    Класс реализует редактор p-ичных чисел
*/
class PNumEditor {
    private:
        std::string num;
        static bool isTaskDigit(char sym, int pin);

    public:
        PNumEditor() { num = ""; }

        bool isEmpty() { return num == ""; }

        void AddZero();
        void AddSym(const char sym);
        void AddDot();
        void ChangeSign();
        void Clear() { num = ""; }
        void Delete() { if(!num.empty()) num.pop_back(); }

        std::string GetNum() { return num; }
        void SetNum(const std::string number);
        void SetNum(const PNum& number);

        static bool IsCorrect(std::string num, int pin);
};

#endif
