/*******************
 * author: ecgaebler
 * version: 0.4
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
 * 
 * Planned Features That I Might Add At Some Point:
 * - Program can use a file with only the syllables, and generate appropriate 
 *   frequencies following a zipf distribution.
 * - Program can take an arbitrary file as input and determine if it includes
 *   only syllables, or syllables with associated frequencies.
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
        std::cerr << "ERROR: " << substrings.size() << " substrings in line. "
            "Should be 2.\n";
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


// Randomly picks a syllable weighted by the syllable's frequency
std::string GenerateSyllable(std::vector<std::string>& syllables, 
                             std::vector<int>& freq_weights) {
    if(freq_weights.size() != syllables.size()) {
        std::cerr << "ERROR: number of syllables does not match number of "
            "frequencies.\n";
        return "";
    }
    if(freq_weights.size() < 2) {
        std::cerr << "ERROR: Syllables list not long enough.\n";
        return "";
    }

    // Generate random int, then do BinarySearch.
}


// Returns the index of the vector with the smallest value greater than target.
int BinarySearch(std::vector<int>& nums, int target) {
    if(nums.size() == 0) {
        std::cerr << "ERROR: cannot search empty vector\n";
        return -1;
    }

    int l_idx = 0; 
    int r_idx = nums.size() - 1;
    int mid;
    while(l_idx + 1 < r_idx) {
        mid = l_idx + (r_idx - l_idx) / 2; // looks awkward but avoids overflow.
        if(nums.at(mid) < target) {
            l_idx = mid;
        } else {
            r_idx = mid;
        }
    }

    if(target <= nums.at(l_idx)) {
        return l_idx;
    } else {
        return r_idx;
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

        // Testing BinarySearch
        std::vector<int> nums;
        nums.push_back(3);
        nums.push_back(7);
        nums.push_back(13);
        std::clog << "t=0; goal=0, actual=" << BinarySearch(nums, 0) << '\n';
        std::clog << "t=3; goal=0, actual=" << BinarySearch(nums, 3) << '\n';
        std::clog << "t=4; goal=1, actual=" << BinarySearch(nums, 4) << '\n';
        std::clog << "t=7; goal=1, actual=" << BinarySearch(nums, 7) << '\n';
        std::clog << "t=8; goal=2, actual=" << BinarySearch(nums, 8) << '\n';
        std::clog << "t=13; goal=2, actual=" << BinarySearch(nums, 13) << '\n';
        std::clog << "t=42; goal=2, actual=" << BinarySearch(nums, 42) << '\n';
    } 
}
