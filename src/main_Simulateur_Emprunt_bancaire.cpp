#include <iostream>   // Gestion des entrées/sorties
#include <fstream>    // Gestion des fichiers
#include <sstream>
#include <string>     // Utilisation des chaînes de caractères
#include <vector>     // Utilisation des tableaux dynamiques
#include <cmath>      // Fonctions mathématiques (pow)
#include <iomanip>    // Manipulation de l'affichage
#include <limits>     // Gestion des limites
using namespace std;


/* ============================================================================
 *  FONCTION D'EXPORT CSV (TEST ET INTEGRATION LE CODE DE YACINE°
 *  Ajoute les résultats dans le fichier banques.csv
 * ========================================================================== */
void ajouterResultatCSV(string groupe,
                        double capital,
                        string banque,
                        double taux,
                        int duree,
                        double resultat) {

    // Ouverture du fichier en mode ajout
    ofstream file("banques.csv", ios::app);

    // Vérification ouverture fichier
    if (!file) {
        cerr << "Erreur : impossible d'ouvrir banques.csv" << endl;
        return;
    }

    // Si le fichier est vide → écrire l'entête
    if (file.tellp() == 0) {
        file << "GROUPE;CAPITAL;BANQUE;TAUX;DUREE;RESULTAT\n";
    }

    // Écriture des données
    file << groupe << ";"
         << fixed << setprecision(2) << capital << ";"
         << banque << ";"
         << fixed << setprecision(2) << taux << ";"
         << duree << ";"
         << fixed << setprecision(2) << resultat << "\n";

    // Fermeture du fichier
    file.close();
}


/* ============================================================================
 *  CLASSE Utilisateur
 *  Stocke les informations utilisateur
 * ========================================================================== */
class Utilisateur {
private:
    string nom;
    string prenom;
    string email;
    string telephone;

public:

    // Constructeur par défaut
    Utilisateur() : nom(""), prenom(""), email(""), telephone("") {}

    // Saisie des informations utilisateur
    void saisir() {

        cout << "\n========== COORDONNEES DE L'UTILISATEUR ==========\n";

        cout << "Nom       : ";
        getline(cin, nom);

        cout << "Prenom    : ";
        getline(cin, prenom);

        cout << "Email     : ";
        getline(cin, email);

        cout << "Telephone : ";
        getline(cin, telephone);
    }

    // Getters
    string getNom()       const { return nom; }
    string getPrenom()    const { return prenom; }
    string getEmail()     const { return email; }
    string getTelephone() const { return telephone; }
};


/* ============================================================================
 *  CLASSE Compte
 *  Gère le calcul des mensualités
 * ========================================================================== */
class Compte {
private:
    double capital;
    double tauxAnnuel;
    int    nbAnnees;

public:

    // Constructeur
    Compte(double c, double t, int n)
        : capital(c), tauxAnnuel(t), nbAnnees(n) {}

    // Calcul de la mensualité
    double calculerMensualite() const {

        // Nombre total de mois
        int nbMois = nbAnnees * 12;

        // Taux mensuel
        double tauxMensuel = (tauxAnnuel / 100.0) / 12.0;

        // Calcul du facteur
        double facteur = pow(1 + tauxMensuel, nbMois);

        // Formule de mensualité
        return capital * tauxMensuel * facteur / (facteur - 1);
    }
};


/* ============================================================================
 *  CLASSE Banque
 *  Contient les informations d'une banque
 * ========================================================================== */
class Banque {
private:
    string         nom;
    vector<double> taux;

public:

    // Constructeur
    Banque(const string& n, const vector<double>& t)
        : nom(n), taux(t) {}

    // Getters
    string getNom() const { return nom; }

    vector<double> getTaux() const { return taux; }

    // Retourne le nombre de taux
    size_t nbTaux() const { return taux.size(); }

    // Retourne un taux selon son indice
    double getTauxAt(size_t i) const {

        // Vérification indice valide
        return (i < taux.size()) ? taux[i] : -1.0;
    }
};


/* ============================================================================
 *  CLASSE Affichage
 *  Gère l'affichage du tableau
 * ========================================================================== */
class Affichage {
private:
    int largeur;

    // Affichage d'une cellule
    void printCell(const string& contenu) const {

        cout << "| "
             << left
             << setw(largeur - 2)
             << contenu;
    }

    // Affichage des séparateurs
    void printSeparateur(size_t nbColonnes) const {

        for (size_t i = 0; i < nbColonnes; i++) {

            for (int j = 0; j < largeur; j++)
                cout << "-";
        }

        cout << "+\n";
    }

    // Affichage de l'entête
    void printHeader(const vector<Banque>& banques) const {

        printCell("Banque");

        for (const auto& b : banques)
            printCell(b.getNom());

        cout << "|\n";
    }

    // Recherche du nombre maximum de taux
    size_t maxNbTaux(const vector<Banque>& banques) const {

        size_t maxT = 0;

        for (const auto& b : banques)

            if (b.nbTaux() > maxT)
                maxT = b.nbTaux();

        return maxT;
    }

