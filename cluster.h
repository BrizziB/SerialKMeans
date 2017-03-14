//
// Created by Boris on 13/03/2017.
//

#ifndef SERIALKMEANS_CLUSTER_H
#define SERIALKMEANS_CLUSTER_H

#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <algorithm>
#include <vector>
#include "entry.h"
#include <list>

class cluster{

private:
    entry* centroid;
    std::list<entry> points;
    int clusterID;

public:

    cluster(entry* clusterCentroid, int id){
        centroid = clusterCentroid;
        clusterID = id;
    }

    entry* getCentroid(){
        return centroid;
    }

    void setCentroid(entry* point){
        centroid = point;
    }

    void setClusterID(int id){
        clusterID=id;
    }

    int getClusterID(){
        return clusterID;
    }


    void addPoint (entry point){
        points.push_back(point);
    }

    void printPoints(){
        for (std::list<entry>::iterator it=(points).begin(); it!=(points).end(); ++it){ //ad ogni cluster assegno un centroide
            std::cout<<"\n";
            std::cout<< it->getId();
        };
    }

};

#endif //SERIALKMEANS_CLUSTER_H
