#include "data_handling.h"
#include "studentas.h"
#include <fstream>
#include <iostream>
#include <limits>
#include <random>
#include <string>

using namespace std;

double generuotiAtsitiktiniBala() {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dist(0.0, 10.0);
    return dist(gen);
}

void readFromFile(vector<Studentas>& studentai, vector<vector<double>>& nd_rezultatai, vector<double>& egzaminoBalai) {
    ifstream file("C:\\Users\\radvi\\source\\repos\\v.pradinee\\kursiokai.txt");

    if (!file.is_open()) {
        cout << "Nepavyko atidaryti failo!" << endl;
        return;
    }

    string header;
    getline(file, header);

    string vardas, pavarde;
    double uzduotis1, uzduotis2, uzduotis3, uzduotis4, uzduotis5, egzam;

    while (file >> vardas >> pavarde >> uzduotis1 >> uzduotis2 >> uzduotis3 >> uzduotis4 >> uzduotis5 >> egzam) {
        Studentas studentas;
        studentas.vardas = vardas;
        studentas.pavarde = pavarde;
        studentai.push_back(studentas);
        nd_rezultatai.push_back({ uzduotis1, uzduotis2, uzduotis3, uzduotis4, uzduotis5 });
        egzaminoBalai.push_back(egzam);
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
        cout << "Pasirinkite duomenu irasymo tipa:\n";
        cout << "1 - Ivesti duomenis\n";
        cout << "2 - Generuoti duomenis atsitiktinai\n";
        cout << "3 - Nuskaityti duomenis is failo\n";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == '1' || choice == '2' || choice == '3') {
            return choice;
        }
        else {
            cout << "Klaida! Prasome pasirinkti 1, 2 arba 3." << endl;
        }
    }
}
