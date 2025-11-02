// for strings , 2nd one for bits
// 1. for strings
struct Node{
    Node *links[26];
    bool flag=false;
    bool isEnd() {return flag;}
    void setEnd() {flag=true;}
    bool containsKey(char ch) {return links[ch-'a']!=NULL;}
    void put(char ch, Node*node) {links[ch-'a']=node;}
    Node*get(char ch) {return links[ch-'a'];}
};
class Trie {
private: Node *root;
public:
    Trie() {
        root= new Node();
    }
    void insert(string word) {
        Node*node=root;
        int n=word.size();
        for(int i=0;i<n;i++){
            if(!(node->containsKey(word[i]))){
                node->put(word[i],new Node());
            }
            node=node->get(word[i]);
        }
        node->setEnd();
    }
    
    bool search(string word) {
        Node*node=root;
        int n=word.size();
        for(int i=0;i<n;i++){
            if(!(node->containsKey(word[i]))){
                return false;
            }
            node=node->get(word[i]);
        }
        return node->isEnd();
    }
    bool startsWith(string prefix) {
         Node*node=root;
        int n=prefix.size();
        for(int i=0;i<n;i++){
            if(!(node->containsKey(prefix[i]))){
                return false;
            }
            node=node->get(prefix[i]);
        }
        return true;
    }
};

// 2. For bits
struct Node{
    Node * links[2];
    bool flag=false;
    bool containsKey(int bit){
        return links[bit]!=NULL;
    }
    void put(int bit, Node *node){
        links[bit] = node;
        //Current node ke bit-th slot me child node add karna
    }
    Node* get(int bit){
        return links[bit];
        //Current node ke bit-th child node ka pointer return karna Example: agar bit = 1 → return links[1]
    }
    void setEnd(){
        flag=true;
    }
};
class Trie{
private : Node *root;
public:
    Trie(){
        root= new Node();
    }
    void insert(int num){
        Node *node = root;
        for(int i=31;i>=0;i--){
            // msb to lsb for easier prefix match
            int bit = (num >> i) & 1 ; //extracting ith bit
            if(!node->containsKey(bit)){
                // insert bit
                node->put(bit,new Node());
            }
            // go to next 
            node = node->get(bit);
        }
        node->setEnd();
    }
// below function modify accordingly to need this is of LC-421
    int f(int num){
        // check if opposite bit thing is there or not
        Node * node=root;
        int val=0;
        for(int i=31;i>=0;i--){
            int bit = (num >> i) & 1;  
            if(node->containsKey(1-bit)){
                 val= val | (1<<i);
                 node= node->get(1-bit);
                 // if opposite bit found, head into that direction only
            }
            else node=node->get(bit); // if opposite bit not found
        }
        return val;
    }

};
