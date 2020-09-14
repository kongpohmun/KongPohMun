#include	<iostream>
#include	<opencv2/opencv.hpp>
#include	<opencv2/highgui/highgui.hpp>
#include	<fstream>
#include	<opencv2/core.hpp>
#include	<opencv2/imgproc.hpp>
#include	<opencv2/highgui.hpp>
#include	<opencv2/ml.hpp>
#include	"Supp.h"

using namespace cv;
using namespace std;
using namespace cv::ml;

int main(int argc, char** argv) {
	char		filename[300][128], filename2[150][128];
	const int	noOfImagePerCol = 1, noOfImagePerRow = 4; // create window partition 
	int			winI = 0, rows, cols;
	char		name[128];
	float		trainingData[300][7], verificationData[150][7];
	int labels[300] = { 1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,
	2,2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,2,
	3,3,3,3,3,3,3,3,3,3,
	3,3,3,3,3,3,3,3,3,3,
	3,3,3,3,3,3,3,3,3,3,
	3,3,3,3,3,3,3,3,3,3,
	3,3,3,3,3,3,3,3,3,3,
	4,4,4,4,4,4,4,4,4,4,
	4,4,4,4,4,4,4,4,4,4,
	4,4,4,4,4,4,4,4,4,4,
	4,4,4,4,4,4,4,4,4,4,
	4,4,4,4,4,4,4,4,4,4,
	5,5,5,5,5,5,5,5,5,5,
	5,5,5,5,5,5,5,5,5,5,
	5,5,5,5,5,5,5,5,5,5,
	5,5,5,5,5,5,5,5,5,5,
	5,5,5,5,5,5,5,5,5,5,
	6,6,6,6,6,6,6,6,6,6,
	6,6,6,6,6,6,6,6,6,6,
	6,6,6,6,6,6,6,6,6,6,
	6,6,6,6,6,6,6,6,6,6,
	6,6,6,6,6,6,6,6,6,6 };
	Mat			srcI, largeWin, win[noOfImagePerRow * noOfImagePerCol],
		legend[noOfImagePerRow * noOfImagePerCol], tt;
	std::fstream fs;
	std::fstream fs1;

	//training set
	fs.open("Fruit/Fruit.txt", std::fstream::in);
	for (int j = 0; j < 300; j++)
		fs >> filename[j];
	for (int q = 0; q < 2; q++) { // generate moments twice; once from region and other from edge to compare
		for (int p = 0; p < 300; p++) {
			srcI = imread(filename[p], IMREAD_GRAYSCALE);
			if (srcI.empty()) {
				cout << "cannot open " << filename << endl;
				return -1;
			}
			rows = srcI.rows, cols = srcI.cols;
			createWindowPartition(srcI, largeWin, win, legend, noOfImagePerCol, noOfImagePerRow);

			srcI.copyTo(win[0]);
			putText(legend[0], "Original", Point(5, 11), 1, 1, Scalar(250, 250, 250), 1);

			GaussianBlur(win[0], win[1], Size(7, 7), 0, 0);
			putText(legend[1], "Blur", Point(5, 11), 1, 1, Scalar(250, 250, 250), 1);

			threshold(win[1], win[2], 108, 255, THRESH_OTSU);
			putText(legend[2], "threshold", Point(5, 11), 1, 1, Scalar(250, 250, 250), 1);

			if (q == 0) win[2].copyTo(tt); // prepare to generate moments from tt (region or edge)
			else {
				Canny(win[2], win[3], 30, 90, 3);
				win[3].copyTo(tt);
			}

			// generate Hu moments here.
			Moments 	mom;
			double		hu[7];

			mom = moments(tt, true); // get moments of the thresholded image in win[1]
			HuMoments(mom, hu); // generate the Hu moments
			//cout << "Generate Hu moments for input " << p << endl;
			for (int k = 0; k < 7; k++) {
				trainingData[p][k] = (float)hu[k];
			}
		}
	}
	Mat labelsMat(300, 1, CV_32SC1, labels);
	Mat trainingDataMat(300, 3, CV_32FC1, trainingData);

	//testing set
	fs1.open("Fruit2/Fruit2.txt", std::fstream::in);
	for (int j = 0; j < 150; j++)
		fs >> filename[j];
	for (int q = 0; q < 2; q++) { // generate moments twice; once from region and other from edge to compare
		for (int p = 0; p < 150; p++) {
			srcI = imread(filename[p], IMREAD_GRAYSCALE);
			if (srcI.empty()) {
				cout << "cannot open " << filename << endl;
				return -1;
			}
			rows = srcI.rows, cols = srcI.cols;
			createWindowPartition(srcI, largeWin, win, legend, noOfImagePerCol, noOfImagePerRow);

			srcI.copyTo(win[0]);
			putText(legend[0], "Original", Point(5, 11), 1, 1, Scalar(250, 250, 250), 1);

			GaussianBlur(win[0], win[1], Size(7, 7), 0, 0);
			putText(legend[1], "Blur", Point(5, 11), 1, 1, Scalar(250, 250, 250), 1);

			threshold(win[1], win[2], 108, 255, THRESH_OTSU);
			putText(legend[2], "threshold", Point(5, 11), 1, 1, Scalar(250, 250, 250), 1);

			if (q == 0) win[2].copyTo(tt); // prepare to generate moments from tt (region or edge)
			else {
				Canny(win[2], win[3], 30, 90, 3);
				win[3].copyTo(tt);
			}

			// generate Hu moments here.
			Moments 	mom;
			double		hu[7];

			mom = moments(tt, true); // get moments of the thresholded image in win[1]
			HuMoments(mom, hu); // generate the Hu moments
			//cout << "Generate Hu moments for input " << p << endl;
			for (int k = 0; k < 7; k++) {
				verificationData[p][k] = (float)hu[k];
			}
		}
	}

	// Section 2: Do normalization of the data
	// Xnew = (X - mean) / sigma
	vector<double> mean, sigma;
	for (int i = 0; i < trainingDataMat.cols; i++) {  //take each of the features in vector
		Scalar meanOut, sigmaOut;
		meanStdDev(trainingDataMat.col(i), meanOut, sigmaOut);  //get mean and std deviation
		mean.push_back(meanOut[0]);
		sigma.push_back(sigmaOut[0]);
	}
	for (size_t i = 0; i < trainingDataMat.cols; i++)
		trainingDataMat.col(i) = (trainingDataMat.col(i) - mean[i]) / sigma[i];

	// Section 3: Train the SVM
	Ptr<SVM> svm = SVM::create();
	svm->setType(SVM::C_SVC);
	svm->setKernel(SVM::LINEAR);
	svm->setTermCriteria(TermCriteria(TermCriteria::MAX_ITER, 100, 1e-6));
	svm->train(trainingDataMat, ROW_SAMPLE, labelsMat);


	// Section 4: check on the training and verification data
	Mat			input;

	cout << "Test on training data";
	for (int j = 0; j < trainingDataMat.rows; j++) { // Test on training data
		if (j % 120 == 0) cout << "\n";
		cout << svm->predict(trainingDataMat.row(j)) << ' ';
	}
	cout << "\n\n";

	cout << "Test on verification data";
	for (int j = 0; j < 150; j++) { // Test on verification data
		if (j % 30 == 0) cout << "\n";
		for (int k = 0; k < 7; k++) // normalize all features using the same mean and sigma from section 2
			verificationData[j][k] = (verificationData[j][k] - mean[k]) / sigma[k];
		input = (Mat_<float>(1, 7) << verificationData[j][0], verificationData[j][1], verificationData[j][2],
			verificationData[j][3], verificationData[j][4], verificationData[j][5], verificationData[j][6]);
		cout << svm->predict(input) << ' ';
	}
	cout << "\n\n";

	system("pause");
	waitKey();
}