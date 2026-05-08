

#include <iostream>
#include <fstream>      // pour l'export CSV
#include <sstream>      // pour la mise en forme
#include <string>
#include <vector>
#include <cmath>        // pour pow()
#include <iomanip>      // pour setw, setprecision
#include <limits>       // pour numeric_limits (vidage du buffer)
using namespace std;


/* ============================================================================
 *  CLASSE 1 : Utilisateur
 *  ----------------------------------------------------------------------------
 *  Représente le client qui souhaite simuler un emprunt.
 *  Stocke ses coordonnées (nom, prénom, email, téléphone).
 * ========================================================================== */
class Utilisateur {
private:
    string nom;
    string prenom;
    string email;
    string telephone;

public:
    Utilisateur() : nom(""), prenom(""), email(""), telephone("") {}

    // Saisie interactive (1ère lecture du programme : buffer propre)
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

    // Accesseurs
    string getNom()       const { return nom; }
    string getPrenom()    const { return prenom; }
    string getEmail()     const { return email; }
    string getTelephone() const { return telephone; }
};


/* ============================================================================
 *  CLASSE 2 : Compte
 *  ----------------------------------------------------------------------------
 *  Représente un emprunt (un "compte" de prêt).
 *  Calcule la mensualité à partir du capital, du taux et de la durée.
 *  Formule : M = C * t * (1+t)^n / ((1+t)^n - 1)
 *      C = capital, t = taux mensuel, n = nombre de mois
 * ========================================================================== */
class Compte {
private:
    double capital;
    double tauxAnnuel;
    int    nbAnnees;

public:
    Compte(double c, double t, int n)
        : capital(c), tauxAnnuel(t), nbAnnees(n) {}

    double calculerMensualite() const {
        int    nbMois      = nbAnnees * 12;
        double tauxMensuel = (tauxAnnuel / 100.0) / 12.0;
        double facteur     = pow(1 + tauxMensuel, nbMois);
        return capital * tauxMensuel * facteur / (facteur - 1);
    }
};


/* ============================================================================
 *  CLASSE 3 : Banque
 *  ----------------------------------------------------------------------------
 *  Représente une banque : son nom + sa liste de taux proposés.
 * ========================================================================== */
class Banque {
private:
    string         nom;
    vector<double> taux;

public:
    Banque(const string& n, const vector<double>& t) : nom(n), taux(t) {}

    string         getNom()  const { return nom; }
    vector<double> getTaux() const { return taux; }
    size_t         nbTaux()  const { return taux.size(); }

    // Renvoie le taux à l'index donné, ou -1 si hors limite
    double getTauxAt(size_t i) const {
        return (i < taux.size()) ? taux[i] : -1.0;
    }
};


/* ============================================================================
 *  CLASSE 4 : Affichage
 *  ----------------------------------------------------------------------------
 *  Gère la présentation des résultats :
 *      - Affichage console formaté (style identique au code original)
 *      - Export CSV
 * ========================================================================== */
class Affichage {
private:
    int largeur;   // largeur d'une colonne du tableau (= 18 comme l'original)

    // ---------- Helpers privés ----------

    // Affiche une cellule avec alignement à gauche (style original)
    void printCell(const string& contenu) const {
        cout << "| " << left << setw(largeur - 2) << contenu;
    }

    // Affiche une ligne de séparation horizontale (style original)
    // Reproduit exactement la fonction printSeparateur() du code original
    void printSeparateur(size_t nbColonnes) const {
        for (size_t i = 0; i < nbColonnes; i++) {
            for (int j = 0; j < largeur; j++) cout << "-";
        }
        cout << "+\n";
    }

    // En-tête du tableau (libellé + noms des banques)
    void printHeader(const vector<Banque>& banques) const {
        printCell("Banque");
        for (const auto& b : banques) printCell(b.getNom());
        cout << "|\n";
    }

    // Trouve le nombre maximum de taux parmi toutes les banques
    size_t maxNbTaux(const vector<Banque>& banques) const {
        size_t maxT = 0;
        for (const auto& b : banques)
            if (b.nbTaux() > maxT) maxT = b.nbTaux();
        return maxT;
    }

    // ---------- Affichage des 3 lignes (Taux / Durée / Mensualité) ----------
    // Reproduit fidèlement la structure originale de printLigne()
    void printBloc(double capital,
                   const vector<Banque>& banques,
                   const vector<int>& durees,
                   size_t j, size_t k) const
    {
        // --- Ligne 1 : Taux ---
        printCell("Taux");
        for (const auto& b : banques) {
            if (j < b.nbTaux()) {
                string t = to_string((int)b.getTauxAt(j)) + "%";
                printCell(t);
            } else {
                printCell("-");
            }
        }
        cout << "|\n";
        printSeparateur(banques.size() + 1);

        // --- Ligne 2 : Duree ---
        printCell("Duree");
        for (size_t i = 0; i < banques.size(); i++) {
            string d = to_string(durees[k]) + " ans";
            printCell(d);
        }
        cout << "|\n";
        printSeparateur(banques.size() + 1);

        // --- Ligne 3 : Mensualite ---
        printCell("Mensualite");
        for (const auto& b : banques) {
            if (j < b.nbTaux()) {
                Compte c(capital, b.getTauxAt(j), durees[k]);
                string val = to_string((int)c.calculerMensualite());
                printCell(val);
            } else {
                printCell("-");
            }
        }
        cout << "|\n";
        printSeparateur(banques.size() + 1);
    }

public:
    Affichage(int l = 18) : largeur(l) {}   // largeur 18 comme l'original

