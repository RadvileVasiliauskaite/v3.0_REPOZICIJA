#include "rezultatai.h"
#include "studentas.h"
#include "data_handling.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <limits>
#include <fstream>


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
        std::cerr << "Nepavyko sukurti failo!" << std::endl;
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
    std::cout << "Sugeneruoti duomenys buvo issaugoti faile!" << std::endl;
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
                        std::cout << "Klaida! Prasome pasirinkti 1000, 10000, 100000, 1000000 arba 10000000." << std::endl;
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
            }
            else {
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
