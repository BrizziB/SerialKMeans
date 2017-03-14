//
// Created by Boris on 13/03/2017.
//

#ifndef SERIALKMEANS_KMEANS_SOLVER_H
#define SERIALKMEANS_KMEANS_SOLVER_H
#include <iostream>
#include <string>
#include <iterator>
#include <algorithm>
#include <vector>
#include <list>
#include "FileReader.h"
#include "entry.h"
#include "cluster.h"
using namespace std;


class KmeansSolver {


private:
    list<cluster> clusters; //c'è un cluster per ogni centroide
    vector<entry> centroids ;
    vector<entry> *points; //in ogni cluster ci possono essere n points

    entry* getNearestCentroid(entry, vector<entry>*);
    double getEuclideanNDistance (entry, entry);
    cluster* findClusterByID(int ID);

    void initCentroids(int num, int dim, std::vector<entry> *centroids);
    void initClusters(list<cluster> *clusters, vector<entry>* centroids);

public:


    KmeansSolver(std::vector<entry> *points, int numCentroids, int dimCentroids);
    ~KmeansSolver();
    void addPointsToCluster();

};

#endif //SERIALKMEANS_KMEANS_SOLVER_H
