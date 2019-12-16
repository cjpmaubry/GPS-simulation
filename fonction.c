#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "fonction.h"


int nombre_de_caractere(char caract,char* chaine)
{
	int resultat=0;
	int taille=strlen(chaine);
	for(int i=0;i<taille;i++)
	{
		if(chaine[i]==caract)
		{
			resultat++;
		}
	}
	return resultat;
	
}

int position_du_ieme_caractere(char caract,int recurence,char* chaine)
{
	int resultat=-1;
	if (nombre_de_caractere(caract,chaine)<recurence)
		return resultat;
	else
	{
	int index=0;
	int compteur=0;
	while (compteur!=recurence)
	{
		if(chaine[index]==caract)
		{
			compteur++;
		}
		index++;
	}
	return index;
	}
	
}

char* select_csv(int partie,char* chaine)
{
	int k=0;
	int tab[3];
	int taille=strlen(chaine);
	tab[0]=position_du_ieme_caractere(',',1,chaine)-1; // le -1 permet de connaitre la position du dernier caractère avant la virgule
	tab[1]=position_du_ieme_caractere(',',2,chaine)-1;
	tab[2]=position_du_ieme_caractere(',',3,chaine)-1;
	
if (partie==1)
	{
		
	char * resultat=malloc((tab[0]+1)*sizeof(char));
	for(int i=0;i<tab[0];i++)
	{
		resultat[k]=chaine[i];
		k++;
	}
	resultat[k]='\0';
	return resultat;
    }
if (partie==2)
	{
	char * resultat=malloc((tab[1]-tab[0]+1)*sizeof(char));
	for(int i=tab[0]+1;i<tab[1];i++)
	{
		resultat[k]=chaine[i];
		k++;
	}
	resultat[k]='\0';
	return resultat;
	}
if (partie==3)
	{
	char * resultat=malloc((tab[2]-tab[1]+1)*sizeof(char));
	for(int i=tab[1]+1;i<tab[2];i++)
	{
		resultat[k]=chaine[i];
		k++;
	}
	resultat[k]='\0';
	return resultat;
	}
if (partie==4)
	{
	char * resultat=malloc((taille-tab[2]+1)*sizeof(char));
	for(int i=tab[2]+1;i<taille;i++)
	{
		resultat[k]=chaine[i];
		k++;
	}
	resultat[k]='\0';
	return resultat;
	}
return NULL; // Ce return evite un Warning jaune. En verité il n'est jamais atteind car le CVS que l'on utilise comporte toujours 4 partie.
}


char *selection (char*ville1,int ligne, int element_ligne)
{
	char* resultat;
	int i=-1; //-1 et non 0 car sinon on ne recupère pas la ligne d'indice "0" par la suite
	char line[81];
	FILE* fic ;
	fic = fopen( "connexions.csv", "r") ;
	if (fic==NULL)
	{
		printf("Ouverture fichier impossible !");
		exit(0);
	}
	while ( fgets( line, 81, fic) != NULL )
	{
		if (strcmp(select_csv(1,line),ville1) == 0)
		{
			i++;
		}
		if(i==ligne) // permet de selectionner la ville en connexions souhaité ( la premiere dans le CSV  est d'indice 0 )
		{
			resultat=select_csv(element_ligne,line);
			fclose(fic);
			return resultat;
		}
	}
	return NULL;
}

int compteur_lien(char* nom)
{
FILE* fic ;
	char ligne[81];
	int compteur=0;
	fic = fopen( "connexions.csv", "r") ;
	if (fic==NULL)
	{
		printf("Ouverture fichier impossible !");
	}

	while ( fgets( ligne, 81, fic) != NULL )
	{
		strtok(ligne,",");
		if (strcmp(nom,ligne) == 0) // strcmp permet de renvoyer 0 si les 2 chaines sont egales
			compteur++;
	}
	fclose(fic);
	return compteur;
}

element * allouer(char* valeur)
{
	element * elem=malloc(sizeof(element));
	elem->value=valeur;
	elem->next=NULL;
	return elem;
}

stockage * allouer2(noeud* valeur)
{
	stockage * elem=malloc(sizeof(stockage));
	elem->stokageinfo=valeur;
	elem->next=NULL;
	return elem;
}

element* inserer_en_tete(char *valeur, element *liste)
{
	element *liste2;
	liste2= allouer(valeur);
	liste2->next=liste;
	return liste2;
}

