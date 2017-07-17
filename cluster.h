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
#include "Point.h"
#include <list>

class cluster{

private:
    Point centroid;
    std::vector<Point> points;
    int clusterID;

public:

    cluster(Point* clusterCentroid, int id){
        centroid = (*clusterCentroid);
        clusterID = id;
    }

    Point* getCentroid(){
        return &centroid;
    }


    void deletePoints(){
      points.clear();
    };

    void setCentroid(Point* point){
        centroid = *point;
    }

    void setClusterID(int id){
        clusterID=id;
    }

    int getClusterID(){
        return clusterID;
    }


    void addPoint (Point point){
        points.push_back(point);
    }

    void printPoints(){
 /*       std::cout<<"\nID di tutti i punti appartenenti al Cluster: ";
        std::cout<<clusterID;
        std::cout<<" __\n";
        for (std::vector<Point>::iterator it=(points).begin(); it!=(points).end(); ++it){ //ad ogni cluster assegno un centroide
            std::cout<< it->getId()<<",  ";
        };*/
        std::cout<<"\n";
    }

    void changeCentroidAttributes(std::vector<float> attributes){
        centroid.setNewAttributes(attributes);
    }

    std::vector<Point> getPoints(){
        return points;
    }





};

#endif //SERIALKMEANS_CLUSTER_H
