#include "data_handling.h"
#include "studentas.h"
#include "rezultatai.h"
#include <fstream>
#include <iostream>
#include <limits>
#include <random>
#include <string>
#include <sstream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <iomanip>


using namespace std;


std::string formatIndex(int index, int maxLength) {
    std::string formatted = std::to_string(index);
    while (formatted.length() < maxLength) {
        formatted = "0" + formatted;
    }
    return formatted;
}

void categorizeStudents(const std::list<Studentas>& studentai, std::list<Studentas>& vargsiai, std::list<Studentas>& kietiakiai) {
    for (const auto& studentas : studentai) {
        if (studentas.galutinisBalas < 5.0) {
            vargsiai.push_back(studentas);
        }
        else {
            kietiakiai.push_back(studentas);
        }
    }
}

char getSortingChoice() {
    char choice;
    while (true) {
        cout << "Pasirinkite rusavimo tvarka:\n1 - Didejimo tvarka\n2 - Mazejimo tvarka\n";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == '1' || choice == '2') {
            return choice;
        }
        else {
            cout << "Klaida! Prasome pasirinkti 1 arba 2." << endl;
        }
    }
}

void writeToFile(const std::list<Studentas>& studentai, const std::vector<std::vector<double>>& nd_rezultatai, const std::vector<double>& egzaminoBalai, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        return;
    }
    file << std::left << std::setw(15) << "Vardas"
        << std::setw(15) << "Pavarde" << " ";


    if (!nd_rezultatai.empty()) {
        for (size_t j = 0; j < nd_rezultatai[0].size(); ++j) {
            file << std::setw(10) << "ND" + std::to_string(j + 1) << " ";
        }
    }
    auto nd_it = nd_rezultatai.begin();
    auto egzaminas_it = egzaminoBalai.begin();
    for (auto it = studentai.begin(); it != studentai.end(); ++it, ++nd_it, ++egzaminas_it) {
        file << std::left << std::setw(15) << it->vardas
            << std::setw(15) << it->pavarde << " ";

        for (double balas : *nd_it) {
            file << std::setw(10) << static_cast<int>(balas) << " ";
        }

        file << std::setw(15) << static_cast<int>(*egzaminas_it) << std::endl;
    }
    file.close();
}

void writeResultsToFile(const std::list<Studentas>& studentai, const std::string& filename) {
    std::ofstream file(filename + ".txt");
    if (!file.is_open()) {
        return;
    }
    file << std::left << std::setw(15) << "Vardas"
        << std::setw(15) << "Pavarde"
        << std::setw(15) << "Galutinis(Vid.)"
        << std::setw(15) << "Galutinis(Med.)" << std::endl;

    for (const auto& studentas : studentai) {
        file << std::left << std::setw(15) << studentas.vardas
            << std::setw(15) << studentas.pavarde << " "
            << std::fixed << std::setprecision(2)
            << std::setw(15) << studentas.galutinisBalas << " "
            << std::setw(15) << studentas.galutinisMediana << std::endl;
    }
    file.close();
}

void processAndWriteResults(std::list<Studentas>& studentai, const std::string& category, char sortOrder) {

    if (sortOrder == '1') {
        studentai.sort([](const Studentas& a, const Studentas& b) {
            return a.galutinisBalas < b.galutinisBalas;
            });
    }
    else {
        studentai.sort([](const Studentas& a, const Studentas& b) {
            return a.galutinisBalas > b.galutinisBalas;
            });
    }

    std::list<Studentas> vargsiai, kietiakiai;
    categorizeStudents(studentai, vargsiai, kietiakiai);


    if (category == "vargsiai") {
        writeResultsToFile(vargsiai, "vargsiai.txt");
    }
    else if (category == "kietiakiai") {
        writeResultsToFile(kietiakiai, "kietiakiai.txt");
    }
}

void generateStudents(int studentCount, std::list<Studentas>& studentai, std::vector<std::vector<double>>& nd_rezultatai, std::vector<double>& egzaminoBalai) {
    studentai.resize(studentCount);
    nd_rezultatai.resize(studentCount);
    egzaminoBalai.resize(studentCount);

    int indexLength = std::to_string(studentCount).length();
    auto start = std::chrono::high_resolution_clock::now();
    auto it = studentai.begin();
    for (int i = 0; i < studentCount; ++i, ++it) {
        it->vardas = "Vardas" + formatIndex(i + 1, indexLength);
        it->pavarde = "Pavarde" + formatIndex(i + 1, indexLength);
        std::vector<double> uzduotys(5);
        for (int j = 0; j < 5; ++j) {
            uzduotys[j] = generuotiAtsitiktiniBala();
        }
        nd_rezultatai[i] = uzduotys;
        egzaminoBalai[i] = generuotiAtsitiktiniBala();
    }
    std::string filename = "studentai_" + std::to_string(studentCount) + ".txt";
    writeToFile(studentai, nd_rezultatai, egzaminoBalai, filename);
    std::cout << "Sugeneruotas failas: " << filename << " su " << studentCount << " studentais.\n";
}

void inputStudentData(int studentCount, std::list<Studentas>& studentai, std::vector<std::vector<double>>& nd_rezultatai, std::vector<double>& egzaminoBalai) {
    studentai.resize(studentCount);
    nd_rezultatai.resize(studentCount);
    egzaminoBalai.resize(studentCount);

    auto it = studentai.begin();
    for (int i = 0; i < studentCount; ++i) {
        std::cout << "Iveskite " << i + 1 << "-ojo studento varda: ";
        std::getline(std::cin, it->vardas);
        std::cout << "Iveskite " << i + 1 << "-ojo studento pavarde: ";
        std::getline(std::cin, it->pavarde);

        std::cout << "Studento atminties adresas: " << &(*it) << std::endl;
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


double generuotiAtsitiktiniBala() {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dist(1, 10);
    return dist(gen);
}

void readFromFile(std::list<Studentas>& studentai, std::vector<std::vector<double>>& nd_rezultatai, std::vector<double>& egzaminoBalai, const std::string& filename) {

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Nepavyko atidaryti failo: " << filename << std::endl;
        return;
    }

    std::string header;
    std::getline(file, header);

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        Studentas studentas;
        iss >> studentas.vardas >> studentas.pavarde;

        std::vector<double> uzduotys;
        double balas;
        while (iss >> balas) {
            uzduotys.push_back(balas);
        }

        if (uzduotys.size() == 6) {
            double egzaminoBalas = uzduotys.back();
            uzduotys.pop_back();
            studentai.push_back(studentas);
            nd_rezultatai.push_back(uzduotys);
            egzaminoBalai.push_back(egzaminoBalas);
        }
        else {
            std::cout << "Netinkama duomenu struktura: " << line << std::endl;
        }
    }

    file.close();
}

double getPositiveScore(const string& prompt) {
    double score;
    while (true) {
        cout << prompt;
        cin >> score;
        if (cin.fail() || score < 0.0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Klaida! Prasome ivesti teigiama skaiciu." << endl;
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return score;
        }
    }
}

char getInputChoice() {
    char choice;
    while (true) {
        cout << "Pasirinkite duomenu irasymo tipa:\n1 - Ivesti duomenis\n2 - Generuoti duomenis atsitiktinai\n3 - Nuskaityti duomenis is failo\n4 - Atlikti programos veikimo greicio analize\n";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == '1' || choice == '2' || choice == '3' || choice == '4') {
            return choice;
        }
        else {
            cout << "Klaida! Prasome pasirinkti 1, 2, 3 arba 4." << endl;
        }
    }
}