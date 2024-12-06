#include "data_handling.h"
#include "studentas.h"
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
//copy constructor
void categorizeStudents(const std::vector<Studentas>& studentai, std::vector<Studentas>& vargsiai, std::vector<Studentas>& kietiakiai) {
    for (const auto& studentas : studentai) {
        if (studentas.getGalutinisBalas() < 5.0) {
            vargsiai.push_back(studentas);
        } else {
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
        } else {
            cout << "Klaida! Prasome pasirinkti 1 arba 2." << endl;
        }
    }
}

void writeToFile(const std::vector<Studentas>& studentai, const std::vector<std::vector<double>>& nd_rezultatai, const std::vector<double>& egzaminoBalai, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        return;
    }
    file << std::left << std::setw(15) << "Vardas"
         << std::setw(15) << "Pavarde";

    if (!nd_rezultatai.empty()) {
        for (size_t j = 0; j < nd_rezultatai[0].size(); ++j) {
            file << std::setw(10) << "ND" + std::to_string(j + 1);
        }
    }

    file << std::setw(15) << "EgzaminoBalas" << std::endl;

    for (size_t i = 0; i < studentai.size(); ++i) {
        file << std::left << std::setw(15) << studentai[i].getVardas()
             << std::setw(15) << studentai[i].getPavarde();

        for (double balas : nd_rezultatai[i]) {
            file << std::setw(10) << static_cast<int>(balas);
        }
        file << std::setw(15) << static_cast<int>(egzaminoBalai[i]) << std::endl;
    }
    file.close();
}

void writeResultsToFile(const std::vector<Studentas>& studentai, const std::string& filename) {
    std::ofstream file(filename, std::ios::out | std::ios::trunc);

    if (!file.is_open()) {
        return;
    }
    file << std::left << std::setw(15) << "Vardas"
         << std::setw(15) << "Pavarde"
         << std::setw(15) << "Galutinis (Vid.)"
         << std::setw(15) << "Galutinis (Med.)" << std::endl;

    for (const auto& studentas : studentai) {
        file << std::left << std::setw(15) << studentas.getVardas()
            << std::setw(15) << studentas.getPavarde()
            << std::setw(20) << std::fixed << std::setprecision(2) << studentas.getGalutinisBalas()
            << std::setw(20) << std::fixed << std::setprecision(2) << studentas.getGalutinisMediana()
            << std::endl;
    }

    file.close();
}

void processAndWriteResults(std::vector<Studentas>& studentai, const std::string& category, char sortOrder) {
    if (sortOrder == '1') {
        std::sort(studentai.begin(), studentai.end(), [](const Studentas& a, const Studentas& b) {
            return a.getGalutinisBalas() < b.getGalutinisBalas();
        });
    } else {
        std::sort(studentai.begin(), studentai.end(), [](const Studentas& a, const Studentas& b) {
            return a.getGalutinisBalas() > b.getGalutinisBalas();
        });
    }

    std::vector<Studentas> vargsiai, kietiakiai;
    categorizeStudents(studentai, vargsiai, kietiakiai);

    if (category == "vargsiai") {
        writeResultsToFile(vargsiai, "vargsiai.txt");
    } else if (category == "kietiakiai") {
        writeResultsToFile(kietiakiai, "kietiakiai.txt");
    }
}

void generateStudents(int studentCount, std::vector<Studentas>& studentai, std::vector<std::vector<double>>& nd_rezultatai, std::vector<double>& egzaminoBalai) {
    studentai.resize(studentCount);
    nd_rezultatai.resize(studentCount);
    egzaminoBalai.resize(studentCount);

    int indexLength = std::to_string(studentCount).length();
    for (int i = 0; i < studentCount; ++i) {
        studentai[i].setVardas("Vardas" + formatIndex(i + 1, indexLength));
        studentai[i].setPavarde("Pavarde" + formatIndex(i + 1, indexLength));

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
//priskyrimo operatorius
void inputStudentData(int studentCount, std::vector<Studentas>& studentai, std::vector<std::vector<double>>& nd_rezultatai, std::vector<double>& egzaminoBalai) {
    studentai.resize(studentCount);
    nd_rezultatai.resize(studentCount);
    egzaminoBalai.resize(studentCount);

    for (int i = 0; i < studentCount; ++i) {
        std::cout << "Iveskite " << i + 1 << "-ojo studento varda: ";
        std::string vardas;
        std::getline(std::cin, vardas);
        studentai[i].setVardas(vardas);

        std::cout << "Iveskite " << i + 1 << "-ojo studento pavarde: ";
        std::string pavarde;
        std::getline(std::cin, pavarde);
        studentai[i].setPavarde(pavarde);

        std::cout << "Studento atminties adresas: " << &studentai[i] << std::endl;
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
                } else {
                    uzduotys.push_back(uzduotis);
                }
            } catch (const std::invalid_argument&) {
                std::cout << "Neteisingas balas! Prasome ivesti skaiciu." << std::endl;
            }
        }
        nd_rezultatai[i] = uzduotys;

        double egzaminoBalas = getPositiveScore("Iveskite egzamino rezultata: ");
        egzaminoBalai[i] = egzaminoBalas;
    }
}

