#include"cluster.h"
#include<stdlib.h>
#include<math.h>
#include<float.h>
#include<stdio.h>
#include<string.h>

#include "yakmo.h"

#define DEBUG 0

int kmeans_yakmo(int fea_n, std::vector<double> &dat, int k,
                 std::vector<double> &cents)
{
    int argc_ = 8;
    const char *argv_[] = {
        "./yakmo",
        "-k", "4",
        "-v", "0",
        "covtype", "cents", "-",
    };

    int                         instant = 0;
    int                         cents_m;

    yakmo::option               opt(argc_, (char **)argv_);
    yakmo::orthogonal_kmeans    *m;

    // set parameters
    opt.m = 1;
    opt.k = k;

    // create k-means objects
    m = new yakmo::orthogonal_kmeans (opt);

    // run k-means
    m->train_from_data(fea_n, dat,
                       opt.m, opt.output,
                       opt.mode != yakmo::option::TRAIN, instant);

    // save centers
    m->get_cents(cents, cents_m);

    return 0;
}



int k_means(double** data,int K,long int N,int D,
            double **now_center,int *label){
    double tolerance = 1e-6;

    int* counter   = (int*)calloc(K,sizeof(int)); //the size of every cluster

//    double** now_center  = (double**)calloc(K,sizeof(double*));

    double** cluster_data = (double**)calloc(K,sizeof(double*));

    int i = 0;
    int j = 0;
    int k = 0; //define the loop flag vairable
               //i--cluster number,j--data number,k--dimision

    double last_error = 0;
    double now_error  = 0;//define the square sum of distance

    //pick K data points as the initial center
    for(i = 0,j = 0;i < K;j += N/K,i++){

        cluster_data[i] = (double*)calloc(D,sizeof(double));
//        now_center[i]   = (double*)calloc(D,sizeof(double));

        for(k = 0;k < D;k++){
            now_center[i][k] = data[j][k];
        }

    }

    do{
        //update the error
        last_error = now_error;
        now_error  = 0;

        //clear the counter and cluster_data
        for(i = 0;i < K;i++){
            counter[i] = 0;
            for(k = 0;k < D;k++){
                cluster_data[i][k] = 0;
            }
        }

        //compute the closest cluster and update the label
        for(j = 0;j < N;j++){
            double min_distance = DBL_MAX;
            for(i = 0;i < K;i++){
                double distance = 0;
                for(k = 0;k < D;k++){
                    distance += pow(data[j][k]-now_center[i][k],2);
                }
                if(distance < min_distance){
                    min_distance = distance;
                    label[j]     = i;
                }
            }

		//update the number of every cluster
	     counter[label[j]]++;

        //update the cluster size and cluster data
            for(k = 0;k < D;k++){
	//			printf("%d ",counter[label[j]]);
                cluster_data[label[j]][k] += data[j][k];
            }

            now_error += min_distance;
        }

        //update the cluster center
        for(i = 0;i < K;i++){
            for(k = 0;k < D;k++){
//				printf("%lf ",cluster_data[i][k]);
//				printf("%d ",counter[i]);
                now_center[i][k] = cluster_data[i][k]/counter[i];

            }
        }

    }while(fabs(last_error-now_error) > tolerance);

#if 0
    //save the cluster center
    FILE *center;

    center = fopen("../scene_recognition/Data/cluster_center.txt","w");
    if(center == NULL){
        printf("can not open the %s!\n","cluster_center.txt");
        exit(1);
    }

//    int num = 0;
    for(i = 0;i < K;i++){
        for(k = 0;k < D;k++){
            fprintf(center,"%lf ",now_center[i][k]);
        }
       fprintf(center,"\n");
    }

    fclose(center);

    //save the cluster data
    FILE *cluster_dat;

    cluster_dat = fopen("../scene_recognition/Data/cluster_data.txt","w");
    if(cluster_dat == NULL){
        printf("can not open the cluster_data.txt!\n");
        exit(1);
    }

//    num = 0;
    #if save_way
        for(i = 0;i < K;i++){
            fprintf(cluster_dat,"the %d cluster data :\n",i+1);
            for(j = 0;j < N;j++){
                if(label[j] == i)
                    for(k = 0;k < D;k++){
                        fprintf(cluster_dat,"%lf ",data[j][k]);
     //                   num++;
     //                   if(num == 20){
      //                      fprintf(cluster_dat,"\n");
     //                       num =0;
     //                    }
                    }
            }
            fprintf(cluster_dat,"\n");
        }
    #else
    int index = 0;
    for(j = 0;j < N;j++){
        fprintf(cluster_dat,"%d ",label[j]);
        for(k = 0;k < D;k++){
            if(data[j][k] == 0)
                index++;
            else{
                index++;
                fprintf(cluster_dat,"%d:%lf ",index,data[j][k]);
             }
        }

    }
    #endif
    fclose(cluster_dat);
#endif

    //free the space
    for(i = 0;i < K;i++){
        free(cluster_data[i]);
//        free(now_center[i]);
    }
//    free(label);
    free(counter);
    return 0;
 }

