//
// Created by Boris on 06/03/2017.
//

#ifndef SERIALKMEANS_DATAPARSER_H
#define SERIALKMEANS_DATAPARSER_H
#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <algorithm>
#include <vector>
#include "entry.h"

class FileReader {


private:

    ~FileReader();
    std::vector<entry> data ;
    std::string path;
    std::vector<entry> centroids;
    bool readFromFile(std::string path);


public:
    FileReader(std::string filePath);
    //fai il distruttore poi !!
    bool getDataOutput();
    std::vector<entry>* getData(){
        return &(data);
    }
    int getAttributesDim(){
        return data[0].getdimAttributes();
    }


};


#endif //SERIALKMEANS_DATAPARSER_H
