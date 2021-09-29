//
// Created by DELL on 22/03/2021.
//

#ifndef ISOLAGAME_POSITION_H
#define ISOLAGAME_POSITION_H
//Dans la classe Position une case est representèe par ces coordonnee (ligne , colonne )
#include "GameSpace.h"
#include <iostream>
#include <vector>
using namespace std ;
// si la case est à l'interieur elle admet 8 voisins sinon elle admet 3
//matrice de taille 10*2 chaque line reprsente une direction??????????????????????????

//remplisage automatique????????????????????????????????????????????????????????????????
const int WayToMove[10][2]={
        {0,0}/* 0 fixed */ ,
        {1,-1} /*1 sw*/,
        {1,0} /*2 sud*/ ,
        {1,1} /*3 se*/ ,
        {0,-1} /*4 Ouest*/ ,
        {0,0} /*5 fixed dont move*/,
        {0,1} /*6 est*/ ,
        {-1,-1} /*7 nw*/ ,
        {-1,0} /*8 North*/ ,
        {-1,1} /*9 ne*/}  ;

class Position {
    //*****************attributs et methodes de classe*****************
    int x ;
    int y ;
public :
     void setX(int x);
     int getX() const;
     void setY(int y);
     int getY() const;
/*public:
    void setX(int x);

public:
    int getX() const;

private:
    int y ;
public:
    void setY(int y);

public:
    int getY() const;*/

//public:
    Position(int a=0 ,int b=0) ; // constructeur de classe point
    bool CaseValidation(GameSpace,int) ; // si int =0 il verifie si la nouvelle position est dans l'espace jeu ou non , et si int = 1 il verifie si la nouvelle position est vide ou non.
    Position GetNeighborPos(int) ; //cette fonction prendre la direction de mouvement est retourne la position voisin selon cette direction
    bool NeighborCaseValidation(const GameSpace&,int) ; //validation si la case vioisins est vide ou detruit ou un bord (il utilise la methode GetNeighborPos)
    Position GetNewMovmentOfCase(const GameSpace&) ; //cette fonction demande au joueur la direction et retourne la nouvelle position
    //*******methode de fin de jeu************
    bool BlockedCase(const GameSpace&) ;
    //**************les methodes necessaire pour le PVE********************
    int NbrOfFreeCases(const GameSpace& ech) ; //calculer le nombre des cases vides
    Position FindOptimalNeighborCase(const GameSpace&) ; //chercher la case optimale et utilise la methode de "plongee"
    //********* les methodes necessaire pour l'algorithme de minimax **************
    int ListOfPlayerLegalMoves(const GameSpace&) ;//retourner le nombre des cases vides accessible par le joueur
    vector<Position> ListOfPlayerLegalMoves1(const GameSpace&) ;//retourner un tableau qui renferme les position des cases vides accessible
};


#endif //ISOLAGAME_POSITION_H
