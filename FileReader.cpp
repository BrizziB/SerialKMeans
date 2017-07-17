//
// Created by Boris on 06/03/2017.
//
#include <string>
#include <iostream>
#include <fstream>
#include <regex>
#include "FileReader.h"

using namespace std;

FileReader::FileReader(string filePath, string centPath){
    datasetPath=filePath;
    centroidsPath = centPath;
}
FileReader::~FileReader() {
    delete &(data);
    delete &(datasetPath);
    delete &(centroidsPath);
    return;

}

// std::array<FileReader::Point, FileReader::maxDataSize>
bool FileReader::getDataOutput() {

    bool fileReaded = false;
    bool centroidsReaded = false;
    fileReaded = readDatasetFromFile(datasetPath);
    centroidsReaded = readCentroidsFromFile(centroidsPath);

    if(fileReaded&&centroidsReaded){
        //cout<< "\ndataset acquired\n";
        return true;
    }
    else {
        //cout << "\nfile reading problem was encountered";
        return false;
    }

}


bool FileReader::readDatasetFromFile(string path) {

    ifstream datasetFile(path);
    string line;
    string output;
    //datasetFile.open;
    if(datasetFile.is_open()){
        //cout<<"\nreading dataset";
        //cout.flush();
        regex rgx("\\b\\d[\\d,.]+[\\d,.]\\b|\\d+");
        smatch subMatch;
        vector<float> attributes;
        int index = 0;
        while(getline(datasetFile, line)){
            //printf("\nsto leggendo velocissimo la riga: %d", index);
            attributes.clear();
            while(regex_search(line, subMatch, rgx)){
                for(auto x:subMatch) attributes.push_back(stod(x));//registra x come float in Point

                line = subMatch.suffix().str();
            }
            index++;
            Point *newEntry = new Point(attributes, index);
            data.push_back(*newEntry);

        }
        datasetFile.close();
        return true;
    }
    else {
        return false;
    }
}
bool FileReader::readCentroidsFromFile(string path) {

    ifstream datasetFile(path);
    string line;
    string output;
    //datasetFile.open;
    if(datasetFile.is_open()){
        //cout<<"\nreading centroids";
        cout.flush();
        regex rgx("\\b\\d[\\d,.]+[\\d,.]\\b|\\d+");
        smatch subMatch;
        vector<float> attributes;
        int index = 0;
        while(getline(datasetFile, line)){
            //printf("\nsto leggendo velocissimo la riga: %d", index);
            attributes.clear();
            while(regex_search(line, subMatch, rgx)){
                for(auto x:subMatch) attributes.push_back(stod(x));//registra x come float in Point

                line = subMatch.suffix().str();
            }
            index++;
            Point *newEntry = new Point(attributes, index);
            centroids.push_back(*newEntry);

        }
        datasetFile.close();
        return true;
    }
    else {
        return false;
    }
}