#include "IO_Objects.hpp"
#include <algorithm>
#include <iterator>

namespace ryzhov {
std::istream &operator>>(std::istream &in, LabelIO &&dest) {
    // Включаем streamguard
    std::istream::sentry sentry(in);
    if (!sentry) {
        return in;
    }
    // Проверка, что вводимый label соответствует заявленному
    std::string label;
    // Считываем вводимый
    std::copy_n(std::istream_iterator<char>(in), dest.label.length(), std::back_inserter(label));
    // Если поток ввода еще мертв или label не соответствует заявленному
    if (in && (label != dest.label)) {
        // Убиваем поток
        in.setstate(std::ios_base::failbit);
    }
    return in;
}

std::istream &operator>>(std::istream &in, DelimiterIO &&dest) {
    // Включаем streamguard
    std::istream::sentry sentry(in);
    if (!sentry) {
        return in;
    }
    // Проверяем, если введенный разделитель соответствует заявленному
    char c;
    in >> c;
    // Если поток мертв или разделитель не соответствует, убиваем поток
    if (in && (c != dest.delimiter)) {
        in.setstate(std::ios::failbit);
    }
    return in;
}

std::istream &operator>>(std::istream &in, ComplexDoubleIO &&dest) {
    // Включаем streamguard
    std::istream::sentry sentry(in);
    if (!sentry) {
        return in;
    }
    double real, imag;
    // Вытаскиваем формальности
    in >> LabelIO{"#c("};
    // Вытаскиваем сами части комплексного числа
    in >> real >> imag;
    // Вытаскиваем формальности
    in >> DelimiterIO{')'};
    // Присваиваем значение
    dest.ref = std::complex<double>(real, imag);
    return in;
}

std::istream &operator>>(std::istream &in, SignedLongLongIO &&dest) {
    // Включаем streamguard
    std::istream::sentry sentry(in);
    if (!sentry) {
        return in;
    }
    // Вытаскиваем число
    in >> dest.ref;
    // Вытаскиваем формальности
    std::string suffix;
    std::copy_n(std::istream_iterator<char>(in), 2, std::back_inserter(suffix));
    if (in && (suffix != "ll" && suffix != "LL")) {
        in.setstate(std::ios::failbit);
    }
    return in;
}

std::istream &operator>>(std::istream &in, StringIO &&dest) {
    // Включаем streamguard
    std::istream::sentry sentry(in);
    if (!sentry) {
        return in;
    }
    // Вытаскиваем строку
    return std::getline(in >> DelimiterIO{'"'}, dest.ref, '"');
}
} // namespace ryzhov
