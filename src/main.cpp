#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip> // pour setprecision
#include <string>
using namespace std;

class Emprunt {
public:
    double capital;
    double tauxAnnuel;
    int nbAnnees;

    Emprunt(double c, double t, int n) : capital(c), tauxAnnuel(t), nbAnnees(n) {}

    double calculerMensualite() {
        int nbMois = nbAnnees * 12;
        double tauxMensuel = (tauxAnnuel / 100) / 12;
        return (capital * tauxMensuel * pow(1 + tauxMensuel, nbMois)) / (pow(1 + tauxMensuel, nbMois) - 1);
    }
};

int main() {
    double capital;
    cout << "Montant du capital : ";
    cin >> capital;
    // declaration des tableaux
    vector<string> banques = {"Credit Agricole", "BNP Paribas", "LCL", "Credit Mutuel"};
    vector<vector<double>> taux = {{3,4},{3,4},{3,4},{3,4}};
    vector<int> durees = {10, 15, 20};

    // Ajouter des banques dynamiquement
    char ajouter_banque ;
    cout << "Ajouter une banque ? (o/n) : ";
    cin >> ajouter_banque;
    while(ajouter_banque=='o'||ajouter_banque=='O') {
      
        string nom;
        int nbTaux;
        cout << "Nom de la banque : ";
        getline(cin, nom);
        cout << "Nombre de taux : ";
        cin >> nbTaux;
        vector<double> nouveauxTaux(nbTaux);
        for(int i=0;i<nbTaux;i++){
            cout << "Taux " << i+1 << " : ";
            cin >> nouveauxTaux[i];
        }
        banques.push_back(nom);
        taux.push_back(nouveauxTaux);
        cout << "Ajouter une autre banque ? (o/n) : ";
        cin >> ajouter_banque;
    }

    //affichage tableau 

}
