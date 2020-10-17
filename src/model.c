#include "model.h"

s_move *create_empty_move(){

    s_move* move = (s_move*)malloc(sizeof(s_move));

    if (move==NULL)
    {
        return NULL;
    }
    else{
        move->inner_position=FREE;
        move->outer_position=FREE;
        move->player=NOBODY;

        return move;
    }

}

 

s_tictactoe * create_empty_tictactoe(){
    int i ;
    s_tictactoe* utt = (s_tictactoe*)malloc(sizeof(s_tictactoe));

    if (utt==NULL){
        return NULL;
    }

    /// all cells of tictactoe
    utt->content = (e_player *)malloc(TICTACTOE_SIZE*sizeof(e_player));

    if (utt->content==NULL) {
        free(utt);
        return NULL;
    }

    utt->winner=NOBODY; // the winner is set to nobody

    /// now setting content cells to nobody :

    for( i = 0 ; i < TICTACTOE_SIZE ; i++ )
    utt->content[i] = NOBODY ;

    return utt;
    
}

/// 9

s_utictactoe * create_empty_utictactoe(uint inception_level){

    int i;
    s_utictactoe* uttt = (s_utictactoe*)malloc(sizeof(s_utictactoe));
    if (uttt==NULL){
        return NULL
    }


    s_tictactoe * ottt = create_empty_tictactoe();
    if (ottt==NULL){
        return NULL
    }
    
    /// outer tictactoe :
    uttt->outer_tictactoe=ottt;

    if (inception_level < 1 || inception_level > 3 ){
        inception_level = 2 ; /// assign a default level which is 2 ;
    }

        uttt->inception_level = inception_level;

        /// size du tableau des inner tictactoes :
        int number_of_inners = uttt->inception_level*uttt->inception_level;
        
        /// an inner tictactoes depend on the inception_level

        if (uttt->inception_level != 1) {

            uttt->inner_tictactoes = (s_tictactoe*)malloc(sizeof(s_tictactoe)*number_of_inners);
        
            /// each inner tictactoe should be initialized :
            if (uttt->inner_tictactoes == NULL)
            {
                return NULL ;
            }
    
            for(i = 0 ; i < number_of_inners ; i++)
            {
                uttt->inner_tictactoes[i] = create_empty_tictactoe();
            }
        }
        else /// if (uttt->inception_level == 1)
        {
            uttt->inner_tictactoes = NULL ;
        }
        
        uttt->history=NULL;

        return uttt;
    
    /*
    else if (inception_level==2)
    {   
        int* Lp[TICTACTOE_SIZE] = (int)malloc(TICTACTOE_SIZE*sizeof(int)); //Liste des pointeurs menant à des s_tictactoe 

        if (LP==NULL){
            return NULL
        }

        int cpt=0;

        for (cpt = 0; cpt < TICTACTOE_SIZE; cpt++)
        {
            s_tictactoe *ittt = (s_tictactoe)malloc(sizeof(s_tictactoe)); //allocation memoire s_tictatoe
            if (ittt==NULL){
            return NULL;
            }
            s_tictactoe* ittt=create_empty_tictactoe(); //création s_tictacktoe vide
            Lp[cpt]=ptr; //stockage pointeur 
        }

        uttt.inception_level=2;
        uttt.inner_tictactoes=Lp;
        uttt.outer_tictactoe=ottt;
        uttt.history=NULL;
        return uttt;
    }
    else
    {
        return NULL;
    }*/
        

}

void free_move(s_move *p_move){
 
    if (p_move==NULL){
        return ;
    }
    
    free(p_move);
}

void free_tictactoe(s_tictactoe *p_ttt){

    if (p_ttt==NULL){
        return ;
    }

    free(p_ttt->content);
    // free(p_ttt->winner);
    free(p_ttt);

}



void free_utictactoe(s_utictactoe *p_uttt){
    if (p_uttt==NULL){
        return ;
    }
    
    free(p_uttt->history);

    if (p_uttt->inception_level==1){
        free_tictactoe(p_uttt->outer_tictactoe);
    }
    else{

        free_tictactoe(p_uttt->outer_tictactoe);
        free_tictactoe(p_uttt->inner_tictactoes);

        /*
        int cpt =0;
        for (cpt = 0; cpt < TICTACTOE_SIZE; cpt++)
        {
            free_tictactoe(p_uttt->inner_tictactoe[cpt]);
        }
       // free(p_uttt->inception_level);
       */
    }
    
    free(p_uttt);
    
}

