#include "rezultatai.h"
#include "studentas.h"
#include "data_handling.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

//Funkcija apskaiciuoja kiekvieno studento galutini bala ir mediana pagal pateiktus namu darbu rezultatus bei egzamino balus
void skaiciavimai(std::list<Studentas>& studentai,
    const std::vector<std::vector<double>> nd_rezultatai,
    const std::vector<double>& egzaminoBalai) {
    auto itStudent = studentai.begin();
    auto itNdRezultatai = nd_rezultatai.begin();
    auto itEgzaminoBalai = egzaminoBalai.begin();

    for (; itStudent != studentai.end() && itNdRezultatai != nd_rezultatai.end() && itEgzaminoBalai != egzaminoBalai.end();
        ++itStudent, ++itNdRezultatai, ++itEgzaminoBalai) {

        double egzaminoBalas = *itEgzaminoBalai;
        itStudent->setGalutinisBalas( 0.4 * skaiciuotiVidurki(*itNdRezultatai) + 0.6 * egzaminoBalas);
        itStudent->setGalutinisMediana( 0.4 * skaiciuotiMediana(*itNdRezultatai) + 0.6 * egzaminoBalas);
    }
}

//Funkcija apskaiciuoja pateikto razultatu saraso vidurki
double skaiciuotiVidurki(const std::vector<double>& nd_rezultatai) {
    if (nd_rezultatai.empty()) return 0.0;
    double total = 0.0;
    for (double score : nd_rezultatai) {
        total += score;
    }
    return total / nd_rezultatai.size();
}

//Funkcija apskaiciuoja pateikto razultatu saraso mediana
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

//Si funkcija isveda visu studentu informacija i standartini isvesties srauta
void displayResults(const std::list<Studentas>& studentai) {
    std::cout << std::left << std::setw(20) << "Vardas"
        << std::setw(20) << "Pavarde"
        << std::setw(25) << "Galutinis (Vid.)" 
        << std::setw(25) << "Galutinis (Med.)" << std::endl;
    std::cout << std::string(90, '-') << std::endl;

    for (const auto& studentas : studentai) {
        std::cout << std::left << std::setw(20) << studentas.getVardas()
            << std::setw(20) << studentas.getPavarde()
            << std::setw(20) << std::fixed << std::setprecision(2) << studentas.getGalutinisBalas()
            << std::setw(20) << std::fixed << std::setprecision(2) << studentas.getGalutinisMediana()
            << std::endl;
    }
}