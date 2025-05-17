#include "ObjectsIO.h"
//перегрузка оператора ввода для разделителей
std::istream& operator>>(std::istream& in, DelimiterIO&& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }
    char c;
    in >> c;
    if (in && (c != dest.exp))
    {
        in.setstate(std::ios::failbit);
    }
    return in;
}

//перегрузка оператора ввода для данных 1-го ключа
std::istream& operator>>(std::istream& in, OctIO&& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }
    char c;
    if(!(in>>c) || c !='0')
    {
        in.setstate(std::ios::failbit);
        return in;
    }

    if (isdigit(in.peek())) {
        in >> dest.ref;
    }
    else
    {
        dest.ref = 0;
    }

    return in;
}

//перегрузка оператора ввода для данных 3-го ключа
std::istream& operator>>(std::istream& in, StringIO&& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }
    return std::getline(in >> DelimiterIO{ '"' }, dest.ref, '"');
}

//перегрузка оператора ввода для ключа
std::istream& operator>>(std::istream& in, LabelIO&& dest)
{
    std::istream::sentry sentry(in);
    if(!sentry)
    {
        return in;
    }
    std::string data;
    if ((in >> StringIO{data}) && (data != dest.exp))
    {
        in.setstate(std::ios::failbit);
    }
    return in;
}
//перегрузка оператора ввода данных для 2-го ключа
std::istream& operator>>(std::istream& in, CharIO&& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }
    return in >> DelimiterIO{'\''}>>dest.ref>>DelimiterIO{'\''};
}
