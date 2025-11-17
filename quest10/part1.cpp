#include "common.cpp"
#include <set>


std::__1::vector<std::pair<int,int>> findPossibleMoves(std::__1::vector<std::__1::string>& board, std::pair<int,int> dragon)
{
    // 2 + 1
    std::__1::vector<std::pair<int,int>> moves;

    moves.push_back(std::pair<int,int>(dragon.first - 2, dragon.second -1 ));
    moves.push_back(std::pair<int,int>(dragon.first - 2, dragon.second +1 ));
    moves.push_back(std::pair<int,int>(dragon.first + 2, dragon.second -1 ));
    moves.push_back(std::pair<int,int>(dragon.first + 2, dragon.second +1 ));
    moves.push_back(std::pair<int,int>(dragon.first - 1, dragon.second -2 ));
    moves.push_back(std::pair<int,int>(dragon.first - 1, dragon.second +2 ));
    moves.push_back(std::pair<int,int>(dragon.first + 1, dragon.second -2 ));
    moves.push_back(std::pair<int,int>(dragon.first + 1, dragon.second +2 ));

    return moves;
}

void eatSheep(std::set<std::pair<int,int>>& eaten, std::__1::vector<std::__1::string>& board, std::pair<int,int> dragon, int moves)
{
    if (moves == 0) return;

    auto width = board[0].size();
    auto height = board.size();

    auto possibleMoves = findPossibleMoves(board, dragon);
    for (auto& possibleMove : possibleMoves)
    {
        if (possibleMove.first >= 0 && possibleMove.first < width && possibleMove.second >= 0 && possibleMove.second < height)
        {
            if (board[possibleMove.second][possibleMove.first] == 'S')
            {
                eaten.insert(possibleMove);
            }
        }
        eatSheep(eaten, board, possibleMove, moves-1);
    }
}

int main()
{
    auto board = readLinesFromFile("input1.txt");
    auto width = board[0].size();
    auto height = board.size();

    std::pair<int,int> dragon(-1,-1);

    for(auto r=0; r<height; r++)
    {
        for(auto c=0; c<width; c++)
        {
            if (board[r][c] == 'D')
            {
                dragon.first = c;
                dragon.second = r;
                break;
            }
        }        
        if (dragon.first != -1) break;
    }


    std::set<std::pair<int,int>> eaten;
    eatSheep(eaten, board, dragon, 4);

    std::cout << eaten.size() << std::endl;


}