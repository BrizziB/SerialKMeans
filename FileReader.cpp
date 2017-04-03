//
// Created by Boris on 06/03/2017.
//
#include <string>
#include <iostream>
#include <fstream>
#include <regex>
#include "FileReader.h"

using namespace std;

FileReader::FileReader(string filePath){
    path=filePath;
}
FileReader::~FileReader() {
    delete &(data);
    delete &(path);
    return;

}

// std::array<FileReader::entry, FileReader::maxDataSize>
bool FileReader::getDataOutput() {

    bool fileReaded = false;
    fileReaded = readFromFile(path);

    if(fileReaded){
        cout<< "\ndataset acquired\n";
        return true;
    }
    else {
        cout << "\nfile reading problem was encountered";
        return false;
    }

}


bool FileReader::readFromFile(string path) {

    ifstream datasetFile(path);
    string line;
    string output;
    //datasetFile.open;
    if(datasetFile.is_open()){
        cout<<"\nreading dataset";
        cout.flush();
        regex rgx("\\b\\d[\\d,.]+[\\d,.]\\b|\\d+");
        smatch subMatch;
        vector<double> attributes;
        int index = 0;
        while(getline(datasetFile, line)){
            attributes.clear();
            while(regex_search(line, subMatch, rgx)){
                for(auto x:subMatch) attributes.push_back(stod(x));//registra x come double in entry

                line = subMatch.suffix().str();
            }
            index++;
            entry *newEntry = new entry(attributes, index);
            data.push_back(*newEntry);

        }
        datasetFile.close();
        return true;
    }
    else {
        return false;
    }
}
