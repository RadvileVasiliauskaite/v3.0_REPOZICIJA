#include <iostream>
#include <vector>
#include <stdexcept>
#include <limits>
#include <string>
#include <iomanip> 
#include <algorithm>


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
    string input;

    while (true) {
        cout << "Iveskite namu darbo rezultata(paspauskite ENTER norint baigti): ";
        getline(cin, input); // Use getline to capture user input including spaces

        // Check for empty input, but ensure at least one result is entered
        if (input.empty() && nd_rezultatai.size() > 0) {
            break; // Exit loop if there's at least one result
        }
        else if (input.empty()) {
            cout << "Klaida: Turite ivesti bent viena namu darbo rezultata!" << endl;
            continue;
        }

        // Convert the string input to a double
        try {
            double balas = stod(input); // Convert string to double
            // Validate the score range
            if (balas < 0 || balas > 10) {
                cout << "Klaida: Iveskite skaiciu tarp 0 ir 10." << endl;
            }
            else {
                nd_rezultatai.push_back(balas); // Add the valid score to the results
            }
        }
        catch (const invalid_argument&) {
            cout << "Klaida: Iveskite tinkama skaiciu!" << endl; // Handle non-numeric input
        }
        catch (const out_of_range&) {
            cout << "Klaida: Iveskite tinkama skaiciu!" << endl; // Handle out of range input
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

// Function to display the results in a table format
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
    bool naudotiMediana;

    cout << "Kiek studentu norite ivesti? ";
    cin >> studentCount;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<string> vardai(studentCount);
    vector<string> pavardes(studentCount);
    vector<double> galutiniaiBalai(studentCount);

    char pasirinkimas;
    cout << "Ar norite skaiciuoti galutini bala naudodami medianos skaiciavima? (y/n): ";
    cin >> pasirinkimas;
    naudotiMediana = (pasirinkimas == 'y' || pasirinkimas == 'Y');
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int i = 0; i < studentCount; ++i) {
        cout << "Iveskite " << i + 1 << "-ojo studento varda: ";
        getline(cin, vardai[i]);
        cout << "Iveskite " << i + 1 << "-ojo studento pavarde: ";
        getline(cin, pavardes[i]);

        vector<double> nd_rezultatai = ivestiND();
        double egz_bal = ivestiBala("Iveskite egzamino rezultata: ");
        galutiniaiBalai[i] = skaiciuotiGalutiniBala(nd_rezultatai, egz_bal, naudotiMediana);
    }

    // Display results
    displayResults(vardai, pavardes, galutiniaiBalai, naudotiMediana);

    return 0;
}