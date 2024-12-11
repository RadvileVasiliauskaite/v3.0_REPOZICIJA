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
#include <cstdlib>

int main() {
    int studentCount = 0; //Kinatmasis studentu skaiciui saugoti
    char choice = getInputChoice(); // funkcija, vartotojo pasirinkimui nuskaityti
    std::vector<Studentas> studentai; //Studentu objektu vektorius
    std::vector<std::vector<double>> nd_rezultatai; //Studentu namu darbu rezultatai
    std::vector<double> egzaminoBalai; //Studentu egzamino balai
    std::vector<Studentas> vargsiai; //Vektorius studentu kuriu balai <5.0
    std::vector<Studentas> kietiakiai; //Vektorius studentu kuriu balai >5.0

    try {
        if (choice == '1' || choice == '2') {
            if (choice == '2') { //jei pasirenkamas duomenu generavimas
                while (true) {
                    //Nuskaitomas generuojamu studentu skaicius
                    std::cout << "Kiek studentu norite generuoti (1000, 10000, 100000, 1000000, 10000000)? ";
                    std::cin >> studentCount;

                    //Patikrinama, ar ivestis teisinga
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
                //Generuojami studentai
                generateStudents(studentCount, studentai, nd_rezultatai, egzaminoBalai);

            }
            else { //Jei pasirenkamas duomenu ivedimas rankiniu budu
                while (true) {
                    //Nuskaitomas ivedamu studentu skaicius
                    std::cout << "Kiek studentu norite ivesti? ";
                    std::cin >> studentCount;

                    //patikrinama ar ivestis teisinga
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
                // Vartotojo ivesties apdorojimas
                inputStudentData(studentCount, studentai, nd_rezultatai, egzaminoBalai);
                // Rezultatu skaiciavimas
                skaiciavimai(studentai, nd_rezultatai, egzaminoBalai);
                // Rezultatu isvedimas
                displayResults(studentai);
            }
        }
        else if (choice == '3') { // Jei pasirenkamas duomenu nuskaitymas is failo
            std::string filename;
            std::cout << "Iveskite failo pavadinima: ";
            std::getline(std::cin, filename);

            // Duomenu nuskaitymas is failo
            readFromFile(studentai, nd_rezultatai, egzaminoBalai, filename);
            studentCount = studentai.size();
            // Rezultatu skaiciavimas ir isvedimas
            skaiciavimai(studentai, nd_rezultatai, egzaminoBalai);
            displayResults(studentai);
        }
        else if (choice == '4') { //Masinis failu nuskiatymas ir programos analize
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

                // Failo nuskaitymo laiko matavimas
                auto start = std::chrono::high_resolution_clock::now();
                readFromFile(studentai, nd_rezultatai, egzaminoBalai, filename);
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> fileReadTime = end - start;
                std::cout << "Failo \"" << filename << "\" nuskaitymas uztruko: " << fileReadTime.count() << " sekundes." << std::endl;

                skaiciavimai(studentai, nd_rezultatai, egzaminoBalai);

                char sortOrder;
                std::cout << "Pasirinkite rusiavima (1 - didejimo, 2 - mazejimo): ";
                std::cin >> sortOrder;

                // Rusiavimas pagal vartotojo pasirinkta tvarka
                start = std::chrono::high_resolution_clock::now();
                if (sortOrder == '1') {
                    std::sort(studentai.begin(), studentai.end(), [](const Studentas& a, const Studentas& b) {
                        return a.getGalutinisBalas() < b.getGalutinisBalas(); 
                        });
                }
                else if (sortOrder == '2') {
                    std::sort(studentai.begin(), studentai.end(), [](const Studentas& a, const Studentas& b) {
                        return a.getGalutinisBalas() > b.getGalutinisBalas();  
                        });
                }
                else {
                    std::cout << "Neteisingas pasirinkimas! Rusiavimas nebus atliktas." << std::endl;
                    continue;
                }

                end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> sortTime = end - start;
                std::cout << "Studentu rusiavimas uztruko: " << sortTime.count() << " sekundes." << std::endl;

                // Studentu padalijimas i grupes
                start = std::chrono::high_resolution_clock::now();
                int strategyChoice = selectStrategyAndCategorizeStudents(studentai, vargsiai, kietiakiai);
                end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> splitTime = end - start;
                std::cout << "Studentu dalijimas i grupes uztruko: " << splitTime.count() << " sekundes." << std::endl;

                start = std::chrono::high_resolution_clock::now();
                writeResultsToFile(vargsiai, "vargsiai_" + filename);
                end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> writeVargsiaiTime = end - start;
                std::cout << "Vargsiu irasymas i faila uztruko: " << writeVargsiaiTime.count() << " sekundes." << std::endl;

                start = std::chrono::high_resolution_clock::now();
                if (strategyChoice == 1) {
                    writeResultsToFile(kietiakiai, "kietiakiai_" + filename); 
                }
                else if (strategyChoice == 2) {
                    writeResultsToFile(studentai, "kietiakiai_" + filename); 
                }
                else if (strategyChoice == 3) {
                    writeResultsToFile(kietiakiai, "kietiakiai_" + filename);
                }
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
        else if (choice == '5') {
            std::cout << "Triju metodu taisykle" << std:: endl;
            RuleOfThree();
        }


    }
    catch (const std::exception& e) {
        std::cerr << "Klaida: " << e.what() << std::endl; //Klaidos pranesimas
    }

    system("pause"); // Pauze pries uzdarant programa
    return 0; // Programos pabaiga
}