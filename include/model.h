#ifndef MODEL_H
#define MODEL_H
#include "common.h"

#define MIN_BOARD_LEVEL 1
#define MAX_BOARD_LEVEL 2


// Constant character to represent the cross player, the round, none or both of
// them (this last one is usefull for tie game)
typedef enum {
  PLAYER_O = 'O',
  PLAYER_X = 'X',
  NOBODY = ' ',
  BOTH = '#'
} e_player;

// Constant defining the 9 possible positions in a tic tac toe, any of this
// position and none of this position
typedef enum {
  TOPLEFT,
  TOPCENTER,
  TOPRIGHT,
  MIDLEFT,
  MIDCENTER,
  MIDRIGHT,
  BOTTOMLEFT,
  BOTTOMCENTER,
  BOTTOMRIGHT,
  FREE,
  NONE
} e_location;

#define TICTACTOE_SIZE 9
#define TICTACTOE_WIDTH 3

// The tic tac toe structure
typedef struct {
  e_player *content;  // array of TICTACTOE_SIZE e_player defining content of
                      // each the TICTACTOE_SIZE cells of a tic tac toe defined
                      // from top left to bottom right
  e_player winner;  // player who have won the tic tac toe game; BOTH in case of
                    // a tie game
} s_tictactoe;

// A move structure
typedef struct {
  e_location inner_position;  // The position in the inner tic tac toe
  e_location outer_position;  // The position in the outer tic tact toe
  e_player player;           // The player who achieve the move
} s_move;

// A simple linked list of s_move
typedef struct list {
  s_move *last_move;
  struct list *next;
} list_element_s_move;

// The ultimate tic tac toe structure
typedef struct {
  uint inception_level;  // inception level of the ultimate tictactoe
  s_tictactoe *
      *inner_tictactoes;  // array of the TICTACTOE_SIZE inner tic tac
                          // toes defining content of each the
                          // TICTACTOE_SIZE cells of an ultimate tic tac
                          // toe defined from top left to bottom right
  s_tictactoe *
      outer_tictactoe;  // a tic tac toe representing the outer game which
                        // allows to store the winners of each inner tic tac toe
  list_element_s_move *history;  // full history of the played moves as a stack
                                 // of s_moves - LIFO ended by a NULL pointer.
} s_utictactoe;
/*
 * A uttt of inception-level 1 just correspond to the outer_tictactoe while
 * inner_tictactoes is NULL
 *
 * A uttt of inception-level 2 is an array of TICTACTOE_SIZE tictactoes from
 * TOP_LEFT to BOTTOM_RIGHT and outer_ticatactoe represent the overall game
 * Example of indices for a uttt of inception-level 1
 * 0|1|2
 * -----
 * 3|4|5
 * -----
 * 6|7|8
 */

/*!
 * This function allocates an s_move structure corresponding to an empty move
 * (free positions and nobody as player).
 *
 * \return a reference to the s_move memory space allocated, NULL in case of
 * allocation problem.
 */
s_move *create_empty_move();

/*!
 * This function allocates an s_tictactoe structure corresponding to an empty
 * tictactoe ready to be played.
 *
 * \return a reference to the s_tictactoe memory space allocated, NULL in case
 * of allocation problem.
 */
s_tictactoe *create_empty_tictactoe();

/*!
 * This function allocates an s_utictactoe structure corresponding to an empty
 * utictactoe of the corresponding inception_level and ready to be played
 * starting by PLAYER_X player.
 *
 * \return a reference to the s_utictactoe memory space allocated, NULL in case
 * of allocation problem.
 */
s_utictactoe *create_empty_utictactoe(uint inception_level);

/*!
 * This function free all the memory used by a given s_move which reference is
 * given.
 *
 * \param p_move a pointer on a s_move to be freed.
 */
void free_move(s_move *p_move);

/*!
 * This function free all the memory used by a given tictactoe structure which
 * reference is given.
 *
 * \param p_ttt a pointer on a s_tictactoe to be freed.
 */
void free_tictactoe(s_tictactoe *p_ttt);

/*!
 * This function free all the memory used by a given ultimate tictactoe
 * structure which reference is given.
 *
 * \param p_uttt a pointer on a s_utictactoe to be freed.
 */
void free_utictactoe(s_utictactoe *p_uttt);

/*!
 * This function determines the e_player which should be the next player to play
 * in the corresponding p_uttt.
 *
 * \param p_uttt a pointer on a s_utictactoe.
 * \return a e_player (PLAYER_X - if last player who played was PLAYER_O or its
 * the first move, PLAYER_O - if last player who played was PLAYER_X, or NOBODY
 * if no move can be done anymore or if there is a winner).
 */
e_player get_next_player_to_play(s_utictactoe *p_uttt);

/*!
 * This function determines the next outer position where the current player
 * should play its next move in the corresponding p_uttt.
 *
 * \param p_uttt a pointer on a s_utictactoe.
 * \return a e_location corresponding to the next outer position induced by the
 * last move
 * - set to FREE if the next move is free of constraints
 */
e_location get_next_outer_position(s_utictactoe *p_uttt);

/*!
 * This function evaluate if a move is valid in the corresponding p_uttt.
 * A move is valid if its player and the inner and outer positions are
 * consistent with the current s_utictactoe: correct unused position, not a
 * tictactoe with already a winner and the correct player. It returns a boolean
 * corresponding to the success of the move.
 *
 * \param p_uttt a pointer on a s_utictactoe.
 * \param a_move an s_move to be played.
 * \return YES if playing a_move was possible - NO if impossible.
 */
e_status is_move_valid(s_utictactoe *p_uttt, s_move *p_move);

/*!
 * This function set the winner of the corresponding p_ttt.
 *
 * \param p_ttt a pointer on a s_tictactoe whose winner field will be updated.
 */
void set_tictactoe_winner(s_tictactoe *p_ttt);

/*!
 * This function tries to play a given move in the corresponding p_uttt.
 * It plays the corresponding move if possible and returns a boolean
 * corresponding to the success of the move. The function should set the
 * possible winner.
 *
 * \param p_uttt a pointer on a s_utictactoe.
 * \param p_move an s_move to be played.
 * \return YES if playing a_move was possible - NO if impossible.
 */
e_status play_move(s_utictactoe *p_uttt, s_move *p_move);

/*Given usefull functions*/
void draw_utictactoe(s_utictactoe *p_uttt);
void draw_utictactoe_history(s_utictactoe *p_uttt);
#endif /* MODEL_H */