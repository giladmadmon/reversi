//
// Created by gilad on 11/19/17.
//

#include "AIPlayer.h"
#include <cstdlib>
#include <cstdio>
AIPlayer::AIPlayer(string &name, Board &board, Logic &logic) : Player(name), board_(board), logic_(logic) {

}

int AIPlayer::GetGrade(Position &position, Board board, PlayerColor color) {
  PlayerColor player_color = color;
  PlayerColor rival_color = OtherColor(player_color);
  vector<Position> rival_moves;
  int max_grade = INT_MIN;

  logic_.PlaceAToken(player_color, position.GetRow(), position.GetColumn(), board);
  rival_moves = logic_.PossibleMoves(rival_color, board);

  for (vector<Position>::iterator it = rival_moves.begin(); it != rival_moves.end(); ++it) {
    int current_grade = GetTokensDifference(*it, rival_color, board);
    if (current_grade > max_grade) {
      max_grade = current_grade;
    }
  }

  return max_grade;
}

int AIPlayer::GetTokensDifference(Position &position, PlayerColor color, Board board) {
  logic_.PlaceAToken(color, position.GetRow(), position.GetColumn(), board);
  return board.CountColor(color) - board.CountColor(OtherColor(color));
}

Position AIPlayer::MakeAMove(vector<Position> &possible_moves, Printer &printer, PlayerColor color) {
  if (possible_moves.size() > 0) {
    vector<Position> min_positions;
    int min_grade = INT_MAX;

    for (vector<Position>::iterator it = possible_moves.begin(); it != possible_moves.end(); ++it) {
      int current_grade = GetGrade(*it, board_, color);
      if (current_grade < min_grade) {
        min_grade = current_grade;
        min_positions.clear();
      }

      if (current_grade == min_grade) {
        min_positions.push_back(*it);
      }
    }

    if (min_positions.size() > 1) {
      srand(static_cast<unsigned int>(time(NULL)));
      Position random_position = min_positions[rand() % min_positions.size()];
      printer.PrintMove(random_position, color);
      return random_position;
    } else {
      printer.PrintMove(*min_positions.begin(), color);
      return *min_positions.begin();
    }
  }

  printer.PrintAINoMove(color);
  return Position(-1, -1);
}
