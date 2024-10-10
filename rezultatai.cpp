#include "rezultatai.h"
#include "studentas.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

double skaiciuotiVidurki(const std::vector<double>& nd_rezultatai) {
    double total = 0.0;
    for (double score : nd_rezultatai) {
        total += score;
    }
    return total / nd_rezultatai.size();
}

double skaiciuotiMediana(std::vector<double> nd_rezultatai) {
    std::sort(nd_rezultatai.begin(), nd_rezultatai.end());
    size_t size = nd_rezultatai.size();
    if (size % 2 == 0) {
        return (nd_rezultatai[size / 2 - 1] + nd_rezultatai[size / 2]) / 2.0;
    }
    else {
        return nd_rezultatai[size / 2];
    }
}

void displayResults(const std::vector<Studentas>& studentai) {
    std::cout << std::left << std::setw(20) << "Vardas" << std::setw(20) << "Pavarde"
        << std::setw(25) << "Galutinis (Vidurkis)" << std::setw(25) << "Galutinis (Mediana)" << std::endl;
    std::cout << std::string(90, '-') << std::endl;

    for (const auto& studentas : studentai) {
        std::cout << std::setw(20) << studentas.vardas << std::setw(20) << studentas.pavarde
            << std::setw(25) << std::fixed << std::setprecision(2) << studentas.galutinisBalas
            << std::setw(25) << std::fixed << std::setprecision(2) << studentas.galutinisMediana << std::endl;
    }
}
