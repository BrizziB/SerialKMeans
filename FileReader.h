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
#include "Point.h"

class FileReader {


private:

    std::vector<Point> data ;
    std::string datasetPath;
    std::string centroidsPath;
    std::vector<Point> centroids;
    bool readDatasetFromFile(std::string path);
    bool readCentroidsFromFile(std::string path);

public:
    ~FileReader();
    FileReader(std::string filePath, std::string centroidsPath);
    //fai il distruttore poi !!
    bool getDataOutput();
    std::vector<Point> getData(){
        return (data);
    }
    std::vector<Point> getCenters(){
        return (centroids);
    }
    int getAttributesDim(){
        return data[0].getdimAttributes();
    }


};


#endif //SERIALKMEANS_DATAPARSER_H
