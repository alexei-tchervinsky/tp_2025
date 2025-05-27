#include "geometry.hpp"
#include "iofmtguard.hpp"
#include <algorithm>
#include <functional>
#include <iterator>
#include <numeric>
#include <iomanip>
#include <string>
#include <limits>

// Оператор чтения символа-разделителя с проверкой
std::istream& erofick::operator>>(std::istream& in, DelimiterChar&& exp)
{
  std::istream::sentry guard(in); // Проверка состояния потока
  if (!guard)
  {
    return in;
  }
  char c = 0;
  in >> c;
  c = std::tolower(c);
  if (c != exp.expected) // Если символ не совпадает с ожидаемым
  {
    in.setstate(std::ios::failbit); // Устанавливаем флаг ошибки
  }
  return in;
}

// Оператор чтения строки-разделителя с проверкой
std::istream& erofick::operator>>(std::istream& in, DelimiterString&& exp)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  size_t i = 0;
  while (exp.expected[i] != '\0') // Читаем символы до конца строки
  {
    in >> DelimiterChar{ exp.expected[i] }; // Проверяем каждый символ
    ++i;
  }
  return in;
}

// Оператор чтения точки из потока в формате (x;y)
std::istream& erofick::operator>>(std::istream& in, Point& point)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  using delChar = DelimiterChar;
  Point temp = { 0, 0 };
  // Чтение в формате: ( число ; число )
  in >> delChar{ '(' } >> temp.x >> delChar{ ';' } >> temp.y >> delChar{ ')' };
  if (in) // Если чтение успешно
  {
    point = temp; // Сохраняем результат
  }
  return in;
}

// Оператор сравнения точек
bool erofick::operator==(const Point& lhs, const Point& rhs)
{
  return ((lhs.x == rhs.x) && (lhs.y == rhs.y));
}

// Оператор сравнения полигонов
bool erofick::operator==(const Polygon& lhs, const Polygon& rhs)
{
  if (lhs.points.size() != rhs.points.size()) // Если разное количество точек
  {
    return false;
  }
  // Сравниваем точки поэлементно
  return std::equal(lhs.points.cbegin(), lhs.points.cend(), rhs.points.cbegin());
}

// Проверка вхождения одного полигона в другой (по ограничивающим прямоугольникам)
bool erofick::operator<=(const Polygon& lhs, const Polygon& rhs)
{
  // Находим границы полигонов
  int innerMinX = findMinX(lhs);
  int innerMinY = findMinY(lhs);
  int innerMaxX = findMaxX(lhs);
  int innerMaxY = findMaxY(lhs);
  int outerMinX = findMinX(rhs);
  int outerMinY = findMinY(rhs);
  int outerMaxX = findMaxX(rhs);
  int outerMaxY = findMaxY(rhs);
  // Проверяем полное вхождение
  return (innerMinX >= outerMinX) && (innerMaxX <= outerMaxX) &&
         (innerMinY >= outerMinY) && (innerMaxY <= outerMaxY);
}

// Оператор чтения полигона из потока
std::istream& erofick::operator>>(std::istream& in, Polygon& polygon)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  size_t countPoints = 0;
  in >> countPoints; // Читаем количество точек
  if (countPoints < 3) // Полигон должен иметь хотя бы 3 точки
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  std::vector< Point > temp;
  using input_iterator_t = std::istream_iterator< Point >;
  // Читаем точки (countPoints-1 раз)
  std::copy_n(input_iterator_t{ in }, (countPoints - 1), std::back_inserter(temp));
  if (in.peek() != '\n') // Если осталась еще одна точка
  {
    std::copy_n(input_iterator_t{ in }, 1, std::back_inserter(temp));
  }
  // Проверяем успешность чтения и количество точек
  if (in && (temp.size() == countPoints) && ((in.peek() == '\n')))
  {
    polygon.points = temp; // Сохраняем результат
  }
  else
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

// Функтор для вычисления площади (метод трапеций)
double erofick::AreaPolygon::operator()(double area, const Point& p2, const Point& p3)
{
  // Формула площади через векторное произведение
  area += 0.5 * std::abs((p3.y - p1.y) * (p2.x - p1.x) - (p3.x - p1.x) * (p2.y - p1.y));
  p1 = p2; // Запоминаем текущую точку для следующего вызова
  return area;
}

// Вычисление площади полигона
double erofick::getPolygonArea(const Polygon& polygon)
{
  using namespace std::placeholders;
  // Связываем первую точку для использования в accumulate
  auto accumulateArea = std::bind(AreaPolygon{ polygon.points[1] },
    _1, _2, polygon.points[0]);
  // Накопление площади через все точки полигона
  return std::accumulate(polygon.points.cbegin(),
  polygon.points.cend(), 0.0, accumulateArea);
}

