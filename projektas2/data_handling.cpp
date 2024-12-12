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

/**
 * @brief Suformuoja skaiciu (indeksa), pridedant nulinius simbolius iki nurodyto ilgio.
 * @param index Skaicius, kuri reikia formatuoti.
 * @param maxLength Maksimalus simboliu skaicius.
 * @return Suformuotas eilutes pavidalo skaicius.
 */
std::string formatIndex(int index, int maxLength) {
    std::string formatted = std::to_string(index);
    while (formatted.length() < maxLength) {
        formatted = "0" + formatted;
    }
    return formatted;
}

/**
 * @brief Skirsto studentus i dvi grupes: "vargsiai" ir "kietiakiai" pagal ju galutini bala.
 * @param studentai Pradinis studentu sarasas.
 * @param vargsiai Grupe studentu su galutiniu balu mazesniu nei 5.
 * @param kietiakiai Grupe studentu su galutiniu balu 5 arba daugiau.
 */
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

/**
 * @brief Leidzia vartotojui pasirinkti rusiavimo tvarka.
 * @return Vartotojo pasirinkimas: '1' - didejimo tvarka, '2' - mazejimo tvarka.
 */
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

/**
 * @brief Iraso studentu duomenis i faila.
 * @param studentai Sarasas studentu.
 * @param nd_rezultatai Namu darbu rezultatai.
 * @param egzaminoBalai Egzamino balai.
 * @param filename Failo pavadinimas.
 */
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

/**
 * @brief Iraso studentu rezultatus i faila suformavus galutini bala.
 * @param studentai Sarasas studentu.
 * @param filename Failo pavadinimas.
 */
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
        file << std::left << std::setw(15) << studentas.getVardas()
            << std::setw(15) << studentas.getPavarde()
            << std::setw(15) << std::fixed << std::setprecision(2) << studentas.getGalutinisBalas()
            << std::setw(15) << std::fixed << std::setprecision(2) << studentas.getGalutinisMediana()
            << std::endl;
    }

    file.close();
}

/**
 * @brief Rusiuoja studentus ir iraso juos i kategorinius failus: "vargsiai" ir "kietiakiai".
 * @param studentai Studentu sarasas.
 * @param category Kategorija: "vargsiai" arba "kietiakiai".
 * @param sortOrder Rusiavimo tvarka.
 */
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

/**
 * @brief Sugeneruoja studentu duomenis atsitiktinai.
 *
 * Kiekvienam studentui priskiriami atsitiktiniai namu darbu balai ir egzamino balas.
 * Sukuriamas failas su sugeneruotais studentu duomenimis.
 *
 * @param studentCount Studentu skaicius, kuriems bus sugeneruoti duomenys.
 * @param studentai Vektorius, kuriame bus saugomi studentu objektai.
 * @param nd_rezultatai Vektorius, kuriame bus saugomi studentu namu darbu balai.
 * @param egzaminoBalai Vektorius, kuriame bus saugomi studentu egzamino balai.
 */
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

/**
 * @brief Leidzia vartotojui ivesti studentu duomenis rankiniu budu.
 *
 * Vartotojas iveda studentu vardus, pavardes, namu darbu balus ir egzamino balus.
 *
 * @param studentCount Studentu skaicius, kuriems bus ivesti duomenys.
 * @param studentai Vektorius, kuriame bus saugomi studentu objektai.
 * @param nd_rezultatai Vektorius, kuriame bus saugomi studentu namu darbu balai.
 * @param egzaminoBalai Vektorius, kuriame bus saugomi studentu egzamino balai.
 */
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

/**
 * @brief Generuoja atsitiktini bala tarp 1 ir 10.
 *
 * @return Atsitiktinis balas, kurio reiksme tarp 1 ir 10.
 */
double generuotiAtsitiktiniBala() {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dist(1, 10);
    return dist(gen);
}

/**
 * @brief Nuskaito studentu duomenis is failo.
 *
 * Nuskaito faila, kuriame yra studentu vardai, pavardes, namu darbu balai ir egzamino balas.
 * Duomenys irasomi i atitinkamus vektorius.
 *
 * @param studentai Vektorius, kuriame bus saugomi studentu objektai.
 * @param nd_rezultatai Vektorius, kuriame bus saugomi studentu namu darbu balai.
 * @param egzaminoBalai Vektorius, kuriame bus saugomi studentu egzamino balai.
 * @param filename Failo pavadinimas, is kurio bus skaitomi duomenys.
 */
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

/**
 * @brief Uztikrina, kad vartotojas ivestu teigiama bala.
 *
 * Vartotojas iveda bala, ir funkcija tikrina, kad jis butu teigiamas.
 * Jei ivestas neteisingas balas, prasoma ivesti dar karta.
 *
 * @param prompt zinute, kuria vartotojas matys pries ivedant bala.
 * @return ivestas teigiamas balas.
 */
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