double generuotiAtsitiktiniBala() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(1, 10);
    return dist(gen);
}

void readFromFile(std::vector<Studentas>& studentai, std::vector<std::vector<double>>& nd_rezultatai, std::vector<double>& egzaminoBalai, const std::string& filename) {
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
        std::string vardas, pavarde;
        iss >> vardas >> pavarde;

        studentas.setVardas(vardas);
        studentas.setPavarde(pavarde);

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

double getPositiveScore(const std::string& prompt) {
    double score;
    while (true) {
        std::cout << prompt;
        std::cin >> score;
        if (std::cin.fail() || score < 0.0) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Klaida! Prasome ivesti teigiama skaiciu." << std::endl;
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return score;
        }
    }
}

char getInputChoice() {
    char choice;
    while (true) {
        cout << "Pasirinkite duomenu irasymo tipa:\n1 - Ivesti duomenis\n2 - Generuoti duomenis atsitiktinai\n3 - Nuskaityti duomenis is failo\n4 - Atlikti programos veikimo greicio analize\n5 - Demonstruoti Triju metodu taisykle\n";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == '1' || choice == '2' || choice == '3' || choice == '4' || choice == '5') {
            return choice;
        }
        else {
            cout << "Klaida! Prasome pasirinkti 1, 2, 3, 4 arba 5." << endl;
        }
    }
}

void strategija1(const std::vector<Studentas>& studentai, std::vector<Studentas>& vargsiai, std::vector<Studentas>& kietiakiai) {
    for (const auto& studentas : studentai) {
        if (studentas.getGalutinisBalas() < 5.0) {
            vargsiai.push_back(studentas);
        }
        else {
            kietiakiai.push_back(studentas);
        }
    }
}
//priskyrimo konstruktorius
void strategija2(std::vector<Studentas>& studentai, std::vector<Studentas>& vargsiai) {
    vargsiai.reserve(vargsiai.size() + studentai.size());

    auto it = studentai.begin();
    while (it != studentai.end()) {
        if (it->getGalutinisBalas() < 5.0) {
            vargsiai.push_back(*it);
            it = studentai.erase(it);
        }
        else {
            ++it;
        }
    }
    std::cout << "Strategija 2 taikyta: sukurti vargsiai ir pasalinti juos is pradinio saraso." << std::endl;
}


//copy constructor
void strategija3(std::vector<Studentas>& studentai, std::vector<Studentas>& vargsiai, std::vector<Studentas>& kietiakiai) {

    auto partition_point = std::partition(studentai.begin(), studentai.end(), [](const Studentas& s) {
        return s.getGalutinisBalas() < 5.0;
        });

    vargsiai.insert(vargsiai.end(), studentai.begin(), partition_point);
    kietiakiai.insert(kietiakiai.end(), partition_point, studentai.end());

    studentai.clear();

    std::cout << "Strategija 3 paremta 1 strategija: sukurti vargsiai ir kietiakiai." << std::endl;
}

int selectStrategyAndCategorizeStudents(std::vector<Studentas>& studentai, std::vector<Studentas>& vargsiai, std::vector<Studentas>& kietiakiai) {
    int strategyChoice;
    std::cout << "Pasirinkite skaidymo strategija:\n";
    std::cout << "1. Bendro konteinerio skaidymas i du naujus konteinerius.\n";
    std::cout << "2. Tik vieno naujo konteinerio sukurimas su studentu pasalinimu is pirminio saraso.\n";
    std::cout << "3. Efektyvi strategija su optimizuotais metodais.\n";
    std::cout << "iveskite pasirinkima (1-3): ";
    std::cin >> strategyChoice;

    std::string filename = "studentai_" + std::to_string(rand()) + ".txt";

    if (strategyChoice == 1) {
        strategija1(studentai, vargsiai, kietiakiai);
    }
    else if (strategyChoice == 2) {
        strategija2(studentai, vargsiai);

    }
    else if (strategyChoice == 3) {
        strategija3(studentai, vargsiai, kietiakiai);
    }
    else {
        std::cout << "Neteisingas pasirinkimas, strategija nebus taikoma." << std::endl;
    }
    return strategyChoice;
}

void RuleOfThree() {
    //Studentas studentas1("Jonas", "Jonaitis", 9.0, 8.0, { 10, 9, 8 }, 10);
    //std::cout << "Studentas1: " << studentas1; 

    //cout << "Studentas2 nukopijuotas studentas1" << endl;
    //Studentas studentas2 = studentas1;
    //std::cout << "Studentas 2:" << studentas2; 

    //cout << "Studentas3 priskiriamas studentas1" << endl;
    //Studentas studentas3(studentas2);

    //std::cout << "Studentas3 (pries priskyrima): " << studentas2; 
  
    //std::cout << "Studentas3 (po priskyrimo): " << studentas3; 

    //studentas1.~Studentas();
    //std::cout << "Studentas1 po destruktoriaus panaudojimo: " << studentas1 << endl;

    Studentas a;
    std::cout << "Iveskite studento varda pavarde namu darbus(norint baigti namu darbu ivedima iveskite -1) egzamino bala: " << endl;
    std::cin >> a;
    Studentas b;
    b = a;
    Studentas c(b);
    std:: cout << a << "\n" << b << c << std::endl;

}