#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include "Trie.cpp"

using namespace std;

const string vowels = "aeiouy";
const string consonants = "bcdfghjklmnpqrstvwxz";

bool isVowel(char c){
    switch (c)
    {
    case 'a':
    case 'e':
    case 'i':
    case 'o':
    case 'u':
    case 'y':
        return true;
    default:
        break;
    }
    return false;
}

bool customComp(char a, char b){
    bool avowel = isVowel(a);
    bool bvowel = isVowel(b);
    
    if(avowel && bvowel) {
        return a < b;
    }else if (bvowel) {
        return 0;
    }else if (avowel) {
        return 1;
    }
    return a < b;
}

//https://stackoverflow.com/questions/24496063/remove-duplicates-in-string-algorithm
string stringSingles(string word){
    auto last = word.end();

    for ( auto first = word.begin(); first != last; ++first )
    {
        last = std::remove( std::next( first ), last, *first );
    }

    word.erase( last, word.end() );
    return word;

}

//this ofcourse doesnt work
vector<string> wordleSolver(string newWord, Trie root, vector<string> wordTuple){
    vector<string> newWordTuple = wordTuple;
    newWordTuple.push_back(newWord);

    if(newWordTuple.size() >= 7){
        return newWordTuple;
    }

    vector<int> allowedLetters = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25};
//    vector<int> allowedVowels = {0,4,8,14,20,24};
    for (string word : newWordTuple) {
        for(char c : word){
        allowedLetters[c-'a'] = -1;
        }
    }

    string newnewWord = root.firstAllowedWord(allowedLetters);
    if(newnewWord.length() > 0){
        return wordleSolver(newnewWord, root, newWordTuple);
    }

}


int main(int argc, char const *argv[])
{ 
    ifstream OriginalWordList("valid-wordle-words.txt");
    string Temptext;
    map<string,string> wordcoding2;
    map<string,string> wordcoding3;
    map<string,string> wordcoding4;
    map<string,string> wordcoding5;
    map<string,string> wordVowelless;
    Trie root;

    string shortWord;
    while (getline (OriginalWordList,Temptext)){
        shortWord = Temptext;
        sort(shortWord.begin(),shortWord.end(),customComp); 
        shortWord = stringSingles(shortWord);
        if(!isVowel(shortWord[0])){
            wordVowelless[shortWord] = Temptext;
        }
        {switch (shortWord.length()){
        case 2:
            wordcoding2[shortWord] = Temptext;
            break;
        case 3:
            wordcoding3[shortWord] = Temptext;
            break;
        case 4:
            wordcoding4[shortWord] = Temptext;
            break;
        case 5:
            wordcoding5[shortWord] = Temptext;
            break;
        default:
            cout << "\n\n shouldnt happen, single letter word\n\n";
            break;
        }}
    }
    //put the words in the special trie, shortest to longest
    {
        for(auto key : wordcoding2) {
            root.insert(key.first,key.second);
        }
        for(auto key : wordcoding3) {
            root.insert(key.first,key.second);
        }
        for(auto key : wordcoding4) {
            root.insert(key.first,key.second);
        }
        for(auto key : wordcoding5) {
            root.insert(key.first,key.second);
        }
        int totals = wordcoding2.size() + wordcoding3.size() + wordcoding4.size() + wordcoding5.size() + wordVowelless.size();
        map<string,string> newList;
        root.getWordList(&newList);
        cout << "from: " << totals << " to: " << newList.size() << endl;

    }
    vector<int> allowedLetters = {-1, 1, 2, 3, 4, 5, 6, -1, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25};
    cout << "word: " << root.firstAllowedWord(allowedLetters) << endl;

    return 0;
}





