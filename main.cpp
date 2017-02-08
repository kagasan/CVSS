#include "cvss.h"

int main(){

	CVSS cvss;
	cv::Mat m = cvss.Get();

	std::cout << "q:quit" << std::endl;
	std::cout << "s:screenshot" << std::endl;
	while (1){
		cv::imshow("ss",m);
		int key = cv::waitKey(1);
		if (key == 'q')break;
		if (key == 's')m = cvss.Get();
	}

	return 0;
}