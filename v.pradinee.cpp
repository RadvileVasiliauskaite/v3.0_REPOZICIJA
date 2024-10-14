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

                // Measure time to read file
                auto start = std::chrono::high_resolution_clock::now();
                readFromFile(studentai, nd_rezultatai, egzaminoBalai);
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> fileReadTime = end - start;
                std::cout << "Failo \"" << filename << "\" nuskaitymas uztruko: " << fileReadTime.count() << " sekundes." << std::endl;

                // Measure time to sort students
                start = std::chrono::high_resolution_clock::now();
                std::sort(studentai.begin(), studentai.end(), [](const Studentas& a, const Studentas& b) {
                    return a.galutinisBalas < b.galutinisBalas;
                    });
                end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> sortTime = end - start;
                std::cout << "Studentu rusiavimas uztruko: " << sortTime.count() << " sekundes." << std::endl;

                // Measure time to split students into groups
                std::vector<Studentas> vargsiai, kietiakiai;
                start = std::chrono::high_resolution_clock::now();
                categorizeStudents(studentai, vargsiai, kietiakiai);
                studentai.clear();
                end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> splitTime = end - start;
                std::cout << "Studentu dalijimas i grupes uztruko: " << splitTime.count() << " sekundes." << std::endl;

                // Measure time to write 'vargsiai' to file
                start = std::chrono::high_resolution_clock::now();
                writeResultsToFile(vargsiai, "vargsiai_");
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
            return 0;  // Exit after performance analysis
        }

        for (int i = 0; i < studentCount; ++i) {
            double egzaminoBalas = egzaminoBalai[i];
            studentai[i].galutinisBalas = 0.4 * skaiciuotiVidurki(nd_rezultatai[i]) + 0.6 * egzaminoBalas;
            studentai[i].galutinisMediana = 0.4 * skaiciuotiMediana(nd_rezultatai[i]) + 0.6 * egzaminoBalas;
        }

        std::vector<Studentas> vargsiai;
        std::vector<Studentas> kietiakiai;
        categorizeStudents(studentai, vargsiai, kietiakiai);


        char sortOrder;
        std::cout << "Pasirinkite rusiavima (1 - didejimo, 2 - mazejimo): ";
        std::cin >> sortOrder;

        //  tai dabar padarys processAndWriteResults funkcija
        // if (sortOrder == '1') { 
        //     std::sort(vargsiai.begin(), vargsiai.end(), [](const Studentas& a, const Studentas& b) {
        //         return a.galutinisBalas < b.galutinisBalas;
        //         });
        //     std::sort(kietiakiai.begin(), kietiakiai.end(), [](const Studentas& a, const Studentas& b) {
        //         return a.galutinisBalas < b.galutinisBalas;
        //         });
        // }
        // else if (sortOrder == '2') {
        //     std::sort(vargsiai.begin(), vargsiai.end(), [](const Studentas& a, const Studentas& b) {
        //         return a.galutinisBalas > b.galutinisBalas;
        //         });
        //     std::sort(kietiakiai.begin(), kietiakiai.end(), [](const Studentas& a, const Studentas& b) {
        //         return a.galutinisBalas > b.galutinisBalas;
        //         });
        // }
        // else {
        //     std::cout << "Neteisingas pasirinkimas! Rusiavimas nebus atliktas." << std::endl;
        // }

        processAndWriteResults(vargsiai, "vargsiai", sortOrder);
        processAndWriteResults(kietiakiai, "kietiakiai", sortOrder);
        std::cout << "Rezultatai isvesti i failus." << std::endl;

    }
    catch (const std::exception& e) {
        std::cerr << "Klaida: " << e.what() << std::endl;
    }

    return 0;
}
