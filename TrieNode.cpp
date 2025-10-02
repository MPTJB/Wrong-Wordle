#include <string>

class TrieNode {
    public:
        TrieNode* children[26];
        bool endofWord;
        std::string word;
        
        TrieNode()
        {
            endofWord = false;
            word = "";
            for (int i = 0; i < 26; i++) {
                children[i] = nullptr;
            }
        }
};