#include "rezultatai.h"
#include "studentas.h"
#include "data_handling.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <limits> // Added for std::numeric_limits

int main() {
    int studentCount = 0;

    char choice = getInputChoice();

    std::vector<Studentas> studentai;
    std::vector<std::vector<double>> nd_rezultatai;
    std::vector<double> egzaminoBalai;

    if (choice == '1') {
        std::cout << "Kiek studentu norite ivesti? ";
        std::cin >> studentCount;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        studentai.resize(studentCount);
        nd_rezultatai.resize(studentCount);
        egzaminoBalai.resize(studentCount);

        for (int i = 0; i < studentCount; ++i) {
            std::cout << "Iveskite " << i + 1 << "-ojo studento varda: ";
            std::getline(std::cin, studentai[i].vardas);
            std::cout << "Iveskite " << i + 1 << "-ojo studento pavarde: ";
            std::getline(std::cin, studentai[i].pavarde);

            std::vector<double> uzduotys;
            std::cout << "Iveskite uzduociu balus (spauskite ENTER du kartus, kad baigti):" << std::endl;

            std::string input;
            while (true) {
                std::getline(std::cin, input);
                if (input.empty()) {
                    break;
                }

                try {
                    double uzduotis = std::stod(input);
                    if (uzduotis < 0) {
                        std::cout << "Neteisingas balas! Prasome ivesti teigiama skaiciu." << std::endl;
                    }
                    else {
                        uzduotys.push_back(uzduotis);
                    }
                }
                catch (std::invalid_argument&) {
                    std::cout << "Neteisingas balas! Prasome ivesti skaiciu." << std::endl;
                }
            }
            nd_rezultatai[i] = uzduotys;

            double egzaminoBalas = getPositiveScore("Iveskite egzamino rezultata: ");
            egzaminoBalai[i] = egzaminoBalas;
        }
    }
    else if (choice == '2') {
        std::cout << "Kiek studentu norite ivesti? ";
        std::cin >> studentCount;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        studentai.resize(studentCount);
        nd_rezultatai.resize(studentCount);
        egzaminoBalai.resize(studentCount);

        for (int i = 0; i < studentCount; ++i) {
            studentai[i].vardas = "Vardas" + std::to_string(i + 1);
            studentai[i].pavarde = "Pavarde" + std::to_string(i + 1);

            std::vector<double> uzduotys(5);
            for (int j = 0; j < 5; ++j) {
                uzduotys[j] = generuotiAtsitiktiniBala();
            }
            nd_rezultatai[i] = uzduotys;

            egzaminoBalai[i] = generuotiAtsitiktiniBala();
        }
    }
    else if (choice == '3') {
        readFromFile(studentai, nd_rezultatai, egzaminoBalai);
        studentCount = studentai.size();
    }

    for (int i = 0; i < studentCount; ++i) {
        double egzaminoBalas = egzaminoBalai[i];
        studentai[i].galutinisBalas = 0.4 * skaiciuotiVidurki(nd_rezultatai[i]) + 0.6 * egzaminoBalas;
        studentai[i].galutinisMediana = 0.4 * skaiciuotiMediana(nd_rezultatai[i]) + 0.6 * egzaminoBalas;
    }

    std::sort(studentai.begin(), studentai.end(), [](const Studentas& a, const Studentas& b) {
        return a.vardas < b.vardas;
        });

    displayResults(studentai);

    return 0;
}

