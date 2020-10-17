#include "utictactoe.h"
#include "common.h"
#include "model.h"

int main(int argc, char *argv[]){
    
    int optc;
    
    static struct option long_opts[]={
        {"help", no_argument, 0, 'h'},
        {"version", no_argument, 0, 'V'},
        {"verbose", no_argument, 0, 'v'},
        {"inception-level", required_argument, 0, 'i'},
        {"cross-ai", required_argument, 0, 'x'},
        {"white-ai", required_argument, 0, 'o'},
        {"contest", required_argument, 0, 'c'},
    };

    const char* shortopts="hVvi:x:o:c:";

    const char* patht="utictactoe.h";
    
    bool verbose = false;

    bool contest_mode=false;

    size_t board_level =2;

    int tactic_to_use = 0;

    while ((optc = getopt_long (argc, argv, shortopts, long_opts, NULL)) != -1)
    {

        switch (optc) {
        
        case 'h':/*help option */
        printf("Usage: utictactoe ([-i LEVEL|-x N|-o N|-v|-V|-h] | -c FILE)\nPlay a utictactoe game with human or program players.\n-i, --inception-level LEVEL deepness of the game (min=1, max=3(default=2))\n-x, --cross-ai N set tactic of cross player 'X'\n-o, --round-ai N set tactic of round player 'O'\n-c, --contest enable 'contest' mode\n-v, --verbose verbose output\n-V, --version display version and exit\n-h, --help display this help and exit\nTactics list: random (0), clever (1)\n");
        break;

        case 'V': /* version option */
        printf ("utictactoe %d.%d.%d \n",VERSION,SUBVERSION,REVISION);
        printf( "This software allows to play to ultimate tictactoe game.\n");
        break;
        
        case 'v': /* verbose option */
        verbose = true;
        break;

        case 'i':
        if (atoi(optarg) == 1 || atoi(optarg) == 2 || atoi(optarg) == 3) {
            board_level= atoi(optarg);
        }
        else{
            printf("taille non valide");
            exit (EXIT_FAILURE);
        }
        break;
        
        case 'x':
        if (atoi(optarg)==0 || atoi(optarg)==1 ) {
            tactic_to_use= atoi(optarg);
        }
        else{
            printf("argument non valide");
            exit (EXIT_FAILURE);
        }
        break;

        case 'o':
        if (atoi(optarg)==0 || atoi(optarg)==1 ) {  
            tactic_to_use= atoi(optarg); 
        }
        else{
            printf("argument non valide");
             exit (EXIT_FAILURE);
        }
        break;

        case 'c':
        if (optarg != NULL ) {

            if (access(patht, R_OK) == 0) {

                contest_mode=true;
                printf("le fichier est lisible\n");  
            }
            else {
                printf("le fichier  n'est pas lisible\n");
                exit (EXIT_FAILURE);
            }
        }
        else {

            printf("il manque un argument\n"); 
            exit (EXIT_FAILURE);
        }

        default :
        printf("Try `utictactie --help' for more information.");    
        break;

        default:

            exit (EXIT_FAILURE);
        }
    //CODE DE TEST FAIT PAR LE PROFESSEUR
    s_move *test_move = create_empty_move();
    free_move(test_move);
    s_tictactoe *test_ttt = create_empty_tictactoe();
    free_tictactoe(test_ttt);
    s_utictactoe *test_uttt = create_empty_utictactoe(1);
    free_utictactoe(test_uttt);
    test_uttt = create_empty_utictactoe(2);
    free_utictactoe(test_uttt);
    test_uttt = create_empty_utictactoe(3);
    free_utictactoe(test_uttt);

    srand(time(NULL));
    s_utictactoe *s = create_empty_utictactoe(1); //replace by 2 for uttt play
    s_move *m = create_empty_move();
    m->outer_position = TOPLEFT + rand() % TICTACTOE_SIZE;
    while (s->outer_tictactoe->winner == NOBODY) {
        draw_utictactoe(s);
        m->player = get_next_player_to_play(s);
        m->inner_position = TOPLEFT + rand() % TICTACTOE_SIZE;
        play_move(s, m);
        m->outer_position = m->inner_position;
    }
    draw_utictactoe(s);
    draw_utictactoe_history(s);
    printf("The winner is : %c\n", s->outer_tictactoe->winner);
    free_move(m);
    free_utictactoe(s);
    //FIN CODE DE TEST

    exit(EXIT_SUCCESS);     
    }
}