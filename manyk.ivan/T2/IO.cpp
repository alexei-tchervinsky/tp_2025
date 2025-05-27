#include "DataStruct.hpp"

std::istream& operator>>(std::istream& in, DataStruct& data) {
    std::string line;
    if (!std::getline(in, line))
        return in;

    std::istringstream iss(line);
    char ch;
    data = DataStruct{};
    bool key1Found = false, key2Found = false, key3Found = false;

    iss >> std::ws >> ch;
    if (ch != '(')
    {
        return in;
    }

    std::string keyPart;
    while (iss >> std::ws >> ch && ch != ')')
    {
        if (ch == ':')
        {
            std::string key;
            iss >> key;

            if (key == "key1")
            {
                char chgrid, chc;
                double real, imag;
                iss >> chgrid >> chc >> ch >> real >> imag >> ch;
                if (chgrid != '#' || chc != 'c' || ch != ')') {
                    break;
                }
                data.key1 = {real, imag};
                key1Found = true;
            }
            else if (key == "key2")
            {
                std::string octStr;
                std::getline(iss, octStr, ':');
                //const char* str = octStr.c_str();
                //std::cout << "step1: " << octStr << ", "<< octStr.at(1)<<'\n';
                if (octStr.at(1) != '0')
                    break;
                //std::cout << "step2" << '\n';
                for(char temp : octStr)
                {
                    // temp = std::tolower(temp);
                    // if ((temp >= 'a' && temp <= 'z') || temp == '.')
                    // {
                    //     break;
                    // }
                    if(!std::isdigit(temp))
                    {
                        break;
                    }
                }

                try {
                    //std::cout << "key2";
                    data.key2 = std::stoull(octStr, nullptr, 8);
                    //std::cout << "data.key2 " << data.key2 << '\n';
                }
                catch (const std::exception &e) {

                    break;
                }
                iss.unget();
                key2Found = true;
            }
            else if (key == "key3")
            {
                char quote;
                iss >> std::ws >> quote;
                if (quote != '"')
                {
                    break;
                }
                std::string str;
                std::getline(iss, str, '"');
                data.key3 = str;
                key3Found = true;
            }
        }
    }

    if (!key1Found || !key2Found || !key3Found)
    {
        //std::cout<<"fail"<<'\n';
        in.setstate(std::ios::failbit);
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& data) {
    out << "(:key1 #c(" << std::fixed << std::setprecision(1) << data.key1.real() << " " << data.key1.imag() << ")";
    out << ":key2 0" << std::oct << data.key2 << std::dec;
    out << ":key3 \"" << data.key3 << "\":)";
    return out;
}
