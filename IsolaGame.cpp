//
// Created by DELL on 22/03/2021.
//

#include "IsolaGame.h"

IsolaGame::IsolaGame(int GSsize,int nbplayers ,int nbmachine):NbIAmachines(nbmachine),NbPlayers(nbplayers),GS(GSsize)
{

    for(int k=1;k<=nbplayers;++k)
    {
        Position pos1;
        while(!(pos1.CaseValidation(GS,1)&& pos1.CaseValidation(GS,0)))
        {
            pos1.setX(rand()%GS.getsize() + 1);
            pos1.setY(rand()%GS.getsize()+ 1);
        }
        GS.FixeCase(pos1.getX(),pos1.getY(),k);
        Plys[k]=pos1 ;
    }
    ActivePlayer=rand()%NbPlayers+1 ;

}
void IsolaGame::DisplayGame()
{
    GS.DisplayGameSpace();
    cout<<(ActivePlayer<=NbPlayers-NbIAmachines?" Active Player :":" Active IAmachine : ")<<ActivePlayer<<endl;
}
void IsolaGame::GivePlayerTurn()
{
    ActivePlayer++ ;
    if(ActivePlayer > NbPlayers)
    {
        ActivePlayer=1 ;
    }
}
void IsolaGame::SwitchCase(GameSpace& ech ,const Position& pos1,const Position& pos2)
{
    int aux=ech.GetCase(pos1.getX(),pos1.getY());
    ech.FixeCase(pos1.getX(),pos1.getY(),ech.GetCase(pos2.getX(),pos2.getY()));
    ech.FixeCase(pos2.getX(),pos2.getY(),aux);
}
void IsolaGame::MovePlayerInGame()
{
    Position oldpos=Plys[ActivePlayer];
    Position newpos;
    newpos=oldpos.GetNewMovmentOfCase(GS);
    SwitchCase(GS,oldpos,newpos);
    Plys[ActivePlayer]=newpos;

}
Position IsolaGame::AskForCaseToDestroy()
{
    Position pos ;
    int x1,y1 ;
    while(!(pos.CaseValidation(GS,1)&&pos.CaseValidation(GS,0)))
    {
        cout<<"Case to destroy ? :"<<endl ;
        cin>>x1>>y1 ;
        pos.setX(x1) ;
        pos.setY(y1) ;
    }
    return(pos) ;
}
void IsolaGame::DestroyCase(GameSpace& ech ,const Position& pos)
{
    ech.FixeCase(pos.getX(),pos.getY(),IsDestroyed) ;
}
void IsolaGame::DestroyCaseInGame()
{
    Position pos=AskForCaseToDestroy();
    DestroyCase(GS,pos);
}
bool IsolaGame::EndGame()
{
    Position pos=Plys[ActivePlayer] ;
    return(pos.BlockedCase(GS)) ;
}


void IsolaGame::MovePlayerInGameIA()
{
    Position oldpos=Plys[ActivePlayer] ;
    Position newpos;
    if(ActivePlayer<=NbPlayers-NbIAmachines)
    {
        //un jouer normal
        newpos=oldpos.GetNewMovmentOfCase(GS);
        cout<<newpos.getX()<<newpos.getY()<<endl ;
    }
    else
    {
        //le jouer machine
        newpos=oldpos.FindOptimalNeighborCase(GS);
    }
    SwitchCase(GS,oldpos,newpos);
    Plys[ActivePlayer]=newpos ;


}
Position IsolaGame::FindCaseToDestroyIA()
{
    Position ActualPos ;
    Position PosToDestroy ;
    int test = 1 ;

    while(test)
    {

        int nbrofplayer=(NbPlayers==2 ? 1 : rand()%(NbPlayers-NbIAmachines)+1) ; // s'il ya 2 joueurs : 1 joueur normal et une machine le IAmachine va concentrè sur ce joueur si on a plusieur joueurs normal on choisie aleatoirement parmie ces joueur
        ActualPos=Plys[nbrofplayer] ;
        PosToDestroy=ActualPos.FindOptimalNeighborCase(GS) ;
        //pour le teste
        cout<<"IAplayer  is destroying: "<<nbrofplayer<<" :("<<PosToDestroy.getX()<< ","<<PosToDestroy.getY()<<") "<<endl ;
        system("pause");
        test=(PosToDestroy.getX()==ActualPos.getX())&&(PosToDestroy.getY()==ActualPos.getY()) ;
    }
    return(PosToDestroy);

}
void IsolaGame::IADestroyCaseInGame()
{
    Position postodestroy;
    if(ActivePlayer<=NbPlayers-NbIAmachines)
    {
        postodestroy=AskForCaseToDestroy();
    }
    else
    {
        postodestroy=FindCaseToDestroyIA();
    }
    DestroyCase(GS,postodestroy);
}

