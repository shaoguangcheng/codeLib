#ifndef CLUSTER_H
#define CLUSTER_H

#include<vector>

//data is the data that will be clustered
//K is the the number of cluster
//N is the number of data
//tolerance is the terminal condition(write by myself)
//int *k_means(double** data, int K, long int N, int D,double tolerance,
 //   int save_way);
//
int k_means(double** data,int K,long int N,int D,
            double **now_center,int *label);

int kmeans_yakmo(int fea_n, std::vector<double> &dat, int k,
                 std::vector<double> &cents);

int feature_distribution(double **buf,int K,long int N,int D);

#if 0
void k_means(double data[N][D],int K,long int N,int D);
/*define K as the number of the clusters,N as the the number of data,D as the
number of dimisions*/

bool is_equal(int last_center[K][D],int center[K][D],int K,int D);
#endif

#endif // CLUSTER_H
