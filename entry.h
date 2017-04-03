//
// Created by Boris on 13/03/2017.
//

#ifndef SERIALKMEANS_ENTRY_H
#define SERIALKMEANS_ENTRY_H

#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <algorithm>
#include <vector>


class entry{
private:

    unsigned int dimAttributes;
    int id;
    int encapsulatingClusterID ;

public:
    std::vector<double> attributes;
    entry(){

    }

    entry(std::vector<double> attribs, int identifier){
        attributes = attribs;
        dimAttributes = attribs.size();
        id=identifier;

    }

    int getdimAttributes(){
        return dimAttributes;
    }

    std::vector<double> getAttributes(){
        return attributes;
    }
    int getId(){
        return id;
    }

    double getAttribute(int index){

        return attributes.at(index);
    }

    void printAttributes(){
        int size=attributes.size();

        std::cout<<"-------------------------------------------------------------------------------------";
        std::cout<<"\nattributi del punto:   "<<id<<"\n";

        for(int i=0; i<size; i++){
            std::cout<<"attributo "<<i<<":  "<<attributes.at(i)<<"   ";

        }
        std::cout<<std::endl;
        std::cout<<"------------------------------------------------------------------------------------"<<std::endl;
    }
    void printAttributes(std::string centroid){
        int size=attributes.size();

        std::cout<<"-------------------------------------------------------------------------------------";
        std::cout<<"\nattributi del centroide:   "<<id<<"\n";

        for(int i=0; i<size; i++){
            std::cout<<"attributo "<<i<<":  "<<attributes.at(i)<<"   ";
        }
        std::cout<<std::endl;
        std::cout<<"------------------------------------------------------------------------------------"<<std::endl;

    }

    std::string logAttributes(std::string output){
        int size=attributes.size();
        for(int i=0; i<size; i++){
            output += std::to_string(attributes.at(i));
            output +=" ";
        }
        output += "\n";

        return output;
    }

    void setCluster(int id){
        encapsulatingClusterID = id;
    }
    int getEncapsulatingClusterID(){
        return encapsulatingClusterID;
    }
    void setEncapsulatingClusterID(int id){
        encapsulatingClusterID=id;
    }
    void setNewAttributes(std::vector<double> attribs){
        attributes.clear();
        attributes.swap(attribs);
    }

};

#endif //SERIALKMEANS_ENTRY_H
