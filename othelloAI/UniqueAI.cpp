//  Copyright © 2016 Oh Jun Kwon. All rights reserved.

#include <ics46/factory/DynamicFactory.hpp>
#include "UniqueAI.hpp"

ICS46_DYNAMIC_FACTORY_REGISTER(OthelloAI, kwonoj::UniqueAI, "uNiQuE aI (Required)");

int color_identity(const OthelloGameState& state){
    int check;
    if (state.isBlackTurn()){
        check=1;
    }
    if (state.isWhiteTurn()){
        check=0;
    }
    return check;
}


int eval(const OthelloGameState& state, bool playerisblack){
    int result;
    if (playerisblack){
        result = state.blackScore() - state.whiteScore();
    }
    else{
        result = state.whiteScore() - state.blackScore();
    }
    return result;
}

void update(int x, int y, int& currentscore, int& bestscore, std::pair<int,int>& mymove){
    if (currentscore > bestscore){
        bestscore = currentscore;
        mymove.first = x;
        mymove.second = y;
    }
}


std::pair<int,int> kwonoj::UniqueAI::chooseMove(const OthelloGameState& state)
{
    int bestscore = -1000;
    int currentscore;
    std::pair<int,int> mymove(0,0);

    int black_player = color_identity(state);

    for (int x=0; x< state.board().width() ; x++){
        for (int y=0; y< state.board().height() ; y++){
            if (state.isValidMove(x,y)){

                std::unique_ptr<OthelloGameState> CurrentState = state.clone();
                CurrentState -> makeMove(x,y);
                currentscore = search(*CurrentState, 6, black_player);
                update(x,y,currentscore, bestscore, mymove);

            }
        }
    }
    return mymove;
}

bool nomore(int depth, const OthelloGameState& state){
    return (depth==0 || state.isGameOver());
}

bool its_myturn(const OthelloGameState& state, bool black_player){
    if (black_player && state.isBlackTurn()){
        return true;
    }
    if (!black_player && !(state.isBlackTurn())){
        return true;
    }
    else{
        return false;
    }
}

int kwonoj::UniqueAI::search (const OthelloGameState& state, int depth, bool black_player){

    int tempM, tempm;
    if (nomore(depth, state)){
        return eval(state, black_player);
    }

    else{
        if (its_myturn(state, black_player)){
            int max = -1000;
            for (int x=0; x < state.board().width() ; x++){
                for (int y=0; y< state.board().height() ; y++){
                    if (state.isValidMove(x,y)){
                        std::unique_ptr<OthelloGameState> NewState1 = state.clone();
                        NewState1 -> makeMove(x,y);
                        tempM = search(*NewState1, depth-1, black_player);

                        if (tempM> max){
                            return tempM;
                        }
                    }
                }
            }
            return max;
        }

        else{
            int min = 1000;
            for (int x=0; x < state.board().width() ; x++){
                for (int y=0 ; y < state.board().height() ; y++){
                    if (state.isValidMove(x,y)){
                        std::unique_ptr<OthelloGameState> NewState2 = state.clone();
                        NewState2 -> makeMove(x,y);
                        tempm = search(*NewState2, depth-1, black_player);

                        if (tempm < min){
                            return tempm;
                        }
                    }
                }
            }
            return min;
        }
    }
}