void inserer_en_fin(noeud *valeur, stockage *liste)
{
	stockage *liste2;
	liste2= allouer2(valeur);
		while(liste->next!=NULL)
	{
		liste=liste->next;
	}
	liste->next=liste2;
}

noeud* initiatiliser_noeud(char* nom_ville,noeud* temporaire)
{
	noeud *ville = malloc(sizeof(noeud));
	ville->nom = nom_ville;
	ville->nombrelien=compteur_lien(nom_ville);
	ville->ville_en_lien=malloc((sizeof(noeud*))*ville->nombrelien);
	for (int i=0;i<ville->nombrelien;i++)
	{
		noeud *new=malloc(sizeof(noeud));
		new->nom=selection(nom_ville,i,2);
		new->kilometre=atoi(selection(nom_ville,i,3)); // atoi ( Ascii to int )
		new->temps=(selection(nom_ville,i,4));
		new->kilometre_cumule=(new->kilometre)+(temporaire->kilometre_cumule);
		new->temps_cumule=conversion_duree(new->temps,temporaire->temps_cumule);
		ville->ville_en_lien[i]=new;
	}
	return ville;
}

void Creation(noeud* depart,char* ville_arrivee,stockage* trajet)
{
	element* liste=allouer(depart->nom);
	int hauteur=0;
	Creation_Core(depart,liste,ville_arrivee,hauteur,trajet);
}

bool Recherche_chemin_errone(char* nom,element* liste)
{
	bool resultat=false;
	while (liste!=NULL)
	{
		if (strcmp(liste->value,nom) == 0)
			resultat=true;
		liste=liste->next;
	}
	
return resultat;
}

void Creation_Core(noeud* depart, element* liste,char* ville_arrivee,int hauteur,stockage* trajet) // ATTENTION LISTE DOIT CONTENIR VILLE DEPART........
{
	hauteur++;
	if (hauteur<7)
	{
	for(int i=0; i< depart->nombrelien ;i++)
	{
		noeud* temporaire=depart->ville_en_lien[i];
		if ((depart->ville_en_lien[i]!=NULL)&&(Recherche_chemin_errone(temporaire->nom,liste)!=true))
		{
			if (strcmp(temporaire->nom,ville_arrivee) != 0)
			{
				noeud* suivant=initiatiliser_noeud(temporaire->nom,temporaire);
				element* liste_suivant=inserer_en_tete(suivant->nom,liste);
				Creation_Core(suivant, liste_suivant, ville_arrivee,hauteur,trajet);
			}
			
			else
			{
				element* listefinal=inserer_en_tete(ville_arrivee,liste);//permet de rajouter dans la liste la ville d'arrivee'
				temporaire->liste_ville_parcourue=listefinal;
				inserer_en_fin(temporaire,trajet);
			}
			
		}
	}
	
    }
}

int longueur_liste(element* liste)
{
	int compteur=0;
	while (liste!=NULL)
	{
		compteur++;
		liste=liste->next;
	}
	return compteur;
}

void afficher_liste(element* liste)
{
	int taille=longueur_liste(liste);
	for(int i=0;i<taille;i++)
	{
		element* temporaire=liste;
		for(int k=0;k<taille-1-i;k++)
		{
			temporaire=temporaire->next;
		}
		if(i==taille-1)
        printf("%s", temporaire->value);
		if(i!=taille-1)
		printf("%s -> ", temporaire->value);
    }
}

void afficher_resultat(stockage* liste)
{
	if (liste != NULL)
	{
	int compteur=0;
	stockage *actuel = liste;
	actuel = actuel->next;
    while (actuel != NULL)
    {	noeud* affichage=actuel->stokageinfo;
		compteur++;
        printf("\n%d km et %d minutes pour le trajet : ", affichage->kilometre_cumule, affichage->temps_cumule);
		afficher_liste(affichage-> liste_ville_parcourue);
		printf("\n");
        actuel = actuel->next;
    }
	printf("\n\n Il y a %d trajets trouves",compteur);
	}
}

void afficher_un_resultat(stockage* liste)
{
	if (liste != NULL)
	{
	stockage *actuel = liste;
	actuel = actuel->next;
		noeud* affichage=actuel->stokageinfo;
        printf("\n%d km et %d minutes pour le trajet : ", affichage->kilometre_cumule, affichage->temps_cumule);
		afficher_liste(affichage-> liste_ville_parcourue);
		printf("\n");
        actuel = actuel->next;
    }
}

