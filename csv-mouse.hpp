#pragma once
#include <stdexcept>
#include <vector>
#include <string>
#include <fstream>

class csv_mouse {
public:
    inline csv_mouse(int columns, char separator = ',');
    inline csv_mouse(const std::vector<std::string> &row, char separator = ',');
    inline ~csv_mouse();

    inline void add_row(const std::vector<std::string> &row);
    inline void save_table(std::string filename) const;
private:
    std::vector<std::vector<std::string>> table;
    char sep;
    inline void check_row_size(const std::vector<std::string> &row);
};

csv_mouse::csv_mouse(int columns, char separator) {
    table = std::vector<std::vector<std::string>>(columns);
    sep = static_cast<char>(separator);
}

csv_mouse::csv_mouse(const std::vector<std::string> &row, char separator) :
    csv_mouse(row.size(), separator) {
        add_row(row);
    }

csv_mouse::~csv_mouse() {
    table.clear();
}

void csv_mouse::add_row(const std::vector<std::string> &row) {
    check_row_size(row);
    for (int i = 0; i < row.size(); ++i) {
        table[i].push_back(row[i]);
    }
}

void csv_mouse::save_table(std::string filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Can't open file: " + filename);
    }

    if (table.empty() || table[0].empty()) {
        throw std::runtime_error("Table is empty, nothing to save.");
    }

    for (int i = 0; i < table[0].size(); ++i) {
        for (int j = 0; j < table.size(); ++j) {
            file << table[j][i];
            if (j != table.size() - 1) {
                file << sep;
            }
        }
        file << '\n';
    }

    file.close();
}

void csv_mouse::check_row_size(const std::vector<std::string> &row) {
    if (row.size() != table.size()) {
        throw std::invalid_argument(
            "Row size does not match defined number of columns in the table: " +
            std::to_string(row.size()) + " != " + std::to_string(table.size())
        );
    }
}
