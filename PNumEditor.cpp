#include "PNumEditor.h"

/*
    Добавление нуля к числу
*/
void PNumEditor::AddZero() {
    // ситуации, когда ноль добавлять нельзя
    if (num != "0" && num != "-0")
        num += "0";
}

/*
    Добавление цифры
    (Вообще любого символа, но используется для цифр)
*/
void PNumEditor::AddSym(char sym) {
    // если в числе "ноль", то не добавляем, а заменяем
    if (num == "0" || num == "-0")
        *(num.end() - 1) = sym;
    else
        num += sym;
}

/*
    Добавление точки - разделителя целой и дробной частей
*/
void PNumEditor::AddDot() {
    if (num == "" || num == "-")
        num += "0.";
    else if
        // добавляем точку только если ее нет в числе
        (num.find(".") == num.npos) num +=".";
}

/*
    Смена знака числа
*/
void PNumEditor::ChangeSign() {
    if (num[0] == '-') {
        num.erase(0, 1);
    } else {
        num = "-" + num;
    }
}

/*
    Установка числа по строке
*/
void PNumEditor::SetNum(std::string number) {
    this->num = number;
}

/*
    Установка числа по объекту PNum
*/
void PNumEditor::SetNum(const PNum& number) {
    this->num = number.GetNumString();
}

/*
    Проверяет, является ли sym цифрой в системе счисления pin или точкой
    УЧИТЫВАЕТ БУКВЫ ЛЮБОГО РЕГИСТРА (a/A...)
*/
bool PNumEditor::isTaskDigit(char sym, int pin) {
    //  Условие проверяет, что цифра возможна в текущей системе счисления
    //  ставит в соотв. каждой цифре число (A - 10, B - 11, ...) и проверяет, что такое число строго меньше pin
    if ( ('0' <= sym && sym <= '9' && (sym - '0' < pin)) ||
        ('A' <= sym && sym <= 'F' && (sym - 55 < pin)) ||
        ('a' <= sym && sym <= 'f' && (sym - 87 < pin)) ||
        (sym == '.'))
    {
        return 1;
    } else {
        return 0;
    }
}

/*
    Проверяет, является ли число num корректным в сисетме счисления pin
*/
bool PNumEditor::IsCorrect(std::string num, int pin) {
    if (num.empty()) return 1;

    // фиксирует число точек
    bool dot_met = false;
    bool res = 1;


    auto it = num.begin();
    // минус пропускаем
    if (*it == '-') it++;
    // точка в начале - невозможно
    if (*it == '.') res = 0;
    // если в начале ноль
    if (*it == '0'){
        // и это не конец числа, то ок
        if (it + 1 == num.end())
            res = 1;
        // иначе может быть только "0."
        else if (*(it + 1) != '.')
            res = 0;
    }

    for (; it != num.end() && res; it++) {
        if (*it == '.') {
            // если точка в начале или не единственна - ошибка
            if (dot_met || it == num.begin()) res = 0;
            dot_met = true;
        } else if (!isTaskDigit(*it, pin)) {
            res = 0;
        }
    }

    return res;
}
