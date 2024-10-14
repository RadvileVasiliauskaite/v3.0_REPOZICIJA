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
                generateStudents(studentCount, studentai, nd_rezultatai, egzaminoBalai);
                writeToFile(studentai, nd_rezultatai, egzaminoBalai, "generated_students.txt");
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
                inputStudentData(studentCount, studentai, nd_rezultatai, egzaminoBalai);
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
