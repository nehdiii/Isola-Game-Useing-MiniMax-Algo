//
// Created by DELL on 22/03/2021.
//

#ifndef ISOLAGAME_ISOLAGAME_H
#define ISOLAGAME_ISOLAGAME_H
#include "GameSpace.h"
#include "Position.h"
#include <cstdlib>
#include <vector>
#include <limits>
#include <cmath>
//nombre max des joueurs
const int MaxPlayers=10 ;
//le profondeur max de recherche pour mini_max
const int max_depth=30 ;

class IsolaGame {
    //*********attributs du classe*******
    GameSpace GS; // l'espace jeu
    Position Plys[MaxPlayers]; //cette attribus modelise la position actuelle de chaque joueurs dans le jeu
    int NbPlayers ; // nombre de joueurs totale
    int NbIAmachines ; // nombre de joueurs machine
    int ActivePlayer ; // numero de joueurs active
    //**************methodes du classe****************
public:
    int getActivePlayer() const;

    IsolaGame(int,int,int nbmachine=0 ) ;//constructeur de la classe IsolaGame (size,nombre des joueurs total,nombre des joueurs machine)
    void DisplayGame() ; // afficher et initialiser le jeu
    void GivePlayerTurn() ; // passer la main a une autre joueur c.a.d incrementer le activeplayer
    //***********les mouvements des joueurs dans le jeu*****************
    static void SwitchCase(GameSpace&,const Position&,const Position&) ; //SwitchCase est une methode a pour role de permuter les cases d'un espace jeu
    void MovePlayerInGame() ; // MovePlayerInGame c'est une methode qui s'applique sur une instance de classe IsolaGame permet de changer la position d'un joueur
    //************pour la destruction d'une case*****************
    Position AskForCaseToDestroy() ; //accèe a la case a detruire
    void DestroyCase(GameSpace&,const Position&) ;//detruire une case
    void DestroyCaseInGame() ; //detruire une case dans le jeux (cette methode utilise DestroyCase et AskForCaseToDestroy )
    //*************tester si un jeu est determinèe*****************
    bool EndGame() ; // tester la fin de jeux


    //*************la movement du IAplayer dans le jeu*******************
    void  MovePlayerInGameIA() ; //si le joueur est la machine donc il va cherchè la position optimal , sinon il va demondè à l'utilisateur de jouer
    Position FindCaseToDestroyIA() ;
    // IADestroyCaseInGame: il va detruire une case dans le jeu est afficher la nouvelle partie
    // donner la main a un joueur normal pour jouer
    void IADestroyCaseInGame() ;//detruire la case retourner par FindCaseToDestroyIA (car il utilise cet methode)

    //****************Minimax Bot*****************************
    static GameSpace FutureGameSpace(GameSpace,int,Position) ; // il va deonnè la nouvelle GameSpace après la movement de la dernier joueur
    int NbrGetEmptyCases() ; // donner le nombre total des cases vides du GameSpace
    float GetHeuristicOfGameState(Position,Position,GameSpace) ; // calculer l'Heuristic score d'un etat de jeu particulier
    float maxval(GameSpace,Position,Position,int,float,float); // donner l'Heuristec score maximal de la profondeur actuel dans l'arbre de jeu
    float minval(GameSpace,Position,Position,int,float ,float ) ; // donner l'Heuristec score minimal dde la profondeur actuel dans l'arbre de jeu
    Position MiniMaxWithAlphaBetaPruning(GameSpace,Position,Position,int,float,float) ; //l'algorithme de minimax ordinaire mais avec une autre methode appelè alpha beta pruning (il accelère la recherche )
    //il nous permet de faire une recherche plus vite dans l'arbre que mini_max
    //la methode MiniMaxWithAlphaBetaPruning nous retournè la position optimal
    void  MovePlayerInGameIAWithMiniMax() ;//deplacer le joueur machine dans l'espace jeu vers la position optimal retourner par MiniMaxWithAlphaBetaPruning
    void IADestroyCaseInGameMiniMax();

};


#endif //ISOLAGAME_ISOLAGAME_H
