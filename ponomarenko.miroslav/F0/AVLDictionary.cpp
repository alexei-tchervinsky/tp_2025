#include "AVLDictionary.hpp"

#include <algorithm>

void AVLDictionary::insert(const std::string &word) {
    dict_[word]++;
}

bool AVLDictionary::removeWord(const std::string &word) {
    return dict_.erase(word) > 0;
}

void AVLDictionary::clear() {
    dict_.clear();
}

std::size_t AVLDictionary::getFreq(const std::string &word) const {
    auto it = dict_.find(word);

    if (it == dict_.end()) {
        return 0;
    }

    return it->second;
}

bool AVLDictionary::isEmpty() const {
    return dict_.empty();
}

std::size_t AVLDictionary::size() const {
    return dict_.size();
}

void AVLDictionary::printAll(std::ostream &out) const {
    if (dict_.empty()) {
        out << "<EMPTY>\n";
        return;
    }

    for (const auto& a : dict_) {
        out << a.first << ":" << a.second << " ";
    }

    out << "\n";
}

std::vector<std::pair<std::string, std::size_t>> AVLDictionary::getTopN(std::size_t n) const {
    std::vector<std::pair<std::string, std::size_t>> result(dict_.begin(), dict_.end());

    std::sort(result.begin(), result.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });

    if (result.size() > n) {
        result.resize(n);
    }

    return result;
}

void AVLDictionary::printTopThree(std::ostream &out) const {
    std::vector<std::pair<std::string, std::size_t>> topWords = getTopN(3);

    for (const auto& a : topWords) {
        out << a.first << ":" << a.second << " ";
    }

    out << "\n";
}
