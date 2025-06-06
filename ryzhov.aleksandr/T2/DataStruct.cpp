#include <iomanip>
#include "DataStruct.hpp"
#include "StreamGuard.hpp"
#include "IO_Objects.hpp"


namespace ryzhov {
    std::ostream &operator<<(std::ostream &out, const DataStruct &src) {
        std::ostream::sentry sentry(out);
        if (!sentry) {
            return out;
        }
        // (:key1 #c(1 -1):key2 -12LL:key3 "a?":)
        out << "(:key1 #c(";
        DataStruct::printDouble(out, src.key1_.real());
        out << " ";
        DataStruct::printDouble(out, src.key1_.imag());
        out << "):key2 ";
        out << src.key2_;
        out << "ll";
        out << ":key3 \"";
        out << src.key3_;
        out << "\":)";
        return out;
    }

    void DataStruct::printDouble(std::ostream &out, double x) {
        StreamGuard outGuard(out);
        if (std::floor(x) == x) {
            out << std::fixed << std::setprecision(1) << x;
        }
        else {
            out << x;
        }
    }


    std::istream &operator>>(std::istream &in, DataStruct &dest) {
        // Включаем streamguard
        std::istream::sentry sentry(in);
        if (!sentry) {
            return in;
        }
        // Для проверки, что введены все ключи введены
        bool key1 = false;
        bool key2 = false;
        bool key3 = false;
        DataStruct tmp;
        in >> DelimiterIO{'('};
        for (std::size_t i = 0; i < 3; i++) {

            short number = 0;
            // Достаем "формальности" и ключ
            in >> DelimiterIO{':'} >> LabelIO{"key"} >> number;
            // Проверяем ключ и вводим значения.
            switch (number) {
                case CMP: {
                    in >> ComplexDoubleIO{tmp.key1_};
                    key1 = true;
                    break;
                }
                case SLL: {
                    in >> SignedLongLongIO{tmp.key2_};
                    key2 = true;
                    break;
                }
                case STR: {
                    in >> StringIO{tmp.key3_};
                    key3 = true;
                    break;
                }
                default:
                    break;
            }
        }
        // Вытаскиваем формальности
        in >> DelimiterIO{':'} >> DelimiterIO{')'};
        if (in && key1 && key2 && key3) {
            dest = tmp;
        }
        return in;
    }

    bool compare(const DataStruct &a, const DataStruct &b) {
        // Сравниваем первые ключи
        double checkComplexKey1 = std::abs(a.key1_);
        double checkComplexKey2 = std::abs(b.key1_);
        // Если они не равны
        if (checkComplexKey1 != checkComplexKey2) {
            // Значит по ним можно сравнить, возвращаем результат сравнения
            return checkComplexKey1 < checkComplexKey2;
        }
        // Иначе сравниваем по вторым ключам
        if (a.key2_ != b.key2_) {
            return a.key2_ < b.key2_;
        }
        // И, если вторые равны, сравниваем по третьим.
        return a.key3_.length() < b.key3_.length();
    }
}