void afficher_resultat_court(stockage* liste)
{
	if (liste != NULL)
	{
	noeud* affichage2;
	int index=0;
	int kilometre=1000000;
	int compteur=0;
	stockage *actuel = liste;
	stockage *actuel2=actuel;
	actuel = actuel->next;
    while (actuel != NULL)
    {	noeud* affichage=actuel->stokageinfo;
		actuel = actuel->next;
		compteur++;
		if (kilometre>affichage->kilometre_cumule)
		{
			kilometre=affichage->kilometre_cumule;
			index=compteur;
		}
	}
    
	for(int i=0;i<index;i++)
	{
        actuel2 = actuel2->next;
    }
	affichage2=actuel2->stokageinfo;
	printf("\n%d km et %d minutes pour le trajet : ", affichage2->kilometre_cumule, affichage2->temps_cumule);
	afficher_liste(affichage2-> liste_ville_parcourue);
	}
}

void afficher_resultat_rapide(stockage* liste)
{
	if (liste != NULL)
	{
	noeud* affichage2;
	int index=0;
	int temps=1000000;
	int compteur=0;
	stockage *actuel = liste;
	stockage *actuel2=actuel;
	actuel = actuel->next;
    while (actuel != NULL)
    {	compteur++;
		noeud* affichage=actuel->stokageinfo;
		actuel = actuel->next;
		if (temps>affichage->temps_cumule)
		{
			temps=affichage->temps_cumule;
			index=compteur;
		}
    }
	for(int i=0;i<index;i++)
	{	
        actuel2 = actuel2->next;
    }
	affichage2=actuel2->stokageinfo;
	printf("\n%d km et %d minutes pour le trajet : ", affichage2->kilometre_cumule, affichage2->temps_cumule);
	afficher_liste(affichage2-> liste_ville_parcourue);
	}
}

noeud* initiatiliser_noeuddedepart(char* nom_ville)
{
	noeud *ville = malloc(sizeof(noeud));
	ville->nom = nom_ville;
	ville->kilometre=0;
	ville->kilometre_cumule=0;
	ville->temps_cumule=0;
	ville->nombrelien=compteur_lien(nom_ville);
	ville->ville_en_lien=malloc((sizeof(noeud*))*ville->nombrelien);
	for (int i=0;i<ville->nombrelien;i++)
	{
		noeud *new=malloc(sizeof(noeud));
		new->nom=selection(nom_ville,i,2);
		new->kilometre=atoi(selection(nom_ville,i,3)); // atoi ( Ascii to int )
		new->temps=(selection(nom_ville,i,4));
		new->kilometre_cumule=(new->kilometre);
		new->temps_cumule=conversion_duree(new->temps,0);
		ville->ville_en_lien[i]=new;
	}
	return ville;
}

int conversion_duree(char* temps1,int temps2)
{
	char* time1=malloc(sizeof(char)*3);
	for(int i=0; i<2;i++)
	{
		time1[i]=temps1[i];
	}
	int tempsminute=atoi(time1);
	int resultat_int=(tempsminute)*60;
	for(int i=0; i<2;i++)
	{
		time1[i]=temps1[i+3];
	}
	 tempsminute=atoi(time1);
	 resultat_int+=temps2;
	 resultat_int+=tempsminute;
return resultat_int;
}

void Creation_Core_2(noeud* depart, element* liste,char* ville_arrivee,int hauteur,stockage* trajet)
{
	hauteur++;
	if (hauteur<7)
	{
	for(int i=0; i< depart->nombrelien ;i++)
	{
		noeud* temporaire=depart->ville_en_lien[i];
		if ((depart->ville_en_lien[i]!=NULL)&&(Recherche_chemin_errone(temporaire->nom,liste)!=true))
		{
			if (strcmp(temporaire->nom,ville_arrivee) != 0)
			{
				depart->ville_en_lien[i]=initiatiliser_noeud(temporaire->nom,depart->ville_en_lien[i]);
				element* liste_suivant=inserer_en_tete(depart->ville_en_lien[i]->nom,liste);
				Creation_Core_2(depart->ville_en_lien[i], liste_suivant, ville_arrivee,hauteur,trajet);
			}
			
			else
			{
				element* listefinal=inserer_en_tete(ville_arrivee,liste);//permet de rajouter dans la liste la ville d'arrivee'
				temporaire->liste_ville_parcourue=listefinal;
				inserer_en_fin(temporaire,trajet);
			}
			
		}
		else
		{
			depart->ville_en_lien[i]=NULL;
		}
	}
	
	}
}