    // ---------- Affichage console (style original) ----------
    void afficherTableau(double capital,
                         const vector<Banque>& banques,
                         const vector<int>& durees) const
    {
        size_t nbCols = banques.size() + 1;
        size_t maxT   = maxNbTaux(banques);

        printSeparateur(nbCols);
        printHeader(banques);
        printSeparateur(nbCols);

        // Pour chaque taux (j) et chaque durée (k) : afficher un bloc 3 lignes
        for (size_t j = 0; j < maxT; j++) {
            for (size_t k = 0; k < durees.size(); k++) {
                printBloc(capital, banques, durees, j, k);
            }
        }
    }

    // ---------- Export CSV ----------
    // Génère un fichier .csv contenant :
    //   - les coordonnées de l'utilisateur
    //   - le tableau des mensualités sous forme tabulaire
    void exporterCSV(const string& nomFichier,
                     const Utilisateur& user,
                     double capital,
                     const vector<Banque>& banques,
                     const vector<int>& durees) const
    {
        ofstream fichier(nomFichier);
        if (!fichier.is_open()) {
            cout << "\n[ERREUR] Impossible de creer le fichier "
                 << nomFichier << "\n";
            return;
        }

        // --- Section 1 : informations utilisateur ---
        fichier << "INFORMATIONS UTILISATEUR\n";
        fichier << "Nom;"       << user.getNom()       << "\n";
        fichier << "Prenom;"    << user.getPrenom()    << "\n";
        fichier << "Email;"     << user.getEmail()     << "\n";
        fichier << "Telephone;" << user.getTelephone() << "\n";
        fichier << "Capital emprunte (EUR);" << capital << "\n\n";

        // --- Section 2 : tableau des mensualités ---
        fichier << "TABLEAU DES MENSUALITES (EUR)\n";
        fichier << "Taux;Duree (ans)";
        for (const auto& b : banques) fichier << ";" << b.getNom();
        fichier << "\n";

        size_t maxT = maxNbTaux(banques);
        for (size_t j = 0; j < maxT; j++) {
            for (size_t k = 0; k < durees.size(); k++) {

                // Taux de référence pour la ligne (1ère banque ayant ce taux)
                double tauxRef = -1;
                for (const auto& b : banques)
                    if (j < b.nbTaux()) { tauxRef = b.getTauxAt(j); break; }

                if (tauxRef >= 0)
                    fichier << fixed << setprecision(2) << tauxRef << "%";
                else
                    fichier << "Taux " << (j + 1);

                fichier << ";" << durees[k];

                for (const auto& b : banques) {
                    if (j < b.nbTaux()) {
                        Compte c(capital, b.getTauxAt(j), durees[k]);
                        fichier << ";" << fixed << setprecision(2)
                                << c.calculerMensualite();
                    } else {
                        fichier << ";-";
                    }
                }
                fichier << "\n";
            }
        }

        fichier.close();
        cout << "\n[OK] Fichier exporte : " << nomFichier << "\n";
    }
};


/* ============================================================================
 *  FONCTION : ajouterBanquesDynamiquement
 *  ----------------------------------------------------------------------------
 *  Permet à l'utilisateur d'ajouter autant de banques qu'il le souhaite.
 *  getline() est utilisé pour gérer les noms contenant des espaces
 *  (ex: "Credit Agricole", "Societe Generale").
 * ========================================================================== */
void ajouterBanquesDynamiquement(vector<Banque>& banques) {
    char choix;
    cout << "\nAjouter une banque ? (o/n) : ";
    cin >> choix;

    while (choix == 'o' || choix == 'O') {
        string nom;
        int    nbTaux;

        // Vide le \n laissé par cin >> avant getline
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Nom de la banque : ";
        getline(cin, nom);          // <-- gère les espaces

        cout << "Nombre de taux   : ";
        cin >> nbTaux;

        vector<double> nouveauxTaux(nbTaux);
        for (int i = 0; i < nbTaux; i++) {
            cout << "  Taux " << (i + 1) << " (en %) : ";
            cin >> nouveauxTaux[i];
        }

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

    // 1) Saisie des coordonnées de l'utilisateur
    Utilisateur user;
    user.saisir();

    // 2) Saisie du capital
    double capital;
    cout << "\nMontant du capital a emprunter (EUR) : ";
    cin >> capital;

    // 3) Banques par défaut
    vector<Banque> banques = {
        Banque("CA",  {3.0, 4.0}),
        Banque("BNP", {3.0, 4.0}),
        Banque("LCL", {3.0, 4.0}),
        Banque("CM",  {3.0, 4.0})
    };

    // 4) Durées proposées (en années)
    vector<int> durees = {10, 15, 20};

    // 5) Ajout dynamique de banques supplémentaires
    ajouterBanquesDynamiquement(banques);

    // 6) Affichage du tableau (structure 3 lignes par bloc, style original)
    Affichage aff(18);   // largeur de colonne = 18 caractères (comme l'original)
    aff.afficherTableau(capital, banques, durees);

    // 7) Export CSV automatique
    string nomFichier = "simulation_" + user.getNom() + ".csv";
    aff.exporterCSV(nomFichier, user, capital, banques, durees);

    cout << "\nMerci " << user.getPrenom() << " ! Simulation terminee.\n";
    return 0;
}
