#include "Choice.hpp"

class Tree{

    private:
    Choice root_;
    Choice *ptr;

    public:

    /**
    * Empty Constructor
    **/
    Tree(){
        root_.Reset();
        Go_Root();
    }

    /**
    * Ptr points to root
    **/
    void Go_Root(){
        ptr=&root_;
    }
    /**
    * Find a node
    * @param node node to find
    * @return true if the node is found
    **/
    bool find(Choice node){
        if(ptr->minimun_equal(node)){
            if(ptr->equal(node))
            return true;
            else
            {
                std::vector<Choice*>& childs = ptr->get_Childs();
                for (size_t i = 0; i < childs.size(); i++)
                {
                    ptr=childs[i];
                    if(find(node))
                    return true;
                }
                return false;
            }
        }
        return false;
    }
    /**
    * Tree has the node
    * @param node_to_find 
    * @return true if the tree has the node
    **/
    bool Has(Choice node_to_find){
        Go_Root();
        bool found=find(node_to_find);
        return found;
    }
    /**
    * Add a match
    * @param match vector of choices
    **/
    void Add_Match(std::vector<Choice> match){
        
        Choice *parent;
        for (size_t i = 0; i < match.size(); i++)
        {   
            //Root
            if(i==0)
            parent=&root_;
            else
            {    
                //The tree doesn't has the node 
                if(!Has(match[i])){
                    parent->Add_Child(&match[i]);
                    parent=parent->get_Last_Child();
                    parent->set_n_parents(parent->get_n_parents()+1);
                }
                //The tree has the node
                else{
                    //the node is in the parent's branch
                    if(parent->Has_Child(match[i]))
                    parent=ptr;
                    //the node is not in the parent's branch    
                    else{
                       parent->Add_Existing_Child(ptr);
                       ptr->set_n_parents(ptr->get_n_parents()+1);
                       parent=parent->get_Last_Child(); 
                    }
                }
            }
        }

    }
    /**
    * Compute scores for each node recursively
    * @return the score of the node which ptr is pointing
    **/
    int Compute_Scores_Recursive(){

        if(ptr->get_Childs().size()==0)//leaf node
            return ptr->get_Score();
        else{
            int score=-1,received_score,ones=0,twos=0,zeros=0;
            std::vector<Choice*>& childs = ptr->get_Childs();
            Choice * actual_node=&(*ptr);
            for (size_t i = 0; i < childs.size(); i++)
            {
                ptr=childs[i];
                received_score = Compute_Scores_Recursive();

                if(received_score == 1)
                    ones++;
                else if(received_score == 2)
                    twos++;
                else if(received_score == 0)
                    zeros++;

            }
            if((actual_node->get_Following_Player() == 1 && ones == 0 && zeros > 0) || (actual_node->get_Following_Player() == 2 && twos == 0 && zeros > 0))
                score = 0;
            else if(ones > twos)
                score = 1;
            else if(twos > ones)
                score = 2;
            else if(twos == ones)
                score = actual_node->get_Following_Player();

            ptr=actual_node;
            ptr->set_Score(score);
            return score;
        }
    }
    /**
    * Compute scores for each node recursively
    **/
    void Compute_Scores(){
        Go_Root();
        Compute_Scores_Recursive();
    }
    /**
    * Find an unexplored node
    * @return a vector with the row[0] and the col[1] of an unexplored child node from ptr
    **/
    std::vector<int> find_unexplored_node(){
        std::vector<int> choosed;
        for (size_t i = 0; i < ptr->get_Childs().size(); i++)
        {
            if(!ptr->get_Childs()[i]->is_explored()){
                choosed.push_back(ptr->get_Childs()[i]->get_Row());
                choosed.push_back(ptr->get_Childs()[i]->get_Col());
                return choosed;
            }
        }
        int another_player=1;
        if(ptr->get_player()==1)
            another_player = 2;

        
        for (size_t i = 0; i < 3; i++)
        for (size_t j = 0; j < 3; j++)
        {
            if(ptr->get_Board().Check_Position(i,j)){
                Choice new_child(ptr->get_Board(),i,j,-1,another_player);
                new_child.get_Board_Adress()->Put(another_player,i,j);
                if(!ptr->Has_Child(new_child)){
                    choosed.push_back(i);
                    choosed.push_back(j);
                    return choosed;
                }
            }
            
        }
        
        return choosed;
        
    }
    /**
    * Save the tree to a file recursively
    * @param f file
    **/
    void save(std::ofstream &f){

        if(ptr->get_n_parents()>ptr->get_writted() || ptr->equal(root_)){
            f << ptr->get_player()<<" "<< ptr->get_Row() <<" "<< ptr->get_Col()<<" "<<ptr->get_Score()<<" ";
            for (size_t i = 0; i < 3; i++)
            for (size_t j = 0; j < 3; j++)
                    f << ptr->get_Board().Get(i,j)<< " ";
            f << ptr->get_Childs().size()<<std::endl;
            

            if(ptr->get_writted()<1){

                ptr->set_writted(ptr->get_writted()+1);
                std::vector<Choice*> childs = ptr->get_Childs();
                for (size_t i = 0; i < childs.size(); i++)
                    {
                    ptr=childs[i];
                    save(f);
                }
            }
            else
            ptr->set_writted(ptr->get_writted()+1);
            
            
        }
        
    }
    /**
    * Save the tree to a file 
    * @param filename file
    **/
    void write(std::string filename){
        Go_Root();
        std::ofstream f( filename);
        if (f.is_open()){
            save(f);
        }
        else std::cerr << "Fail to open "<< filename << std::endl;
    }
    /**
    * Load the tree from a file recursively
    * @param f filename
    * @param parent parent of ptr
    **/
    int load(std::ifstream &f,Choice *parent){
        if(!f.eof()){
            std::string row,col,score,board,childs,player;
            f >> player >> row >> col >> score;
            Choice final(Board(),std::stoi(row),std::stoi(col),std::stoi(score),std::stoi(player));

            for (size_t i = 0; i < 3; i++)
            for (size_t j = 0; j < 3; j++){
                f >> board;
                final.get_Board_Adress()->Put(stoi(board),i,j);
            }
            
            f >> childs;
            Choice *actual;

            if(!final.equal(root_)){
                if(!Has(final)){
                    parent->Add_Child(&final);
                    actual = parent->get_Last_Child();
                    actual->set_n_parents(actual->get_n_parents()+1);

                }
                else
                {
                    parent->Add_Existing_Child(ptr);
                    actual = parent->get_Last_Child();
                    actual->set_n_parents(actual->get_n_parents()+1);
                    return 0;
                }
                
            }
            else
            {
                actual = parent;
            }
            
                
        
            for (size_t i = 0; i < std::stoi(childs); i++)
            {
                load(f,actual);
            }
            
            
   
        }
        return 1;
        
    }
    /**
    * Load the tree from a file 
    * @param filename file
    **/
    bool read(std::string filename){
        Go_Root();
        int cont=0;
        std::ifstream f;
        f.open(filename, std::ifstream::in);
        if(f.is_open()){
            std::cout<<"Loading memory file... "<<std::endl;
            load(f,&root_);
            return true;
        }
        return false;
    }
    /**
    * Clear the tree
    **/
    void clear(){
        Go_Root();
        root_.Delete_Childs();
    }

    //Getters
    Choice get_current(){return *ptr;}
    Choice* get_Current_Address(){return ptr;}
    Choice get_root(){return root_;}
};