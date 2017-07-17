
#include "FileReader.h"
#include "KmeansSolver.h"
#include <string>
#include <stdlib.h>
#include <ctime>


int main() {

    int numCentroids=6;

    using namespace std;
    cout<<"\n numero di Centroidi:  "+numCentroids;
  //  std::string datasetPath = "..\\..\\dataset\\dataset.txt";
  //  std::string centersPath = "..\\..\\dataset\\centers.txt";

    std::string datasetPath = "C:\\Developer\\SerialKMeans\\dataset.txt";
    std::string centersPath = "C:\\Developer\\SerialKMeans\\centers.txt";

    FileReader *parser = new FileReader(datasetPath, centersPath);


    if(parser->getDataOutput() == false){
        return 1;
    }

    int dimCentroids = parser->getAttributesDim();
    int start_s = clock();
    KmeansSolver *solver = new KmeansSolver(parser->getData(), parser->getCenters(), numCentroids, dimCentroids);
    //a questo punto sono già costruiti e popolati i clusters (con centroidi e punti).
    solver->computeClusters();
    int stop_s = clock();
    cout << "time: " << (stop_s - start_s) / float(CLOCKS_PER_SEC) << endl;
    return 0;

}