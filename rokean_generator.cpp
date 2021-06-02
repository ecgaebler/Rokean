/*******************
 * author: ecgaebler
 * version: 1.0
 * date: 2021.06.01
 * 
 * This program requires two files in the same directory as itself:
 * "syllables_with_freq.csv" and "dictionary.txt".
 * 
 * - "syllables_with_freq.csv" requires a specific format. Each line should be
 *   in the form "<string>,<int>" where <string> is a syllable, and <int> is the
 *   relative frequency of that syllable. For example, the first few lines might
 *   look like this:
 * 
 *   foo,9001
 *   bar,4296
 *   bat,492
 * 
 *   Note that spaces and tabs in the csv file may be treated as alphanumeric
 *   characters. Be careful how you use them or you might get whitespace in your
 *   syllables.
 * 
 * - For "dictionary.txt", each line of the file should be a unique word to be
 *   translated. It's okay for a word to have special characters like apostrophe
 *   or hyphen, or to have white space, but avoid using commas in this file.
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
#include <unordered_set>
#include <random>


// This function loads the lines of the given file into a vector.
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


/* This function loads strings from a vector into a file and saves it.
 * Note that this will overwrite the given file if it already exists. */
bool SaveLines(std::string file_name, std::vector<std::string>& lines) {
    std::ofstream file(file_name.c_str(), std::ofstream::trunc);
    for(std::string& current_line : lines) {
        file << current_line << '\n';
    }
    file.close();
}


/* Takes a line from the CSV file and parses it into a string and an int where 
 * the string is a syllable and the int is the relative frequency of that 
 * syllable. */
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


// Randomly picks a syllable weighted by the syllable's frequency
std::string GenerateSyllable(std::vector<std::string>& syllables, 
                             std::vector<int>& freq_weights,
                             int target) {
    if(freq_weights.size() != syllables.size()) {
        std::cerr << "ERROR: number of syllables does not match number of "
            "frequencies.\n";
        return "";
    }
    if(freq_weights.size() < 2) {
        std::cerr << "ERROR: Syllables list not long enough.\n";
        return "";
    }

    int index = BinarySearch(freq_weights, target);
    if(index < 0 or index >= syllables.size()) {
        return "";
    }
    return syllables.at(index);
}


// Generates a new Rokean word by combining multiple randomly chosen syllables
std::string GenerateWord(std::string& current_word,
                         std::unordered_set<std::string>& rokean_words,
                         std::vector<std::string>& syllables, 
                         std::vector<int>& freq_weights,
                         std::mt19937& generator,
                         std::uniform_int_distribution<>& distrib) {
    int target = distrib(generator);
    std::string result = GenerateSyllable(syllables, freq_weights, target);
    int max_retries = 0; // number of retries before increasing # of syllables
    int num_retries = 1;
    int num_syllables = 1;
    std::unordered_set<std::string>::const_iterator location;
    location = rokean_words.find(result);
    while(location != rokean_words.end()) {
        if(num_retries >= max_retries) {
            num_retries = 0;
            ++num_syllables;
            //std::clog << "DEBUG: num_syllables == " << num_syllables << '\n';
        }
        result = "";
        for(int i=0; i < num_syllables; i++) {
            target = distrib(generator);
            //std::clog << "DEBUG: target == " << target << '\n';
            result.append(GenerateSyllable(syllables, freq_weights, target));
        }
        ++num_retries;
        location = rokean_words.find(result);
    }

    rokean_words.insert(result);
    return result;
}



int main() {
    // Load syllables and their frequencies
    std::vector<std::string> syl_lines;
    bool syl_file_read = LoadLines("syllables_with_freq.csv", syl_lines);
    if(!syl_file_read) {
        std::cerr << "Aborting...\n";
        return -1;
    }

    // Load list of words to translate
    std::vector<std::string> dict_lines;
    bool dict_file_read = LoadLines("dictionary.txt", dict_lines);
    if(!dict_file_read) {
        std::cerr << "Aborting...\n";
        return -1;
    }

    // Build vectors for syllables and frequencies
    std::vector<std::string> syllables;
    std::vector<int> freq_weights;
    std::string current_syllable;
    int current_frequency;
    int frequency_sum = 0;
    for(std::string& current_line : syl_lines) {
        if(SplitLine(current_line, current_syllable, current_frequency)) {
            syllables.push_back(current_syllable);
            frequency_sum += current_frequency;
            freq_weights.push_back(frequency_sum); 
        } else {
            std::cerr << "ERROR: could not parse line.\n";
            return -1;
        }
    }

    // Set up random number generator
    std::random_device rd; 
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distrib(1, freq_weights.back());

    // Create Rokean translation for each word in dict_lines
    std::vector<std::string> rokean_dict; 
    std::unordered_set<std::string> rokean_words = {};
    for(std::string& current_word : dict_lines) {
        std::string current_rokean = GenerateWord(current_word, rokean_words, 
                                                  syllables, freq_weights,
                                                  generator, distrib);
        std::string translation = current_word + ',' + current_rokean;
        //std::clog << "DEBUG: " << translation << '\n';
        rokean_dict.push_back(translation);
    }
    //std::clog << "DEBUG: " << rokean_dict.size() << '\n';
    bool save_dict = SaveLines("rokean_dictionary.csv",rokean_dict);
    if(save_dict) {
        std::cout << "Saved dictionary to \"rokean_dictionary.csv\"\n";
        return 1;
    } else {
        std::cerr << "ERROR: couldn't save to \"rokean_dictionary.csv\"\n";
        return -1;
    }

}
