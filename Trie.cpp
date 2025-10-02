#include "TrieNode.cpp"
#include <string>
#include <map>
#include <iostream>

using namespace std;

// class for the Trie implementation
class Trie {
private:
    TrieNode* root;

public:
    Trie() { root = new TrieNode(); }

    // Function to insert a word into the trie
    void insert(std::string word, std::string originalWord)
    {
        TrieNode* node = root;
        std::string wordCopy = word;
        int index;
        do{
            for(int i = 0; i < 5; ++i){
     //           cout << "word:" << wordCopy << " i=" << i << " at node: " << node << endl;
                if(!wordCopy[i]){
                    break;
                }
                index = wordCopy[i] - 'a';
                if(node->children[index]){
                     node = node->children[index];
                    wordCopy = wordCopy.erase(i,1);
                    i = -1;
                }
            }
            if(!wordCopy.length()){
                break;
            }
            index = wordCopy[0] - 'a';
            node->children[index] = new TrieNode();
        }while(wordCopy.length());

        node->endofWord = true;
        node->word = originalWord;
    }
    
    void getWordList(map<string,string>* list) {
        getWordList(list, root, "");
    }

    void getWordList(map<string,string>* list, TrieNode* node, string prefix){
        if (node->endofWord){
            list->insert({prefix, node->word});
            return;
        }
        for (int i = 0; i < 26; ++i){
            if (node->children[i]) {
                getWordList(list,node->children[i],
                      prefix + char('a' + i));
            }
        }
    }

    bool startsWith(string prefix)
    {
        TrieNode* node = root;
        for (char c : prefix) {
            int index = c - 'a';
            if (!node->children[index]) {
                return false;
            }
            node = node->children[index];
        }
        return true;
    }


    string firstAllowedWord(vector<int> allowedLetters, TrieNode* node){
        if(node->endofWord){
            return node->word;
        }
        for(int l : allowedLetters){
            if(l+1 && node->children[l]){
                node = node->children[l];
                return firstAllowedWord(allowedLetters,node);
            }
        }
        return "";
    }
    string firstAllowedWord(vector<int> allowedLetters){
        return firstAllowedWord(allowedLetters,root);
    }


};