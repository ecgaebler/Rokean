/*******************
 * author: ecgaebler
 * version: 0.3
 * date: 2021.05.31
 * 
 * This program requires a file "syllables_with_freq.csv" with a specific
 * format. Each line should be in the form "<string>,<int>" where <string>
 * is a syllable, and <int> is the relative frequency of that syllable. For
 * example, the first few lines might look like this:
 * 
 * foo,9001
 * bar,4296
 * bat,492
 * 
 * Note that spaces and tabs in the csv file may be treated as alphanumeric 
 * characters. Be careful how you use them or you might get whitespace in your 
 * syllables.
 *******************/
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>


// This function loads the lines of the syllables_with_freq file into a vector.
bool LoadLines(std::string file_name, std::vector<std::string>& lines) {
    std::ifstream file(file_name.c_str());
    if(!file) {
        std::cerr << "ERROR: could not find file: " << file_name << '\n';
        return false;
    }

    // Read lines into string vector
    std::string current_line;
    while (std::getline(file, current_line)) {
        //std::clog << current_line << '\n'; 
        if(current_line.size() > 0) {
            lines.push_back(current_line);
        }
    }

    file.close();
    return true;
}


// This function takes a line from the CSV file and parses it into a string and
// an int where the string is a syllable and the int is the relative frequency 
// of that syllable.
bool SplitLine(std::string& line, std::string& syllable, int& frequency) {
    std::vector<std::string> substrings;
    std::string current_substring;
    std::stringstream ss(line);
    
    // split line at commas and collect in substrings vector
    while (std::getline(ss, current_substring, ',')) {
        if(!current_substring.empty()) {
            substrings.push_back(current_substring);
        }
    }
    
    if(substrings.size() != 2) {
        std::cerr << "ERROR: " << substrings.size() << " substrings in line. Should be 2.";
        return false;
    }

    syllable = substrings.at(0);
    // Convert second element of line into an int
    try {
        frequency = stoi(substrings.at(1));
    }
    catch(...) {
        std::cerr << "ERROR: could not convert given str to int.\n";
        return false;
    }

    //std::clog << "syl = " << syllable << ", ";
    //std::clog << "freq = " << frequency << "\n";
    return true;
}


// This function randomly picks a syllable weighted by the syllable's frequency
std::string GenerateSyllable(std::vector<std::string>& syllables, std::vector<int>& freq_weights) {
    if(freq_weights.size() != syllables.size()) {
        std::cerr << "ERROR: number of syllables does not match number of frequencies.\n";
        return "";
    }
    if(freq_weights.size() < 2) {
        std::cerr << "ERROR: Syllables list not long enough.\n";
        return "";
    }

    // Binary search for 
}


int BinarySearch(std::vector<int>& nums, int& target) {
    int l = 0; 
    int r = nums.size() - 1;
    int mid;
    while(l + 1 < r) {
        mid = l + (r - l) / 2; // This looks awkward, but avoids int overflow.
        if(nums.at(mid) < target) {
            l = mid;
        } else {
            r = mid;
        }
    }
    

}



int main() {
    std::vector<std::string> lines;
    bool file_read = LoadLines("syllables_with_freq.csv", lines);
    if(file_read) {
        std::vector<std::string> syllables;
        std::vector<int> freq_weights;
        std::string current_syllable;
        int current_frequency;
        int frequency_sum = 0;

        // Build vectors for syllables and frequencies
        for(std::string & current_line : lines) {
            if(SplitLine(current_line, current_syllable, current_frequency)) {
                syllables.push_back(current_syllable);
                frequency_sum += current_frequency;
                freq_weights.push_back(current_frequency); 
            } else {
                std::cerr << "ERROR: could not parse line.\n";
                return -1;
            }
        }


    } 
}
