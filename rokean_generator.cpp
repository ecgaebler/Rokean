// author: ecgaebler
// version: 0.1
// date: 2021.05.30
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

// This function loads the lines of the syllables_with_freq file into a vector
bool LoadLines(std::string file_name, std::vector<std::string> & lines) {
    std::ifstream file(file_name.c_str());
    if(!file) {
        std::cerr << "ERROR: could not find file: " << file_name << '\n';
        return false;
    }
    //std::clog << "Successfully opened file: " << file_name << '\n'; 

    // Read lines into vector of strings
    std::string current_line;
    while (std::getline(file, current_line)) {
        //std::clog << current_line << '\n'; 
        if(current_line.size() > 0) {
            lines.push_back(current_line);
        }
    }

    //std::clog << "closing file\n";
    file.close();
    return true;
}

// This function takes a line from the CSV file and parses it into a string and
// an int where the string is a syllable and the int is the relative frequency 
// of that syllable.
bool SplitLine(std::string& line/*, std::string & syllable, int & frequency*/) {
    std::vector<std::string> substrings;
    std::string current_substring;
    std::stringstream ss(line);
    
    while (std::getline(ss, current_substring, ',')) {
        if(!current_substring.empty()) {
            substrings.push_back(current_substring);
        }
    }
    
    if(substrings.size() != 2) {
        std::cerr << "ERROR: " << substrings.size() << " substrings in line. Should be 2.";
        return false;
    }

    std::clog << "substrs[0] = " << substrings.at(0) << ", ";
    std::clog << "substrs[1] = " << substrings.at(1) << "\n";

    return true;
}

int main() {
    std::vector<std::string> lines;
    bool file_read = LoadLines("syllables_with_freq.csv", lines);

    if(file_read) {
        /*std::string syllable;
        int frequency;*/
        for(std::string & current_line : lines) {
            SplitLine(current_line/*, syllable, frequency*/);
        }
        //std::clog << "lines count: " << lines.size() << '\n';
    } else {

    }
}
