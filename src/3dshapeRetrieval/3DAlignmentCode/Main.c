#define GLUT_DISABLE_ATEXIT_HACK

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <time.h>
#include <float.h>
#include <string.h>
#include <limits.h>

#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>

#include "win_types.h"
#include "Ds.h"
#include "RWObj.h"
#include "Bitmap.h"
#include "TranslateScale.h"
#include "Rotate.h"
#include "RegionShape.h"
#include "RecovAffine.h"
#include "Refine.h"
#include "Edge.h"
#include "convert.h"
#include "ColorDescriptor.h"
#include "Circularity.h"
#include "FourierDescriptor.h"
#include "Eccentricity.h"

#define abs(a) (a>0)?(a):-(a)

#define	QUANT8				256		// 2^8
#define FD_SCALE			2		// *2 first, and then quantization
#define CIR_SCALE			2.318181818		// the range of circularity is [0~110], so *2.318 to be [0~255]
#define ECC_SCALE			25.5			// the range of circularity is [0~10], so *25.5 to be [0~255]

unsigned char	CamMap[CAMNUM_2]={0,1,2,3,4,5,6,7,8,9,5,6,7,8,9,2,3,4,0,1};

char srcfn[100];
char destfn[100];

int			winw = WIDTH, winh = HEIGHT;

pVer		vertex=NULL;
pTri		triangle=NULL;
int			NumVer=0, NumTri=0;		// total number of vertex and triangle.

pVer		vertex1, vertex2;
pTri		triangle1, triangle2;
int			NumVer1, NumTri1, NumVer2, NumTri2;		// total number of vertex and triangle.

// translate and scale of model 1 and 2
Ver				Translate1, Translate2;
double			Scale1, Scale2;

void FindCenter(unsigned char *srcBuff, int width, int height, double *CenX, double *CenY)
{
    int					x, y, count;
    unsigned char		*pImage;
    int					maxX, minX, maxY, minY;
    int					MeanX, MeanY;

    count = 0;
    pImage = srcBuff;

    // ***********************************************************************************************
    // if use "mean" to each 2D shape independnetly, the origin will be moved a lot in 3D
    // if ues "center" to each 2D shape independnetly, the origin will be moved only a little in 3D
    // if center can be defined in 3D, the origin will not be moved any more.
    // But this will not very robust in 3D similarity transformation
    // In addition, to make center of each 2D shape more close to user drawn 2D shapes,
    // it's better to define center for each 2D shape independently

    // uee center of max and min to be center
    maxX = maxY = -1;
    minX = minY = INT_MAX;
    for (y=0 ; y<height ; y++)
    for (x=0 ; x<width; x++)
    {
        if( *pImage < 255 )
        {
            if( x > maxX ) maxX = x;
            if( x < minX ) minX = x;
            if( y > maxY ) maxY = y;
            if( y < minY ) minY = y;
        }
        pImage++;
    }

    if( maxX > 0 )
    {
        *CenX = (maxX+minX) / 2.0;
        *CenY = (maxY+minY) / 2.0;
    }
    else
        *CenX = *CenY = -1;		// nothing to be rendered
}

void display(void)
{
    int				i, j;
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
//		glColor3f((GLfloat)0.0, (GLfloat)0.0, (GLfloat)0.0);
        for(i = 0; i<NumTri; i++)
        {
            glColor3f((GLfloat)triangle[i].r, (GLfloat)triangle[i].g, (GLfloat)triangle[i].b);
            glBegin(GL_POLYGON);
                for(j=0; j<triangle[i].NodeName; j++)
                    glVertex3d(vertex[triangle[i].v[j]].coor[0], vertex[triangle[i].v[j]].coor[1], vertex[triangle[i].v[j]].coor[2]);
            glEnd();
        }
    glPopMatrix();

    glutSwapBuffers();
}

void RenderToMem(unsigned char *bmBits, unsigned char *bmColor, pVer CamVertex, pVer v, pTri t, int nv, int nt)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(CamVertex->coor[0], CamVertex->coor[1], CamVertex->coor[2],
                0, 0, 0,
                0, 1, 0);

    vertex = v;
    triangle = t;
    NumVer = nv;
    NumTri = nt;
    display();

    glReadBuffer(GL_BACK);
    glReadPixels(0, 0, winw, winh, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, bmBits);
    if( bmColor )
        glReadPixels(0, 0, winw, winh, GL_RGB, GL_UNSIGNED_BYTE, bmColor);
}

