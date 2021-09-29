//
// Created by DELL on 22/03/2021.
//

#ifndef ISOLAGAME_GAMESPACE_H
#define ISOLAGAME_GAMESPACE_H
//constante pour la taille max et min de l'espace jeu
const int MinGameSize=4 ; // taille min de l'espace jeu
const int MaxGameSize=20 ; //taille max de l'espace jeu
//les constantes qui vont identifier l'etat d'une case
const int IsEmpty=0; // case vide
const int IsDestroyed=-1 ; // case detruite
const int IsBord=-3 ; // case en dehors de l'espace jeu
//Classe GameSpace qui caracterise l'espace jeu
class GameSpace {
    //***************declaration des attributs***************
    int Table[MaxGameSize+1][MaxGameSize+1]; //matrice qui caracterise l'espace jeux
    int dim ; // dimension de l'espace jeu dont laquel on va jouè
public:
    //****************declaration des methodes du classe*******
    GameSpace(int val=0) ;//contructeur avec le paramtre "val" initialise la dimension (0 par defaut)
    void DisplayCase(int) ; // affiche la case sous forma d'un symbole
    void DisplayGameSpace() ;// affiche l'espace jeu
    int GetCase(int x,int y) ; //retourne la case de coordonnèe (x,y)
    void FixeCase(int x,int y,int n); // fixe la nouvelle valeur "n" dans la case (x,y)
    int getsize() ; //retourne la dimension


};


#endif //ISOLAGAME_GAMESPACE_H
