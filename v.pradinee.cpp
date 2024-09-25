#include <iostream>
#include <vector>
#include <stdexcept>
#include <limits>
#include <string>
#include <iomanip> 


using namespace std;

// Funkcija ivesti ir tikrinti balo korektiskuma
double ivestiBala(const string& prompt) {
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

// Funkcija ivesti namu darbu rezultatus
vector<double> ivestiND() {
    vector<double> nd_rezultatai;
    int nd_sk;

    while (true) {
        cout << "Kiek namu darbu atlikta? ";
        cin >> nd_sk;

        if (cin.fail() || nd_sk <= 0) {
            cin.clear(); // atstatyti cin busena
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // praleisti netinkama ivesti
            cout << "Klaida: Iveskite teigiama namu darbu skaiciu." << endl;
        }
        else {
            break;
        }
    }

    for (int i = 0; i < nd_sk; ++i) {
        double balas = ivestiBala("Iveskite " + to_string(i + 1) + "-ojo namu darbo rezultata: ");
        nd_rezultatai.push_back(balas);
    }
    return nd_rezultatai;
}

// Funkcija apskaiciuoti galutini bala
double skaiciuotiGalutiniBala(const vector<double>& nd_rezultatai, double egz_bal) {
    double nd_vidurkis = 0.0;
    for (double balas : nd_rezultatai) {
        nd_vidurkis += balas;
    }
    nd_vidurkis /= nd_rezultatai.size();
    return 0.4 * nd_vidurkis + 0.6 * egz_bal;
}

// Function to display the results in a table format
void displayResults(const vector<string>& vardai, const vector<string>& pavardes, const vector<double>& galutiniaiBalai) {
    cout << left << setw(20) << "Vardas" << setw(20) << "Pavarde" << setw(20) << "Galutinis (Vid.)" << endl;
    cout << string(60, '-') << endl;

    for (size_t i = 0; i < vardai.size(); ++i) {
        cout << setw(20) << vardai[i] << setw(20) << pavardes[i] << setw(20) << fixed << setprecision(2) << galutiniaiBalai[i] << endl;
    }
}

int main() {
    int studentCount;

    cout << "Kiek studentu norite ivesti? ";
    cin >> studentCount;

    vector<string> vardai(studentCount);
    vector<string> pavardes(studentCount);
    vector<double> galutiniaiBalai(studentCount);

    for (int i = 0; i < studentCount; ++i) {
        cout << "Iveskite " << i + 1 << "-ojo studento varda: ";
        cin >> vardai[i];
        cout << "Iveskite " << i + 1 << "-ojo studento pavarde: ";
        cin >> pavardes[i];

        vector<double> nd_rezultatai = ivestiND();
        double egz_bal = ivestiBala("Iveskite egzamino rezultata: ");
        galutiniaiBalai[i] = skaiciuotiGalutiniBala(nd_rezultatai, egz_bal);
    }

    // Display results
    displayResults(vardai, pavardes, galutiniaiBalai);

    return 0;
}
