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
#include <list>


int main() {
    int studentCount = 0;
    char choice = getInputChoice();

    std::list<Studentas> studentai;
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
            std::string filename;
            std::cout << "Iveskite failo pavadinima: ";
            std::getline(std::cin, filename);
            readFromFile(studentai, nd_rezultatai, egzaminoBalai, filename);
            studentCount = studentai.size();
        }
        else if (choice == '4') {
            std::vector<std::string> filenames = {
                "studentai_1000.txt",
                "studentai_10000.txt",
                "studentai_100000.txt",
                "studentai_1000000.txt",
                "studentai_10000000.txt"
            };

            for (const auto& filename : filenames) {
                std::cout << "Analizuojamas failas: " << filename << std::endl;

                auto totalStart = std::chrono::high_resolution_clock::now();


                auto start = std::chrono::high_resolution_clock::now();
                readFromFile(studentai, nd_rezultatai, egzaminoBalai, filename);
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> fileReadTime = end - start;
                std::cout << "Failo \"" << filename << "\" nuskaitymas uztruko: " << fileReadTime.count() << " sekundes." << std::endl;

                auto itStudent = studentai.begin();
                auto itNdRezultatai = nd_rezultatai.begin();
                auto itEgzaminoBalai = egzaminoBalai.begin();

                for (; itStudent != studentai.end(); ++itStudent, ++itNdRezultatai, ++itEgzaminoBalai) {
                    double egzaminoBalas = *itEgzaminoBalai;
                    itStudent->galutinisBalas = 0.4 * skaiciuotiVidurki(*itNdRezultatai) + 0.6 * egzaminoBalas;
                    itStudent->galutinisMediana = 0.4 * skaiciuotiMediana(*itNdRezultatai) + 0.6 * egzaminoBalas;
                }

                char sortOrder;
                std::cout << "Pasirinkite rusiavima (1 - didejimo, 2 - mazejimo): ";
                std::cin >> sortOrder;


                start = std::chrono::high_resolution_clock::now();
                if (sortOrder == '1') {
                    studentai.sort([](const Studentas& a, const Studentas& b) {
                        return a.galutinisBalas < b.galutinisBalas;
                        });
                }
                else if (sortOrder == '2') {
                    studentai.sort([](const Studentas& a, const Studentas& b) {
                        return a.galutinisBalas > b.galutinisBalas;
                        });
                }
                else {
                    std::cout << "Neteisingas pasirinkimas! Rusiavimas nebus atliktas." << std::endl;
                    continue;
                }
                end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> sortTime = end - start;
                std::cout << "Studentu rusiavimas uztruko: " << sortTime.count() << " sekundes." << std::endl;

                // Measure time to split students into groups
                std::list<Studentas> vargsiai, kietiakiai;
                start = std::chrono::high_resolution_clock::now();
                categorizeStudents(studentai, vargsiai, kietiakiai);
                studentai.clear();
                end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> splitTime = end - start;
                std::cout << "Studentu dalijimas i grupes uztruko: " << splitTime.count() << " sekundes." << std::endl;

                // Measure time to write 'vargsiai' to file
                start = std::chrono::high_resolution_clock::now();
                writeResultsToFile(vargsiai, "vargsiai_" + filename);
                end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> writeVargsiaiTime = end - start;
                std::cout << "Vargsiu irasymas i faila uztruko: " << writeVargsiaiTime.count() << " sekundes." << std::endl;

                // Measure time to write 'kietiakiai' to file
                start = std::chrono::high_resolution_clock::now();
                writeResultsToFile(kietiakiai, "kietiakiai_" + filename);
                end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> writeKietiakiaiTime = end - start;
                std::cout << "Kieteku irasymas i faila uztruko: " << writeKietiakiaiTime.count() << " sekundes." << std::endl;

                auto totalEnd = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> totalTime = totalEnd - totalStart;
                std::cout << "Bendras laikas visiems veiksmams: " << totalTime.count() << " sekundes." << std::endl;

                std::cout << std::endl;
            }
            return 0;
        }

        auto itStudent = studentai.begin();
        auto itNdRezultatai = nd_rezultatai.begin();
        auto itEgzaminoBalai = egzaminoBalai.begin();

        for (; itStudent != studentai.end(); ++itStudent, ++itNdRezultatai, ++itEgzaminoBalai) {
            double egzaminoBalas = *itEgzaminoBalai;
            itStudent->galutinisBalas = 0.4 * skaiciuotiVidurki(*itNdRezultatai) + 0.6 * egzaminoBalas;
            itStudent->galutinisMediana = 0.4 * skaiciuotiMediana(*itNdRezultatai) + 0.6 * egzaminoBalas;
        }

        std::list<Studentas> vargsiai;
        std::list<Studentas> kietiakiai;
        categorizeStudents(studentai, vargsiai, kietiakiai);


        char sortOrder;
        std::cout << "Pasirinkite rusiavima (1 - didejimo, 2 - mazejimo): ";
        std::cin >> sortOrder;


        processAndWriteResults(vargsiai, "vargsiai", sortOrder);
        processAndWriteResults(kietiakiai, "kietiakiai", sortOrder);
        std::cout << "Rezultatai isvesti i failus." << std::endl;

    }
    catch (const std::exception& e) {
        std::cerr << "Klaida: " << e.what() << std::endl;
    }

    return 0;
}