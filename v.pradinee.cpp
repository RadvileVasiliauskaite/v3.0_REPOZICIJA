#include "rezultatai.h"
#include "studentas.h"
#include "data_handling.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <stdexcept> 

int main() {
    int studentCount = 0;
    char choice = getInputChoice();

    std::vector<Studentas> studentai;
    std::vector<std::vector<double>> nd_rezultatai;
    std::vector<double> egzaminoBalai;

    try {
        if (choice == '1' || choice == '2') {
            
            while (true) {
                std::cout << "Kiek studentu norite ivesti? ";
                std::cin >> studentCount;

                
                if (std::cin.fail() || studentCount <= 0) {
                    std::cin.clear(); 
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                    std::cout << "Klaida! Prasome ivesti teigiama studentu skaiciu." << std::endl;
                }
                else {
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    break;
                }
            }

            studentai.resize(studentCount);
            nd_rezultatai.resize(studentCount);
            egzaminoBalai.resize(studentCount);

            if (choice == '1') {
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
            else if (choice == '2') {
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
    }
    catch (const std::exception& e) {
        std::cerr << "Klaida: " << e.what() << std::endl;
    }


    return 0;
}

