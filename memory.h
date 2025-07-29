#ifndef MEMORY_H
#define MEMORY_H

/*
    Класс реализует "память" калькулятора
    Является шаблонным, в работе принимает в качестве параметра шаблона класс PNum
*/
template<typename NumType>
class Memory
{
private:
    NumType MemNum;     // число в памяти
    bool isUsed;    // активна ли память

public:
    Memory() {
        isUsed = false;
    }

    void Write(const NumType& val) {
        MemNum = val;
        isUsed = true;
    }

    NumType Read() {
        return MemNum;
    }

    void Add(const NumType& val) {
        MemNum = MemNum.Sum(val);
        isUsed = true;
    }

    void Clear() {
        MemNum = NumType();
        isUsed = false;
    }

    bool GetIsUsed() {
        return isUsed;
    }

    void SetP(const short unsigned val) {
        MemNum.SetP(val);
    }
};

#endif // MEMORY_H