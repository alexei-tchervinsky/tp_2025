#include "IO_Objects.hpp"

#include <iterator>
#include <algorithm>

namespace myspace {
    std::istream& operator>>(std::istream& is, LimitingSymbolIO&& ls) {
        std::istream::sentry sentry(is);
        if(!sentry) return is;
        char c;
        is >> c;
        if(is and (c != ls.symbol)) is.setstate(std::ios::failbit);
        return is;
    }

    std::istream& operator>>(std::istream& is, LabelIO&& l) {
        std::istream::sentry sentry(is);
        if(!sentry) {
            std::cerr << "LabelIO: sentry failed" << std::endl;
            return is;
        }
        
        std::string temp;
        for(std::size_t i = 0; i < l.label.length(); ++i) {
            char c;
            if(!(is >> c)) {
                std::cerr << "LabelIO: failed to read char " << i << std::endl;
                return is;
            }
            temp += c;
        }
        
        std::cerr << "LabelIO: read '" << temp << "', expected '" << l.label << "'" << std::endl;
        
        if(temp != l.label) {
            std::cerr << "LabelIO: label mismatch" << std::endl;
            is.setstate(std::ios::failbit);
        }
        return is;
    }

    std::istream& operator>>(std::istream& is, ComplexIO&& c) {
        std::istream::sentry sentry(is);
        if(!sentry) return is;
        double real, imag;
        is >> LabelIO{"#c"} >> LimitingSymbolIO{'('};
        is >> real >> imag;
        is >> LimitingSymbolIO{')'};
        c.ref = std::complex<double>(real, imag);
        return is;
    }

    std::istream& operator>>(std::istream& is, BinaryIO&& r) {
        std::istream::sentry sentry(is);
        if(!sentry) {
            std::cerr << "BinaryIO: sentry failed" << std::endl;
            return is;
        }
        
        // Читаем префикс "0b"
        char zero, b;
        is >> zero >> b;
        std::cerr << "BinaryIO: read chars '" << zero << "' and '" << b << "'" << std::endl;
        
        if(!is || zero != '0' || b != 'b') {
            std::cerr << "BinaryIO: prefix error, expected '0b'" << std::endl;
            is.setstate(std::ios::failbit);
            return is;
        }
        
        // Читаем бинарную строку до ':'
        std::string binary_str;
        char c;
        while(is.get(c) && c != ':') {
            std::cerr << "BinaryIO: reading char '" << c << "'" << std::endl;
            if(c == '0' || c == '1') {
                binary_str += c;
            } else if(c != ' ' && c != '\t') {
                // Если встретили не цифру и не пробел, это ошибка
                std::cerr << "BinaryIO: unexpected char '" << c << "'" << std::endl;
                is.setstate(std::ios::failbit);
                return is;
            }
        }
        
        std::cerr << "BinaryIO: binary string = '" << binary_str << "'" << std::endl;
        
        // Возвращаем ':' обратно в поток
        if(c == ':') {
            is.putback(c);
        }
        
        r.ref = binary_str;
        std::cerr << "BinaryIO: reading final ':'" << std::endl;
        is >> LimitingSymbolIO{':'};
        if(!is) {
            std::cerr << "BinaryIO: failed to read final ':'" << std::endl;
        }
        return is;
    }

    std::istream& operator>>(std::istream& is, StringIO&& s) {
        std::istream::sentry sentry(is);
        if(!sentry) return is;
        return std::getline(is >> LimitingSymbolIO{'\"'}, s.ref, '\"');
    }
}