void Creation2(noeud* depart,char* ville_arrivee,stockage* trajet)
{
	element* liste=allouer(depart->nom);
	int hauteur=0;
	Creation_Core_2(depart,liste,ville_arrivee,hauteur,trajet);
}

void _affichage_arborescence(noeud * arbre, int offset)
{
    if (offset > 0)
    {
        decalage(offset);
    }
    printf("%s\n", arbre->nom);
    if (arbre != NULL)
    {
	
	if (arbre->nombrelien==2)
	{
        if (arbre->ville_en_lien[1] != NULL)
        {
            _affichage_arborescence(arbre->ville_en_lien[1] , offset + 1);
        }
        if (arbre->ville_en_lien[1]  == NULL && arbre->ville_en_lien[0] != NULL)
        {
            decalage(offset+1);
            printf("x\n");
        }
        if (arbre->ville_en_lien[0]  != NULL)
        {
            _affichage_arborescence(arbre->ville_en_lien[0] , offset + 1);
        }
        if (arbre->ville_en_lien[0]  == NULL && arbre->ville_en_lien[1]  != NULL)
        {
            decalage(offset+1);
            printf("x\n");
        }
    }
	
	if (arbre->nombrelien==1)
	{
        if (arbre->ville_en_lien[0]  != NULL)
        {
            _affichage_arborescence(arbre->ville_en_lien[0] , offset + 1);
        }
        
    }
	if (arbre->nombrelien==3)
	{
        if (arbre->ville_en_lien[1] != NULL)
        {
            _affichage_arborescence(arbre->ville_en_lien[1] , offset + 1);
        }
        if (arbre->ville_en_lien[1]  == NULL && arbre->ville_en_lien[0] != NULL && arbre->ville_en_lien[2] != NULL)
        {
            decalage(offset+1);
            printf("x\n");
        }
        if (arbre->ville_en_lien[0]  != NULL)
        {
            _affichage_arborescence(arbre->ville_en_lien[0] , offset + 1);
        }
        if (arbre->ville_en_lien[0]  == NULL && arbre->ville_en_lien[1]  != NULL && arbre->ville_en_lien[2] != NULL)
        {
            decalage(offset+1);
            printf("x\n");
        }
		if (arbre->ville_en_lien[2]  != NULL)
        {
            _affichage_arborescence(arbre->ville_en_lien[2] , offset + 1);
        }
		 if (arbre->ville_en_lien[2]  == NULL && arbre->ville_en_lien[0] != NULL && arbre->ville_en_lien[1] != NULL)
        {
            decalage(offset+1);
            printf("x\n");
        }
		
    }
	if (arbre->nombrelien==4)
	{
        if (arbre->ville_en_lien[1] != NULL)
        {
            _affichage_arborescence(arbre->ville_en_lien[1] , offset + 1);
        }
        if (arbre->ville_en_lien[1]  == NULL && arbre->ville_en_lien[0] != NULL && arbre->ville_en_lien[2] != NULL && arbre->ville_en_lien[3] != NULL)
        {
            decalage(offset+1);
            printf("x\n");
        }
        if (arbre->ville_en_lien[0]  != NULL)
        {
            _affichage_arborescence(arbre->ville_en_lien[0] , offset + 1);
        }
        if (arbre->ville_en_lien[0]  == NULL && arbre->ville_en_lien[1]  != NULL && arbre->ville_en_lien[2] != NULL && arbre->ville_en_lien[3] != NULL )
        {
            decalage(offset+1);
            printf("x\n");
        }
		if (arbre->ville_en_lien[2]  != NULL)
        {
            _affichage_arborescence(arbre->ville_en_lien[2] , offset + 1);
        }
		 if (arbre->ville_en_lien[2]  == NULL && arbre->ville_en_lien[0] != NULL && arbre->ville_en_lien[1] != NULL && arbre->ville_en_lien[3] != NULL )
        {
            decalage(offset+1);
            printf("x\n");
        }
		if (arbre->ville_en_lien[3] != NULL)
        {
            _affichage_arborescence(arbre->ville_en_lien[3] , offset + 1);
        }
        if (arbre->ville_en_lien[3]  == NULL && arbre->ville_en_lien[0] != NULL && arbre->ville_en_lien[2] != NULL && arbre->ville_en_lien[1] != NULL)
        {
            decalage(offset+1);
            printf("x\n");
        }
	}	
		if (arbre->nombrelien==5)
	{
        if (arbre->ville_en_lien[1] != NULL)
        {
            _affichage_arborescence(arbre->ville_en_lien[1] , offset + 1);
        }
        if (arbre->ville_en_lien[1]  == NULL && arbre->ville_en_lien[0] != NULL && arbre->ville_en_lien[2] != NULL && arbre->ville_en_lien[3] != NULL && arbre->ville_en_lien[3] != NULL)
        {
            decalage(offset+1);
            printf("x\n");
        }
        if (arbre->ville_en_lien[0]  != NULL)
        {
            _affichage_arborescence(arbre->ville_en_lien[0] , offset + 1);
        }
        if (arbre->ville_en_lien[0]  == NULL && arbre->ville_en_lien[1]  != NULL && arbre->ville_en_lien[2] != NULL && arbre->ville_en_lien[3] != NULL && arbre->ville_en_lien[3] != NULL)
        {
            decalage(offset+1);
            printf("x\n");
        }
		if (arbre->ville_en_lien[2]  != NULL)
        {
            _affichage_arborescence(arbre->ville_en_lien[2] , offset + 1);
        }
		 if (arbre->ville_en_lien[2]  == NULL && arbre->ville_en_lien[0] != NULL && arbre->ville_en_lien[1] != NULL && arbre->ville_en_lien[3] != NULL && arbre->ville_en_lien[3] != NULL)
        {
            decalage(offset+1);
            printf("x\n");
        }
		if (arbre->ville_en_lien[3] != NULL)
        {
            _affichage_arborescence(arbre->ville_en_lien[3] , offset + 1);
        }
        if (arbre->ville_en_lien[3]  == NULL && arbre->ville_en_lien[0] != NULL && arbre->ville_en_lien[2] != NULL && arbre->ville_en_lien[1] != NULL && arbre->ville_en_lien[3] != NULL)
        {
            decalage(offset+1);
            printf("x\n");
        }
		if (arbre->ville_en_lien[4] != NULL)
        {
            _affichage_arborescence(arbre->ville_en_lien[4] , offset + 1);
		if (arbre->ville_en_lien[4]  == NULL && arbre->ville_en_lien[0] != NULL && arbre->ville_en_lien[2] != NULL && arbre->ville_en_lien[1] != NULL && arbre->ville_en_lien[3] != NULL)
        {
            decalage(offset+1);
            printf("x\n");
        }
	}	
	}
}
}
void affichage_arborescence(noeud * arbre)
{
    _affichage_arborescence(arbre, 0);
}

