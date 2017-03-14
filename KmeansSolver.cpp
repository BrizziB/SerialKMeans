//
// Created by Boris on 13/03/2017.
//
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "KmeansSolver.h"


KmeansSolver::KmeansSolver(std::vector<entry> *dataPts, int numCentroids, int dimCentroids) {

    points=dataPts; //gli passo il puntatore al vettore, dovrebbe essere così che si fa il passaggio per riferimento in c++
    std::vector<entry> *centroidsTmp;

    (*centroids).push_back(*(points->begin()));
    initCentroids(numCentroids, dimCentroids, centroids);
   // initClusters(clusters, centroids);
    //addPointsToCluster();
}
void KmeansSolver::initCentroids(int num, int dim, std::vector<entry> *centroids){
    srand(time(NULL));//per ora inizializzo i centroidi con valori casuali di ogni attributo presi fra -10 e 10, poi si inseriranno metodi basati sui valori dei data
    double upperBound =10, lowerBound = -10; //questi potrebbero essere il massimo ed il minimo fra ogni attributo di ogni punto
    int range = upperBound-lowerBound;
    std::vector<double> attribs;

    for(int i=0; i<num; i++){ //scorro ogni centroide - alla fine sto creando "num" entry
        attribs={};
        for(int j=0; j<dim; j++){ //scorro gli attributi di ogni centroide
            attribs.push_back(rand()%20 -10);
            std::cout<<"attributo\n";
            std::cout<<attribs[j];
            std::cout<<"\n";
        }
        entry* newEntry = new entry(attribs, i);
        (*centroids).push_back(*newEntry);// questo fa crashare ogni cosa LOL segmentation fault
    }
};

void KmeansSolver::initClusters(list<cluster>* clusters, vector<entry>* centroids){
    for (std::vector<entry>::iterator it=(*centroids).begin(); it!=(*centroids).end(); ++it){ //per ogni centroide inizializzo un cluster

        cluster* newCluster = new cluster(&(*it), it->getId()); //NB centroidi e cluster hanno il medesimo ID


        clusters->push_back(*newCluster);
    };

};


double KmeansSolver::getEuclideanNDistance(entry point, entry centroid){

    double distance=0;
    for(int i=0; i<point.getdimAttributes(); i++){ //scorre tutti gli attributi e ne somma il quadrato della differenza
        distance += pow((point.getAttributes()[i] - centroid.getAttributes()[i]), 2.0d);
    }
    return sqrt(distance);

}

entry* KmeansSolver::getNearestCentroid(entry point, std::vector<entry>* centroids){ //scorre tutti i centroidi e trova quello più vicino a point

    double minDistance=100000;

    entry* closestCentroid;
    double distance;
    for(std::vector<entry>::iterator itr=(*centroids).begin(); itr!=(*centroids).end(); ++itr){
        distance = getEuclideanNDistance(point, *itr);

        if(minDistance > distance){
            minDistance = distance;
            closestCentroid = &(*itr);
        }

    }
    return closestCentroid;
}

cluster* KmeansSolver::findClusterByID(int id){

    for(std::list<cluster>::iterator itr=(*clusters).begin(); itr!=(*clusters).end(); ++itr){
        if(itr->getClusterID() == id)
            return &(*itr);
    }

}

void KmeansSolver::addPointsToCluster(){

    cluster* wrappingCluster;
    entry* nearestCentroid;

    for(std::vector<entry>::iterator itr=(*points).begin(); itr!=(*points).end(); ++itr){

        nearestCentroid = getNearestCentroid((*itr), centroids); //trovato il centroide più vicino al punto
        wrappingCluster = findClusterByID(nearestCentroid->getId());
        wrappingCluster->addPoint((*itr));


    }

};