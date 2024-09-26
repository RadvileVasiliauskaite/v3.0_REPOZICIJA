#include <iostream>
#include <vector>
#include <stdexcept>
#include <limits>
#include <string>
#include <iomanip> 
#include <algorithm>
#include <random> 


using namespace std;

double generuotiAtsitiktiniBala() {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dist(0.0, 10.0); // Balai tarp 0 ir 10
    return dist(gen);
}


// Funkcija ivesti ir tikrinti balo korektiskuma
double ivestiBala(const string& prompt, bool naudotiAtsitiktini) {
    if (naudotiAtsitiktini) {
        double balas = generuotiAtsitiktiniBala();
        cout << prompt << balas << endl;
        return balas;
    }

    double balas;
    while (true) {
        cout << prompt;
        cin >> balas;

        if (cin.fail()) {
            cin.clear(); // atstatyti cin busena
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // praleisti netinkama ivesti
            cout << "Klaida: Iveskite tinkama skaiciu!" << endl;
        }
        else if (balas < 0 || balas > 10) {
            cout << "Klaida: Iveskite skaiciu tarp 0 ir 10." << endl;
        }
        else {
            return balas;
        }
    }
}

vector<double> ivestiND(bool naudotiAtsitiktini) {
    vector<double> nd_rezultatai;

    if (naudotiAtsitiktini) {
        int nd_sk = rand() % 10 + 1; // Generuoja atsitiktini namu darbu skaiciu (nuo 1 iki 10)
        for (int i = 0; i < nd_sk; ++i) {
            double balas = generuotiAtsitiktiniBala();
            nd_rezultatai.push_back(balas);
            cout << "Generuojamas " << i + 1 << "-ojo namu darbo rezultatas: " << balas << endl;
        }
    }
    else {
        string input;
        while (true) {
            cout << "Iveskite namu darbo rezultata(paspauskite ENTER norint baigti): ";
            getline(cin, input); 

         
            if (input.empty() && nd_rezultatai.size() > 0) {
                break; // Baigti jei yra ivestas bent vienas rezultatas
            }
            else if (input.empty()) {
                cout << "Klaida: Turite ivesti bent viena namu darbo rezultata!" << endl;
                continue;
            }


            try {
                double balas = stod(input); 
               
                if (balas < 0 || balas > 10) {
                    cout << "Klaida: Iveskite skaiciu tarp 0 ir 10." << endl;
                }
                else {
                    nd_rezultatai.push_back(balas);
                }
            }
            catch (const invalid_argument&) {
                cout << "Klaida: Iveskite tinkama skaiciu!" << endl; 
            }
            catch (const out_of_range&) {
                cout << "Klaida: Iveskite tinkama skaiciu!" << endl; 
            }
        }
    }

    return nd_rezultatai;
}

double skaiciuotiVidurki(const vector<double>& nd_rezultatai) {
    if (nd_rezultatai.empty()) return 0.0;

    double nd_vidurkis = 0.0;
    for (double balas : nd_rezultatai) {
        nd_vidurkis += balas;
    }
    return nd_vidurkis / nd_rezultatai.size();
}

double skaiciuotiMediana(vector<double> nd_rezultatai) {
    if (nd_rezultatai.empty()) return 0.0;

    sort(nd_rezultatai.begin(), nd_rezultatai.end());
    size_t size = nd_rezultatai.size();
    if (size % 2 == 0) {
        return (nd_rezultatai[size / 2 - 1] + nd_rezultatai[size / 2]) / 2.0;
    }
    else {
        return nd_rezultatai[size / 2];
    }
}
// Funkcija apskaiciuoti galutini bala
double skaiciuotiGalutiniBala(const vector<double>& nd_rezultatai, double egz_bal, bool naudotiMediana) {
    double galutinis_nd = naudotiMediana ? skaiciuotiMediana(nd_rezultatai) : skaiciuotiVidurki(nd_rezultatai);
    return 0.4 * galutinis_nd + 0.6 * egz_bal;
}

// Funkcija pavaizduoti galutini rezultata
void displayResults(const vector<string>& vardai, const vector<string>& pavardes, const vector<double>& galutiniaiBalai, bool naudotiMediana) {
    cout << left << std::setw(20) << "Vardas" << std::setw(20) << "Pavarde" << std::setw(25)
        << (naudotiMediana ? "Galutinis (Med.)" : "Galutinis (Vid.)") << endl;
    cout << string(65, '-') << endl;

    for (size_t i = 0; i < vardai.size(); ++i) {
        cout << std::setw(20) << vardai[i] << std::setw(20) << pavardes[i] << std::setw(25) << fixed << setprecision(2) << galutiniaiBalai[i] << endl;
    }
}

int main() {
    int studentCount;
    bool naudotiMediana, naudotiAtsitiktini;

    while (true) {
        cout << "Kiek studentu norite ivesti? ";
        cin >> studentCount;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Klaida: Iveskite skaiciu!" << endl;
        }
        else if (studentCount <= 0) {
            cout << "Klaida: Iveskite teigiama skaiciu!" << endl;
        }
        else {
            break;
        }
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<string> vardai(studentCount);
    vector<string> pavardes(studentCount);
    vector<double> galutiniaiBalai(studentCount);

    char pasirinkimas;

    while (true) {
        cout << "Ar norite skaiciuoti galutini bala naudodami medianos skaiciavima? (y/n): ";
        cin >> pasirinkimas;
        if (pasirinkimas == 'y' || pasirinkimas == 'Y') {
            naudotiMediana = true;
            break;
        }else if (pasirinkimas == 'n' || pasirinkimas == 'N') {
            naudotiMediana = false;
            break;
        }else {
            cout << "Klaida: Iveskite 'y' arba 'n'!" << endl;
        }
    }
    while (true) {
        cout << "Ar norite naudoti atsitiktinius balus? (y/n): ";
        cin >> pasirinkimas;
        if (pasirinkimas == 'y' || pasirinkimas == 'Y') {
            naudotiAtsitiktini = true;
            break;
        } else if (pasirinkimas == 'n' || pasirinkimas == 'N') {
            naudotiAtsitiktini = false;
            break;
        } else {
            cout << "Klaida: Iveskite 'y' arba 'n'!" << endl;
        }
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int i = 0; i < studentCount; ++i) {
        cout << "Iveskite " << i + 1 << "-ojo studento varda: ";
        getline(cin, vardai[i]);
        cout << "Iveskite " << i + 1 << "-ojo studento pavarde: ";
        getline(cin, pavardes[i]);

        vector<double> nd_rezultatai = ivestiND(naudotiAtsitiktini);
        double egz_bal = ivestiBala("Iveskite egzamino rezultata: ", naudotiAtsitiktini);
        galutiniaiBalai[i] = skaiciuotiGalutiniBala(nd_rezultatai, egz_bal, naudotiMediana);
    }

    
    displayResults(vardai, pavardes, galutiniaiBalai, naudotiMediana);

    return 0;
}