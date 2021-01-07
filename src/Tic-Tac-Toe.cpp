#include "Tree_Min_Max.hpp"
/**
* Compute a human player choice
*@param player the number of the player
*@param row row choosed
*@param col col choosed
*@param board current board
**/
bool player_choice(int player,int &row,int &col,Board &board){

    std::cout<<"Enter row:";
    std::cin>>row;
    std::cout<<"Enter col:";
    std::cin>>col;
    
    if(row <=3 && row >=0 && col<=3 && col >=0){
        if(board.Check_Position(row,col))
            return true;
        else{
            board.Print_Board();
            std::cout<<"The position choosed is not empty, choose a empty position.";
            return false;
        }
    }
    else{
        board.Print_Board();
        std::cout<<"Wrong row or col, try again."<<std::endl;
        return false;
    }
}
/**
* Compute a human player movement
*@param player the number of the player
*@param board current board
**/
std::vector<int> play_player(int player,Board &board){
    std::cout<<"Play player: "<<player<<std::endl;
    int row,col;
    bool el=false;
    board.Print_Board();
    while(!el){
        el=player_choice(player,row,col,board);
    }
    board.Put(player,row,col);
    std::vector<int> choosed;
    choosed.push_back(row);
    choosed.push_back(col);
    return choosed;
}
/**
* Compute a random computer choice
*@param player the number of the player
*@param row row choosed
*@param col col choosed
*@param board current board
**/
bool computer_choice_random(int player,int &row,int &col,Board &board){

    row=rand()%3;
    col=rand()%3;

    if(board.Check_Position(row,col))
        return true;
    else{
        return false;
    }
}
/**
* Compute a computer choice
*@param player the number of the player
*@param row row choosed
*@param col col choosed
*@param board current board
*@param choosed contains the row and the col of the last movement
*@param memory memory tree
**/
bool computer_choice(int player,int &row,int &col,Board &board,std::vector<int> choosed,Tree &memory){
    bool el=false;
    int another_player;
    if(player==1)
        another_player=2;
    else
        another_player=1;

    Choice actual_game(board,choosed[0],choosed[1],-1,another_player);
    
    if(memory.Has(actual_game))
    if(memory.get_current().get_Childs().size()>0){
        Choice actual=memory.get_current();
        int choosed,score;
        for (size_t i = 0; i < actual.get_Childs().size(); i++)
        {
            if(i==0){
                choosed = i;
                score = actual.get_Childs()[i]->get_Score();
            }
            else if(actual.get_Childs()[i]->get_Score()==player && score != player){
                choosed = i;
                score = actual.get_Childs()[i]->get_Score();
            }
            else if(score==player && actual.get_Childs()[i]->get_Score()==player && !actual.get_Childs()[i]->has_victory_child(another_player)){
                choosed = i;
                score = actual.get_Childs()[i]->get_Score();
            }
            else if(score == another_player && actual.get_Childs()[i]->get_Score()==0){
                choosed = i;
                score = actual.get_Childs()[i]->get_Score();
            }
        }
        row=actual.get_Childs()[choosed]->get_Row();
        col=actual.get_Childs()[choosed]->get_Col();
        return true;
    }
    
    while(!el){
        el=computer_choice_random(player,row,col,board);
    }
    return true;
}
/**
* Compute a computer movement
*@param player the number of the player
*@param row row choosed
*@param col col choosed
*@param board current board
*@param choosed_by_player contains row and col choosed by player in the last movement
*@param memory memory tree
**/
void play_computer(int player,Board &board,std::vector<int> choosed_by_player,Tree &memory){
    std::cout<<"Play player: "<<player<<std::endl;
    int row,col;
    bool el=false;
    board.Print_Board();
    while(!el){
        el=computer_choice(player,row,col,board,choosed_by_player,memory);
    }

    board.Put(player,row,col);
}
/**
* Train the memory tree
*@param player the number of the player
*@param board current board
*@param memory tree memory
*@param choosed_by_other row and col of the last movement
**/
std::vector<int> train_computer(int player, Board &board,Tree &memory,std::vector<int> choosed_by_other){
    int row,col;
    bool el=false;

    int another_player;
    if(player==1)
        another_player=2;
    else
        another_player=1;

    Choice actual_game;

    if(choosed_by_other.size()!=0)
        actual_game = Choice(board,choosed_by_other[0],choosed_by_other[1],-1,another_player);
    else
        actual_game= memory.get_root();
    


    if(memory.Has(actual_game)){

        std::vector<int> results = memory.find_unexplored_node();
        if(results.size()!=0){
            row = results[0];
            col = results[1]; 
        }
        else{
            while(!el)
            el=computer_choice_random(player,row,col,board);
        }
    }
    else{
        while(!el)
            el=computer_choice_random(player,row,col,board);
    }
    board.Put(player,row,col);
    std::vector<int> choosed;
    choosed.push_back(row);
    choosed.push_back(col);
    return choosed;

}
/**
* Check if there is a victory or tie
*@param board current board
**/
int victory(Board &board){
    int win=board.Win();
    if(win==1){
        board.Print_Board();
        std::cout<<"End of Game, player 1 wins."<<std::endl;
        return 1;
    }
    else if(win==2){
        board.Print_Board();
        std::cout<<"End of Game, player 2 wins."<<std::endl;
        return 2;
    }
    else if(win==0){
        board.Print_Board();
        std::cout<<"Tie."<<std::endl;
        return 0;
    }
    else
        return -1;
}

