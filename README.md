# Wrong-Wordle
Program for finding the worst hardmode guesses for any given wordle answer, inspired by a youtube video by Ellie Rasmussen.
https://youtu.be/zoh5eLOjwHA

Ellie however uses a flawed algorithm and does not find a valid, all black square solution for hardmode wordle. 
(effectively we're trying to find 7 words, all 5 letters each that have no overlap with each other) 
One such solution is

{cwtch,
peepe,
susus,
grrrl,
nonno,
mamma,
vivid}

(vivid was a past wordle answer on february 25, 2022)
this answer I found by first collecting all words withiut vowels and with only 2 different letters, and then solving it by hand, where i found 6 out of the 7 letters, and then using a standard wordle solcer to find the seventh word. my code sucks...

my code first sorts word internally, such that vowels are in front and repeats of letters are taken out, storing the modified string and original word in a pair. 
Using several dictionaries, thw words are sorted based on modified string length and vowelless words are kept seperate. 
then the modified strings are put into a trie, storing the original words on the leaf nodes. This allows the first layer of the trie to be the 6 vowels (a,e,i,o,u,y). 
TODO: Dont put words with more than 1 vowel in the trie
TODO: Deal with the case of 2 vowelless words and a word with 2 vowels later.
The main problem Rasmussen did not account for is that there are only 6 vowels and with 6 guesses you run out of space for thkse vowems very quickly. vowelless words are very uncommon, and very unlikely to ever be answers, so we need to keep at least 1 vowel available for the answer.
the trie reflects this by having the first layer be the vowels the code can wasily skip vowels that are unavailable. 
this effectly creates 7 sets: 1 set for each of the vowels, and a vowelless set. 
Each of the sets of vowels can only supply 1 word (only 1 word in the final set can have an 'a'), while the vowelless set {"grrrl","grrls","pffft","phpht","cwtch","crwth"} can supply 2 words.
(the vowelless set can get "grrls" and "crwth" removed, as the letters in those words are srrict supersets of "grrrl" and "cwtch" respectively)
This means, that the final set camnot contain words that have 3 or more vowels; or words that contain one of {'g','r','l'} and a 't' (as that makes the vowelless set empty).

