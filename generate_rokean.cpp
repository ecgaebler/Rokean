#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

bool LoadSyllables(std::string file_name, std::vector<std::string> & syllables) {
    std::ifstream file(file_name.c_str());
    if(!file) {
        std:cerr << "ERROR: could not find syllables file: " << file_name << '\n';
        return false;
    }
    clog << "Successfully opened syllables file: " << file_name << '\n'; 

    //read lines into vector of syllables
    std::string current_line;
    while (std::getline(file, current_line)) {
        //clog << current_line << '\n'; 
        if(current_line.size() > 0) {
            syllables.push_back(current_line);
            //clog << "syllables vector size: " << syllables.size() << '\n';
        }
        //syllables.push_back(current_line);
    }

    clog << "closing file\n";
    file.close();
    //clog << "FINAL vector size: " << syllables.size() << '\n';
    return true;
}


int main() {
    std::vector<std::string> syllables;

    bool file_read = LoadSyllables("rokean_syllables", syllables);

    if(file_read) {
        for(std::string & line : syllables) {
            std::cout << line << '\n';
        }
        clog << "syllables count: " << syllables.size() << '\n';
    }
}