int main(int argc,char *argv[]){
    srand(time(NULL));
    std::cout<<"Welcome to AI Tic-Tac-Toe, the rows and cols go from 0 to 2."<<std::endl;
    Board board;
    if(argc<2 && argc>4){
        std::cout<<"Bad arguments, ./Tic-Tac-Toe [0,1,2]."<<std::endl;
        std::cout<<"If you choose 2,you have to train over a memory file, add the argument: ./Tic-Tac-Toe 2 1 memoryfile.txt"<<std::endl;
        std::cout<<"0=player vs player  1=player vs pc  2=training."<<std::endl;
        return 0;
    }
    int gamemode = std::atoi(argv[1]);
    int max_training;
    int play_again;
    std::string memory_file;
    Tree memory;

    if(argc==3){
        memory_file = argv[2];
        memory.read(memory_file);
    }
    else if(argc==4){
        max_training = std::atoi(argv[2]);
        memory_file = argv[3];
        memory.read(memory_file);
    }
        

    int matchs=0;
    std::vector<int> choosed;
    std::vector<Choice> match;
    Choice final;
    match.push_back(final);

    switch(gamemode)
    {
    case 0:   //player vs player

        while(true){
            //player 1
            play_player(1,board);

            if(victory(board)!=-1){
                std::cout<<"To play again enter 1, enter 0 to exit:";
                std::cin >> play_again;
                if(play_again==0)
                    return 0;
                else
                    board.Reset();
            }
            return 0;

            //player 2
            play_player(2,board);

            if(victory(board)!=-1){
                std::cout<<"To play again enter 1, enter 0 to exit:";
                std::cin >> play_again;
                if(play_again==0)
                    return 0;
                else
                    board.Reset();
            }
            return 0;
            
        }

    break;
    case 1:  //player vs pc
        while(true){
            //player 1
            choosed=play_player(1,board);

            if(victory(board)!=-1){
                std::cout<<"To play again enter 1, enter 0 to exit:";
                std::cin >> play_again;
                if(play_again==0)
                    return 0;
                else
                    board.Reset();
            }
            else{
                //player 2
                play_computer(2,board,choosed,memory);

                if(victory(board)!=-1){
                    std::cout<<"To play again enter 1, enter 0 to exit:";
                    std::cin >> play_again;
                    if(play_again==0)
                        return 0;
                    else
                        board.Reset();
                }
            }   
        }
    
    break;

    case 2:     //training
        while(matchs<max_training)
        {
            std::cout<<"MATCHS:"<<matchs<<std::endl;
            //PLAYER 1
            choosed=train_computer(1,board,memory,choosed);

            //save the movement 
            final=Choice(board,choosed[0],choosed[1],-1,1);

            if(victory(board)!=-1){
               
                //the movement gave the victory to player 1, we save it
                final.set_Score(1);
                match.push_back(final);
        

                //add match
                memory.Add_Match(match);

                //reset for rematch
                board.Reset();
                final.Reset();
                match.clear();
                choosed.clear();
                match.push_back(Choice());
                matchs++;
            }
            else{
                //save in memory the movement of player 1(no victory)
                match.push_back(final);
                //PLAYER 2
                choosed=train_computer(2,board,memory,choosed);

                //save the movement
                final=Choice(board,choosed[0],choosed[1],-1,2);

                if(victory(board)!=-1){
                
                //the movement gave the victory to player 2, we save it
                final.set_Score(2);
                match.push_back(final);


                //addmatch
                memory.Add_Match(match);

                //reset for rematch
                board.Reset();
                final.Reset();
                match.clear();
                choosed.clear();
                match.push_back(Choice());
                matchs++;
                }
                else
                //save in memory the movement of player 2(no victory)
                match.push_back(final);

            }
        }

    break;
    
    default:
        std::cout<<"The option choosed is invalid.";
        return 0;
    break;
    }
    memory.Compute_Scores();
    memory.write(memory_file);
    memory.clear();
    
}