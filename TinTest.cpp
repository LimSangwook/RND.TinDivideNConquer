#include <iostream>

#include <memory>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <math.h>
#include <atltime.h>
#include <map>
#include <set>
#include <fstream>

#include "Delaunay.h"
const BOOL RANDON_POINT = FALSE;

// DATA_NUM 갯수만큼의 Point Create
real* _GetRandomPoints(int DATA_NUM);
void DisplayFaces(int nCountOfTrangle, int *faces, real* pt);
void SaveWKT(int nCountOfTrangle, int *faces, real* pt, CString filePath);

int main(int argc, char **argv) {
    int DATA_NUM = 100000;

	////////////////
	// Time Check
	clock_t StartClock, LoadingClock, TinClock;
	StartClock = clock();

	////////////////
	// Load Points
    real* pt = _GetRandomPoints(DATA_NUM);
	// Display
	LoadingClock = clock();	
	std::cout << "PointCount : " << DATA_NUM << std::endl;
	std::cout << "Load Points Time : " << (double)(LoadingClock - StartClock)/CLOCKS_PER_SEC << "초" << std::endl;
    
	////////////////
	// Make Tin
    int *faces;
    int nCountOfTrangle = delaunay2d(pt, DATA_NUM, &faces);
	TinClock = clock();
	// Display
    std::cout << "count Trangle : " << nCountOfTrangle - 1 << std::endl;
	std::cout << "Make Tin Time : " << (double)(TinClock - LoadingClock)/CLOCKS_PER_SEC << "초" << std::endl;

	//DisplayFaces(nCountOfTrangle, faces, pt);
	//SaveWKT(nCountOfTrangle, faces, pt, "D:\\work\\Polygons.txt");

	int l;
	std::cin >> l;
    return 0;
}

real* _GetRandomPoints(int DATA_NUM)
{

    srand((int)time(NULL));    // 현재 시간을 이용해서 씨드 설정
    real* pt = new real[DATA_NUM * 2];
	int sq =(int) sqrt((double)DATA_NUM);

	if (!RANDON_POINT) {
      int idx = 0;
      
      for (int i = 0 ; i < sq * 10 + 1 ; i += 10) {
	  for(int j = 0 ; j < sq * 10 + 1; j += 10){
	      real x = (real)i;
	      real y = (real)j;
	      pt[idx*2] = x;// + k/10.0;
	      pt[idx*2 + 1] = y;
		  //std::cout << idx << " : (" << x << "," << y << ")" << std::endl;
	      idx++;
	      if (idx == DATA_NUM) break;
	  }
	  if (idx == DATA_NUM) break;
      }
      return pt;
    }
	std::set<std::pair<real, real>> pointMap;
    for (int i = 0 ; i < DATA_NUM ; i++ ) {
		real x, y;
		std::set<std::pair<real, real>>::iterator iter = pointMap.begin();
		
		BOOL newPoint = TRUE;
		do {
			x = (real)((rand() * rand()) % (sq * 1000));
			y = (real)(rand() % (sq * 1000));
			std::set<std::pair<real, real>>::iterator findIter = pointMap.find(std::pair<real,real>(x,y));
			std::set<std::pair<real, real>>::iterator iterEnd = pointMap.end();
			if (findIter != iterEnd){
				newPoint = FALSE;
			} else {
				newPoint = TRUE;
			}
		} while (newPoint != TRUE);
		pointMap.insert(std::pair<real,real>(x,y));
		pt[i*2] = x;
		pt[i*2 + 1] = y;
		//std::cout << "(" << pt[i*2] << "," << pt[i*2+1] << ")" << std::endl;
    }
    return pt;
}

void DisplayFaces(int nCountOfTrangle, int *faces, real* pt)
{
	int startIndex = 0;
	
	for (int j = 0 ; j < nCountOfTrangle ; j++) {
		std::cout << std::endl;
		std::cout << "###################### Face : " << j << std::endl;
		std::cout << "Count of Points : " << faces[startIndex] << std::endl;
		std::cout << "Point Index : " ;

		for (int i = 0 ; i < faces[startIndex] ; i++) {
		  std::cout << faces[startIndex + i + 1] << "  ";
		}
		startIndex += faces[startIndex] + 1;
	}
}

void SaveWKT(int nCountOfTrangle, int *faces, real* pt, CString filePath)
{
	int startIndex = 0;
	startIndex += faces[startIndex] + 1;
	std::ofstream SaveFile(filePath.GetBuffer(0));
	for (int j = 1 ; j < nCountOfTrangle ; j++) {
		//std::cout << std::endl;
		//std::cout << "###################### Face : " << j << std::endl;
		//std::cout << "Count of Points : " << faces[startIndex] << std::endl;
		//std::cout << "Point Index : " ;

		//for (int i = 0 ; i < faces[startIndex] ; i++) {
		//  std::cout << faces[startIndex + i + 1] << "  ";
		//}

		///////////////
		// WKT Print
		SaveFile << "POLYGON((" ;
		for (int i = 0 ; i < faces[startIndex] ; i++) {
		  SaveFile << pt[2*faces[startIndex + i + 1]] << " " << pt[2*faces[startIndex + i + 1] + 1]<<", ";
		}
		SaveFile << pt[2*faces[startIndex + 1]] << " " << pt[2*faces[startIndex + 1] + 1];
		SaveFile << "))";
		SaveFile << std::endl;
		startIndex += faces[startIndex] + 1;

	}
}
