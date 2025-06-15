#include "commands.hpp"
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <cmath>
#include <string>
#include <cctype>

namespace prokopenko {

  static constexpr double EPS = 1e-6;

  static bool equalArea(const Polygon& a, const Polygon& b) {
    return std::fabs(a.getArea() - b.getArea()) < EPS;
  }

  // Проверка: является ли p уникальным по отношению к already_seen (по isPermOf)
  static bool isUniquePerm(const std::vector<Polygon>& seen, const Polygon& p) {
    for (const auto& q : seen) {
      if (p.isPermOf(q)) return false;
    }
    return true;
  }

  void Area(const std::vector<Polygon>& polys, std::ostream& out) {
    std::string param;
    if (!(std::cin >> param)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    if (param == "EVEN" || param == "ODD") {
      double s = 0.0;
      for (const auto& p : polys) {
        if (p.getArea() > EPS && ((p.points.size() % 2 == 0) == (param == "EVEN"))) {
          s += p.getArea();
        }
      }
      out << std::fixed << std::setprecision(1) << s << '\n';
    }
    else if (param == "MEAN") {
      if (polys.empty()) {
        out << "<INVALID COMMAND>\n";
        return;
      }
      double s = 0.0;
      size_t cnt = 0;
      for (const auto& p : polys) {
        if (p.getArea() > EPS) {
          s += p.getArea();
          ++cnt;
        }
      }
      if (cnt == 0) {
        out << "0.0\n";
      }
      else {
        out << std::fixed << std::setprecision(1) << (s / cnt) << '\n';
      }
    }
    else if (std::all_of(param.begin(), param.end(), ::isdigit)) {
      size_t n = 0;
      try {
        n = std::stoul(param);
      }
      catch (...) {
        out << "<INVALID COMMAND>\n";
        return;
      }
      if (n < 3) {
        out << "<INVALID COMMAND>\n";
        return;
      }
      double s = 0.0;
      for (const auto& p : polys) {
        if (p.getArea() > EPS && p.points.size() == n) {
          s += p.getArea();
        }
      }
      out << std::fixed << std::setprecision(1) << s << '\n';
    }
    else {
      out << "<INVALID COMMAND>\n";
    }
  }

  void Max(const std::vector<Polygon>& polys, std::ostream& out) {
    std::string param;
    if (!(std::cin >> param)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    if (param == "AREA") {
      double mval = -1.0;
      bool found = false;
      for (const auto& p : polys) {
        double a = p.getArea();
        if (a > EPS && (!found || a > mval)) {
          mval = a;
          found = true;
        }
      }
      found ? out << std::fixed << std::setprecision(1) << mval << '\n' :
        out << "<INVALID COMMAND>\n";
    }
    else if (param == "VERTEXES") {
      size_t mv = 0;
      bool found = false;
      for (const auto& p : polys) {
        double a = p.getArea();
        if (a > EPS && (!found || p.points.size() > mv)) {
          mv = p.points.size();
          found = true;
        }
      }
      found ? out << mv << '\n' : out << "<INVALID COMMAND>\n";
    }
    else {
      out << "<INVALID COMMAND>\n";
    }
  }

  void Min(const std::vector<Polygon>& polys, std::ostream& out) {
    std::string param;
    if (!(std::cin >> param)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    if (param == "AREA") {
      double mval = 0.0;
      bool found = false;
      for (const auto& p : polys) {
        double a = p.getArea();
        if (a > EPS && (!found || a < mval)) {
          mval = a;
          found = true;
        }
      }
      found ? out << std::fixed << std::setprecision(1) << mval << '\n' :
        out << "<INVALID COMMAND>\n";
    }
    else if (param == "VERTEXES") {
      size_t mv = 0;
      bool found = false;
      for (const auto& p : polys) {
        double a = p.getArea();
        if (a > EPS && (!found || p.points.size() < mv)) {
          mv = p.points.size();
          found = true;
        }
      }
      found ? out << mv << '\n' : out << "<INVALID COMMAND>\n";
    }
    else {
      out << "<INVALID COMMAND>\n";
    }
  }

  void Mean(const std::vector<Polygon>& polys, std::ostream& out) {
    double s = 0.0;
    size_t cnt = 0;
    for (const auto& p : polys) {
      double a = p.getArea();
      if (a > EPS) {
        s += a;
        ++cnt;
      }
    }
    cnt ? out << std::fixed << std::setprecision(1) << (s / cnt) << '\n' :
      out << "<INVALID COMMAND>\n";
  }

  void CountOdd(const std::vector<Polygon>& polys, std::ostream& out) {
    std::vector<Polygon> unique;
    for (const auto& p : polys) {
      if (p.getArea() > EPS && isUniquePerm(unique, p)) {
        unique.push_back(p);
      }
    }
    size_t cnt = std::count_if(unique.begin(), unique.end(), [](const Polygon& p) {
      return p.points.size() % 2 == 1;
      });
    out << cnt << '\n';
  }

  void CountEven(const std::vector<Polygon>& polys, std::ostream& out) {
    std::vector<Polygon> unique;
    for (const auto& p : polys) {
      if (p.getArea() > EPS && isUniquePerm(unique, p)) {
        unique.push_back(p);
      }
    }
    size_t cnt = std::count_if(unique.begin(), unique.end(), [](const Polygon& p) {
      return p.points.size() % 2 == 0;
      });
    out << cnt << '\n';
  }

  void CountN(const std::vector<Polygon>& polys, std::ostream& out, size_t n) {
    if (n < 3) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    std::vector<Polygon> unique;
    for (const auto& p : polys) {
      if (p.getArea() > EPS && isUniquePerm(unique, p)) {
        unique.push_back(p);
      }
    }
    size_t cnt = std::count_if(unique.begin(), unique.end(), [n](const Polygon& p) {
      return p.points.size() == n;
      });
    out << cnt << '\n';
  }

  void Same(const std::vector<Polygon>& polys, std::ostream& out) {
    size_t n;
    if (!(std::cin >> n)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    Polygon pattern;
    if (!(std::cin >> pattern) || pattern.getArea() <= EPS) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    size_t cnt = std::count_if(polys.begin(), polys.end(), [&pattern](const Polygon& p) {
      return p.isPermOf(pattern);
      });
    out << cnt << '\n';
  }

  void Right(const std::vector<Polygon>& polys, std::ostream& out) {
    size_t cnt = std::count_if(polys.begin(), polys.end(), [](const Polygon& p) {
      return p.getArea() > EPS && p.isRight();
      });
    out << cnt << '\n';
  }

  void Perms(const std::vector<Polygon>& polys, std::ostream& out) {
    size_t n;
    if (!(std::cin >> n)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    Polygon pattern;
    if (!(std::cin >> pattern) || pattern.getArea() <= EPS) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    size_t cnt = std::count_if(polys.begin(), polys.end(), [&pattern](const Polygon& p) {
      return p.isPermOf(pattern);
      });
    out << cnt << '\n';
  }

  void Less(const std::vector<Polygon>& polys, std::ostream& out) {
    Polygon pattern;
    if (!(std::cin >> pattern)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    double a0 = pattern.getArea();
    if (a0 <= EPS) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    size_t cnt = std::count_if(polys.begin(), polys.end(), [a0](const Polygon& p) {
      return p.getArea() > EPS && p.getArea() < a0;
      });
    out << cnt << '\n';
  }

  void More(const std::vector<Polygon>& polys, std::ostream& out) {
    Polygon pattern;
    if (!(std::cin >> pattern)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    double a0 = pattern.getArea();
    if (a0 <= EPS) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    size_t cnt = std::count_if(polys.begin(), polys.end(), [a0](const Polygon& p) {
      return p.getArea() > EPS && p.getArea() > a0;
      });
    out << cnt << '\n';
  }

  void Equal(const std::vector<Polygon>& polys, std::ostream& out) {
    Polygon pattern;
    if (!(std::cin >> pattern) || pattern.getArea() <= EPS) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    size_t cnt = std::count_if(polys.begin(), polys.end(), [&pattern](const Polygon& p) {
      return equalArea(p, pattern);
      });
    out << cnt << '\n';
  }

} // namespace prokopenko
