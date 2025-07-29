#include "converter.h"

Converter::Converter()
{

}

double Converter::convert_pin_10(const std::string& number, int base) {
    double result = 0.0; // Инициализация результата
    size_t dotPosition = number.find('.'); // Поиск позиции десятичной точки
    std::string integerPart, fractionalPart; // Отдельные части числа
    bool isNegative = false; // Флаг отрицательности числа

    // Проверка наличия минуса в начале числа
    size_t start = 0;
    if (number[0] == '-') {
        isNegative = true;
        start = 1;
    }

    // Разделение числа на целую и дробную части
    if (dotPosition != std::string::npos) {
        integerPart = number.substr(start, dotPosition - start);
        fractionalPart = number.substr(dotPosition + 1);
    }
    else {
        integerPart = number.substr(start);
    }

    // Преобразование целой части
    int size = integerPart.size();
    for (int i = 0; i < size; ++i) {
        char digit = integerPart[i];
        int value;
        if (isdigit(digit))
            value = digit - '0'; // Преобразование символа цифры в числовое значение
        else
            value = digit - 'A' + 10; // Преобразование буквы в число (A = 10, B = 11, и т.д.)
        result += value * pow(base, size - i - 1); // Перевод числа в десятичную систему
    }

    // Преобразование дробной части
    size = fractionalPart.size();
    for (int i = 0; i < size; ++i) {
        char digit = fractionalPart[i];
        int value;
        if (isdigit(digit))
            value = digit - '0'; // Преобразование символа цифры в числовое значение
        else
            value = digit - 'A' + 10; // Преобразование буквы в число (A = 10, B = 11, и т.д.)
        result += value * pow(base, -(i + 1)); // Перевод числа в десятичную систему
    }

    // Если число отрицательное, меняем знак результата
    if (isNegative) {
        result = -result;
    }

    return result;
}

std::string Converter::convert_10_pout(double number, int base, int precision) {
    std::string result;

    // Проверка на отрицательное число
    if (number < 0) {
        result = "-";
        number = -number; // Преобразование числа в положительное
    }

    int integerPart = static_cast<int>(number);
    double fractionalPart = number - integerPart;

    // Преобразование целой части
    if (integerPart == 0 && result.empty()) // Добавляем "0" перед минусом, если целая часть нулевая
        result += '0';

    // Преобразование целой части
    std::string integerStr;
    while (integerPart > 0) {
        int digit = integerPart % base;
        char digitChar;
        if (digit < 10)
            digitChar = '0' + digit;
        else
            digitChar = 'A' + digit - 10; // Преобразование чисел в буквы (10 = A, 11 = B и т.д.)
        integerStr = digitChar + integerStr;
        integerPart /= base;
    }
    result += integerStr;

    // Добавление точки для разделения целой и дробной частей
    result += '.';

    // Преобразование дробной части
    for (int i = 0; i < precision; ++i) {
        fractionalPart *= base;
        int digit = static_cast<int>(fractionalPart);
        char digitChar;
        if (digit < 10)
            digitChar = '0' + digit;
        else
            digitChar = 'A' + digit - 10; // Преобразование чисел в буквы (10 = A, 11 = B и т.д.)
        result += digitChar;
        fractionalPart -= digit;
    }

    //удаление лишних нулей
    while (result.back() == '0') result.pop_back();
    //если после удаления нулей в конце осталась точка, то ее тоже удаляем
    if (result.back() == '.') result.pop_back();

    return result;
}

std::string Converter::convert(std::string num, int pin, int pout, int accuracy) {
    double num_10 = convert_pin_10(num, pin);
    return convert_10_pout(num_10, pout, accuracy);
}
