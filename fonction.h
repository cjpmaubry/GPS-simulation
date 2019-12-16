#ifndef FONCTION_H
#define FONCTION_H


typedef struct _element  // Structure de liste permettant de stocker la liste des ville parcourue
{
	char *value;
	struct _element *next;
}element;

typedef  struct  _noeud // Structure des noeuds de l'arbre. Permet de stocker les villes en lien ainsi que de multiples informations
{
char* nom;
struct  _noeud **ville_en_lien;
int nombrelien;
int kilometre;
char* temps;
int kilometre_cumule;
int temps_cumule;
element* liste_ville_parcourue;
}noeud;

typedef struct _stockage // Permet de stocker tous les feuilles de l'arbre aboutissant a un resultat ( c'est à dire la ville d'arrivee )
{
	noeud* stokageinfo;
	struct _stockage *next;
}stockage;

int nombre_de_caractere(char caract,char* chaine); // Fonction qui detremine le nombre de fois qu'un caractere apparait dans une chaine de caractere

int position_du_ieme_caractere(char caract,int recurence,char* chaine); // Fonction qui retourne la position d'un caractere das une chaine de caractere

char* select_csv(int partie,char* chaine); //Fonction permettant de recuper une partie d'une chaine de caractere ( les parties doivent etre separee par des virgules )

char *selection (char*ville1,int ligne, int element_ligne); // Foncton permettant de selectionner dans le CVS tous les lignes qui ont comme premier element le nom de la ville entree en parametre.

int compteur_lien(char* nom); // Fonction permettant de compter "le nombre de fils" d'un noeud d'une ville

element * allouer(char* valeur); // Permet d'initaliser une liste de ville

stockage * allouer2(noeud* valeur); // Permet d'initaliser une liste de noeud

element* inserer_en_tete(char *valeur, element *liste); // Permet d'inserer une ville en tete de liste

void inserer_en_fin(noeud *valeur, stockage *liste); // Permet d'inserer un noeud en fin d'une liste 

noeud* initiatiliser_noeud(char* nom_ville,noeud* temporaire); //Permet d'initialiser le noeud d'une ville. Remplissage de certaines donnees du noeud tel que le nom de la ville...

void Creation(noeud* depart,char* ville_arrivee,stockage* trajet); // Permet de lancer le programme de creation de l'arbre ( Creation_Core),en initailiant certain parametre tel que la hauteur de l'arbre par exemple.

void Creation2(noeud* depart,char* ville_arrivee,stockage* trajet); // Permet de lancer le programme de creation de l'arbre ( Creation_Core_2),en initailiant certain parametre tel que la hauteur de l'arbre par exemple.
// VARIANTE de Creation 1 utilise lors de l'affichage de l'arbre

bool Recherche_chemin_errone(char* nom,element* liste); // Fonction permettant de savoir si la ville en parametre a deja ete parcourue dans le trajet de l'arbre.

void Creation_Core(noeud* depart, element* liste,char* ville_arrivee,int hauteur,stockage* trajet); // Fonction qui  cree l'arbre suivant les regles etablie par les trajets.

int longueur_liste(element* liste); // Fonction permettant de retourner la longueur d'une liste

void afficher_liste(element* liste); // Fonction permettant d'afficher une liste

void afficher_resultat(stockage* liste); // Fonction permettant d'afficher tous les trajets ayant abouti a la ville d'arrivee dans l'arbre.

void afficher_resultat_court(stockage* liste); // Fonction permettant d'afficher le trajet le plus court ayant abouti a la ville d'arrivee 

void afficher_resultat_rapide(stockage* liste); // Fonction permettant d'afficher le trajet le plus rapide ayant abouti a la ville d'arrivee 

void afficher_un_resultat(stockage* liste); // Fonction qui affiche le premier resultat trouve dans l'arbre

noeud* initiatiliser_noeuddedepart(char* nom_ville); // Permet d'initailiser le noeud de depart de l'arbre

int conversion_duree(char* temps1,int temps2); // Permet de calculer le temps de parourt cumule en convertissant un temps sous forme de chaine de caratere en entier.

void Creation_Core_2(noeud* depart, element* liste,char* ville_arrivee,int hauteur,stockage* trajet); // Fonction qui  cree l'arbre suivant les regles etablie par les trajets.
// VARIANTE de Creation_Core utilise lors de l'affichage de l'arbre

void menuGPS(); // Fonction de lancement du programme GPS. Gere l'ordre d'execution des fonctions principales et recupere les informations utilisateurs.

#endif