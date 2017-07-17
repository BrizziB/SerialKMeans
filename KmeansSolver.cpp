//
// Created by Boris on 13/03/2017.
//
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "KmeansSolver.h"
#include <random>


KmeansSolver::KmeansSolver(std::vector<Point> dataPts, std::vector<Point> cents, int numC, int numA) {

    numCentroids=numC;
    numAttributes=numA;
    points=dataPts;

    centroids = cents;
    initClusters(&clusters, &centroids);
    addPointsToCluster();

}
void KmeansSolver::initCentroids(int num, int dim){
    float upperBound =10, lowerBound = -10; //questi potrebbero essere il massimo ed il minimo fra ogni attributo di ogni punto
    int range = upperBound-lowerBound;
    std::vector<float> attribs;

    float tmpAttrib;
    int index;

    std::mt19937 rng;
    rng.seed(std::random_device{}()); //non-deterministic seed
    std::uniform_int_distribution<int> dist(-10, 10);  //(min, max)
    std::vector<float> tmpRandomArray;
    //float tmpRandomArray[num*dim]= {1, 4, 3, 2, 3, 3, 4, 1};
    float tmp;
    for(int i=0; i<num*dim; i++) {
        tmp = (float)dist(rng);
        tmpRandomArray.push_back(tmp);
    }

    for(int i=0; i<num; i++){ //scorro ogni centroide - alla fine sto creando "num" Point
        //per ora inizializzo i centroidi con valori casuali di ogni attributo presi fra -10 e 10, poi si inseriranno metodi basati sui valori dei data
        attribs.clear();
        for(int j=0; j<dim; j++){ //scorro gli attributi di ogni centroide
            index = (i+1)*(j+1)-1;
            tmpAttrib = tmpRandomArray[index];
            attribs.push_back(tmpAttrib);
            std::cout<<"\nattributo  ";
            std::cout<<attribs.at(j);
            std::cout<<"\n";

        }
        Point newEntry = *(new Point(attribs, i));
        (centroids).push_back(newEntry);

    }
};

void KmeansSolver::initClusters(vector<cluster>* clusters, vector<Point>* centroids){
    for (std::vector<Point>::iterator it=(*centroids).begin(); it!=(*centroids).end(); ++it){ //per ogni centroide inizializzo un cluster

        (*it).setEncapsulatingClusterID((*it).getId());
        cluster* newCluster = new cluster(&(*it), it->getId()); //NB centroidi e cluster hanno il medesimo ID


        clusters->push_back(*newCluster);
    };

};

float KmeansSolver::getEuclideanNDistance(Point point, Point centroid){

    float distance=0;
    for(int i=0; i<point.getdimAttributes(); i++){ //scorre tutti gli attributi e ne somma il quadrato della differenza
        distance += pow((point.getAttributes()[i] - centroid.getAttributes()[i]), 2.0d);
    }
    return sqrt(distance);

}

Point* KmeansSolver::getNearestCentroid(Point point, std::vector<Point>* centroids){

    float minDistance=100000;

    Point* closestCentroid;
    float distance;
    for(std::vector<Point>::iterator itr=(*centroids).begin(); itr!=(*centroids).end(); ++itr){
        distance = getEuclideanNDistance(point, *itr);

        if(minDistance > distance){
            minDistance = distance;
            closestCentroid = &(*itr);
        }

    }
    return closestCentroid;
}

cluster* KmeansSolver::findClusterByID(int id){
    //qui si potrebbe fare meglio usando una struttura dati migliore tipo una mappa, farebbe in tempo costante invece che in n..
    for(std::vector<cluster>::iterator itr=clusters.begin(); itr!=clusters.end(); ++itr){
        if(itr->getClusterID() == id)
            return &(*itr);
    }
    return nullptr;
}

void KmeansSolver::addPointsToCluster(){

    cluster* wrappingCluster;
    Point* nearestCentroid;

    for(std::vector<Point>::iterator itr=(points).begin(); itr!=(points).end(); ++itr){

        nearestCentroid = getNearestCentroid((*itr), &centroids); //trovato il centroide più vicino al punto
        wrappingCluster = findClusterByID(nearestCentroid->getId());
        wrappingCluster->addPoint((*itr));

    }

};

std::vector<float> divideAllAttributesBy(vector<float> attributes, float num){
    std::vector<float> tmp;
    for(int i=0; i<attributes.size(); i++){
        tmp[i]=attributes[i]/num;
    }
    return tmp;
}

