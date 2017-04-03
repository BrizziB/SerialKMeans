//
// Created by Boris on 25/03/2017.
//

#ifndef SERIALKMEANS_FILEWRITER_H
#define SERIALKMEANS_FILEWRITER_H

#include <string>
#include <iostream>
#include <fstream>
#include <regex>

class FileWriter {
private:
    std::string outputPath;

public:
    FileWriter( std::string folderPath){
        outputPath=folderPath;
    }
    void setOutputPath(std::string folderPath){
        outputPath=folderPath;
    }
    bool writeFile(std::string log, int fileNum){

        std::string index = std::to_string(fileNum);
        std::string fileName;
        fileName+=outputPath;
        fileName+=std::to_string(fileNum);
        fileName+=".txt";

        std::ofstream out(fileName);
        try{
            out << log;
        }
        catch(std::ofstream::failure f){
            std::cout<<"Failed writing file:  "<<f.what()<< std::endl;
            return false;
        }
        out.close();
        return true;

    }


};


#endif //SERIALKMEANS_FILEWRITER_H