void keyboard (unsigned char key, int x, int y)
{
    unsigned char	*srcBuff[CAMNUM], *EdgeBuff, *ColorBuff[CAMNUM], *YuvBuff;
    char			filename[400];
    pVer			CamVertex[ANGLE];
    pTri			CamTriangle[ANGLE];
    int				CamNumVer[ANGLE], CamNumTri[ANGLE];		// total number of vertex and triangle.
    FILE			*fpt, *fpt1;//, *fpt_ccd;
    int				i, j, k, srcCam, destCam, p, r, itmp;
    clock_t			start, finish;

    // for region shape descriptor
    double			src_ArtCoeff[ANGLE][CAMNUM][ART_ANGULAR][ART_RADIAL];

    int	q8_ArtCoeff[ANGLE][CAMNUM][ART_COEF];

    // for circularity
    double			cir_Coeff[ANGLE][CAMNUM];
    int	q8_cirCoeff[ANGLE][CAMNUM];
    // for fourier descriptor
    double			src_FdCoeff[ANGLE][CAMNUM][FD_COEFF_NO];
    int	q8_FdCoeff[ANGLE][CAMNUM][FD_COEFF_NO];
    sPOINT			*Contour;
    unsigned char	*ContourMask;
    // for eccentricity
    double			ecc_Coeff[ANGLE][CAMNUM];
    int	q8_eccCoeff[ANGLE][CAMNUM];
    // for compare
    int				Count;

    // quantization version
    char			fname[300];
    double			CenX[CAMNUM], CenY[CAMNUM];
    int				total;

	FILE  *AllModelFeature;//save all features including Zinike moment,Fourier,ecc.etc
	FILE  *featureForSingleModel;//save feature for each model
	FILE  *modelNames;// 

    char currentModelName[20],currentModelPath[400];
	int lineNumber = 0;

	char srcName[20];
	char edgeName[20];

    switch (key)
    {
    case 27:
        exit(0);
        break;

/*
 *rewrite case 'n'
 */
// calculate feature and save to file
	case 'n':
		// initialize ART
		GenerateBasisLUT();
		// initialize: read camera set
		for(destCam=0; destCam<ANGLE; destCam++)
		{
            sprintf(filename, "12_%d", destCam);
			ReadObj(filename, CamVertex+destCam, CamTriangle+destCam, CamNumVer+destCam, CamNumTri+destCam);
		}


		for(i=0; i<CAMNUM; i++)
		{
			srcBuff[i] = (unsigned char *) malloc (winw * winh * sizeof(unsigned char));
			ColorBuff[i] = (unsigned char *) malloc (3 * winw * winh * sizeof(unsigned char));
		}
		YuvBuff = (unsigned char *) malloc (3 * winw * winh * sizeof(unsigned char));
		// add edge to test retrieval
		EdgeBuff = (unsigned char *) malloc (winw * winh * sizeof(unsigned char));

		// for Fourier Descriptor
		total = winw * winh;
		Contour = (sPOINT *) malloc( total * sizeof(sPOINT));
		ContourMask = (unsigned char *) malloc( total * sizeof(unsigned char));

        fpt1          = fopen("modelNameData/OBJList.txt", "r");
        modelNames    = fopen("modelNameData/labelIndex.txt","r");
        AllModelFeature = fopen("featureData/allModelFeature.txt","w");

		Count = 0;
        while( !feof(fpt1) )
		{
            if( NULL == fgets(fname, 300, fpt1) ) break;

            fname[strlen(fname)-2] = '\0';

			fgets(currentModelName,20,modelNames);
            currentModelName[strlen(currentModelName)-1] = '\0';

            sprintf(currentModelPath,"%s_lfd.txt",fname);
//            sprintf(currentModelPath,"%s_lfd.txt",fname);
			featureForSingleModel = fopen(currentModelPath,"w");
			
			// record execute time --- start
			start = clock();
            printf("process model: %s ...\n\n",fname);
            fprintf(AllModelFeature,"%d ",++lineNumber);
            fprintf(featureForSingleModel,"%s ",currentModelName);
            fprintf(AllModelFeature,"%s ",currentModelName);

			// get the translatation and scale of the two model
			if( ReadObj(fname, &vertex1, &triangle1, &NumVer1, &NumTri1) == 0 ){
                printf("can not open %s\n",fname);
				continue;
			}

			// ****************************************************************
			// Corase alignment
			// ****************************************************************

			// Translate and scale model 1
            TranslateScale(vertex1, NumVer1, triangle1, NumTri1, fname, &Translate1, &Scale1);

			// read RED only, so size is winw*winh
			for(srcCam=0; srcCam<ANGLE; srcCam++)
			{
				// capture CAMNUM silhouette of srcfn to memory
				for(i=0; i<CAMNUM; i++)
//					printf("size of srcBuff_1 = %d\n",strlen(srcBuff[0]));
//					RenderToMem(srcBuff[i], ColorBuff[i], CamVertex[srcCam]+i, vertex1, triangle1, NumVer1, NumTri1);
					RenderToMem(srcBuff[i], NULL, CamVertex[srcCam]+i, vertex1, triangle1, NumVer1, NumTri1);
//					printf("size of srcBuff_2 = %d\n",strlen(srcBuff[0]));
//				// find center for each shape
				for(i=0; i<CAMNUM; i++)
					FindCenter(srcBuff[i], winw, winh, CenX+i, CenY+i);

				// get Zernike moment
				FindRadius(srcBuff, CenX, CenY);
				for(i=0; i<CAMNUM; i++)
				{
					// from depth
                    sprintf(srcName,"image/%s_%d_%d_src.bmp",currentModelName,srcCam,i);
                    sprintf(edgeName,"image/%s_%d_%d_edge.bmp",currentModelName,srcCam,i);
				    EdgeDetect(EdgeBuff, srcBuff[i], winw, winh);
					WriteBitmap8(srcBuff[i], winw, winh, srcName);
					WriteBitmap8(EdgeBuff, winw, winh, edgeName);
					ExtractCoefficients(srcBuff[i], src_ArtCoeff[srcCam][i], EdgeBuff, CenX[i], CenY[i]);
				}

				// get Fourier descriptor
				for(i=0; i<CAMNUM; i++)
					FourierDescriptor(src_FdCoeff[srcCam][i], srcBuff[i], winw, winh, Contour, ContourMask, CenX[i], CenY[i]);

				// get eccentricity
				for(i=0; i<CAMNUM; i++)
					ecc_Coeff[srcCam][i] = Eccentricity(srcBuff[i], winw, winh, CenX[i], CenY[i]);

				// get circularity
				for(i=0; i<CAMNUM; i++)
				{
					EdgeDetectSil(EdgeBuff, srcBuff[i], winw, winh);
					cir_Coeff[srcCam][i] = Circularity(srcBuff[i], winw, winh, EdgeBuff);
				}

			}

			// free memory of 3D model
            free(vertex1);
			free(triangle1);

			// record execute time --- end
			finish = clock();
			fpt = fopen("feature_time.txt", "a");
			fprintf(fpt, "%s ( V: %d T: %d )\t: %f sec;\n", fname, NumVer1, NumTri1, (double)(finish - start) / CLOCKS_PER_SEC );
			fclose(fpt);


			// **********************************************************************
			// linear Quantization to 8 bits for each coefficient
			for(i=0; i<ANGLE; i++)
				for(j=0; j<CAMNUM; j++)
				{
					// the order is the same with that defined in MPEG-7, total 35 coefficients
					k = 0;
					p = 0;
					for(r=1 ; r<ART_RADIAL ; r++, k++)
					{
						itmp = (int)(QUANT8 *  src_ArtCoeff[i][j][p][r]);
						if(itmp>255)
							q8_ArtCoeff[i][j][k] = 255;
						else
							q8_ArtCoeff[i][j][k] = itmp;
						fprintf(AllModelFeature,"%d ",q8_ArtCoeff[i][j][k]);
						fprintf(featureForSingleModel,"%d ",q8_ArtCoeff[i][j][k]);
					}

					for(p=1; p<ART_ANGULAR ; p++)
						for(r=0 ; r<ART_RADIAL ; r++, k++)
						{
							itmp = (int)(QUANT8 *  src_ArtCoeff[i][j][p][r]);
							if(itmp>255)
								q8_ArtCoeff[i][j][k] = 255;
							else
								q8_ArtCoeff[i][j][k] = itmp;

							fprintf(AllModelFeature,"%d ",q8_ArtCoeff[i][j][k]);
							fprintf(featureForSingleModel,"%d ",q8_ArtCoeff[i][j][k]);
						}
				}



			// linear Quantization to 8 bits for each coefficient
			for(i=0; i<ANGLE; i++)
				for(j=0; j<CAMNUM; j++)
				{
					itmp = (int)(QUANT8 *  cir_Coeff[i][j]);
					if(itmp>255)		q8_cirCoeff[i][j] = 255;
					else				q8_cirCoeff[i][j] = itmp;
					fprintf(AllModelFeature,"%d ",q8_cirCoeff[i][j]);
					fprintf(featureForSingleModel,"%d ",q8_cirCoeff[i][j]);
				}

			// save eccentricity feature to file
			// linear Quantization to 8 bits for each coefficient
			for(i=0; i<ANGLE; i++)
				for(j=0; j<CAMNUM; j++)
				{
					itmp = (int)(QUANT8 * ecc_Coeff[i][j]);
					if(itmp>255)		q8_eccCoeff[i][j] = 255;
					else				q8_eccCoeff[i][j] = itmp;
					fprintf(AllModelFeature,"%d ",q8_eccCoeff[i][j]);
					fprintf(featureForSingleModel,"%d ",q8_eccCoeff[i][j]);
				}

			for(i=0; i<ANGLE; i++)
				for(j=0; j<CAMNUM; j++)
				{
					for(k=0; k<FD_COEFF_NO; k++)
					{
						itmp = (int)(QUANT8 * FD_SCALE * src_FdCoeff[i][j][k]);
						if(itmp>255)
							q8_FdCoeff[i][j][k] = 255;
						else
							q8_FdCoeff[i][j][k] = itmp;

						fprintf(AllModelFeature,"%d ",q8_FdCoeff[i][j][k]);
						fprintf(featureForSingleModel,"%d ",q8_FdCoeff[i][j][k]);
					}
				}

//			fwrite(q8_FdCoeff, ANGLE * CAMNUM * FD_COEFF_NO, sizeof(double), AllModelFeature);
//			fwrite(q8_FdCoeff, ANGLE * CAMNUM * FD_COEFF_NO, sizeof(unsigned char), featureForSingleModel);

			fclose(featureForSingleModel);
			fprintf(AllModelFeature,"\n");
			printf("%d.", Count++);
		}

		for(i=0; i<CAMNUM; i++)
		{
			free(srcBuff[i]);
			free(ColorBuff[i]);
		}
		free(YuvBuff);
		free(EdgeBuff);
		free(Contour);
		free(ContourMask);
		fclose(fpt1);
		fclose(AllModelFeature);
		fclose(modelNames);

		for(destCam=0; destCam<ANGLE; destCam++)
		{
			free(CamVertex[destCam]);
			free(CamTriangle[destCam]);
		}
		NumTri = 0;
		break;

    default:
        break;
    }
}