int IsolaGame::getActivePlayer() const {
    return ActivePlayer;
}

//***************Minimax algo*******************
GameSpace IsolaGame::FutureGameSpace(GameSpace oldGameSpace , int wayToMove,Position activeplayerpos) {
    Position posnew = activeplayerpos.GetNeighborPos(wayToMove) ; // on a retournè une nouvelle position selon la direction entrè en parametre
    Position posold = activeplayerpos ; //pour conservè l'ancien position
    SwitchCase(oldGameSpace,posnew,posold) ;  //une nouvelle etat de jeu
    GameSpace GSclown = oldGameSpace ;//l'instance GSclown est une variable auxiliaire
    SwitchCase(oldGameSpace,posold,posnew) ; //game state prendre son etat initial
       return (GSclown) ;

}
int IsolaGame::NbrGetEmptyCases() {
    vector<Position> empty ;
    for(int i=1;i<=GS.getsize();i++){
        for(int j=1;j<=GS.getsize();j++) {
            if (GS.GetCase(i,j) == 0)
            {
                Position pos(i,j) ;
                empty.push_back(pos) ;

            }
        }
    }
    return(empty.size()) ;

}
float IsolaGame::GetHeuristicOfGameState(Position activeplayerpos,Position opponentplayerpos ,GameSpace G) {
    float score = 0 ;
    //le nombre des movements lègal pour les joueurs
   int player_moves,opponent_moves ;
    player_moves=activeplayerpos.ListOfPlayerLegalMoves(G);
    opponent_moves=opponentplayerpos.ListOfPlayerLegalMoves(G) ;
    //s'il reste 60% espace vide dans le GameSpace , le bot devient plus agressive c.a.d l'heuristicscore devient 3 fois plus agressive que le joueur normal
    if(NbrGetEmptyCases() >= (ceil((G.getsize()*G.getsize()-2)*0.6)))
    {
        score=player_moves-(3*opponent_moves) ;
    }
    //s'il reste plus de 30% espace vide dans le  GameSpace , le bot devient plus agressive c.a.d l'heuristicscore devient 2 fois plus agressive que le joueurs normal
    else if(NbrGetEmptyCases() >= (ceil((G.getsize()*G.getsize()-2)*0.3)))
    {
        score=player_moves-(2*opponent_moves) ;
    }
    //s'il reste moins de 30% espace vide dans le  GameSpace , le bot joue d'une maniere normal
    else
    {
        score= score=player_moves-opponent_moves;
    }
    return(score) ;
}
float IsolaGame::maxval( GameSpace G ,Position activeplayerpos,Position oppenentplayerpos , int depth , float alpha , float beta) {
    float max_score=-numeric_limits<float>::infinity() ;
    float min_score ;
    if(depth == 0 || activeplayerpos.ListOfPlayerLegalMoves(G)==0) //si le "depth" de l'arbre = 0 ou "given player" n'admet pas l'accees à des movements on va retournè le score
    {
        return GetHeuristicOfGameState(activeplayerpos,oppenentplayerpos,G) ;
    }
   vector<Position> legal_moves = activeplayerpos.ListOfPlayerLegalMoves1(G) ;
    for(int i=0 ; i<legal_moves.size();i++)
    {
        min_score=minval(FutureGameSpace(G,i,activeplayerpos),activeplayerpos,oppenentplayerpos,depth-1,alpha,beta) ;
        max_score=max(max_score,min_score) ;
        if(max_score >= beta)
        {}
        else
        {
            alpha=max(alpha,max_score) ;
        }
    }
    return (max_score) ;
}
float IsolaGame::minval(GameSpace G, Position activeplayerpos , Position oppenentplayerpos , int depth , float alpha , float beta ) {
    float min_score = numeric_limits<float>::infinity() ;
    float max_score ;
    if(depth == 0 || activeplayerpos.ListOfPlayerLegalMoves(G)==0) //si le "depth" de l'arbre= 0 ou "given player"  n'admet pas l'accees à des movements on va retournè le score
    {
        return GetHeuristicOfGameState(activeplayerpos,oppenentplayerpos,G) ;
    }
    vector<Position> legal_moves = activeplayerpos.ListOfPlayerLegalMoves1(G) ;
    for(int i=0 ; i<legal_moves.size();i++)
    {
        max_score =maxval(FutureGameSpace(G,i,activeplayerpos),activeplayerpos,oppenentplayerpos,depth-1,alpha,beta) ;
        min_score=min(min_score,max_score) ;
        if(min_score <= alpha)
        {}
        else
        {
            beta=min(beta,min_score) ;
        }
    }

    return min_score ;

}
Position IsolaGame::MiniMaxWithAlphaBetaPruning( GameSpace G , Position activeplayerpos ,Position oppenentplayerpos , int depth, float alpha, float beta) {
    float best_score = -numeric_limits<float>::infinity() ;
    Position best_pos ;
    float min_score ;
    // itha move legale recursively loop recursively loop mining and maxing 7ata tousel lel depyh li t3ada en entre ba3 tarja3 berweli 7ata tkaml les appel recursive teha
    // 5arej legale moves
    vector<Position> legal_moves = activeplayerpos.ListOfPlayerLegalMoves1(G) ;

    for(int i=0 ; i<legal_moves.size();i++)
    {
        min_score=minval(FutureGameSpace(G,i,activeplayerpos),activeplayerpos,oppenentplayerpos,depth-1,alpha,beta) ;
        if(min_score>best_score)
        {
            best_score = min_score ;
            best_pos=legal_moves[i] ;
        }
        if (best_score >= beta)
        {}
        else{
            alpha=max(alpha,best_score) ;
        }
    }

    return best_pos ;

}
void IsolaGame::MovePlayerInGameIAWithMiniMax()
{
    Position oldpos=Plys[ActivePlayer] ;
    Position newpos;
    if(ActivePlayer<=NbPlayers-NbIAmachines)
    {
        //un joueur normal
        newpos=oldpos.GetNewMovmentOfCase(GS);
        cout<<newpos.getX()<<newpos.getY()<<endl ;
    }
    else
    {
        //le joueur machine
        // on travaille par le "depth" = 6 c.a.d la profondeur de l'arbre est 6 et alpha = -infinity et beta = +infinity
        cout<< "im minimax bot ^_^ "<<endl ;
        newpos=MiniMaxWithAlphaBetaPruning(GS,Plys[ActivePlayer],Plys[ActivePlayer-1],6,-numeric_limits<float>::infinity(),numeric_limits<float>::infinity()) ;
    }
    SwitchCase(GS,oldpos,newpos);
    Plys[ActivePlayer]=newpos ;


}
void IsolaGame::IADestroyCaseInGameMiniMax()
{
    Position postodestroy;
    if(ActivePlayer<=NbPlayers-NbIAmachines)
    {
        postodestroy=AskForCaseToDestroy();
    }
    else
    {
        int nbrofplayer=(NbPlayers==2 ? 1 : rand()%(NbPlayers-NbIAmachines)+1) ;
        postodestroy=MiniMaxWithAlphaBetaPruning(GS,Plys[ActivePlayer-1],Plys[ActivePlayer],6,-numeric_limits<float>::infinity(),numeric_limits<float>::infinity()) ;

    }

    DestroyCase(GS,postodestroy);
}