    // Affichage d'un bloc du tableau
    void printBloc(double capital,
                   const vector<Banque>& banques,
                   const vector<int>& durees,
                   size_t j, size_t k) const
    {
        // Ligne taux
        printCell("Taux");

        for (const auto& b : banques) {

            if (j < b.nbTaux()) {

                string t =
                    to_string((int)b.getTauxAt(j)) + "%";

                printCell(t);

            } else {

                printCell("-");
            }
        }

        cout << "|\n";

        printSeparateur(banques.size() + 1);

        // Ligne durée
        printCell("Duree");

        for (size_t i = 0; i < banques.size(); i++) {

            string d =
                to_string(durees[k]) + " ans";

            printCell(d);
        }

        cout << "|\n";

        printSeparateur(banques.size() + 1);

        // Ligne mensualité
        printCell("Mensualite");

        for (const auto& b : banques) {

            if (j < b.nbTaux()) {

                // Création du compte
                Compte c(
                    capital,
                    b.getTauxAt(j),
                    durees[k]
                );

                // Calcul mensualité
                string val =
                    to_string((int)c.calculerMensualite());

                printCell(val);

            } else {

                printCell("-");
            }
        }

        cout << "|\n";

        printSeparateur(banques.size() + 1);
    }

public:

    // Constructeur
    Affichage(int l = 18) : largeur(l) {}

    // Affichage complet du tableau
    void afficherTableau(double capital,
                         const vector<Banque>& banques,
                         const vector<int>& durees) const
    {
        // Nombre de colonnes
        size_t nbCols = banques.size() + 1;

        // Nombre max de taux
        size_t maxT = maxNbTaux(banques);

        printSeparateur(nbCols);

        printHeader(banques);

        printSeparateur(nbCols);

        // Parcours des taux
        for (size_t j = 0; j < maxT; j++) {

            // Parcours des durées
            for (size_t k = 0; k < durees.size(); k++) {

                printBloc(
                    capital,
                    banques,
                    durees,
                    j,
                    k
                );
            }
        }
    }
};


/* ============================================================================
 *  AJOUT DYNAMIQUE DE BANQUES
 * ========================================================================== */
void ajouterBanquesDynamiquement(vector<Banque>& banques) {

    char choix;

    cout << "\nAjouter une banque ? (o/n) : ";
    cin >> choix;

    while (choix == 'o' || choix == 'O') {

        string nom;
        int    nbTaux;

        // Nettoyage du buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // Nom banque
        cout << "Nom de la banque : ";
        getline(cin, nom);

        // Nombre de taux
        cout << "Nombre de taux   : ";
        cin >> nbTaux;

        // Création tableau des taux
        vector<double> nouveauxTaux(nbTaux);

        // Saisie des taux
        for (int i = 0; i < nbTaux; i++) {

            cout << "  Taux "
                 << (i + 1)
                 << " (en %) : ";

            cin >> nouveauxTaux[i];
        }

        // Ajout banque dans le vector
        banques.push_back(Banque(nom, nouveauxTaux));

        cout << "\nAjouter une autre banque ? (o/n) : ";
        cin >> choix;
    }
}


/* ============================================================================
 *  PROGRAMME PRINCIPAL
 * ========================================================================== */
int main() {

    cout << "*****************************************************\n";
    cout << "*       SIMULATEUR D'EMPRUNT BANCAIRE - v1.0        *\n";
    cout << "*****************************************************\n";

    // Création utilisateur
    Utilisateur user;

    // Saisie utilisateur
    user.saisir();

    // Capital à emprunter
    double capital;

    cout << "\nMontant du capital a emprunter (EUR) : ";

    cin >> capital;

    // Liste des banques
    vector<Banque> banques = {

        Banque("CA",  {3.0, 4.0}),
        Banque("BNP", {3.0, 4.0}),
        Banque("LCL", {3.0, 4.0}),
        Banque("CM",  {3.0, 4.0})
    };

    // Liste des durées
    vector<int> durees = {10, 15, 20};

    // Ajout de banques
    ajouterBanquesDynamiquement(banques);

    // Création objet affichage
    Affichage aff(18);

    // Affichage tableau
    aff.afficherTableau(capital, banques, durees);

    /* ==========================================================
     * EXPORT CSV
     * ======================================================== */

    // Création du groupe utilisateur
    string groupe =
        user.getNom() + "_" + user.getPrenom();

    // Parcours des banques
    for (const auto& b : banques) {

        // Parcours des taux
        for (size_t j = 0; j < b.nbTaux(); j++) {

            // Parcours des durées
            for (size_t k = 0; k < durees.size(); k++) {

                // Création du compte
                Compte c(
                    capital,
                    b.getTauxAt(j),
                    durees[k]
                );

                // Calcul mensualité
                double mensualite =
                    c.calculerMensualite();

                // Export CSV
                ajouterResultatCSV(
                    groupe,
                    capital,
                    b.getNom(),
                    b.getTauxAt(j),
                    durees[k],
                    mensualite
                );
            }
        }
    }

    cout << "\n[OK] Donnees exportees dans banques.csv\n";

    cout << "\nMerci "
         << user.getPrenom()
         << " ! Simulation terminee.\n";

    return 0;
}
