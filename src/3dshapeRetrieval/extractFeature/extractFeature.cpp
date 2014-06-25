#include "extractFeature.h"
#include "parameter.h"

#include <iostream>

using namespace std;

void help()
{
    cout << "======================================================="<< endl;
    cout << "[usage] : extractFeature depthImagePath nVoacabulary knn llcMethod lambda" << endl;
    cout << "=======================================================" << endl;
}

int main(int argc,char* argv[])
{
    if(argc < 3){
        help();
        return -1;
    }

    uint64 start = getTickCount();

    parameter::imageFilePath = string(argv[1]);
    parameter::nVocabulary = atoi(argv[2]);

    if(argc >= 4)
        parameter::knn = atoi(argv[3]);
    if(argc >= 5)
        parameter::method = parameter::LLCMethod(atoi(argv[4]));
    if(argc >= 6)
        parameter::lambda =atof(argv[5]);

    parameter p;
    p.saveParameters();
    p.print();

    vector<SiftDescriptor> siftDescriptorForAll,siftDescriptorAfterMerge;
    extractSiftDescriptor(parameter::imageFilePath,siftDescriptorForAll);
    mergeModelSiftDescriptor(siftDescriptorForAll,siftDescriptorAfterMerge);

    vector<BOWDescriptor> bow;
    computeBOW(siftDescriptorAfterMerge,parameter::nVocabulary,bow,true);
  //  computeLLCBOW(siftDescriptorAfterMerge,parameter::nVocabulary,bow);

  //  vector<TF_IDF> tf_idf;
  //  calTF_IDF(bow,tf_idf);

  //  vector<ZCA> zca;
  //  cal_ZCA(bow,zca,true);

    uint64 finish = getTickCount();

    cout << "===================================" << endl;
    cout << "depth images path    : " << parameter::imageFilePath << endl;
    cout << "total models         : " << bow.size() << endl;
    cout << "number of vocabulary : " << parameter::nVocabulary << endl;
    cout << "time consumed        : " << (finish-start)/getTickFrequency() << endl;
    cout << "===================================" << endl;

    return 0;
}