void saveDepthImage(unsigned char key, int x, int y)
{
    unsigned char	*srcBuff[CAMNUM], *EdgeBuff, *ColorBuff[CAMNUM];
    char			filename[400],fname[300],srcName[500],edgeName[500],currentDir[500],currentModelName[20];
    pVer			CamVertex[ANGLE];
    pTri			CamTriangle[ANGLE];
    int				CamNumVer[ANGLE], CamNumTri[ANGLE];		// total number of vertex and triangle.
    int				i,srcCam,destCam,Count,lineNumber=0,num = 0;
    int             preModelName = 1;
    FILE  *depthImageList,*modelNames,*fpt1;

    switch (key)
    {
    case 27:
        exit(0);
        break;

    case 'n':
        GenerateBasisLUT();
        for(destCam=0; destCam<ANGLE; destCam++){
            sprintf(filename, "12_%d", destCam);
            ReadObj(filename, CamVertex+destCam, CamTriangle+destCam, CamNumVer+destCam, CamNumTri+destCam);
        }

        for(i=0; i<CAMNUM; i++){
            srcBuff[i] = (unsigned char *) malloc (winw * winh * sizeof(unsigned char));
            ColorBuff[i] = (unsigned char *) malloc (3 * winw * winh * sizeof(unsigned char));
        }

        EdgeBuff = (unsigned char *) malloc (winw * winh * sizeof(unsigned char));

        fpt1          = fopen("modelNameData/SHREC_2007_OBJList.txt", "r");
        modelNames    = fopen("modelNameData/SHREC_2007_labelIndex.txt","r");
        depthImageList = fopen("featureData/SHREC_2007_depthImageList.txt","w");

        getcwd(currentDir,sizeof(currentDir));
        strcat(currentDir,"/SHREC_2007_image");
        mkdir(currentDir,S_IRWXU);

        Count = 1;

        while( !feof(fpt1) )
        {
            if( NULL == fgets(fname, 300, fpt1) ) break;

            fname[strlen(fname)-2] = '\0';
            fgets(currentModelName,20,modelNames);
            currentModelName[strlen(currentModelName)-1] = '\0';

            num++;
            if(atoi(currentModelName) != preModelName)
                num = 1;
            preModelName = atoi(currentModelName);

            printf("%d.", Count++);
            printf("process model: %s ...\n\n",fname);
            if( ReadObj(fname, &vertex1, &triangle1, &NumVer1, &NumTri1) == 0 ){
                printf("can not open %s\n",fname);
                continue;
            }

            TranslateScale(vertex1, NumVer1, triangle1, NumTri1, fname, &Translate1, &Scale1);

            for(srcCam=0; srcCam<ANGLE; srcCam++){
                for(i=0; i<CAMNUM; i++)
                    RenderToMem(srcBuff[i], NULL, CamVertex[srcCam]+i, vertex1, triangle1, NumVer1, NumTri1);

                for(i=0; i<CAMNUM; i++){
                    sprintf(srcName,"%s/%s_%d_%d_%d_src.bmp",currentDir,currentModelName,num,srcCam,i);
 //                   sprintf(edgeName,"%s/%s_%d_%d_%d_edge.bmp",currentDir,currentModelName,num,srcCam,i);
 //                   EdgeDetect(EdgeBuff, srcBuff[i], winw, winh);
                    WriteBitmap8(srcBuff[i], winw, winh, srcName);
 //                   WriteBitmap8(EdgeBuff, winw, winh, edgeName);
                    fprintf(depthImageList,"%d ",++lineNumber);
                    fprintf(depthImageList,"%s ",currentModelName);
                    fprintf(depthImageList,"%d ",num);
                    fprintf(depthImageList,"%s\n",srcName);
                }
        }

            free(vertex1);
            free(triangle1);

        }

        for(i=0; i<CAMNUM; i++) {
            free(srcBuff[i]);
            free(ColorBuff[i]);
        }

        free(EdgeBuff);
        fclose(fpt1);
        fclose(depthImageList);
        fclose(modelNames);

        for(destCam=0; destCam<ANGLE; destCam++)
        {
            free(CamVertex[destCam]);
            free(CamTriangle[destCam]);
        }
        NumTri = 0;
        break;

    default:
        break;
    }
}

void init(void)
{
    glClearColor (1.0, 1.0, 1.0, 0.0);
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);
}

void reshape (int w, int h)
{
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
//	gluPerspective(90.0, (GLfloat) winw/(GLfloat) winh, 0.1, 10.0);
    glOrtho(-1, 1, -1, 1, 0.0, 2.0);
//	glOrtho(-1, 1, -1, 1, 0.5, 1.5);
    glViewport (0, 0, (GLsizei) winw, (GLsizei) winh);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(1,0,0,0,0,0,0,1,0);
//	gluLookAt(CAMSCALE*-0.85065, CAMSCALE*0.61803, CAMSCALE*-0.20081, 0,0,0,0,1,0);
//	gluLookAt(-0.85065, 0.61803, -0.20081, 0,0,0,0,1,0);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (WIDTH, HEIGHT); 
	glutInitWindowPosition (100, 100);
	glutCreateWindow (argv[0]);
	init ();
	glutDisplayFunc(display); 
	glutReshapeFunc(reshape);
	//   glutMouseFunc(mouse);
	//   glutMotionFunc(motion);
    glutKeyboardFunc(saveDepthImage);

	glutMainLoop();

	return 0;
}
