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

    // ������� �������� ������� ���� �����
    if (fields.size() != 3 || !fields.count("key1") || !fields.count("key2") || !fields.count("key3")) {
        is.setstate(std::ios_base::failbit);
        return is;
    }

    // �������� ������� key1 (������ ���� ������ � ��������� ��������)
    std::string key1Str = fields["key1"];
    if (key1Str.size() != 3 || key1Str[0] != '\'' || key1Str[2] != '\'') {
        is.setstate(std::ios_base::failbit);
        return is;
    }
    ds.key1 = key1Str[1];

    // �������� ������� key2 (������ ���� �����)
    std::string key2Str = fields["key2"];
    try {
        ds.key2 = std::stoull(key2Str);
    } catch (...) {
        is.setstate(std::ios_base::failbit);
        return is;
    }

    // �������� ������� key3 (������ ���� ������ � ��������)
    std::string key3Str = fields["key3"];
    if (key3Str.size() < 2 || key3Str.front() != '"' || key3Str.back() != '"') {
        is.setstate(std::ios_base::failbit);
        return is;
    }
    ds.key3 = key3Str.substr(1, key3Str.size() - 2);

    return is;
}

