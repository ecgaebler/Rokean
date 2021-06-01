# Rokean Agglutinative Language Generator
## About
Another language project of mine, this time influenced by Korean phonetics.
I wanted to practice my C/C++ while revisiting my interest in linguistics. When completed, this program should generate the vocabulary for a new agglutinative synthetic language, given a list of English words and a .csv file containing syllables to build words from, and the relative frequencies of those syllables. While I chose to base Rokean in part on Korean, I designed this program to be more flexible and reuseable than my previous project, Katanese. 

## Usage
### Compiling
Use the included makefile by running

`make`

or compile rokean_generator.cpp using your preferred method.

### Running
After compiling, use the program by running

`./rokean_generator`

### Other Notes
This program requires two files in the same directory as itself: **"syllables_with_freq.csv"** and **"dictionary.txt"**. 
- Each line of the csv must follow the format `<syl>,<freq>` where `<syl>` is a string representing a syllable, and `<freq>` is an integer representing the desired relative frequency of that syllable. The frequency values can be arbitrary non-negative integers, but their values affect how often each syllable is picked. For example, if one syllable has twice the frequency value of another, it will be chosen roughly twice as often when generating words. Do **not** include a header in your csv file; it will attempt to parse it as if it were any other line. Here's an example for what "syllables_with_freq.csv" might look like:
```
foo,9001
bar,42
bat,492
```
- The **dictionary.txt** file should have one word per line. It's okay for words to have punctuation or whitespace in them; each line is parsed as a single string anyway.

