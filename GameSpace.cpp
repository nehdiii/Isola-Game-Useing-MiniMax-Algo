//
// Created by DELL on 22/03/2021.
//

#include "GameSpace.h"
#include <iostream>
using  namespace std ;


GameSpace::GameSpace(int val):dim(val) // constructeur initialise l'espace jeu
{
    for(int i=1;i<=dim;i++)
    {
        for(int j=1;j<=dim;j++)
        {
            Table[i][j]=IsEmpty ;  // initialiser l'echequier par des zeros ( IsEmpty =0 ) (point de vue programmeur )
        }
    }
    //remplissage la bordure par (-3) (IsBord =-3 ) ( point de vue programmeur )
    for(int k=0;k<=dim+1;k++)
    {
        Table[0][k]=IsBord ;
        Table[k][0]=IsBord ;
        Table[dim+1][k]=IsBord ;
        Table[k][dim+1]=IsBord ;
    }


}
void GameSpace::DisplayCase(int val) // affiche la case sous forme d'un symbole (point d vue utilisateur )
{
    if(val>0)
    {
        cout<<val<<' ' ;
    }
    else if(val==IsEmpty)
    {
        cout<<'.'<<' ';
    }
    else if(val==IsDestroyed)
    {
        cout<<'*'<<' ';
    }
    else
    {
        cout<<'#'<<' ';
    }
}
void GameSpace::DisplayGameSpace() // affiche l'espace jeu
{
    cout<<' '<<' '<<'x'<<' ';
    for(int i=1;i<=dim;i++)
        cout<<i<<' ';
    cout<<endl;
    // !!!! prob line de y
    cout<<'y'<<' ';
    for(int i=0 ;i<=dim+1;i++)
    {
        if(i!=0&&i!=dim+1)
        {
            cout<<i<<' ';
        }
        else if (i==dim+1) cout<<' '<<' ' ;
        for(int j=0 ;j<=dim+1;j++)
        {
            DisplayCase(Table[i][j]);
        }

        cout<<endl;
    }

}
int GameSpace::GetCase(int x , int y ) // retourne la case de coordonèe (x,y)
{
    return(Table[x][y]);
}
void GameSpace::FixeCase(int x,int y,int n) // fixe la nouvellre valeur "n" dans la case (x,y)
{
    Table[x][y]=n ;
}
int GameSpace::getsize() {return (dim);} // retourne la dimension
