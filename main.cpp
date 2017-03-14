
#include "FileReader.h"
#include "KmeansSolver.h"
#include <string>
#include <stdlib.h>
#include <ctime>


int main(int numCentroids) {
    srand((unsigned)time(nullptr));
    using namespace std;
    cout<<"\n"+numCentroids;
    std::string filePath = "C:\\Users\\Boris\\ClionProjects\\SerialKMeans\\dataset\\dataset_prova.txt";
    FileReader *parser = new FileReader(filePath);

    if(parser->getDataOutput() == false){
        return 1;
    }

    int dimCentroids = parser->getAttributesDim();
    KmeansSolver *solver = new KmeansSolver(parser->getData(), numCentroids, dimCentroids);

    cout<<"\n \nguarda un po' se va bene vai";

    //adesso vengono inizializzati correttamente i cluster (con i punti ed i centroidi)
    //c'è da fare la parte che ricalcola i centroidi in funzione dei punti e poi credo basti iterare

    return 0;

}