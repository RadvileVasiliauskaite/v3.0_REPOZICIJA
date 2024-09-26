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

double generuotiAtsitiktiniBala() {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dist(0.0, 10.0);
    return dist(gen);
}

void readFromFile(vector<string>& vardai, vector<string>& pavardes, vector<vector<double>>& nd_rezultatai, vector<double>& egzaminoBalai) {
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
        vardai.push_back(vardas);
        pavardes.push_back(pavarde);
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

void displayResults(const vector<string>& vardai, const vector<string>& pavardes, const vector<double>& galutiniaiBalai, const vector<double>& naudotiMediana) {
    cout << left << setw(20) << "Vardas" << setw(20) << "Pavarde" << setw(25) << "Galutinis (Vidurkis)" << setw(25) << "Galutinis (Mediana)" << endl;
    cout << string(90, '-') << endl;

    for (size_t i = 0; i < vardai.size(); ++i) {
        cout << setw(20) << vardai[i] << setw(20) << pavardes[i] << setw(25) << fixed << setprecision(2) << galutiniaiBalai[i] << setw(25) << fixed << setprecision(2) << naudotiMediana[i] << endl;
    }
}

// Function to get a positive score from the user
double getPositiveScore(const string& prompt) {
    double score;
    while (true) {
        cout << prompt;
        cin >> score;
        if (cin.fail() || score < 0.0) { // Check for non-numeric or negative input
            cin.clear(); // Clear the error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Klaida! Prasome ivesti teigiama skaiciu." << endl;
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the buffer
            return score; // Valid input, return score
        }
    }
}

// Function to get a valid choice for data input type
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
            return choice; // Return valid choice
        }
        else {
            cout << "Klaida! Prasome pasirinkti 1, 2 arba 3." << endl; // Invalid choice
        }
    }
}

int main() {
    int studentCount = 0;

    char choice = getInputChoice(); // Get valid choice for data input type

    vector<string> vardai;
    vector<string> pavardes;
    vector<vector<double>> nd_rezultatai;
    vector<double> egzaminoBalai;

    if (choice == '1') {
        cout << "Kiek studentu norite ivesti? ";
        cin >> studentCount;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        vardai.resize(studentCount);
        pavardes.resize(studentCount);
        nd_rezultatai.resize(studentCount);
        egzaminoBalai.resize(studentCount);

        for (int i = 0; i < studentCount; ++i) {
            cout << "Iveskite " << i + 1 << "-ojo studento varda: ";
            getline(cin, vardai[i]);
            cout << "Iveskite " << i + 1 << "-ojo studento pavarde: ";
            getline(cin, pavardes[i]);

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
                    if (uzduotis < 0) { // Ensure the score is positive
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

            // Input exam score using the validation function
            double egzaminoBalas = getPositiveScore("Iveskite egzamino rezultata: ");
            egzaminoBalai[i] = egzaminoBalas;
        }
    }
    else if (choice == '2') {
        cout << "Kiek studentu norite ivesti? ";
        cin >> studentCount;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        vardai.resize(studentCount);
        pavardes.resize(studentCount);
        nd_rezultatai.resize(studentCount);
        egzaminoBalai.resize(studentCount);

        for (int i = 0; i < studentCount; ++i) {
            vardai[i] = "Vardas" + to_string(i + 1);
            pavardes[i] = "Pavarde" + to_string(i + 1);

            vector<double> uzduotys(5);
            for (int j = 0; j < 5; ++j) {
                uzduotys[j] = generuotiAtsitiktiniBala();
            }
            nd_rezultatai[i] = uzduotys;

            egzaminoBalai[i] = generuotiAtsitiktiniBala();
        }
    }
    else if (choice == '3') {
        readFromFile(vardai, pavardes, nd_rezultatai, egzaminoBalai);
        studentCount = vardai.size();
    }

    // Final score calculation
    vector<double> galutiniaiBalai(studentCount);
    vector<double> naudotiMediana(studentCount);
    for (int i = 0; i < studentCount; ++i) {
        double egzaminoBalas = egzaminoBalai[i];
        galutiniaiBalai[i] = 0.4 * skaiciuotiVidurki(nd_rezultatai[i]) + 0.6 * egzaminoBalas;
        naudotiMediana[i] = 0.4 * skaiciuotiMediana(nd_rezultatai[i]) + 0.6 * egzaminoBalas;
    }

    displayResults(vardai, pavardes, galutiniaiBalai, naudotiMediana);

    return 0;
}

