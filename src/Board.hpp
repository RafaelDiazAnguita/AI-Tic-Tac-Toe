#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include <queue>

/**
 * R.D's Tic-Tac-Toe Board Class
 * 
 **/
class Board{

    private:
        int n_=3;
        std::vector<std::vector<int>> board_;
        
    public:

        /**
         * Empty Constructor
         * Reserve memory for board
         **/
        Board(){
            board_= std::vector<std::vector<int>>(n_,std::vector<int>(n_));
            Reset();
        }
        /**
         * Reset a board
         * All squares = 0
         **/
        void Reset(){
            for (size_t i = 0; i < n_; i++)
            for (size_t j = 0; j < n_; j++)
                board_[i][j]=0; 
        }
        /**
         * Print a Board 
         * 
         **/
        void Print_Board(){
            for (size_t i = 0; i < n_; i++){
                std::cout<<std::endl;
                for (size_t j = 0; j < n_; j++)
                std::cout<<board_[i][j]<<"  ";
            }    
            std::cout<<std::endl;
        }
        /**
         * Check if there is a winner 
         * @return the winner play number if there is a winner, 0 if Tie or -1 if there is no win.
         **/
        int Win(){
            int winner=-1;
            for (size_t i = 0; i < n_; i++)
            for (size_t j = 0; j < n_; j++){
                int player=board_[i][j];
                //Right
                if(player!=0 && j+2 == 2 && board_[i][j+1] == player && board_[i][j+2] == player)
                    winner=player;
                //Left
                else if(player!=0 &&  j-2 == 0 && board_[i][j-1] == player && board_[i][j-2] == player)
                    winner=player;
                //Up
                else if(player!=0 &&  i-2 == 0 && board_[i-1][j] == player && board_[i-2][j] == player)
                    winner=player;
                //Down
                else if(player!=0 &&  i+2 == 2 && board_[i+1][j] == player && board_[i+2][j] == player)
                    winner=player;
                //Up-Right
                else if(player!=0 &&  i-2 == 0 && j+2 == 2 && board_[i-1][j+1] == player && board_[i-2][j+2] == player)
                    winner=player;
                //Up-Left
                else if(player!=0 &&  i-2 == 0 && j-2 == 0 && board_[i-1][j-1] == player && board_[i-2][j-2] == player)
                    winner=player;
                //Down-Left
                else if(player!=0 &&  i+2 == 2 && j-2 == 0 && board_[i+1][j-1] == player && board_[i+2][j-2] == player)
                    winner=player;
                //Down-Right
                else if(player!=0 &&  i+2 == 2 && j+2 == 2 && board_[i+1][j+1] == player && board_[i+2][j+2] == player)
                    winner=player;
            }
            if(winner==-1 && Size()==9)
                    winner=0;
            return winner;
        }
        /**
         * Check if a square is empty or not
         * @return true if it is empty 
         * @param row 
         * @param col
         **/
        bool Check_Position(int row,int col){
            if(board_[row][col]==0)
                return true;
            else   
                return false;
        }
        /**
         * Put a player movement in the square(row,col)
         * @param player (0,1,2)
         * @param row
         * @param col
         **/
        void Put(int player,int row,int col){
            board_[row][col]=player;
        }
        /**
         * @return The amount of movements on the board
         * 
         **/
        int Size(){
            int count=0;
            for (size_t i = 0; i < n_; i++)
            for (size_t j = 0; j < n_; j++)
                if(board_[i][j]!=0)
                    count++;
            return count;
        }
        /**
         * @return The value of a square
         * 
         **/
        int Get(int row,int col){
            return board_[row][col];
        }
        /**
         * Check if a board equals to other
         * @return true if equals
         **/
        bool Equals(Board board){
            for (size_t i = 0; i < n_; i++)
            for (size_t j = 0; j < n_; j++)
            {
                if(board_[i][j]!=board.Get(i,j))
                return false;
            }
            return true;
        }
        /**
         * @return the amount of empty squares
         * 
         **/
        int Empty_Squares(){
            int cont = 0;
            for (size_t i = 0; i < n_; i++)
            for (size_t j = 0; j < n_; j++)
                if(board_[i][j]==0)
                    cont++;
            return cont;
        }
};