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
#include "Point.h"
#include "cluster.h"
#include "FileWriter.h"

using namespace std;


class KmeansSolver {


private:


    FileWriter outputWriter=*(new FileWriter("..\\..\\tmp_points\\outputFile"));
    int numCentroids;
    int numAttributes;
    vector<cluster> clusters; //c'è un cluster per ogni centroide
    vector<Point> centroids ;
    vector<Point> points; //in ogni cluster ci possono essere n points

    Point* getNearestCentroid(Point, vector<Point>*);
    float getEuclideanNDistance (Point, Point);
    cluster* findClusterByID(int ID);

    void initCentroids(int num, int dim);
    void initClusters(vector<cluster> *clusters, vector<Point>* centroids);
    void addPointsToCluster();
    vector<float> getNewAttributes(vector<Point>);
    void recalculateCentroids();
    bool reAssignPointsToClusters();

    void printOutput(int n);

public:
    KmeansSolver(std::vector<Point> points, std::vector<Point> centroids, int numCentroids, int dimCentroids);
    ~KmeansSolver();
    void computeClusters();
    void printAllCentroids();
    void printAllPoints();
    void printState();
};

#endif //SERIALKMEANS_KMEANS_SOLVER_H