/**
 * @brief Leidzia vartotojui pasirinkti duomenu ivedimo metoda.
 *
 * Vartotojas gali pasirinkti ivesti duomenis rankiniu budu, generuoti atsitiktinius duomenis, nuskaityti duomenis is failo,
 * atlikti programos veikimo greicio analize arba parodyti "Triju metodu taisykle".
 *
 * @return Pasirinktas ivedimo tipas: '1' - ivesti duomenis, '2' - generuoti atsitiktinius duomenis, '3' - nuskaityti duomenis is failo,
 * '4' - atlikti greicio analize, '5' - demonstruoti "Triju metodu taisykle".
 */
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

/**
 * @brief Skirsto studentus i "vargsius" ir "kietiakus" pagal galutini bala.
 *
 * Si funkcija naudoja paprasta iteracija ir tikrina kiekvieno studento galutini bala:
 * jei balas mazesnis nei 5.0, studentas priskiriamas prie "vargsiu", kitaip prie "kietiaku".
 *
 * @param studentai Vektorius su visais studentais.
 * @param vargsiai Vektorius, kuriame bus saugomi "vargsiu" studentai.
 * @param kietiakiai Vektorius, kuriame bus saugomi "kietiaku" studentai.
 */
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

/**
 * @brief Skirsto studentus i "vargsius" ir pasalina juos is pradinio saraso.
 *
 * Naudojama iteracija, kad pradiniame sarase butu pasalinti studentai su galutiniu balu mazesniu nei 5.0.
 * Sukuriamas "vargsiu" sarasas, i kuri perkelti visi atitinkami studentai.
 *
 * @param studentai Vektorius su visais studentais, is kurio pasalinami "vargsiai".
 * @param vargsiai Vektorius, kuriame bus saugomi "vargsiu" studentai.
 */
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

/**
 * @brief Naudoja optimizuota metoda su `std::partition`, kad paskirstytu studentus i "vargsius" ir "kietiakus".
 *
 * `std::partition` yra naudojama efektyviai atskirti studentus i dvi grupes pagal ju galutinius balus.
 * "Vargsiai" yra studentai, kuriu galutinis balas mazesnis nei 5.0, o "kietiakiai" – kiti.
 *
 * @param studentai Vektorius su visais studentais, kurie bus paskirstyti i dvi grupes.
 * @param vargsiai Vektorius, kuriame bus saugomi "vargsiu" studentai.
 * @param kietiakiai Vektorius, kuriame bus saugomi "kietiaku" studentai.
 */
void strategija3(std::list<Studentas>& studentai, std::list<Studentas>& vargsiai, std::list<Studentas>& kietiakiai) {
    auto it = std::partition(studentai.begin(), studentai.end(), [](const Studentas& studentas) {
        return studentas.getGalutinisBalas() < 5.0;
        });

    vargsiai.assign(studentai.begin(), it);  
    kietiakiai.assign(it, studentai.end());  

    std::cout << "Strategija 3 taikyta: 1 strategija sukurti vargsiai ir kietiakiai sarasus." << std::endl;
}

/**
 * @brief Leidzia vartotojui pasirinkti studentu skirstymo strategija ir ja taikyti.
 *
 * Vartotojas pasirenka skirstymo strategija (1, 2 arba 3), ir pagal pasirinkima taikoma viena is triju strategiju:
 * 1. Bendro konteinerio skaidymas i du naujus konteinerius.
 * 2. Tik vieno naujo konteinerio su studentu padalinimu is pradinio saraso sukurimas.
 * 3. Efektyvi strategija su optimizuotais metodais.
 *
 * @param studentai Vektorius su visais studentais.
 * @param vargsiai Vektorius, kuriame bus saugomi "vargsiu" studentai.
 * @param kietiakiai Vektorius, kuriame bus saugomi "kietiaku" studentai.
 * @return Pasirinkta skirstymo strategija (1-3).
 */
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

/**
 * @brief Demonstruoja "Triju metodu taisykles" veikims, kuri apima objektu kopijavima ir priskyrima.
 *
 * "Triju metodu taisykle" paaiskina, kaip tvarkyti objektu kopijas ir priskyrimus, kad isvengti nepageidaujamu efektu,
 * kai objektai tvarko dinamiskai alokuojamus isteklius. Demonstruojami priskyrimo ir kopijavimo konstruktoriai.
 */
void RuleOfThree() {
    Studentas a;
    std::cout << "Iveskite studento varda pavarde namu darbus(norint baigti namu darbu ivedima iveskite -1) egzamino bala: " << endl;
    std::cin >> a;
    Studentas b;
    b = a;
    Studentas c(b);
    std::cout << a << "\n" << b << c << std::endl;
}