#include <iostream>
#include <cmath>
#include <vector>
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

// Fonction pour afficher une ligne de séparateurs
void printSeparateur(size_t nbColonnes, int largeur) {
    for(size_t i=0;i<nbColonnes;i++){
        cout << "+";
        for(int j=0;j<largeur;j++) cout << "-";
    }
    cout << "+\n";
}

int main() {
    double capital;
    cout << "Montant du capital : ";
    cin >> capital;

    // Noms des banques
    vector<string> banques = {"Credit Agricole", "BNP Paribas", "LCL", "Credit Mutuel"};
    vector<vector<double>> taux = {{3,4},{3,4},{3,4},{3,4}};
    vector<int> durees = {10, 15, 20};
    int taux1[] = {3,4};
    // Durées
    // Ajouter des banques dynamiquement
    char ajouter_banque ;
    cout << "Ajouter une banque ? (o/n) : ";
    cin >> ajouter_banque;
    while(ajouter_banque=='o'||ajouter_banque=='O') {
      
        string nom;
        int nbTaux;
        cout << "Nom de la banque : ";
        cin >> nom;
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
   

    int largeur = 18;

    printSeparateur(banques.size()+1, largeur);

    cout << left << setw(largeur-1) << "Taux/Duree";

    for(auto &b: banques)

        cout << left << setw(largeur-1) << b;

    cout << "|\n";

    printSeparateur(banques.size()+1, largeur);
 
    // En-tête
   
        // En-tête
    cout << left << setw(20) << "Taux/Duree";
    for(int i = 0; i < banques.size(); i++){
        cout << left << setw(20) <<banques[i];
    }
    cout << endl;
    
   
    // Boucles correctes
    for(int j = 0; j < 2; j++){          // taux
        for(int k = 0; k < 3; k++){      // durée
    
            // Affiche taux + durée (ligne)
            cout << left << setw(10) << (to_string(taux1[j]) + "%")<< setw(10) << (to_string(durees[k]) + " ans");
    
            // Colonnes = banques
            for(int i = 0; i < banques.size(); i++){
    
                Emprunt e(capital, taux[i][j], durees[k]);
    
                cout << left << setw(20)<< fixed << setprecision(2)<< e.calculerMensualite();
            }
    
            cout << endl;
        }
    }
    
    return 0;
}