// Проверка наличия прямого угла в полигоне
bool erofick::isRightAngle(const Polygon& polygon)
{
  // Инициализируем функтор последними двумя точками
  auto countAngle = accumulateRightAngle{
    polygon.points[polygon.points.size() - 2],
    polygon.points[polygon.points.size() - 1]
  };
  // Ищем точку, образующую прямой угол
  return (std::find_if(polygon.points.cbegin(), polygon.points.cend(),
  countAngle) != polygon.points.cend());
}

// Функтор для проверки прямого угла между тремя точками
bool erofick::accumulateRightAngle::operator()(const Point& p3)
{
  // Векторы между точками
  Point vec1{ p2.x - p1.x, p2.y - p1.y };
  Point vec2{ p2.x - p3.x, p2.y - p3.y };
  // Сдвигаем точки для следующей проверки
  p1 = p2;
  p2 = p3;
  // Проверка ортогональности (скалярное произведение = 0)
  return ((vec1.x * vec2.x + vec1.y * vec2.y) == 0);
}

// Вспомогательные функции сравнения для точек и полигонов
namespace {
  bool compareByX(const erofick::Point& lhs, const erofick::Point& rhs)
   { return lhs.x < rhs.x; }
  bool compareByY(const erofick::Point& lhs, const erofick::Point& rhs)
  { return lhs.y < rhs.y; }
  bool comparePolygonsByMaxX(const erofick::Polygon& lhs, const erofick::Polygon& rhs)
  { return findMaxX(lhs) < findMaxX(rhs); }
  bool comparePolygonsByMaxY(const erofick::Polygon& lhs, const erofick::Polygon& rhs)
  { return findMaxY(lhs) < findMaxY(rhs); }
  bool comparePolygonsByMinX(const erofick::Polygon& lhs, const erofick::Polygon& rhs)
  { return findMinX(lhs) < findMinX(rhs); }
  bool comparePolygonsByMinY(const erofick::Polygon& lhs, const erofick::Polygon& rhs)
   { return findMinY(lhs) < findMinY(rhs); }
}

// Нахождение максимальной X-координаты в полигоне
int erofick::findMaxX(const Polygon& polygon)
{
  return std::max_element(polygon.points.cbegin(), polygon.points.cend(), compareByX)->x;
}

// Нахождение максимальной Y-координаты в полигоне
int erofick::findMaxY(const Polygon& polygon)
{
  return std::max_element(polygon.points.cbegin(), polygon.points.cend(), compareByY)->y;
}

// Нахождение минимальной X-координаты в полигоне
int erofick::findMinX(const Polygon& polygon)
{
  return std::min_element(polygon.points.cbegin(), polygon.points.cend(), compareByX)->x;
}

// Нахождение минимальной Y-координаты в полигоне
int erofick::findMinY(const Polygon& polygon)
{
  return std::min_element(polygon.points.cbegin(), polygon.points.cend(), compareByY)->y;
}

// Получение ограничивающего прямоугольника для набора полигонов
erofick::Polygon erofick::getBoundingBox(const std::vector<Polygon>& polygon)
{
  // Находим границы всех полигонов
  int pointMaxX = findMaxX(*std::max_element(polygon.cbegin(),
   polygon.cend(), comparePolygonsByMaxX));
  int pointMaxY = findMaxY(*std::max_element(polygon.cbegin(),
   polygon.cend(), comparePolygonsByMaxY));
  int pointMinX = findMinX(*std::min_element(polygon.cbegin(),
   polygon.cend(), comparePolygonsByMinX));
  int pointMinY = findMinY(*std::min_element(polygon.cbegin(),
   polygon.cend(), comparePolygonsByMinY));
  // Создаем прямоугольник из крайних точек
  std::vector< Point > res{ {pointMinX, pointMinY}, {pointMinX, pointMaxY},
                           {pointMaxX, pointMaxY}, {pointMaxX, pointMinY} };
  return Polygon{ res };
}

// Вспомогательные предикаты для полигонов
namespace {
  bool isEven(const erofick::Polygon& polygon) { return (polygon.points.size() % 2 == 0); }
  bool isOdd(const erofick::Polygon& polygon) { return !(polygon.points.size() % 2 == 0); }
  bool isSize(const erofick::Polygon& polygon, size_t numPoints)
   { return (polygon.points.size() == numPoints); }
  bool comparatorPoints(const erofick::Polygon& lhs, const erofick::Polygon& rhs)
  { return lhs.points.size() < rhs.points.size(); }
  bool comparatorArea(const erofick::Polygon& lhs, const erofick::Polygon& rhs)
   { return getPolygonArea(lhs) < getPolygonArea(rhs); }
}

