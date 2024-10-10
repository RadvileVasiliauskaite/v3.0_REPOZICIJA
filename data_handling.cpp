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

using namespace std;

double generuotiAtsitiktiniBala() {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dist(0.0, 10.0);
    return dist(gen);
}

void readFromFile(vector<Studentas>& studentai, vector<vector<double>>& nd_rezultatai, vector<double>& egzaminoBalai) {
    cout << "Pasirinkite faila:\n1. kursiokai.txt\n2. studentai10000.txt\n3. studentai100000.txt\n4. studentai1000000.txt\n";
    int pasirinkimas;
    cin >> pasirinkimas;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string failoKelias;
    switch (pasirinkimas) {
    case 1: failoKelias = "C:\\Users\\radvi\\source\\repos\\v.pradinee\\kursiokai.txt"; break;
    case 2: failoKelias = "C:\\Users\\radvi\\source\\repos\\v.pradinee\\studentai10000 (1).txt"; break;
    case 3: failoKelias = "C:\\Users\\radvi\\source\\repos\\v.pradinee\\studentai100000.txt"; break;
    case 4: failoKelias = "C:\\Users\\radvi\\source\\repos\\v.pradinee\\studentai1000000.txt"; break;
    default: cout << "Neteisingas pasirinkimas!" << endl; return;
    }

    ifstream file(failoKelias);
    if (!file.is_open()) {
        cout << "Nepavyko atidaryti failo!" << endl;
        return;
    }

    string header;
    getline(file, header); 

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        Studentas studentas;
        iss >> studentas.vardas >> studentas.pavarde;

        vector<double> uzduotys;
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
            cout << "Netinkama duomenu struktura: " << line << endl;
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
