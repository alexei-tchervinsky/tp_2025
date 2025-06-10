std::istream& operator>>(std::istream& is, DataStruct& ds) {
    std::string record = extractRecord(is);
    if (record.empty()) {
        is.setstate(std::ios_base::failbit);
        return is;
    }

    std::unordered_map<std::string, std::string> fields;
    std::istringstream ss(record);
    std::string token;
    while (std::getline(ss, token, ':')) {
        if (!token.empty()) {
            parseField(token, fields);
        }
    }

    // —трога€ проверка наличи€ всех полей
    if (fields.size() != 3 || !fields.count("key1") || !fields.count("key2") || !fields.count("key3")) {
        is.setstate(std::ios_base::failbit);
        return is;
    }

    // ѕроверка формата key1 (должен быть символ в одинарных кавычках)
    std::string key1Str = fields["key1"];
    if (key1Str.size() != 3 || key1Str[0] != '\'' || key1Str[2] != '\'') {
        is.setstate(std::ios_base::failbit);
        return is;
    }
    ds.key1 = key1Str[1];

    // ѕроверка формата key2 (должно быть число)
    std::string key2Str = fields["key2"];
    try {
        ds.key2 = std::stoull(key2Str);
    } catch (...) {
        is.setstate(std::ios_base::failbit);
        return is;
    }

    // ѕроверка формата key3 (должна быть строка в кавычках)
    std::string key3Str = fields["key3"];
    if (key3Str.size() < 2 || key3Str.front() != '"' || key3Str.back() != '"') {
        is.setstate(std::ios_base::failbit);
        return is;
    }
    ds.key3 = key3Str.substr(1, key3Str.size() - 2);

    return is;
}

