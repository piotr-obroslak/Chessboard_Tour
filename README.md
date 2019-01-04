# Chessboard_Tour
My solution to the knight's tour problem. No recursion is used - consecutive knight's positions are put on/popped from a stack instead.
The solution contains two versions:
  1. the regular one
  2. one that uses Warnsdorf's rule: the knight is moved so that it always proceeds to the square from which the knight will have the fewest onward moves. Using such heuristic makes the problem solvable in linear time.
  
The code is constructed in a way than allows solving the problem for other figures as well. But... for all the chess' figures except knight the problem is solvable in linear time (e.g. queen or rook) or not solvable at all (e.g. pawn or bishop). Because of this I've added a definition of an artificial figure called superking which can "jump" to the nearest square in the top, left and top-left directions and to the square distant by 2 moves in the bottom, right and bottom-right directions.
