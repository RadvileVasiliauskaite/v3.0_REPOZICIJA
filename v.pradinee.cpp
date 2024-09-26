#include <iostream> 
#include <vector>
#include <stdexcept>
#include <limits>
#include <string>
#include <iomanip>
#include <algorithm>
#include <random>
#include <fstream>

using namespace std;

struct Rezultatai {
    vector<double> nd_rezultatai;  
    double egzaminoBalas;          
};

struct Studentas {
    string vardas;
    string pavarde;
    double galutinisBalas;
    double galutinisMediana;
};

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

double skaiciuotiVidurki(const vector<double>& nd_rezultatai) {
    double total = 0.0;
    for (double score : nd_rezultatai) {
        total += score;
    }
    return total / nd_rezultatai.size();
}

double skaiciuotiMediana(vector<double> nd_rezultatai) {
    sort(nd_rezultatai.begin(), nd_rezultatai.end());
    size_t size = nd_rezultatai.size();
    if (size % 2 == 0) {
        return (nd_rezultatai[size / 2 - 1] + nd_rezultatai[size / 2]) / 2.0;
    }
    else {
        return nd_rezultatai[size / 2];
    }
}

void displayResults(const vector<Studentas>& studentai) {
    cout << left << setw(20) << "Vardas" << setw(20) << "Pavarde" << setw(25) << "Galutinis (Vidurkis)" << setw(25) << "Galutinis (Mediana)" << endl;
    cout << string(90, '-') << endl;

    for (const auto& studentas : studentai) {
        cout << setw(20) << studentas.vardas << setw(20) << studentas.pavarde << setw(25) << fixed << setprecision(2) << studentas.galutinisBalas << setw(25) << fixed << setprecision(2) << studentas.galutinisMediana << endl;
    }
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

int main() {
    int studentCount = 0;

    char choice = getInputChoice(); 

    vector<Studentas> studentai;
    vector<vector<double>> nd_rezultatai;
    vector<double> egzaminoBalai;

    if (choice == '1') {
        cout << "Kiek studentu norite ivesti? ";
        cin >> studentCount;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        studentai.resize(studentCount);
        nd_rezultatai.resize(studentCount);
        egzaminoBalai.resize(studentCount);

        for (int i = 0; i < studentCount; ++i) {
            cout << "Iveskite " << i + 1 << "-ojo studento varda: ";
            getline(cin, studentai[i].vardas);
            cout << "Iveskite " << i + 1 << "-ojo studento pavarde: ";
            getline(cin, studentai[i].pavarde);

            vector<double> uzduotys;
            cout << "Iveskite uzduociu balus (spauskite ENTER du kartus, kad baigti):" << endl;

            string input;
            while (true) {
                getline(cin, input);
                if (input.empty()) {
                    break;
                }

                try {
                    double uzduotis = stod(input);
                    if (uzduotis < 0) { 
                        cout << "Neteisingas balas! Prasome ivesti teigiama skaiciu." << endl;
                    }
                    else {
                        uzduotys.push_back(uzduotis);
                    }
                }
                catch (invalid_argument&) {
                    cout << "Neteisingas balas! Prasome ivesti skaiciu." << endl;
                }
            }
            nd_rezultatai[i] = uzduotys;

            
            double egzaminoBalas = getPositiveScore("Iveskite egzamino rezultata: ");
            egzaminoBalai[i] = egzaminoBalas;
        }
    }
    else if (choice == '2') {
        cout << "Kiek studentu norite ivesti? ";
        cin >> studentCount;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        studentai.resize(studentCount);
        nd_rezultatai.resize(studentCount);
        egzaminoBalai.resize(studentCount);

        for (int i = 0; i < studentCount; ++i) {
            studentai[i].vardas = "Vardas" + to_string(i + 1);
            studentai[i].pavarde = "Pavarde" + to_string(i + 1);

            vector<double> uzduotys(5);
            for (int j = 0; j < 5; ++j) {
                uzduotys[j] = generuotiAtsitiktiniBala();
            }
            nd_rezultatai[i] = uzduotys;

            egzaminoBalai[i] = generuotiAtsitiktiniBala();
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

    sort(studentai.begin(), studentai.end(), [](const Studentas& a, const Studentas& b) {
        return a.vardas < b.vardas;
        });

    displayResults(studentai);

    return 0;
}
