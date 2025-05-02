std::istream& operator>>(std::istream& in, DataStruct& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) return in;

    DataStruct input;
    bool has_key1 = false, has_key2 = false, has_key3 = false;

    in >> DelimiterIO{'('} >> DelimiterIO{':'};

    while (true) {
        if (in.peek() == ')') {
            in.ignore();
            break;
        }

        std::string field;
        if (!(in >> field)) break;

        if (field == "key1") {
            if (in.peek() == '(') {
                if (in >> RationalIO{input.key1}) {
                    has_key1 = true;
                }
            } 
            else if (in.peek() == '\'') {
                char c;
                if (in >> CharIO{c}) {
                    input.key1.first = static_cast<long long>(c);
                    input.key1.second = 1;
                    has_key1 = true;
                }
            }
            else if (std::isdigit(in.peek()) || in.peek() == '-') {
                in >> input.key1.first;
                input.key1.second = 1;
                has_key1 = true;
            }
            in >> DelimiterIO{':'};
        }
        else if (field == "key2") {
            if (in.peek() == '(') {
                if (in >> RationalIO{input.key2}) {
                    has_key2 = true;
                }
            }
            else if (in.peek() == '\'') {
                in >> CharIO{input.key2};
                has_key2 = true;
            }
            in >> DelimiterIO{':'};
        }
        else if (field == "key3") {
            in >> StringIO{input.key3} >> DelimiterIO{':'};
            has_key3 = true;
        }
        else {
            in.setstate(std::ios::failbit);
            break;
        }
    }

    if (has_key1 && has_key2 && has_key3) {
        dest = input;
    } else {
        in.setstate(std::ios::failbit);
    }
    return in;
}
