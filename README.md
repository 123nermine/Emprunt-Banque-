# 🏦 Simulateur d'Emprunt Bancaire

> Mini-logiciel C++ permettant de comparer les mensualités d'un emprunt entre plusieurs banques, avec ajout dynamique de banques et export des résultats au format CSV.

---

## 📋 Table des matières

1. [Présentation](#-présentation)
2. [Fonctionnalités](#-fonctionnalités)
3. [Architecture du projet](#-architecture-du-projet)
4. [Formule mathématique](#-formule-mathématique)
5. [Installation et compilation](#-installation-et-compilation)
6. [Utilisation](#-utilisation)
7. [Exemple d'exécution](#-exemple-dexécution)
8. [Structure du fichier CSV](#-structure-du-fichier-csv)
9. [Détails techniques](#-détails-techniques)
10. [Améliorations possibles](#-améliorations-possibles)
11. [Auteur](#-auteur)

---

## 🎯 Présentation

Ce programme est un **simulateur d'emprunt bancaire** écrit en **C++** dans une approche **orientée objet**. Il permet à un utilisateur de :

- Saisir ses coordonnées personnelles
- Indiquer le montant du capital qu'il souhaite emprunter
- Comparer les mensualités proposées par plusieurs banques pour différentes durées (10, 15 et 20 ans)
- Ajouter dynamiquement de nouvelles banques avec leurs taux d'intérêt
- Exporter automatiquement le résultat de la simulation dans un fichier `.csv` exploitable dans Excel ou LibreOffice

Le projet a été conçu dans une logique **académique** : code structuré, commenté, encapsulation des données, séparation claire des responsabilités.

---

## ✨ Fonctionnalités

| Fonctionnalité | Description |
|---|---|
| 👤 **Saisie utilisateur** | Nom, prénom, email, téléphone |
| 💰 **Calcul de mensualités** | Calcul précis basé sur la formule du crédit à amortissement constant |
| 🏛️ **Banques par défaut** | Crédit Agricole, BNP, LCL, Crédit Mutuel |
| ➕ **Ajout dynamique** | Ajout d'autant de banques que souhaité, avec nombre de taux variable |
| 🔤 **Noms avec espaces** | Gestion correcte des noms composés (ex : "Société Générale") |
| 📊 **Affichage formaté** | Tableau ASCII aligné avec séparateurs |
| 📁 **Export CSV** | Génération automatique d'un fichier `simulation_<NOM>.csv` |

---

## 🏗️ Architecture du projet

Le code est organisé selon une **architecture orientée objet** en **4 classes**, chacune ayant une responsabilité unique (principe SRP — *Single Responsibility Principle*).

```
┌─────────────────────────────────────────────────────────┐
│                    PROGRAMME PRINCIPAL                  │
│                         (main)                          │
└─────────────────────────────────────────────────────────┘
            │                                    │
            ▼                                    ▼
   ┌─────────────────┐                 ┌─────────────────┐
   │   Utilisateur   │                 │     Banque      │
   │                 │                 │                 │
   │ - nom           │                 │ - nom           │
   │ - prenom        │                 │ - taux[]        │
   │ - email         │                 │                 │
   │ - telephone     │                 │ + getNom()      │
   │                 │                 │ + getTauxAt()   │
   │ + saisir()      │                 │ + nbTaux()      │
   └─────────────────┘                 └─────────────────┘
                                                │
                                                ▼
                                        ┌─────────────────┐
                                        │     Compte      │
                                        │                 │
                                        │ - capital       │
                                        │ - tauxAnnuel    │
                                        │ - nbAnnees      │
                                        │                 │
                                        │ + calculer-     │
                                        │   Mensualite()  │
                                        └─────────────────┘
            │                                    │
            └──────────────┬─────────────────────┘
                           ▼
                  ┌─────────────────┐
                  │    Affichage    │
                  │                 │
                  │ - largeur       │
                  │                 │
                  │ + afficher-     │
                  │   Tableau()     │
                  │ + exporterCSV() │
                  └─────────────────┘
```

### 📦 Description des classes

#### 1️⃣ `Utilisateur`
Représente le client qui souhaite simuler un emprunt.
- **Attributs** : `nom`, `prenom`, `email`, `telephone`
- **Méthodes** : `saisir()`, getters

#### 2️⃣ `Compte`
Représente un emprunt bancaire et effectue le calcul de la mensualité.
- **Attributs** : `capital`, `tauxAnnuel`, `nbAnnees`
- **Méthode** : `calculerMensualite()`

#### 3️⃣ `Banque`
Représente une banque avec son nom et la liste de ses taux proposés.
- **Attributs** : `nom`, `taux[]`
- **Méthodes** : `getNom()`, `getTauxAt(i)`, `nbTaux()`

#### 4️⃣ `Affichage`
Gère la présentation des résultats (console + export CSV).
- **Attribut** : `largeur` (largeur d'une colonne)
- **Méthodes** : `afficherTableau()`, `exporterCSV()`

---

## 🧮 Formule mathématique

La mensualité d'un crédit à **amortissement constant** est calculée selon la formule suivante :

```
        C × t × (1 + t)ⁿ
  M = ──────────────────────
         (1 + t)ⁿ − 1
```

Où :
- **M** = mensualité (en €)
- **C** = capital emprunté (en €)
- **t** = taux d'intérêt mensuel (taux annuel ÷ 12 ÷ 100)
- **n** = nombre total de mensualités (durée en années × 12)

### Exemple
Pour un emprunt de **200 000 €** sur **20 ans** au taux de **3 %** :
- t = 0,03 / 12 = 0,0025
- n = 20 × 12 = 240 mois
- **M ≈ 1 109,20 €/mois**

---

## ⚙️ Installation et compilation

### Prérequis
- Un compilateur C++ supportant **C++11** ou supérieur (g++, clang++, MSVC)
- Un terminal (Linux, macOS, ou WSL/PowerShell sous Windows)

### Compilation

```bash
g++ -std=c++11 -Wall -Wextra -o simulateur simulateur_emprunt_final.cpp
```

### Options de compilation recommandées

| Option | Rôle |
|---|---|
| `-std=c++11` | Active le standard C++11 (requis pour `auto`, listes d'initialisation, etc.) |
| `-Wall` | Active tous les warnings courants |
| `-Wextra` | Active des warnings supplémentaires |
| `-O2` | (Optionnel) Optimisations |

### Exécution

```bash
./simulateur          # Linux / macOS
simulateur.exe        # Windows
```

---

## 🚀 Utilisation

Le programme est **interactif** : il pose une série de questions à l'utilisateur dans la console.

### Étapes d'utilisation

1. Saisir les **coordonnées personnelles** (nom, prénom, email, téléphone)
2. Saisir le **montant du capital** à emprunter
3. (Optionnel) **Ajouter des banques** supplémentaires avec leurs taux
4. Le programme **affiche le tableau** des mensualités
5. Le programme **génère automatiquement un fichier CSV** dans le même dossier que l'exécutable

---

## 💻 Exemple d'exécution

### Saisie

```
*****************************************************
*       SIMULATEUR D'EMPRUNT BANCAIRE - v1.0        *
*****************************************************

========== COORDONNEES DE L'UTILISATEUR ==========
Nom       : Dupont
Prenom    : Jean
Email     : jean.dupont@email.com
Telephone : 0612345678

Montant du capital a emprunter (EUR) : 200000

Ajouter une banque ? (o/n) : o
Nom de la banque : Societe Generale
Nombre de taux   : 2
  Taux 1 (en %) : 3.2
  Taux 2 (en %) : 4.1

Ajouter une autre banque ? (o/n) : n
```

### Sortie console

```
------------------------------------------------------------------------------------------+
| Banque          | CA              | BNP             | LCL             | CM              |
------------------------------------------------------------------------------------------+
| Taux            | 3%              | 3%              | 3%              | 3%              |
------------------------------------------------------------------------------------------+
| Duree           | 10 ans          | 10 ans          | 10 ans          | 10 ans          |
------------------------------------------------------------------------------------------+
| Mensualite      | 1931            | 1931            | 1931            | 1931            |
------------------------------------------------------------------------------------------+
| Taux            | 3%              | 3%              | 3%              | 3%              |
------------------------------------------------------------------------------------------+
| Duree           | 15 ans          | 15 ans          | 15 ans          | 15 ans          |
------------------------------------------------------------------------------------------+
| Mensualite      | 1381            | 1381            | 1381            | 1381            |
------------------------------------------------------------------------------------------+
                                       (...)

[OK] Fichier exporte : simulation_Dupont.csv

Merci Jean ! Simulation terminee.
```

---

## 📁 Structure du fichier CSV

Le programme génère un fichier nommé **`simulation_<Nom>.csv`**, contenant deux sections :

### Section 1 — Informations utilisateur

```csv
INFORMATIONS UTILISATEUR
Nom;Dupont
Prenom;Jean
Email;jean.dupont@email.com
Telephone;0612345678
Capital emprunte (EUR);200000
```

### Section 2 — Tableau des mensualités

```csv
TABLEAU DES MENSUALITES (EUR)
Taux;Duree (ans);CA;BNP;LCL;CM;Societe Generale
3.00%;10;1931.21;1931.21;1931.21;1931.21;1949.73
3.00%;15;1381.16;1381.16;1381.16;1381.16;1400.48
3.00%;20;1109.20;1109.20;1109.20;1109.20;1129.33
4.00%;10;2024.90;2024.90;2024.90;2024.90;2034.42
4.00%;15;1479.38;1479.38;1479.38;1479.38;1489.42
4.00%;20;1211.96;1211.96;1211.96;1211.96;1222.53
```

> 💡 Le séparateur utilisé est le **point-virgule** (`;`) — compatible avec **Excel français** et **LibreOffice Calc**. Il suffit d'ouvrir le fichier pour voir les données dans des cellules séparées.

---

## 🔧 Détails techniques

### Encapsulation
Tous les attributs sont **privés**, accessibles uniquement via des **getters/setters publics**. Cela respecte le principe d'encapsulation de la POO.

### Gestion des espaces dans les noms
La saisie des noms (utilisateur et banques) utilise `std::getline()` au lieu de `std::cin >> ` pour permettre les noms composés tels que :
- `Crédit Agricole`
- `Société Générale`
- `BNP Paribas`

> ⚠️ Un appel à `cin.ignore(numeric_limits<streamsize>::max(), '\n')` est nécessaire entre `cin >>` et `getline()` pour vider le `\n` résiduel du buffer.

### Tableau dynamique
- Le nombre de banques n'est **pas limité**
- Chaque banque peut avoir un **nombre de taux différent**
- La fonction `maxNbTaux()` calcule le nombre maximum de taux pour gérer les colonnes de manière flexible

### Robustesse
- Les noms de banque trop longs sont **tronqués automatiquement** pour préserver l'alignement du tableau (dans la version "large", v2)
- Compilation **sans warnings** avec `-Wall -Wextra`

---

## 🚧 Améliorations possibles

Quelques pistes pour étendre le projet :

- [ ] **Validation des entrées** (ex : refuser un capital ≤ 0, un taux négatif)
- [ ] **Gestion des erreurs** : exceptions pour les saisies invalides
- [ ] **Tableau d'amortissement** détaillé (mois par mois)
- [ ] **Coût total du crédit** et **intérêts cumulés**
- [ ] **Interface graphique** (Qt, GTK, Dear ImGui)
- [ ] **Lecture des banques depuis un fichier JSON/CSV** au démarrage
- [ ] **Tests unitaires** (Google Test, Catch2)
- [ ] **Internationalisation** (multi-langues)

---

## 📚 Concepts mis en œuvre

Ce projet illustre les notions suivantes du **C++** et de la **programmation orientée objet** :

- ✅ Classes et objets
- ✅ Encapsulation (`private` / `public`)
- ✅ Constructeurs avec liste d'initialisation
- ✅ Méthodes `const` (immutabilité)
- ✅ Conteneurs STL (`vector`, `string`)
- ✅ Algorithmes mathématiques (`pow`, formule du crédit)
- ✅ Manipulation de flux : `cin`, `cout`, `ofstream`, `ostringstream`
- ✅ Formatage : `setw`, `setprecision`, `fixed`, `left`
- ✅ Lecture de chaînes avec espaces (`getline`)
- ✅ Lecture/écriture de fichiers
- ✅ Boucles `for`/`while`, structures conditionnelles
- ✅ Passage par référence constante (`const &`) — bonne pratique de performance

---

## 👤 Auteur
  Nermine LAMMARI et Gregan RANDRIAMAHNINA

---

## 📄 Licence

Ce projet est libre d'utilisation à des fins **éducatives et académiques**.

---

> 💬 *"Un bon programme se reconnaît à la clarté de son code, pas à sa complexité."*
