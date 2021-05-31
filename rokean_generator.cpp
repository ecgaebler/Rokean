#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// This function just loads the lines of the syllables_with_freq file into a vector
bool LoadLines(std::string file_name, std::vector<std::string> & lines) {
    std::ifstream file(file_name.c_str());
    if(!file) {
        std::cerr << "ERROR: could not find file: " << file_name << '\n';
        return false;
    }
    std::clog << "Successfully opened file: " << file_name << '\n'; 

    // Read lines into vector of strings
    std::string current_line;
    while (std::getline(file, current_line)) {
        //clog << current_line << '\n'; 
        if(current_line.size() > 0) {
            lines.push_back(current_line);
        }
    }

    //std::clog << "closing file\n";
    file.close();
    return true;
}

bool UnpackLines(std::vector<std::string> & lines, 
                 std::vector<std::string> & syllables, 
                 std::vector<int> & frequencies){
    return true;
}

int main() {
    std::vector<std::string> lines;
    bool file_read = LoadLines("syllables_with_freq.csv", lines);

    if(file_read) {
        for(std::string & current_line : lines) {
            std::cout << current_line << '\n';
        }
        //std::clog << "lines count: " << lines.size() << '\n';
    }
}
