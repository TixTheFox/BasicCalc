#ifndef CONVERTER_H
#define CONVERTER_H

#include <vector>
#include <cmath>
#include <string>

class Converter {
public:
    Converter();

    static double convert_pin_10(const std::string& number, int base);

    static std::string convert_10_pout(double number, int base, int precision);

    static std::string convert(std::string num, int pin, int pout, int accuracy);

};

#endif // CONVERTER_H