// Команда AREA: вычисление площади полигонов по условию
void erofick::area(const std::vector<Polygon>& value, std::istream& in, std::ostream& out)
{
  iofmtguard guard(out); // Сохраняем форматирование
  out << std::setprecision(1) << std::fixed; // Устанавливаем точность вывода
  std::string argument = "";
  in >> argument;
  std::vector< Polygon > polygons;
  using namespace std::placeholders;

  // Выбор полигонов по условию
  if (argument == "EVEN")
  {
    std::copy_if(value.cbegin(), value.cend(), std::back_inserter(polygons), isEven);
  }
  else if (argument == "ODD")
  {
    std::copy_if(value.cbegin(), value.cend(), std::back_inserter(polygons), isOdd);
  }
  else if (argument == "MEAN")
  {
    if (value.empty())
    {
      throw std::logic_error("No polygons");
    }
    std::copy_if(value.cbegin(), value.cend(), std::back_inserter(polygons), isOdd);
  }
  else
  {
    size_t countPoints = std::stoull(argument);
    if (countPoints < 3)
    {
      throw std::logic_error("Wrong number");
    }
    std::function< bool(const Polygon&) > isCorrectCount = std::bind(isSize, _1, countPoints);
    std::copy_if(value.cbegin(), value.cend(), std::back_inserter(polygons), isCorrectCount);
  }

  // Вычисление площадей выбранных полигонов
  std::vector< double > areas;
  std::transform(polygons.cbegin(), polygons.cend(),
  std::back_inserter(areas), getPolygonArea);
  double res = std::accumulate(areas.cbegin(), areas.cend(), 0.0);

  // Вывод результата
  if (argument == "MEAN")
  {
    out << res / value.size(); // Среднее значение
  }
  else
  {
    out << res; // Сумма площадей
  }
}

// Команда MAX: поиск максимального значения площади или количества вершин
void erofick::max(const std::vector<Polygon>& value, std::istream& in, std::ostream& out)
{
  std::string argument = "";
  in >> argument;
  if (value.empty())
  {
    throw std::logic_error("No polygons");
  }
  else
  {
    if (argument == "AREA")
    {
      iofmtguard guard(out);
      out << std::setprecision(1) << std::fixed;
      out << getPolygonArea(*std::max_element(value.begin(), value.end(), comparatorArea));
    }
    else if (argument == "VERTEXES")
    {
      out << std::max_element(value.begin(), value.end(), comparatorPoints)->points.size();
    }
    else
    {
      throw std::logic_error("Wrong argument");
    }
  }
}

// Команда MIN: поиск минимального значения площади или количества вершин
void erofick::min(const std::vector<Polygon>& value, std::istream& in, std::ostream& out)
{
  std::string argument = "";
  in >> argument;
  if (value.empty())
  {
    throw std::logic_error("Wrong number");
  }
  else
  {
    if (argument == "AREA")
    {
      iofmtguard guard(out);
      out << std::setprecision(1) << std::fixed;
      out << getPolygonArea(*std::min_element(value.begin(), value.end(), comparatorArea));
    }
    else if (argument == "VERTEXES")
    {
      out << std::min_element(value.begin(), value.end(), comparatorPoints)->points.size();
    }
    else
    {
      throw std::logic_error("Wrong argument");
    }
  }
}

// Команда COUNT: подсчет полигонов по условию
void erofick::count(const std::vector<Polygon>& value, std::istream& in, std::ostream& out)
{
  std::string argument = "";
  in >> argument;
  if (argument == "EVEN")
  {
    out << std::count_if(value.begin(), value.end(), isEven);
  }
  else if (argument == "ODD")
  {
    out << std::count_if(value.begin(), value.end(), isOdd);
  }
  else
  {
    size_t countPoints = std::stoull(argument);
    if (countPoints < 3)
    {
      throw std::logic_error("Wrong number");
    }
    using namespace std::placeholders;
    std::function< bool(const Polygon&) > isCorrectCount = std::bind(isSize, _1, countPoints);
    out << std::count_if(value.begin(), value.end(), isCorrectCount);
  }
}


// Команда INFRAME: проверка вхождения полигона в ограничивающий прямоугольник
void erofick::inframe(const std::vector<Polygon>& value,
  std::istream& in, std::ostream& out)
{
  Polygon argument;
  in >> argument;
  if (!in)
  {
    throw std::invalid_argument("Wrong argument");
  }
  Polygon frameRectangle = getBoundingBox(value); // Получаем ограничивающий прямоугольник
  if (argument <= frameRectangle) // Проверяем вхождение
  {
    out << "<TRUE>";
  }
  else
  {
    out << "<FALSE>";
  }
}

// Команда RMECHO: удаление последовательных дубликатов указанного полигона
void erofick::rmecho(std::vector<Polygon>& value, std::istream& in, std::ostream& out)
{
  Polygon polygon;
  in >> polygon;
  if (!in)
  {
    throw std::logic_error("Wrong argument");
  }

  size_t removedCount = 0;
  // Удаляем последовательные дубликаты указанного полигона
  auto newEnd = std::unique(value.begin(), value.end(),
    [&polygon, &removedCount](const Polygon& lhs, const Polygon& rhs) {
      if (lhs == rhs && lhs == polygon) {
        removedCount++;
        return true;
      }
      return false;
    });

  // Удаляем "лишние" элементы
  value.erase(newEnd, value.end());
  out << removedCount; // Выводим количество удаленных полигонов
}

