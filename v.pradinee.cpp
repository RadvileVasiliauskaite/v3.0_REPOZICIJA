#include <iostream>
#include <vector>
#include <stdexcept>
#include <limits>
#include <string>


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

int main() {
    string vardas, pavarde;

    cout << "Iveskite studento varda: ";
    cin >> vardas;
    cout << "Iveskite studento pavarde: ";
    cin >> pavarde;

    vector<double> nd_rezultatai = ivestiND();
    double egz_bal = ivestiBala("Iveskite egzamino rezultata: ");

    double galutinis_bal = skaiciuotiGalutiniBala(nd_rezultatai, egz_bal);

    cout << "Studentas: " << vardas << " " << pavarde << endl;
    cout << "Galutinis balas: " << galutinis_bal << endl;

    return 0;
}
