#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

class Emprunt {
public:
    double capital;
    double tauxAnnuel;
    int nbAnnees;

    Emprunt(double c, double t, int n) {
        capital = c;
        tauxAnnuel = t;
        nbAnnees = n;
    }

    double calculerMensualite() {
        int nbMois = nbAnnees * 12;
        double tauxMensuel = (tauxAnnuel / 100) / 12;

        double calcul1 = capital * tauxMensuel;
        double calcul2 = pow(1 + tauxMensuel, nbMois);
        double calcul3 = calcul2 - 1;

        return calcul1 * (calcul2 / calcul3);
    }
};

int main() {
    double capital;
    cout << "Montant du capital : ";
    cin >> capital;

    // Noms des banques
    string nomsBanques[4] = {
        "Credit Agricole",
        "BNP Paribas",
        "LCL",
        "Credit Mutuel"
    };

    // Taux
    double taux[4][2] = {
        {3, 4},
        {3, 4},
        {3, 4},
        {3, 4}
    };

    // Durées
    int durees[3] = {10, 15, 20};

    cout << "\n================ TABLEAU DES MENSUALITES ================\n";



    // En-tête
    cout << left << setw(20) << "Banque"
         << setw(10) << "Taux"
         << setw(10) << "Duree"
         << setw(15) << "Mensualite"
         << endl;

    cout << "--------------------------------------------------------\n";

    // Boucles
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 3; k++) {

                Emprunt e(capital, taux[i][j], durees[k]);

                cout << left << setw(20) << nomsBanques[i]
                     << setw(10) << taux[i][j]
                     << setw(10) << durees[k]
                     << setw(15) << fixed << setprecision(2)
                     << e.calculerMensualite()
                     << endl;
            }
        }
    }

    return 0;
}