void decalage(int offset)
{
    for (int i = 0; i < offset; i++)
    {
        printf("  ");
    }
    printf("|-");
}

void menuGPS()
{
	printf("-------------GPS-------------\n");
	printf("\n");
	printf("LANCEMENT DU PROGRAMME\n");
	printf("\n");
	char* ville_depart=malloc(20*sizeof(char));
	char* ville_arrivee=malloc(20*sizeof(char));
do
		{
		printf("Veuillez indiquer la ville de depart (la ville doit exiter dans les donnees )\n");
		scanf("%s",ville_depart);
		}while((selection (ville_depart,0,1)==NULL)||(strcmp(ville_depart,"ville1")==0)); // Recherche dans le CVS une correspondance ( permet de savoir si la ville existe ) ville1 etant aussi dans le CVS il faut l'exclure.
do
		{
		printf("Veuillez indiquer la ville d'arrivee (la ville doit exiter dans les donnees )\n");
		scanf("%s",ville_arrivee);
		}while((selection (ville_arrivee,0,1)==NULL)||(strcmp(ville_arrivee,"ville1")==0));
	
	int choix;
do
		{
		printf("Veuillez indiquer le type de resultat que vous voulez\n");
		printf("Pour cela indiquer le numero de votre choix\n");
		printf("Pour cela taper 1 pour AFFICHER TOUS LES RESULTATS puis ENTRER \n");
		printf("Pour cela taper 2 pour AFFICHER LE TRAJET LE PLUS RAPIDE puis ENTRER \n");
		printf("Pour cela taper 3 pour AFFICHER LE TRAJET LE PLUS COURT puis ENTRER \n");
		printf("Pour cela taper 4 pour AFFICHER L'ARBRE DES TRAJETS puis ENTRER \n");
		printf("Pour cela taper 5 pour AFFICHER LE PREMIER RESULTAT TROUVE puis ENTRER \n");
		scanf("%d",&choix);
		}while((choix!=1)&&(choix!=2)&&(choix!=3)&&(choix!=4)&&(choix!=5));// Le programme redemandera a l'utilisateur s'il veut changer tant que ce dernier repondra autre chose que 1,2,3,4,5
printf("\n");
	
if (choix==4)
{
	noeud* prov;
	stockage* trajet=allouer2(prov);
	noeud* villededepart=initiatiliser_noeuddedepart(ville_depart);
	Creation2(villededepart,ville_arrivee,trajet);
	affichage_arborescence(villededepart);
}
else
{

noeud* prov;
stockage* trajet=allouer2(prov);
noeud* villededepart=initiatiliser_noeuddedepart(ville_depart);
Creation(villededepart,ville_arrivee,trajet);

if(choix==1)
{
	printf("Voici la liste de tous les trajet : \n");
	afficher_resultat(trajet);
}
if (choix==3)
{
	printf("Voici le trajet le plus court : \n");
	afficher_resultat_court(trajet);
}
if (choix==2)
{
	printf("Voici le trajet le plus rapide : \n");
	afficher_resultat_rapide(trajet);
}
if (choix==5)
{
	printf("Voici le premier trajet trouve : \n");
	afficher_resultat_rapide(trajet);
}	
	
}



int choix3;
do{
do
		{
		printf("\n\nVoulez vous afficher d'autre trajet ou quitter ? : \n");
		printf("Pour cela indiquer le numero de votre choix\n");
		printf("Pour cela taper 1 pour D'AUTRE TRAJET puis ENTRER \n");
		printf("Pour cela taper 2 pour QUITTER puis ENTRER \n");
		scanf("%d",&choix3);
		}while((choix3!=1)&&(choix3!=2));// Le programme redemandera a l'utilisateur s'il veut changer tant que ce dernier repondra autre chose que 1 ou 2
printf("\n");

if(choix3==1)
{
	int choix5;
do
		{
		printf("Veuillez indiquer le type de resultat que vous voulez\n");
		printf("Pour cela indiquer le numero de votre choix\n");
		printf("Pour cela taper 1 pour AFFICHER TOUS LES RESULTATS puis ENTRER \n");
		printf("Pour cela taper 2 pour AFFICHER LE TRAJET LE PLUS RAPIDE puis ENTRER \n");
		printf("Pour cela taper 3 pour AFFICHER LE TRAJET LE PLUS COURT puis ENTRER \n");
		printf("Pour cela taper 4 pour AFFICHER L'ARBRE DES TRAJETS puis ENTRER \n");
		printf("Pour cela taper 5 pour AFFICHER LE PREMIER RESULTAT TROUVE puis ENTRER \n");
		scanf("%d",&choix5);
		}while((choix5!=1)&&(choix5!=2)&&(choix5!=3)&&(choix5!=4)&&(choix5!=5));// Le programme redemandera a l'utilisateur s'il veut changer tant que ce dernier repondra autre chose que 1,2,3,4,5
printf("\n");
	
if (choix5==4)
{
	noeud* prov;
	stockage* trajet=allouer2(prov);
	noeud* villededepart=initiatiliser_noeuddedepart(ville_depart);
	Creation2(villededepart,ville_arrivee,trajet);
	affichage_arborescence(villededepart);
}
else
{

noeud* prov;
stockage* trajet=allouer2(prov);
noeud* villededepart=initiatiliser_noeuddedepart(ville_depart);
Creation(villededepart,ville_arrivee,trajet);

if(choix5==1)
{
	printf("Voici la liste de tous les trajet : \n");
	afficher_resultat(trajet);
}
if (choix5==3)
{
	printf("Voici le trajet le plus court : \n");
	afficher_resultat_court(trajet);
}
if (choix5==2)
{
	printf("Voici le trajet le plus rapide : \n");
	afficher_resultat_rapide(trajet);
}
if (choix5==5)
{
	printf("Voici le premier trajet trouve : \n");
	afficher_resultat_rapide(trajet);
}	
	
}

}
}while(choix3==1);
}
