# Rokean
Another language project, this time influenced by Korean phonetics.
I wanted to get some practice with C/C++ while revisiting my interest in linguistics. When completed, this program should generate the vocabulary for a new agglutinative synthetic language, given a list of English words and a .csv file with syllables to build words from, and the relative frequencies of those syllables. While I chose to base Rokean in part on Korean, I designed this program to be more flexible and reuseable than my previous project, Katanese. 

Note: this program requires a file named "syllables_with_freq.csv" in the same directory. Each line of this file must follow this format:
<syllable>,<frequency>
where <syllable> is a string representing a syllable, and <frequency> is an integer representing the desired relative frequency of that syllable (the values are arbitrary, but must be positive integers). If the "frequency" value for one syllable is twice that of another, it will be twice as likely to occur when words are generated.

Use command "make" to compile from source.
