#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
using namespace std;

// créer la class Emprunt
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

    // méthode de calculs

    double calculerMensualite() {
        int nbMois = nbAnnees * 12;
        double tauxMensuel = (tauxAnnuel / 100) / 12;

        double calcul1 = capital * tauxMensuel;
        double calcul2 = pow(1 + tauxMensuel, nbMois);
        double calcul3 = calcul2 - 1;

        return calcul1 * (calcul2 / calcul3);
        
    }
    
    
};


void printCell(string contenu, int largeur) {
    cout << "| " << left << setw(largeur-2) << contenu;
}

void printHeader(vector<string>& banques, int largeur) {
    printCell("Taux/Duree", largeur);

    for(auto &b : banques) {
        printCell(b, largeur);
    }

    cout << "|\n";
}


// Fonction pour afficher une ligne de séparateurs
void printSeparateur(size_t nbColonnes, int largeur) {
    for(size_t i=0;i<nbColonnes;i++){
        
        for(int j=0;j<largeur;j++) cout << "-";
    }
    cout << "+\n";
}

// affichage des séparateurs de lignes 

void printLigne(double capital, vector<string>& banques,
                vector<vector<double>>& taux, vector<int>& durees,
                int j, int k, int largeur) {

    string td = to_string((int)taux[0][j]) + "% " + to_string(durees[k]) + " ans";
    printCell(td, largeur);

    for(int i = 0; i < banques.size(); i++) {

        if(j < taux[i].size()) {
            Emprunt e(capital, taux[i][j], durees[k]);

            string val = to_string((int)e.calculerMensualite());
            printCell(val, largeur);
        } else {
            printCell("-", largeur);
        }
    }

    cout << "|\n";
}

int main() {
    // declaration des attributs
    double capital;
    cout << "Montant du capital : ";
    cin >> capital;

    // Noms des banques
    vector<string> banques = {"Credit Agricole", "BNP Paribas", "LCL", "Credit Mutuel"};
    // 2 taux pour chaque banque 
    vector<vector<double>> taux = {{3,4},{3,4},{3,4},{3,4}};
    // 3 durées pour chaque banque 
    vector<int> durees = {10, 15, 20};
    int taux1[] = {3,4};
  
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
   
    // initialisation d'un max de colonnes 
    int largeur = 18;
    // appel des fonctions 
    printSeparateur(banques.size()+1, largeur);
    printHeader(banques, largeur);
    printSeparateur(banques.size()+1, largeur);
    
    // parcours du tableau avec les separateurs de l'entete et de lignes
    for(int j = 0; j < taux[0].size(); j++){
        for(int k = 0; k < durees.size(); k++){
    
            printLigne(capital, banques, taux, durees, j, k, largeur);
    
            printSeparateur(banques.size()+1, largeur);
        }
    }
    
    return 0;
}
