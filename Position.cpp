//
// Created by DELL on 22/03/2021.
//

#include "Position.h"

Position::Position(int a,int b):x(a),y(b){}
bool Position::CaseValidation(GameSpace ech , int test)
{
    if(test==1)
    {
        // verification si la position est dans l'espace jeu
        return(1<=x && x<=ech.getsize() && 1<=y && y<=ech.getsize());

    }
    if(test==0)
    {
        //verification si la position est vide
        return(ech.GetCase(x,y)==IsEmpty) ;
    }
}
Position Position::GetNeighborPos(int way)
{
    Position neighbor ; // notre constructeur deja defini par defaut
    neighbor.x=x+WayToMove[way][0] ;
    neighbor.y=y+WayToMove[way][1] ;
    return(neighbor) ;
}
bool Position::NeighborCaseValidation(const GameSpace& ech,int way) // ce type de passage par parametre indique que cette methode ne fait pas des changment sur l'echiquier
{
    Position neighbor=GetNeighborPos(way) ;
    return(neighbor.CaseValidation(ech,1)&&neighbor.CaseValidation(ech,0)) ;
}
Position Position::GetNewMovmentOfCase(const GameSpace& ech)
{
    int way;
    bool test=false ;
    do
    {
        cout<<"direction of movement on numeric keybord ? "<<endl ;
        cin>>way ;
    }while(!(0<=way&&way<10&&NeighborCaseValidation(ech,way))) ;
    return(GetNeighborPos(way)) ;
}
bool Position::BlockedCase(const GameSpace& ech)
{
    for(int i=1 ;i<10;++i)
    {
        if(i!=5)
        {

            if(NeighborCaseValidation(ech,i))
            {
                return(false);
                //s'il ya au moins une case valide alors le joueur n'est pas bloqué

            }

        }

    }
    return(true);//tous les joueurs sont bloqués

}
int Position::NbrOfFreeCases(const GameSpace& ech)
{
    int NbrOfFree=0 ;
    for(int i=1 ; i<10;++i)
    {
        if(i!=5&&NeighborCaseValidation(ech,i))
        {
            NbrOfFree+=1 ;
        }
    }
    return(NbrOfFree);
}
Position Position::FindOptimalNeighborCase(const GameSpace& ech)
{
    int Nbmax=0; // nombre maximal des cases libre d'une case
    int BestWay=-1; // la bonne direction a suivre
    Position way1;
    for(int i=1 ;i<10;++i )
    {
        if(i!=5)
        {
            way1=GetNeighborPos(i);
            if(1<=i&&i<10&&NeighborCaseValidation(ech,i))
            {
                int nbFree=way1.NbrOfFreeCases(ech);
                if(nbFree>=Nbmax)
                {
                    Nbmax=nbFree;
                    BestWay=i ;
                }
            }
        }
    }
    Position wayis(0,0);
    if(BestWay==-1)
    {
        wayis.x=x;
        wayis.y=y;
    }
    else wayis=GetNeighborPos(BestWay) ;
    return(wayis) ;

}

int Position::getX() const {
    return x;
}

int Position::getY() const {
    return y;
}

void Position::setX(int x) {
    Position::x = x;
}

void Position::setY(int y) {
    Position::y = y;
}
int Position::ListOfPlayerLegalMoves(const GameSpace& ech)
{
    vector<Position> t ;
    for(int i=1;i<=9;i++)
    {
        if(NeighborCaseValidation(ech,i))
            t.push_back(GetNeighborPos(i)) ;

    }
    return(t.size()) ;
}
vector<Position> Position::ListOfPlayerLegalMoves1(const GameSpace & ech)
{
    vector<Position> t ;
    for(int i=1;i<=9;i++)
    {
        if(NeighborCaseValidation(ech,i))
            t.push_back(GetNeighborPos(i)) ;

    }
    return(t) ;
}
