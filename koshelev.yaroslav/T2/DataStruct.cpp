#include "DataStruct.hpp"
#include "iofmtguard.hpp"
#include <iomanip>
#include <sstream>

namespace solution {

    bool operator<(const DataStruct& lhs, const DataStruct& rhs) {
        if (lhs.key1 != rhs.key1) return lhs.key1 < rhs.key1;
        if (lhs.key2 != rhs.key2) return lhs.key2 < rhs.key2;
        return lhs.key3 < rhs.key3;
    }

    std::istream& operator>>(std::istream& in, DataStruct& data) {
        std::string input;
        if (!std::getline(in, input, '\n')) return in;

        std::istringstream ss(input);
        std::string token;

        size_t pos1 = input.find(":key1 ");
        size_t pos2 = input.find(":key2 ");
        size_t pos3 = input.find(":key3 ");

        if (pos1 == std::string::npos || pos2 == std::string::npos || pos3 == std::string::npos) return in;

        try {
            std::string substr1 = input.substr(pos1 + 7, pos2 - (pos1 + 7));
            std::string substr2 = input.substr(pos2 + 7, pos3 - (pos2 + 7));
            std::string substr3 = input.substr(pos3 + 7);

            substr3.erase(std::remove(substr3.begin(), substr3.end(), ':'), substr3.end());
            substr3.erase(std::remove(substr3.begin(), substr3.end(), ')'), substr3.end());
            if (substr3.front() == '"' && substr3.back() == '"') {
                substr3 = substr3.substr(1, substr3.length() - 2);
            }

            data.key1 = std::stod(substr1);

            if (substr2.rfind("0x", 0) == 0 || substr2.rfind("0X", 0) == 0)
                data.key2 = std::stoull(substr2, nullptr, 16);
            else if (substr2.find("ull") != std::string::npos)
                data.key2 = std::stoull(substr2);
            else
                return in;

            data.key3 = substr3;
        } catch (...) {
            return in;
        }

        return in;
    }

    std::ostream& operator<<(std::ostream& out, const DataStruct& data) {
        iofmtguard guard(out);
        out << std::scientific << std::uppercase << std::setprecision(1);
        out << "(:key1 " << data.key1;
        out << ":key2 0X" << std::hex << std::uppercase << data.key2;
        out << ":key3 \"" << data.key3 << "\":)";
        return out;
    }

}
