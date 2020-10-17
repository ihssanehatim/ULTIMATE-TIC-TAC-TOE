# ULTIMATE-TIC-TAC-TOE
--------------------
DÉROULEMENT DU JEU :
--------------------
Lorsqu’un  joueur  joue  dans  une  case  d’un inner-tictactoe, le  joueur  suivant  doit  jouer alors dans le inner-tictactoe correspondant  à la case jouée précédemment . Si  le  joueur  bleu  a  joué  la  case  en  bas  à droite  d’un  inner-tictactoe,  le  joueur  vert doit jouer dans le inner-tictactoe en bas à droite . Ainsi de suite ...Si l’inner-tictactoe dans lequel un joueur doit jouer  est  déjà  achevé  (gagné  par  quelqu’un ou  match  nul),  le  joueur  en  question  peut jouer où il veut .
--------------------
FIN DU JEU         :
--------------------
Un *inner-tictactoe* remporté par un joueur lui permet d’obtenir la case correspondante  dans  le  outer-tictactoe .
Si  un  joueur  aligne  trois  cases dans  le  outer-tictactoe,  il  est  le gagnant de la partie .

-------------------------

Les erreurs seront toutes gérées via des assertions que l’on pourra désactiver dans la version finale de notre jeu.
On utilisera trois constantes nommées pour coder une réponse négative, une réponse positive et une réponse presque bonne à l’aide de e_status
``` c
typedef enum {   
    NO,         // une réponse négative
    YES,        // une réponse positive
    ALMOST,     // une réponse presque bonne 
}e_status;
```

Les joueurs seront représentés à l’aide de e_player 

``` c
typedef enum 
{
    PLAYER_O = 'O',
    PLAYER_X = 'X',
    NOBODY = ' ',
    BOTH = '#'
}e_player ;

```
Les positions seront représentés à l’aide de e_location
``` c
typedef enum {
    TOPLEFT,   // Case de gauche sur la ligne du haut  
    TOPCENTER, // Case du milieu sur la ligne du haut   
    TOPRIGHT,  // Case de droite sur la ligne du haut   
    MIDLEFT,   // Case de gauche sur la ligne du milieu   
    MIDCENTER,  // Case du milieu sur la ligne du milieu   
    MIDRIGHT,        // Case de droite sur la ligne du milieu   
    BOTTOMLEFT,      // Case de gauche sur la ligne du bas   
    BOTTOMCENTER,   // Case du milieu sur la ligne du bas   
    BOTTOMRIGHT,    // Case de droite sur la ligne du bas   
    FREE,           // N’importe quelle case   
    NONE            // Aucune des cases 
}e_location;

```
Un tictactoe est représenté par un s_tictactoe
``` c
typedef struct{
    e_player *content;
    // un tableau de TICTACTOE_SIZEe_player
    // correspondant aux cellules de haut gauche                                 
    // vers bas droit 
    e_player winner ; 
    // le gagnant du tic-tac-toe, BOTH en cas de    
    // jeu nul, NOBODY sinon

}s_tictactoe;

```
------------------------------------
Les coups seront représentés à l’aide de s_move

``` c
typedef struct{
    e_location inner_position;
    //La position dans le inner-tictactoe   e_locationouter_position;
    //La position dans le outer-tictactoe   
    e_player player ;    
    //Le joueur jouant le coup 
    }s_move;
```

Un historique des coups joués sera stocké grâce à une liste simplement chaînée de s_move

``` c
typedef struct list
{ 
    s_move*last_move;
    struct list *next; 
} list_element_s_move;

// La liste vide étant représentée par un pointeur NULL
```