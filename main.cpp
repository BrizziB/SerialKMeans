
#include "FileReader.h"
#include "KmeansSolver.h"
#include <string>
#include <stdlib.h>
#include <ctime>


int main() {

    int numCentroids=4;

    using namespace std;
    cout<<"\n numero di Centroidi:  "+numCentroids;
    std::string datasetPath = "..\\..\\dataset\\dataset_prova.txt";
    FileReader *parser = new FileReader(datasetPath);


    if(parser->getDataOutput() == false){
        return 1;
    }

    int dimCentroids = parser->getAttributesDim();
    KmeansSolver *solver = new KmeansSolver(parser->getData(), numCentroids, dimCentroids);
    //a questo punto sono già costruiti e popolati i clusters (con centroidi e punti).
    solver->computeClusters();


    return 0;

}