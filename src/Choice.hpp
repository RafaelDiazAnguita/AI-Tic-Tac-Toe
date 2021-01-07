#include "Board.hpp"

/**
 * R.D's Tic-Tac-Toe Choice Class
 * 
 **/
class Choice{

    private:
        Board board_;
        int row_,col_,score_,player_;
        std::vector<Choice*> childs_;
        
        int n_parents;
        int writted;
    
    public:

    /**
    *  Constructor
    * @param board actual board
    * @param row row choosed
    * @param col col choosed
    * @param score score of the choice (0,1,2)
    * @param player player who moves (1,2)
    **/
    Choice(Board board,int row,int col,int score,int player){
        board_=board;
        row_=row;
        col_=col;
        score_=score;
        player_=player;
        n_parents = 0;
        writted = 0;
    }
    /**
    * Empty Constructor
    **/
    Choice(){
        Reset();
    }
    /**
    * Reset the Choice object
    **/
    void Reset(){
        board_.Reset();
        row_=-1;
        col_=-1;
        score_=-1;
        player_=-1;
        n_parents = 0;
        writted = 0;
    }
    /**
    * Add a new child which not exists in the tree
    * @param new_child 
    **/
    void Add_Child(Choice *new_child){
        childs_.push_back(new Choice(*new_child));
    }
    /**
    * Add a new child which already exists in the tree
    * @param existing_child 
    **/
    void Add_Existing_Child(Choice *existing_child){
        childs_.push_back(new Choice());
        childs_[childs_.size()-1] = existing_child;
    }
    /**
    * Get the last child added
    * @return last child
    **/
    Choice* get_Last_Child(){
        return childs_.back();
    }
    /**
    * Delete childs
    **/
    void Delete_Childs(){
        childs_.clear();
    }
    /**
    * Check if the choice has the child
    * @param child
    * @return true if the choide has the child
    **/
    bool Has_Child(Choice child){
        for (size_t i = 0; i < childs_.size(); i++)
            if(childs_[i]->equal(child))
                return true;
        return false;
    }
    /**
    * Check if the choice equal to other
    * @param choice_to_compare
    * @return true if are equals
    **/
    bool equal(Choice choice_to_compare){
        if(this->get_Board().Equals(choice_to_compare.get_Board()) && this->get_Row()==choice_to_compare.get_Row() && this->get_Col()==choice_to_compare.get_Col() && this->get_player()==choice_to_compare.get_player())
            return true;
        else
            return false;
    }
    /**
    * Alpha Beta Prunning function
    * @param choice_to_compare choice to search
    * @return true if the min_equal is true
    **/
    bool minimun_equal(Choice choice_to_compare){
        for (size_t i = 0; i < 3; i++)
        for (size_t j = 0; j < 3; j++)
        {
            if(this->get_Board().Get(i,j)!=0){
                if(this->get_Board().Get(i,j)!=choice_to_compare.get_Board().Get(i,j))
                    return false;
            }
        }
        return true;
    }
    /**
    * Check if a node has all possible childs
    * @return true if its explored
    **/
    bool is_explored(){
        if(board_.Win()!=-1)
            return true;

        if(board_.Empty_Squares()!=childs_.size())
            return false;

        bool explored=true;
        for (size_t i = 0; i < childs_.size(); i++)
        {
            explored = explored || childs_[i]->is_explored(); 
        }
        return explored;
    }
    /**
    * Check if a node has a victory child
    * @return true if its explored
    **/
    bool has_victory_child(int player){
        for(int i=0;i<childs_.size();i++){
            if(childs_[i]->Depth()==1 && childs_[i]->get_Score() ==player)
                return true;
        }
        return false;
    }
    
    /**  Depth of the node
     * @return the amount of nodes below this node
     **/ 
    int Depth(){
        int counter=1;
        for (size_t i = 0; i < childs_.size(); i++)
            counter += childs_[i]->Depth();
        
        return counter;
    }

    //Getters
    Board get_Board(){return board_;}
    Board *get_Board_Adress(){return &board_;}
    int get_Row(){return row_;}
    int get_Col(){return col_;}
    std::vector<Choice*>& get_Childs(){return childs_;}
    int get_Score(){return score_;}
    int get_player(){return player_;}
    int get_Following_Player(){if(player_==1)return 2; return 1;}
    int get_writted(){return writted;}
    int get_n_parents(){return n_parents;}


    //Setters
    void set_Score(int score){score_=score;}
    void set_Player(int player){player_=player;}
    void set_Row(int row){row_=row;}
    void set_Col(int col){col_=col;}
    void set_writted(int w){writted = w;}
    void set_n_parents(int parents){n_parents = parents;}
    
};