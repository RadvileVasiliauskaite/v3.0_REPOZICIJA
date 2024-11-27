#include "rezultatai.h"
#include "studentas.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <numeric>

void skaiciavimai(std::vector<Studentas>& studentai, const std::vector<std::vector<double>>& nd_rezultatai, const std::vector<double>& egzaminoBalai) {
    for (size_t i = 0; i < studentai.size(); ++i) {
        double egzaminoBalas = egzaminoBalai[i];
        studentai[i].setGalutinisBalas(0.4 * skaiciuotiVidurki(nd_rezultatai[i]) + 0.6 * egzaminoBalas);
        studentai[i].setGalutinisMediana(0.4 * skaiciuotiMediana(nd_rezultatai[i]) + 0.6 * egzaminoBalas);
    }
}

double skaiciuotiVidurki(const std::vector<double>& nd_rezultatai) {
    if (nd_rezultatai.empty()) return 0.0;
    return std::accumulate(nd_rezultatai.begin(), nd_rezultatai.end(), 0.0) / nd_rezultatai.size();
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
    std::cout << std::left << std::setw(20) << "Vardas"
        << std::setw(20) << "Pavarde"
        << std::setw(20) << "Galutinis (Vid.)"
        << std::setw(20) << "Galutinis (Med.)"
        << std::endl;
    

    for (const auto& studentas : studentai) {
        studentas.printInfo();
    }
}