vector<float> KmeansSolver::getNewAttributes(vector<Point> points){
    int numAttributes = KmeansSolver::numAttributes;
    int numPoints = points.size();
    float sum[numAttributes];
    for(int j=0; j<numAttributes; j++){
        sum[j] = 0;
    }
    for(int i=0; i<numPoints; i++){
        for(int j=0; j<numAttributes; j++){
            sum[j] += points.at(i).getAttribute(j);
        }
    }

    for(int j=0; j<numAttributes; j++){
        sum[j] = sum[j]/numPoints;
    }
    vector<float> tmp(sum, sum +sizeof(sum)/ sizeof(sum[0]) );

    return tmp;
}

void KmeansSolver::recalculateCentroids(){
    centroids.clear();
    Point centroid;
    vector<cluster>::iterator iterator =clusters.begin();
    for(int i=0; i<clusters.size(); i++){
        vector<Point> tmpPts = iterator->getPoints();

        vector<float> tmp=(getNewAttributes(tmpPts));
        centroid = (*new Point(tmp, iterator->getClusterID()));
        centroid.setEncapsulatingClusterID(iterator->getClusterID());

        centroids.push_back(centroid);
        iterator->setCentroid(&centroid);

        ++iterator;
    }

    //}
}

bool KmeansSolver::reAssignPointsToClusters(){

    cluster* wrappingCluster;

    for(std::vector<cluster>::iterator itr=(clusters).begin(); itr!=(clusters).end(); ++itr){
        itr->deletePoints();
    }

    int nearestCentroidID;
    int currentCentroidID;
    int changed=0;
    bool significantChange = false;
    int numPts = points.size();

    for(std::vector<Point>::iterator itr=(points).begin(); itr!=(points).end(); ++itr){

        currentCentroidID = (*itr).getEncapsulatingClusterID();
        nearestCentroidID = (*getNearestCentroid((*itr), &centroids)).getId(); //trovato il centroide più vicino al punto
        if(currentCentroidID != nearestCentroidID){
            changed++;
        }
        wrappingCluster = findClusterByID(nearestCentroidID);
        wrappingCluster->addPoint((*itr));
        (*itr).setEncapsulatingClusterID(wrappingCluster->getClusterID());
    }

    if(changed > numPts/500){
        significantChange = true;
    }

    return significantChange;
}

void KmeansSolver::computeClusters() {
    bool changeHappened;
    int i=0;
    //printOutput(i);
    do{

        cout<<"############## iterazione numero:  "<< i<<"  ################\n";

        recalculateCentroids();
        changeHappened = reAssignPointsToClusters();
        //printState();
       //printOutput(i+1);
        i++;

        //cout<<"##############################################################\n\n\n";
    }
    while(changeHappened);
    for(Point centroid:centroids){
        centroid.printAttributes();
    }
}

void KmeansSolver::printOutput(int num){

    std::string output ="";
    output += std::to_string(points.size());
    output += "\n";
/*    output += std::to_string(centroids.size());
    output += "\n";*/
    std::vector<float> attribs;
    for(std::vector<cluster>::iterator itr=(clusters).begin(); itr!=(clusters).end(); ++itr){


        //stampo attributi del centroide
        attribs= itr->getCentroid()->getAttributes();
        for(int i=0; i<attribs.size(); i++){
            output += std::to_string(attribs.at(i));
            output += " ";
        }

        output += "\n";
        std::vector<Point> clusterPoints = itr->getPoints();


        //stampo gli attributi di ogni punto del cluster
        for(std::vector<Point>::iterator it=clusterPoints.begin(); it!=clusterPoints.end(); ++it){
            attribs = it->getAttributes();
            for(int i=0; i<attribs.size(); i++){
                output += std::to_string(attribs.at(i));
                output += " ";
            }
            output += "\n";
        }

        output += "\n";
    }

    //! si itera sui ogni cluster e di questo si stampa il centroide ed i points. così i punti sono già pronti per essere rappresentati

    outputWriter.writeFile(output, num);

    //imposta il path in cui scrivere il file e richiama il metodo di write passandogli a stringa da inserire nel file

}

void KmeansSolver::printState(){
    cout<<"\n---------------------------------------------------------------------------------------\n";
    for(std::vector<cluster>::iterator itr=(clusters).begin(); itr!=(clusters).end(); ++itr){

        //itr->printPoints();

        //itr->getCentroid()->printAttributes("test");

        std::vector<Point> clusterPoints = itr->getPoints();
        for(std::vector<Point>::iterator it=clusterPoints.begin(); it!=clusterPoints.end(); ++it){
            it->printAttributes();
        }


    }
}








