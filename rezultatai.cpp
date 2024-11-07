#include "rezultatai.h"
#include "studentas.h"
#include "data_handling.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

void skaiciavimai(std::vector<Studentas>& studentai, const std::vector<std::vector<double>>& nd_rezultatai, const std::vector<double>& egzaminoBalai) {
    for (size_t i = 0; i < studentai.size(); ++i) {
        double egzaminoBalas = egzaminoBalai[i];
        studentai[i].galutinisBalas = 0.4 * skaiciuotiVidurki(nd_rezultatai[i]) + 0.6 * egzaminoBalas;
        studentai[i].galutinisMediana = 0.4 * skaiciuotiMediana(nd_rezultatai[i]) + 0.6 * egzaminoBalas;
    }
}

double skaiciuotiVidurki(const std::vector<double>& nd_rezultatai) {
    if (nd_rezultatai.empty()) return 0.0;
    double total = 0.0;
    for (double score : nd_rezultatai) {
        total += score;
    }
    return total / nd_rezultatai.size();
}

double skaiciuotiMediana(const std::vector<double>& uzduotys) {
    if (uzduotys.empty()) return 0.0;
    std::vector<double> sortedUzduotys = uzduotys;
    std::sort(sortedUzduotys.begin(), sortedUzduotys.end());
    size_t size = sortedUzduotys.size();
    if (size % 2 == 0) {
        return (sortedUzduotys[size / 2 - 1] + sortedUzduotys[size / 2]) / 2;
    }
    else {
        return sortedUzduotys[size / 2];
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