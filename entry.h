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
    std::vector<double> attributes;
    unsigned int dimAttributes;
    int id;
    int encapsulatingClusterID ;

public:

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

    void setCluster(int id){
        encapsulatingClusterID = id;
    }
    int getEncapsulatingClusterID(){
        return encapsulatingClusterID;
    }

};

#endif //SERIALKMEANS_ENTRY_H