int feature_distribution(double **buf,int K,long int N,int D)
{
	double **vocabulary = (double**)calloc(K,sizeof(double*));
	double **data = (double**)calloc(N,sizeof(double*));
	for(int i=0;i<K;i++){
		vocabulary[i] = (double*)calloc(D,sizeof(double));
	}
	for(int i=0;i<N;i++){
		data[i] = (double*)calloc(D,sizeof(double));
	}
	double *temp = (double*)calloc(K,sizeof(double));

    //read cluster center
	FILE* fp_voc;
    fp_voc =fopen("../scene_recognition/Data/cluster_center.txt","r");
	if(fp_voc == NULL){
		printf("can not open the %s file\n","cluster_center");
		exit(1);
	}
	for(int i=0;i<K;i++){
		for(int j=0;j<D;j++){
			fscanf(fp_voc,"%lf ",&vocabulary[i][j]);
		}
	}
	fclose(fp_voc);

    double delta_square = 0;
    //compute the value of delta
    for(int i=0;i<K-1;i++){
        double center_sum =0;
        for(int j=i+1;j<K;j++){
            for(int k=0;k<D;k++){
                center_sum += pow(vocabulary[i][k]-vocabulary[j][k],2);
            }
            if(delta_square < center_sum)
                delta_square = center_sum;
        }
    }
    printf("delta_square = %lf\n",delta_square);

    //read cluster data
	FILE* fp_data;
    fp_data =fopen("../scene_recognition/Data/bow_dat.txt","r");
	if(fp_data == NULL){
        printf("can not open the %s file\n","bow_dat.txt");
		exit(1);
	}
	for(int i=0;i<N;i++){
		for(int j=0;j<D;j++){
			fscanf(fp_data,"%lf ",&data[i][j]);
		}
	}
	fclose(fp_data);

#if DEBUG
    printf("N=%d\n",N);
    printf("K=%d\n",K);
    printf("D=%d\n",D);
#endif

	for(int i=0;i<N;i++){
#if DEBUG
		printf("i=%d",i);
#endif
        for(int j=0;j<K;j++){
			double sum = 0;

			for(int k=0;k<D;k++){
#if DEBUG
				printf("voc=%lf\ndata=%lf\n",vocabulary[j][k],data[i][k]);
#endif
				sum += pow(vocabulary[j][k]-data[i][k],2);
			}
            temp[j] = exp(-1*sum/(2*delta_square));
		}
		double sum_generalize = 0;
		for(int j=0;j<K;j++){
			sum_generalize += temp[j];
		}
		for(int j=0;j<K;j++){
			buf[i][j] = temp[j]/sum_generalize;
		}
	}
	free(temp);
	for(int i=0;i<K;i++){
		free(vocabulary[i]);
		free(data[i]);
	}
	return 0;
}

#if 0
void k_means( const double data[N][D],int K,long int N,int D ){
	int last_center[K][D]={0};
	int center[K]{D}={0};
	double cluster_data[K][N]={0};
	
	//初始化聚类中心
	int init[K];
    time_t t;

    srand((int)(time(0)));

    for(int i=0;i<K;i++){
        init[i] = (int)(N*rand()/(RAND_MAX+1.0));
    }

	for(i=0;i<K;i++){
		for(int j=0;j<D;j++){
			center[i][j] = data[init[i]][j];
		}
	}
	//聚类
	while(!is_equal(data[N][D],last_center[K][D],center[K][D],K,D)){

		double distance[K] = {0};
		int    pos[K]      = {0};

		int index = 0;

		for(int i=0;i<N;i++){
			distance = computer_distance(data[i]);

			index	 = min_index(distance);	//index为距第i个数据最近的质心索引号
			cluster_data[index][pos[index]++] = i;
		}

		for(i=0;i<K;i++){
			for(j=0;j<D;j++){
				last_center[i][j] = center[i][j];
			}
		}
		
		double sum = 0;
		for(i=0;i<K;i++){
			for(int j =0;j<D;j++)
				for(int k =0;k<pos[i];k++){
					sum = sum+data[cluster_data[i][k]][j];
				}
				center[i][j] = sum/pos[i];
		}

    }

	for(i=0;i<K;i++){
		for(j=0;j<D;j++){
			printf("%f ",center[i][j]);
		}
		printf("\n");
	}

	//保存类中心
	FILE* fp;

    fp=fopen("../scene_recognition/cluster_data.txt","w");
	if(fp==NULL){
		printf("can not open the file!");
	}

	for(i=0;i<K;i++){
		fprintf(fp,"第%d个类中心为：\n",i);
		for(j=0;j<D;j++){
			fprintf(fp,"%f ",center[i][j]);
		}
		fprintf(fp,"\n");
	}

	fclose(fp);

	//保存每类数据
	FILE* dat;

	dat = fopen("cluster_data.txt","w");
	if(dat==NULL){
		printf("can not open the file!");
	}

	for(i=0;i<K;i++){
		fprintf("第%d类数据：\n",i);
		for(j=0;j<pos[i];j++){
			for(k=0;k<D;k++){			
				fprintf(dat，"&f ",data[cluster_data[i][j]][k]);
			}
		}
		fprintf(dat,"\n");
	}
	fclose(fp);
}



bool is_equal(const double data[N][D],int last_center[K][D],int center[K][D],int K,int D){
	double sum =0;
	double cluster_data;
	int j = 0;

	while(j<K){
		for(i=0;i<D;i++){
			sum += (center[j][i] - last_center[j][i])
				*(center[j][i] - last_center[j][i]);
		}
		j++;
	}
	
	if(sqrt(sum)<EPS)
		return 1;
	else
		return 0;
}

#endif


