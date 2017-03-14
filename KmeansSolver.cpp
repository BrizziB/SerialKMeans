//
// Created by Boris on 13/03/2017.
//
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "KmeansSolver.h"
#include <random>


KmeansSolver::KmeansSolver(std::vector<entry> *dataPts, int numCentroids, int dimCentroids) {

    points=dataPts; //gli passo il puntatore al vettore, dovrebbe essere così che si fa il passaggio per riferimento in c++

    initCentroids(numCentroids, dimCentroids, &centroids);
    initClusters(&clusters, &centroids);
    addPointsToCluster();
    //!for test
    for(std::list<cluster>::iterator itr=(clusters).begin(); itr!=(clusters).end(); itr++){
        cout<<(*itr).getClusterID();
        cout<<endl;
        (*itr).printPoints();
        cout<<"\n --------------------------------------------- \n";
    }
    //for test
}
void KmeansSolver::initCentroids(int num, int dim, std::vector<entry> *centroids){
    double upperBound =10, lowerBound = -10; //questi potrebbero essere il massimo ed il minimo fra ogni attributo di ogni punto
    int range = upperBound-lowerBound;
    std::vector<double> attribs;

    double tmpAttrib;
    int index;

    std::mt19937 rng;
    std::uniform_real_distribution<double> dist(-5, 5);  //(min, max)
    rng.seed(std::random_device{}()); //non-deterministic seed
    vector<double> tmpRandomArray;
    double tmp;
    for(int i=0; i<num*dim; i++){
        tmp =dist(rng);
        cout<<tmp;
        cout<<endl;
        tmpRandomArray.push_back(tmp);
    }

    for(int i=0; i<num; i++){ //scorro ogni centroide - alla fine sto creando "num" entry
        //per ora inizializzo i centroidi con valori casuali di ogni attributo presi fra -10 e 10, poi si inseriranno metodi basati sui valori dei data

        attribs.reserve(dim);
        attribs={};
        for(int j=0; j<dim; j++){ //scorro gli attributi di ogni centroide
            index = (i+1)*(j+1)-1;
            tmpAttrib = tmpRandomArray.at(index);
            attribs.push_back(tmpAttrib);
            std::cout<<"\nattributo  ";
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

entry* KmeansSolver::getNearestCentroid(entry point, std::vector<entry>* centroids){

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

    for(std::list<cluster>::iterator itr=clusters.begin(); itr!=clusters.end(); ++itr){
        if(itr->getClusterID() == id)
            return &(*itr);
    }

}

void KmeansSolver::addPointsToCluster(){

    cluster* wrappingCluster;
    entry* nearestCentroid;

    for(std::vector<entry>::iterator itr=(*points).begin(); itr!=(*points).end(); ++itr){

        nearestCentroid = getNearestCentroid((*itr), &centroids); //trovato il centroide più vicino al punto
        wrappingCluster = findClusterByID(nearestCentroid->getId());
        wrappingCluster->addPoint((*itr));

    }

};