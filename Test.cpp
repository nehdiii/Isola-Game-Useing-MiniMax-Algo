#include <iostream>
using  namespace  std ;
#include <ctime>
#include <stdlib.h>
#include "IsolaGame.cpp"
#include "GameSpace.cpp"
#include "Position.cpp"
//put all 2gather for PVP
void isolaGamepvp(int Size,int nbp)
{
    cout<< "PVP Game" << endl ;
    IsolaGame Game(Size,nbp) ;
    while(!(Game.EndGame()))
    {
        //display of game
        Game.DisplayGame() ;
        //move of active player
        Game.MovePlayerInGame() ;
        system("CLS") ;
        Game.DisplayGame() ;
        //destruction of case
        Game.DestroyCaseInGame();
        system("CLS") ;
        Game.DisplayGame();
        //pass to next player
        Game.GivePlayerTurn();
        system("CLS") ;
    }
    // loser hh
    cout<<"loser is : "<<Game.getActivePlayer()<<endl ;
    system("pause") ;

}
//put all 2gater for PVE
void isolaGamepve(int Size,int nbp,int nbm)
{
    cout<<" PVE Game "<<endl ;
    IsolaGame Game(Size,nbp,nbm) ;
    while(!(Game.EndGame()))
    {
        //display of game
        Game.DisplayGame();
        //move of active player
        Game.MovePlayerInGameIA();
        system("CLS") ;
        Game.DisplayGame();
        //destruction of case
        Game.IADestroyCaseInGame();
        system("CLS") ;
        Game.DisplayGame();
        //pass to next player
        Game.GivePlayerTurn();
        system("CLS") ;
    }
    cout<<"loser is : "<<Game.getActivePlayer()<<endl ;
}
//put all 2gather with minimax bot
void isolaGamepveMiniMax(int Size,int nbp,int nbm)
{
    cout<<" PVE Game minimax bot "<<endl ;
    IsolaGame Game(Size,nbp,nbm) ;
    while(!(Game.EndGame()))
    {
        //display of game
        Game.DisplayGame();
        //move of active player
        Game.MovePlayerInGameIAWithMiniMax();


        Game.IADestroyCaseInGame();
        system("CLS") ;
       // Game.DisplayGame();
        //destruction of case
        //Game.IADestroyCaseInGame();
        system("CLS") ;
        Game.DisplayGame();
        //pass to next player
        Game.GivePlayerTurn();
        system("CLS") ;
    }
    cout<<"loser is : "<<Game.getActivePlayer()<<endl ;
}
void affiche_annexe ()
{
    cout<<"pour le movement tu va utilise :"<<endl;
    cout<< "0--> fixed"<<endl;
    cout<< "1--> sw"<<endl;
    cout<< "2--> sud"<<endl;
    cout<< "3--> se"<<endl;
    cout<< "4--> Ouest"<<endl;
    cout<< "5--> fixed"<<endl;
    cout<<"6 -->est"<<endl;
    cout<< "7 -->nw"<<endl;
    cout<< "8--> North"<<endl;
    cout<< "9--> ne"<<endl<<endl;
}

int main()
{
    int p=1;
    do
    {
        int n=0,m=0,l=0;
        do
        {

            cout <<"donner le size de l'echequier"<<endl;
            cin >> n;
            cout <<"donner le nombre des joueurs"<<endl;
            cin >> m;
            cout <<"donner le nombre des joueurs machine"<<endl;
            cin >> l;
        }while(n<=0 && m<=1 && l>=m);
        affiche_annexe();

        if (l==0)
        {
            system("CLS") ;
            srand(time(NULL)) ;

            isolaGamepvp(n,m);
        }

        else
       {

           int k=0;
           while (k!=1 && k!=2)
           {

               cout <<"tu es choisi de jouer contre la machine "<<endl;
               cout<<"cliquer sur (1) pour un niveau facile et (2) pour un niveau difficile"<<endl;
               cin>>k;
           }
           if (k==1)
           {

                system("CLS") ;
               srand(time(NULL)) ;
               isolaGamepve(n,m,l);
           }
           else
           {

               system("CLS") ;
               srand(time(NULL)) ;
               isolaGamepveMiniMax(n,m,l) ;
           }


        }

        cout <<" si vous voulez de jouer autre fois taper sur (1)"<<endl;
        cin>>p;
    }while(p==1);
    return 0 ;


}

