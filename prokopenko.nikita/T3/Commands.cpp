﻿#include "commands.hpp"
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

  static bool isValidPolygon(const Polygon& p) {
    return p.getArea() > EPS && p.points.size() >= 3;
  }

  void Area(const std::vector<Polygon>& polys, std::ostream& out) {
    std::string param;
    if (!(std::cin >> param)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    if (param == "EVEN") {
      double s = 0.0;
      for (const auto& p : polys) {
        if (isValidPolygon(p) && (p.points.size() % 2 == 0)) {
          s += p.getArea();
        }
      }
      out << std::fixed << std::setprecision(1) << s << '\n';
    }
    else if (param == "ODD") {
      double s = 0.0;
      for (const auto& p : polys) {
        if (isValidPolygon(p) && (p.points.size() % 2 == 1)) {
          s += p.getArea();
        }
      }
      out << std::fixed << std::setprecision(1) << s << '\n';
    }
    else if (param == "MEAN") {
      double s = 0.0;
      size_t cnt = 0;
      for (const auto& p : polys) {
        if (isValidPolygon(p)) {
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
        if (isValidPolygon(p) && p.points.size() == n) {
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
        if (isValidPolygon(p) && (!found || p.getArea() > mval)) {
          mval = p.getArea();
          found = true;
        }
      }
      if (!found) {
        out << "<INVALID COMMAND>\n";
      }
      else {
        out << std::fixed << std::setprecision(1) << mval << '\n';
      }
    }
    else if (param == "VERTEXES") {
      size_t mv = 0;
      bool found = false;
      for (const auto& p : polys) {
        if (isValidPolygon(p) && (!found || p.points.size() > mv)) {
          mv = p.points.size();
          found = true;
        }
      }
      if (!found) {
        out << "<INVALID COMMAND>\n";
      }
      else {
        out << mv << '\n';
      }
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
        if (isValidPolygon(p) && (!found || p.getArea() < mval)) {
          mval = p.getArea();
          found = true;
        }
      }
      if (!found) {
        out << "<INVALID COMMAND>\n";
      }
      else {
        out << std::fixed << std::setprecision(1) << mval << '\n';
      }
    }
    else if (param == "VERTEXES") {
      size_t mv = 0;
      bool found = false;
      for (const auto& p : polys) {
        if (isValidPolygon(p) && (!found || p.points.size() < mv)) {
          mv = p.points.size();
          found = true;
        }
      }
      if (!found) {
        out << "<INVALID COMMAND>\n";
      }
      else {
        out << mv << '\n';
      }
    }
    else {
      out << "<INVALID COMMAND>\n";
    }
  }

  void Mean(const std::vector<Polygon>& polys, std::ostream& out) {
    double s = 0.0;
    size_t cnt = 0;
    for (const auto& p : polys) {
      if (isValidPolygon(p)) {
        s += p.getArea();
        ++cnt;
      }
    }
    if (cnt == 0) {
      out << "<INVALID COMMAND>\n";
    }
    else {
      out << std::fixed << std::setprecision(1) << (s / cnt) << '\n';
    }
  }

  void CountOdd(const std::vector<Polygon>& polys, std::ostream& out) {
    size_t cnt = 0;
    for (const auto& p : polys) {
      if (isValidPolygon(p) && (p.points.size() % 2 == 1)) {
        ++cnt;
      }
    }
    out << cnt << '\n';
  }

  void CountEven(const std::vector<Polygon>& polys, std::ostream& out) {
    size_t cnt = 0;
    for (const auto& p : polys) {
      if (isValidPolygon(p) && (p.points.size() % 2 == 0)) {
        ++cnt;
      }
    }
    out << cnt << '\n';
  }

  void CountN(const std::vector<Polygon>& polys, std::ostream& out, size_t n) {
    if (n < 3) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    size_t cnt = 0;
    for (const auto& p : polys) {
      if (isValidPolygon(p) && p.points.size() == n) {
        ++cnt;
      }
    }
    out << cnt << '\n';
  }

  void Same(const std::vector<Polygon>& polys, std::ostream& out) {
    size_t n;
    if (!(std::cin >> n)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    Polygon pattern;
    if (!(std::cin >> pattern)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    size_t cnt = 0;
    if (isValidPolygon(pattern)) {
      for (const auto& p : polys) {
        if (isValidPolygon(p) && p.isPermOf(pattern)) {
          ++cnt;
        }
      }
    }
    out << cnt << '\n';
  }

  void Right(const std::vector<Polygon>& polys, std::ostream& out) {
    size_t cnt = 0;
    for (const auto& p : polys) {
      if (isValidPolygon(p) && p.isRight()) {
        ++cnt;
      }
    }
    out << cnt << '\n';
  }

  void Perms(const std::vector<Polygon>& polys, std::ostream& out) {
    size_t n;
    if (!(std::cin >> n)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    Polygon pattern;
    if (!(std::cin >> pattern)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    size_t cnt = 0;
    if (isValidPolygon(pattern)) {
      for (const auto& p : polys) {
        if (isValidPolygon(p) && p.isPermOf(pattern)) {
          ++cnt;
        }
      }
    }
    out << cnt << '\n';
  }

  void Less(const std::vector<Polygon>& polys, std::ostream& out) {
    Polygon pattern;
    if (!(std::cin >> pattern)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    if (!isValidPolygon(pattern)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    double a0 = pattern.getArea();
    size_t cnt = 0;
    for (const auto& p : polys) {
      if (isValidPolygon(p) && p.getArea() < a0) {
        ++cnt;
      }
    }
    out << cnt << '\n';
  }

  void More(const std::vector<Polygon>& polys, std::ostream& out) {
    Polygon pattern;
    if (!(std::cin >> pattern)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    if (!isValidPolygon(pattern)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    double a0 = pattern.getArea();
    size_t cnt = 0;
    for (const auto& p : polys) {
      if (isValidPolygon(p) && p.getArea() > a0) {
        ++cnt;
      }
    }
    out << cnt << '\n';
  }

  void Equal(const std::vector<Polygon>& polys, std::ostream& out) {
    Polygon pattern;
    if (!(std::cin >> pattern)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    size_t cnt = 0;
    if (isValidPolygon(pattern)) {
      for (const auto& p : polys) {
        if (isValidPolygon(p) && equalArea(p, pattern)) {
          ++cnt;
        }
      }
    }
    out << cnt << '\n';
  }

} // namespace prokopenko
