#include "rezultatai.h"
#include "studentas.h"
#include "data_handling.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <limits>
#include <chrono>
#include <numeric>
#include <fstream>
#include <iomanip>

std::string formatIndex(int index, int maxLength) {
    std::string formatted = std::to_string(index);
    while (formatted.length() < maxLength) {
        formatted = "0" + formatted;
    }
    return formatted;
}

void writeToFile(const std::vector<Studentas>& studentai, const std::vector<std::vector<double>>& nd_rezultatai, const std::vector<double>& egzaminoBalai, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        return;
    }
    file << "Vardas Pavarde UzduociuBalai EgzaminoBalas" << std::endl;
    for (size_t i = 0; i < studentai.size(); ++i) {
        file << studentai[i].vardas << " " << studentai[i].pavarde << " ";
        for (double balas : nd_rezultatai[i]) {
            file << balas << " ";
        }
        file << egzaminoBalai[i] << std::endl;
    }
    file.close();
}

void writeResultsToFile(const std::vector<Studentas>& studentai, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        return;
    }
    file << "Vardas Pavarde Galutinis (Vidurkis) Galutinis (Mediana)" << std::endl;
    for (const auto& studentas : studentai) {
        file << studentas.vardas << " " << studentas.pavarde << " "
            << std::fixed << std::setprecision(2) << studentas.galutinisBalas << " "
            << studentas.galutinisMediana << std::endl;
    }
    file.close();
}

void processAndWriteResults(const std::vector<Studentas>& studentai, const std::string& category) {
    if (category == "vargsiai") {
        writeResultsToFile(studentai, "vargsiai.txt");
    }
    else if (category == "kietiakiai") {
        writeResultsToFile(studentai, "kietiakiai.txt");
    }
}

int main() {
    int studentCount = 0;
    char choice = getInputChoice();

    std::vector<Studentas> studentai;
    std::vector<std::vector<double>> nd_rezultatai;
    std::vector<double> egzaminoBalai;

    try {
        if (choice == '1' || choice == '2') {
            if (choice == '2') {
                while (true) {
                    std::cout << "Kiek studentu norite generuoti (1000, 10000, 100000, 1000000, 10000000)? ";
                    std::cin >> studentCount;
                    if (std::cin.fail() || (studentCount != 1000 && studentCount != 10000 && studentCount != 100000 && studentCount != 1000000 && studentCount != 10000000)) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Neteisingas pasirinkimas! Bandykite dar karta." << std::endl;
                    }
                    else {
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        break;
                    }
                }
                studentai.resize(studentCount);
                nd_rezultatai.resize(studentCount);
                egzaminoBalai.resize(studentCount);
                int indexLength = std::to_string(studentCount).length();
                auto start = std::chrono::high_resolution_clock::now();
                for (int i = 0; i < studentCount; ++i) {
                    studentai[i].vardas = "Vardas" + formatIndex(i + 1, indexLength);
                    studentai[i].pavarde = "Pavarde" + formatIndex(i + 1, indexLength);
                    std::vector<double> uzduotys(5);
                    for (int j = 0; j < 5; ++j) {
                        uzduotys[j] = generuotiAtsitiktiniBala();
                    }
                    nd_rezultatai[i] = uzduotys;
                    egzaminoBalai[i] = generuotiAtsitiktiniBala();
                }
                writeToFile(studentai, nd_rezultatai, egzaminoBalai, "generated_students.txt");
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> elapsed = end - start;
                std::cout << "Failo 'generated_students.txt' sukurimas uztruko: " << elapsed.count() << " sekundziu." << std::endl;
            }
            else {
                while (true) {
                    std::cout << "Kiek studentu norite ivesti? ";
                    std::cin >> studentCount;
                    if (std::cin.fail() || studentCount <= 0) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Neteisingas pasirinkimas! Bandykite dar karta." << std::endl;
                    }
                    else {
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        break;
                    }
                }
                studentai.resize(studentCount);
                nd_rezultatai.resize(studentCount);
                egzaminoBalai.resize(studentCount);
                for (int i = 0; i < studentCount; ++i) {
                    std::cout << "Iveskite " << i + 1 << "-ojo studento varda: ";
                    getline(std::cin, studentai[i].vardas);
                    std::cout << "Iveskite " << i + 1 << "-ojo studento pavarde: ";
                    getline(std::cin, studentai[i].pavarde);
                    std::vector<double> uzduotys;
                    std::cout << "Iveskite uzduociu balus (spauskite ENTER du kartus, kad baigti):" << std::endl;
                    std::string input;
                    while (true) {
                        getline(std::cin, input);
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
                        catch (const std::invalid_argument&) {
                            std::cout << "Neteisingas balas! Prasome ivesti skaiciu." << std::endl;
                        }
                    }
                    nd_rezultatai[i] = uzduotys;
                    double egzaminoBalas = getPositiveScore("Iveskite egzamino rezultata: ");
                    egzaminoBalai[i] = egzaminoBalas;
                }
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

        std::vector<Studentas> vargsiai;
        std::vector<Studentas> kietiakiai;
        for (const auto& studentas : studentai) {
            if (studentas.galutinisBalas < 5.0) {
                vargsiai.push_back(studentas);
            }
            else {
                kietiakiai.push_back(studentas);
            }
        }
        std::cout << "Rusiavimas pagal vidurki..." << std::endl;
        std::sort(vargsiai.begin(), vargsiai.end(), [](const Studentas& a, const Studentas& b) {
            return a.galutinisBalas < b.galutinisBalas;
            });
        std::sort(kietiakiai.begin(), kietiakiai.end(), [](const Studentas& a, const Studentas& b) {
            return a.galutinisBalas < b.galutinisBalas;
            });

        processAndWriteResults(vargsiai, "vargsiai");
        processAndWriteResults(kietiakiai, "kietiakiai");
        std::cout << "Rezultatai isvesti i failus." << std::endl;

    }
    catch (const std::exception& e) {
        std::cerr << "Klaida: " << e.what() << std::endl;
    }

    return 0;
}