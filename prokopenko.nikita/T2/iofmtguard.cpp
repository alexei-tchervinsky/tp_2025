#include "iofmtguard.hpp"

namespace prokopenko {

    // Сохраняем параметры потока при создании объекта
    iofmtguard::iofmtguard(std::basic_ios<char>& stream)
        : stream_(stream),
        fill_(stream.fill()),
        precision_(stream.precision()),
        flags_(stream.flags()) {}

    // Восстанавливаем параметры потока при уничтожении объекта
    iofmtguard::~iofmtguard() {
        stream_.fill(fill_);
        stream_.precision(precision_);
        stream_.flags(flags_);
    }

}