e_player get_next_player_to_play(s_utictactoe *p_uttt){

    
    if ((p_uttt->history->last_move->player==PLAYER_O)||(p_uttt->history->last_move==NULL) ){
        return PLAYER_X;
    }
    else if ((p_uttt->history->last_move->player==PLAYER_O)||(p_uttt->history->last_move->player==NOBODY)){
        return PLAYER_O;
    }
}


e_location get_next_outer_position(s_utictactoe *p_uttt){
    if(p_uttt->inception_level==1){
        if (p_uttt->outer_position->winner==NOBODY){
            return FREE;
        }
        else{
            return NONE;
        }
            
    }
    else if(p_uttt->inception_level >= 2){
        
        if (p_uttt->outer_tictactoe->winner==NOBODY){

            if (p_uttt->inner_tictactoe[p_uttt->history->last_move->outer_position]->winner==NOBODY)
            {
                return p_uttt->history->last_move->outer_position;
            }
            else
            {
                return FREE;
            }
            
        }
        else{
            return NONE;
        }
    }    

}

e_status is_move_valid(s_utictactoe *p_uttt, s_move *p_move){
   
    if (inception_level==1){

        if ((get_next_player_to_play(p_uttt) == p_move->player)
        &&(p_uttt->outer_tictactoe->winner ==NOBODY )
        &&(p_uttt->outer_tictactoe[p_move->outer_position]==NOBODY)) 
        {
            return YES;
        }
        else
        {
        return NO;
        }
    }
    else if (inception_level >= 2)
    {
        if ((get_next_player_to_play( p_uttt)== p_move->player)
        &&(p_uttt->outer_tictactoe->winner ==NOBODY )
        &&(p_uttt->inner_tictactoe[p_move->outer_position]->content[p_move->inner_position] ==NOBODY )
        &&(p_uttt->inner_tictactoe[p_move->outer_tictactoe]->winner ==NOBODY)) 
        {
            return YES;
        }
        else
        {
            return NO;
        }
    }

}

void set_tictactoe_winner(s_tictactoe *p_ttt){

    if (p_ttt->winner==NOBODY){
        
    for(int cpt = 0 ; cpt < TICTACTOE_WIDTH ; cpt++)
    {
        if((p_ttt->content[cpt]==p_ttt->content[cpt+3]==p_ttt->content[cpt+6])&&(p_ttt->content[cpt]!=NOBODY)) //Colonne
        {
            p_ttt->winner=p_tt->content[cpt];
        }
        int case = cpt*3 ;
        if((p_ttt->content[case]==p_ttt->content[case+1]==p_ttt->content[case+2])&(p_ttt->content[cpt]!=NOBODY)) //Ligne
        {
            p_ttt->winner=p_tt->content[cpt];
        }
    }
                    
        if((p_ttt->content[0]==p_ttt->content[4]=p_ttt->content[8])&&(p_ttt->content[cpt]!=NOBODY) //Diagonale 2
        {
            p_ttt->winner=p_tt->content[0];

        }
        if((p_ttt->content[2]==p_ttt->content[4]=p_ttt->content[6])&(p_ttt->content[cpt]!=NOBODY)//Diagonale 1
        {
            p_ttt->winner=p_tt->content[2];
            

        }
    }
}
e_status play_move(s_utictactoe *p_uttt, s_move *p_move){
    
    if (is_move_valid==YES){

        if(p_uttt->inception_level==1){
            
            p_uttt->outer_position->content[p_move->outer_position]=p_move->e_player;
            set_tictactoe_winner(p_uttt);
            return YES;
        }
        else if(p_uttt->inception_level>=2)
        {
            p_uttt-> inner_tictactoes[p_move->outer_position]->content[p_uttt->inner_position]=p_move->e_player;

            set_tictactoe_winner(p_uttt-> inner_tictactoes[p_move->outer_position]);

            if (p_uttt-> inner_tictactoes[p_move->outer_position]->winner!=NOBODY)
            {  //si le move est gagnant on met à jour le outer_tictactoe
                p_uttt->outer_tictactoe->content[p_move->outer_position]==p_move->player;

                set_tictactoe_winner(p_uttt-> outer_tictactoe);

                return YES;
            }

                return NO;
        else 
            return NO;
            
    }
    else{
        return NO;
    }

}
