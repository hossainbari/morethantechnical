#include <iostream>

using namespace std;

#include "cv.h"
#include "cxcore.h"
#include "highgui.h"

using namespace cv;

#include "matting.h"
#include "gui.h"

int main(int argc, char **argv)
{
	char key;

	Matting *matting;

	//if(argc==4)
	//{
	//	IplImage *largeAmbient = cvLoadImage(argv[1]);
	//	IplImage *largeFlash   = cvLoadImage(argv[2]);
	//	IplImage *largeTrimap   = cvLoadImage(argv[3], CV_LOAD_IMAGE_GRAYSCALE );

	//	IplImage *smallFlash   = cvCreateImage( cvSize( largeFlash->width/2, largeFlash->height/2 ), 8, 3 );
	//	IplImage *smallAmbient = cvCreateImage( cvGetSize( smallFlash ), 8, 3 );
	//	IplImage* smallTrimap = cvCreateImage( cvGetSize( smallFlash ), 8, 1 );

	//	IplImage* flashOnlyImg = cvCreateImage( cvGetSize( smallAmbient ), 8, 3 );
	//	cvResize( largeFlash, smallFlash );
	//	cvResize( largeAmbient, smallAmbient );
	//	cvResize( largeTrimap, smallTrimap );

	//	cvSub( smallFlash, smallAmbient, flashOnlyImg );

	//	// gui
	//	initializeGUI( smallAmbient, smallTrimap , flashOnlyImg);
	//	run();
	//	returnTrimap( smallTrimap );
	//	destructGUI();

	//	
	//	matting  = new FlashMatting( smallAmbient, smallFlash, smallTrimap);			

	//			
	//	cvReleaseImage( &largeAmbient );
	//	cvReleaseImage( &largeFlash );
	//	cvReleaseImage( &smallAmbient );
	//	cvReleaseImage( &smallFlash );
	//	cvReleaseImage( &largeTrimap );
	//	cvReleaseImage( &smallTrimap );
	//	cvReleaseImage( &flashOnlyImg );

	//	goto SOLVE;
	//}

	// my code
//	printf("automatically generate trimap by flashmatting? (y/n) \n");
//	cin >> key;
//
//	if(key=='y')
//	{
//		IplImage *largeAmbient = cvLoadImage(argv[1]);
//		IplImage *largeFlash   = cvLoadImage(argv[2]);
//
//		IplImage *smallFlash   = cvCreateImage( cvSize( largeFlash->width/2, largeFlash->height/2 ), 8, 3 );
//		IplImage *smallAmbient = cvCreateImage( cvGetSize( smallFlash ), 8, 3 );
//
//		IplImage* trimap = NULL;// = cvCreateImage( cvGetSize( smallFlash ), 8, 1 );
//		IplImage* flashOnlyImg = cvCreateImage( cvGetSize( smallAmbient ), 8, 3 );
//		cvResize( largeFlash, smallFlash );
//		cvResize( largeAmbient, smallAmbient );
//
//		cvSub( smallFlash, smallAmbient, flashOnlyImg );
//
//		FlashMatting::GenerateTrimap( flashOnlyImg, trimap, T);
//
//		// gui
//		initializeGUI( smallAmbient, trimap , flashOnlyImg);
//		run();
//		returnTrimap( trimap );
//		destructGUI();
//
//		printf("use which matting algorithm? (b/r/p/f)\n");
//		cin >> key;
//
//		switch(key)
//		{
//		case 'b':
//			matting = new BayesianMatting( smallAmbient, trimap );
//			break;
//#ifdef ROBUST_MATTING
//		case 'r':
//			matting  = new RobustMatting( smallAmbient, trimap );			
//		    break;
//#endif
//		//case 'p':		
//		//	matting  = new PoissonMatting( smallAmbient, trimap );			
//		//	break;
//		case 'f':
//			matting  = new FlashMatting( smallAmbient, smallFlash, trimap);			
//			break;
//		default:
//			exit(1);
//			break;
//		}
//				
//		cvReleaseImage( &largeAmbient );
//		cvReleaseImage( &largeFlash );
//		cvReleaseImage( &smallAmbient );
//		cvReleaseImage( &smallFlash );
//		cvReleaseImage( &trimap );
//		cvReleaseImage( &flashOnlyImg );
//	}
//	else if(key=='n')
//	{
		//IplImage *largeImg  = &((IplImage)cv::imread( argv[1] ));
		//IplImage *largeTrimap = &((IplImage)cv::imread( argv[2] ));	
		//IplImage *grayTrimap = cvCreateImage( cvGetSize( largeTrimap ), 8, 1 );
		//cvCvtColor( largeTrimap,  grayTrimap, CV_BGR2GRAY );		

		//IplImage *smallImg  = cvCreateImage( cvSize( largeImg->width/2, largeImg->height/2 ), 8, 3 );
		//IplImage *smallTrimap    = cvCreateImage( cvGetSize( smallImg ), 8, 1 );		
		//cvResize( largeImg, smallImg );
		//cvResize( grayTrimap, smallTrimap );
		Mat largeImage = imread(string(argv[1]),1);
		Mat largeTrimap = imread(string(argv[2]),1);
		
		Mat grayTrimap; 
		cvtColor(largeTrimap,grayTrimap,CV_RGB2GRAY);
		
		Mat smallImg; 
		resize(largeImage,smallImg,Size(largeImage.cols/2,largeImage.rows/2));
		
		Mat smallTrimap; 
		resize(grayTrimap,smallTrimap,smallImg.size(),0,0,INTER_NEAREST);

		// gui
		//initializeGUI( &((IplImage)smallImg), &((IplImage)smallTrimap) );
		//run();
		//returnTrimap( &((IplImage)smallTrimap) );
		//destructGUI();

		printf("use which matting algorithm? (b/r/p)\n");
		cin >> key;
		switch(key)
		{
		case 'b':
			matting  = new BayesianMatting( &((IplImage)smallImg), &((IplImage)smallTrimap) );
			break;
#ifdef ROBUST_MATTING
		case 'r':
			matting  = new RobustMatting( &((IplImage)smallImg), &((IplImage)smallTrimap) );
			break;
#endif
		//case 'p':
		//	matting  = new PoissonMatting( smallImg, smallTrimap );
		//	break;
		default:
			exit(1);			
		} 				

		//cvReleaseImage( &largeImg );
		//cvReleaseImage( &largeTrimap );
		//cvReleaseImage( &grayTrimap );
		//cvReleaseImage( &smallImg );
		//cvReleaseImage( &smallTrimap );
	//}


SOLVE:

	matting->Solve(false);

	cvSaveImage( "trimap.png", matting->trimap );

	IplImage *uchar_alphamap = cvCreateImage( cvGetSize( matting->alphamap ), 8, 1 );
	cvCvtScale( matting->alphamap, uchar_alphamap, 255 );
	cvSaveImage( "alphamap.png", uchar_alphamap );

	// my code end

	//BayesianMatting* bm = new BayesianMatting( simg, sgmask );
	//bm->Solve();

	//RobustMatting* rm = new RobustMatting( simg, sgmask );
	//rm->Solve();

	//PoissonMatting* pm = new PoissonMatting( simg, sgmask );
	//pm->Solve();

	//IplImage* flash   = cvLoadImage("../testdata/mouse_f.bmp");
	//IplImage* ambient = cvLoadImage("../testdata/mouse_n.bmp");	

	//IplImage* simg  = cvCreateImage( cvSize( flash->width/4, flash->height/4 ), 8, 3 );
	//IplImage* sgmask = cvCreateImage( cvGetSize( simg ), 8, 3 );	
	//IplImage* flashOnlyImg = cvCreateImage( cvGetSize( simg ), 8, 3 );
	//
	//
	//cvResize( flash, simg );
	//cvResize( ambient, sgmask );

	//IplImage* trimap;
	//cvSub( simg, sgmask, flashOnlyImg );
	//
	
	//
	//FlashMatting* fm;
	//fm->GenerateTrimap( flashOnlyImg, trimap );
	//BayesianMatting *bm = new BayesianMatting( sgmask, trimap );
	//bm->Solve();


	//FlashMatting* fm = new FlashMatting( sgmask, simg );
	//fm->Solve();

	
	//int i, j, v;
	//for(i=0;i<gmask->height;++i)
	//	for(j=0;j<gmask->width;++j)
	//	{			
	//		cout<<(int)CV_IMAGE_ELEM( gmask, uchar, i, j )<<"\n";
	//	}
	cvWaitKey( 0 );
}

