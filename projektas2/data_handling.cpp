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
        if (studentas.getGalutinisBalas() < 5.0) {
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

    file << std::setw(15) << "EgzaminoBalas" << std::endl;

    
    auto itStudentas = studentai.begin();
    auto itNd = nd_rezultatai.begin();
    auto itEgz = egzaminoBalai.begin();

    
    while (itStudentas != studentai.end()) {
        file << std::left << std::setw(15) << itStudentas->getVardas()
            << std::setw(15) << itStudentas->getPavarde() << " ";

       
        for (double balas : *itNd) {
            file << std::setw(10) << static_cast<int>(balas) << " ";
        }

        file << std::setw(15) << static_cast<int>(*itEgz) << std::endl;

        ++itStudentas;
        ++itNd;
        ++itEgz;
    }

    file.close();
}


void writeResultsToFile(const std::list<Studentas>& studentai, const std::string& filename) {
    std::ofstream file(filename + ".txt", std::ios::out | std::ios::trunc);

    if (!file.is_open()) {
        std::cerr << "Nepavyko atidaryti failo: " << filename << std::endl;
        return;
    }
    file << std::left << std::setw(15) << "Vardas"
        << std::setw(15) << "Pavarde"
        << std::setw(15) << "Galutinis(Vid.)"
        << std::setw(15) << "Galutinis(Med.)" << std::endl;

    for (const auto& studentas : studentai) {
        file << studentas << std::endl; //isvedimo operatorius
    }

    file.close();
}

void processAndWriteResults(std::list<Studentas>& studentai, const std::string& category, char sortOrder) {

    if (sortOrder == '1') {
        studentai.sort([](const Studentas& a, const Studentas& b) {
            return a.getGalutinisBalas() < b.getGalutinisBalas();
            });
    }
    else {
        studentai.sort([](const Studentas& a, const Studentas& b) {
            return a.getGalutinisBalas() > b.getGalutinisBalas();
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
    studentai.clear();
    nd_rezultatai.clear();
    egzaminoBalai.clear();

    int indexLength = std::to_string(studentCount).length();
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < studentCount; ++i) {
        
        Studentas studentas;
        studentas.setVardas( "Vardas" + formatIndex(i + 1, indexLength));
        studentas.setPavarde( "Pavarde" + formatIndex(i + 1, indexLength));

        std::vector<double> uzduotys(5);
        for (int j = 0; j < 5; ++j) {
            uzduotys[j] = generuotiAtsitiktiniBala();
        }
        nd_rezultatai.push_back(uzduotys);
        egzaminoBalai.push_back(generuotiAtsitiktiniBala());
        studentai.push_back(studentas);
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
        std::string vardas;
        std::getline(std::cin, vardas);
        it->setVardas(vardas);
        std::cout << "Iveskite " << i + 1 << "-ojo studento pavarde: ";
        std::string pavarde;
        std::getline(std::cin, pavarde);
        it->setPavarde(pavarde);

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

        ++it;
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

        std::string vardas, pavarde;
        iss >> vardas >> pavarde;

        Studentas studentas;
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
        cout << "Pasirinkite duomenu irasymo tipa:\n1 - Ivesti duomenis\n2 - Generuoti duomenis atsitiktinai\n3 - Nuskaityti duomenis is failo\n4 - Atlikti programos veikimo greicio analize\n5 - Pademonstruoti Triju metodu taisykle\n";
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

void strategija1(const std::list<Studentas>& studentai, std::list<Studentas>& vargsiai, std::list<Studentas>& kietiakiai) {
    for (const auto& studentas : studentai) {
        if (studentas.getGalutinisBalas() < 5.0) {
            vargsiai.push_back(studentas);
        }
        else {
            kietiakiai.push_back(studentas);
        }
    }
    std::cout << "Strategija 1 taikyta: sukurti vargsiai ir kietiakiai sarasus." << std::endl;
}

void strategija2(std::list<Studentas>& studentai, std::list<Studentas>& vargsiai) {
    for (auto it = studentai.begin(); it != studentai.end(); ) {
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

void strategija3(std::list<Studentas>& studentai, std::list<Studentas>& vargsiai, std::list<Studentas>& kietiakiai) {
    auto it = std::partition(studentai.begin(), studentai.end(), [](const Studentas& studentas) {
        return studentas.getGalutinisBalas() < 5.0;
        });

    vargsiai.assign(studentai.begin(), it);  
    kietiakiai.assign(it, studentai.end());  

    std::cout << "Strategija 3 taikyta: 1 strategija sukurti vargsiai ir kietiakiai sarasus." << std::endl;
}

int selectStrategyAndCategorizeStudents(std::list<Studentas>& studentai, std::list<Studentas>& vargsiai, std::list<Studentas>& kietiakiai) {
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
    Studentas studentas1("Petras", "Petraitis", 9.7, 8.5);
    std::cout << "Studentas1: " << studentas1.getVardas() << " " << studentas1.getPavarde() << " " << " Galutinis(Vid.): " << studentas1.getGalutinisBalas() << " Galutinis(Med.): " << studentas1.getGalutinisMediana() << std::endl;

    cout << "Studentas2 nukopijuotas studentas1" << endl;
    Studentas studentas2 = studentas1;
    std::cout << "Studentas 2:" << studentas2.getVardas() << " " << studentas2.getPavarde() << " " << " Galutinis(Vid.): " << studentas2.getGalutinisBalas() << " Galutinis(Med.): " << studentas2.getGalutinisMediana() << std::endl;

    cout << "Studentas3 priskiriamas studentas1" << endl;
    Studentas studentas3("Jonas", "Jonaitis", 5.5, 3.4);
    std::cout << "Studentas3 (pries priskyrima): " << studentas3.getVardas() << " " << studentas3.getPavarde() << " " << " Galutinis(Vid.): " << studentas3.getGalutinisBalas() << " Galutinis(Med.): " << studentas3.getGalutinisMediana() << std::endl;
    studentas3 = studentas1;
    std::cout << "Studentas3 (po priskyrimo): " << studentas3.getVardas() << " " << studentas3.getPavarde() << " " << " Galutinis(Vid.): " << studentas3.getGalutinisBalas() << " Galutinis(Med.): " << studentas3.getGalutinisMediana() << std::endl;

    studentas1.~Studentas();
    std::cout << "Studentas1 po destruktoriaus panaudojimo: " << studentas1 << endl;

}