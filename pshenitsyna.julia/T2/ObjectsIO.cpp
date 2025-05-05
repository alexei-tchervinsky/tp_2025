#include "ObjectsIO.h"
std::istream& operator>>(std::istream& in, DelimiterIO&& dest) //перегрузка оператора ввода для разделителей
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }
    char c = '0';
    in >> c;
    if (in && (c != dest.exp))
    {
        in.setstate(std::ios::failbit);
    }
    return in;
}
std::istream& operator>>(std::istream& in, OctIO&& dest) //перегрузка оператора ввода для данных 1-го ключа
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }
    return in >> DelimiterIO{'0'} >> dest.ref;
}
std::istream& operator>>(std::istream& in, StringIO&& dest) //перегрузка оператора ввода для данных 3-го ключа
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }
    return std::getline(in >> DelimiterIO{ '"' }, dest.ref, '"');
}
std::istream& operator>>(std::istream& in, LabelIO&& dest) //перегрузка оператора ввода для ключа
{
    std::istream::sentry sentry(in);
    if(!sentry)
    {
        return in;
    }
    std::string data = "";
    if ((in >> StringIO{ data }) && (data != dest.exp))
    {
        in.setstate(std::ios::failbit);
    }
    return in;
}
std::istream& operator>>(std::istream& in, CharIO&& dest) //перегрузка оператора ввода данных для 2-го ключа
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }
    return in >> DelimiterIO{'\''}>>dest.ref>>DelimiterIO{'\''};
}