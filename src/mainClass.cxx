/*
Copyright (c) 2024 Daren Kostov

This file is part of connect-them-dots

connect-them-dots is free software: you can redistribute it and/or modify it under the terms
of the GNU General Public License as published by the Free Software Foundation,
either version 3 of the License, or (at your option) any later version.

connect-them-dots is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with connect-them-dots
If not, see <https://www.gnu.org/licenses/>.
*/

#include "mainClass.hxx"
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <unistd.h>


MainClass::MainClass(){
  window.create(sf::VideoMode(123, 123), "connect-them-dots");
  mainView=sf::View(sf::FloatRect(0, 0, 123, 123));
  mainView.setViewport(sf::FloatRect(0, 0, 1, 1));
  window.setView(mainView);
  window.setVerticalSyncEnabled(true);

  hasClicked=false;

  srand(std::time(nullptr));
  

  maxPointDistance=500;
  minPointDistance=100;
  PointDistanceFromBorder=100;
  circleRadius=10;
  
  randomizePoints();

  
}
MainClass::~MainClass(){
}



void MainClass::startProgram(){

  clock.restart();


  while(window.isOpen()){

    //drawing 66666-15fps 33333-30fps 16666-60fps 11111-90fps 8333-120fps 4166-240fps 
    usleep(16666);

    performActions();
    // update();
    draw();
  }

  saveDataPoints();


}


void MainClass::randomizePoints(double minDistance, double maxDistance){

  double distance{0};

  //lets save some computation
  minDistance*=minDistance;
  maxDistance*=maxDistance;

  do{
    pointA.x=PointDistanceFromBorder+(rand()%(window.getSize().x-PointDistanceFromBorder*2));    
    pointA.y=PointDistanceFromBorder+(rand()%(window.getSize().y-PointDistanceFromBorder*2));    

    pointB.x=PointDistanceFromBorder+(rand()%(window.getSize().x-PointDistanceFromBorder*2));    
    pointB.y=PointDistanceFromBorder+(rand()%(window.getSize().y-PointDistanceFromBorder*2));    
    
    distance=(pointA.x-pointB.x)*(pointA.x-pointB.x)+(pointA.y-pointB.y)*(pointA.y-pointB.y);

  }while(distance<minDistance || distance>maxDistance);

}

void MainClass::randomizePoints(){
  randomizePoints(minPointDistance, maxPointDistance);
}

double MainClass::getDistanceError(){
  double output{0};

  
  for(auto& coordinate : mouseCoordinates){

    // https://en.wikipedia.org/wiki/Distance_from_a_point_to_a_line
    double distance{0};
    distance=(pointB.x-pointA.x)*(pointA.y-coordinate.y);
    distance-=(pointB.y-pointA.y)*(pointA.x-coordinate.x);
    distance=std::abs(distance);
    distance/=std::sqrt((pointB.x-pointA.x)*(pointB.x-pointA.x)+(pointB.y-pointA.y)*(pointB.y-pointA.y));
  
    output+=distance;
    
  }

  output/=mouseCoordinates.size();

  return output;
}


void MainClass::recordDataPoint(){

  dataPoint newDataPoint;

  //record the total distance error
  newDataPoint.totalDistanceError=getDistanceError();

  //record the average distance error
  newDataPoint.averageDistanceError=newDataPoint.totalDistanceError/mouseCoordinates.size();

  //record the points inputted
  newDataPoint.inputtedPointsCount=mouseCoordinates.size();

  //record how much time this whole thing took
  newDataPoint.timeMiliseconds=clock.getElapsedTime().asMilliseconds();

  //record the actual shortest path
  newDataPoint.shortestPathLength=std::sqrt(
    (pointA.x-pointB.x)*(pointA.x-pointB.x)+
    (pointA.y-pointB.y)*(pointA.y-pointB.y));


  //record the users shortest path
  newDataPoint.inputtedPathLength=0;
  if(mouseCoordinates.size()>=2){
    for(auto coordinate=mouseCoordinates.begin()+1; coordinate!=mouseCoordinates.end(); coordinate++){

      sf::Vector2f coordA{*(coordinate-1)};
      sf::Vector2f coordB{*(coordinate)};
      
      newDataPoint.inputtedPathLength+=std::sqrt(
        (coordA.x-coordB.x)*(coordA.x-coordB.x)+
        (coordA.y-coordB.y)*(coordA.y-coordB.y));



    }


    
  }else{
    //how did we get here??????
    //if no points inputted the shortest path would be 0
    newDataPoint.inputtedPathLength=0;
  }

  newDataPoint.percentErrorInLength=((
    newDataPoint.inputtedPathLength-
    newDataPoint.shortestPathLength)/
    newDataPoint.shortestPathLength)*
    100;

  if(newDataPoint.percentErrorInLength<0){
    //how did we get here???
    //the shortest path should be the shortest path
    newDataPoint.percentErrorInLength=-newDataPoint.percentErrorInLength;
  }
  
  newDataPoint.pointAX=pointA.x;
  newDataPoint.pointAY=pointA.y;
  newDataPoint.pointBX=pointB.x;
  newDataPoint.pointBY=pointB.y;

  // std::cout << newDataPoint.inputtedPathLength << "====\n";
  dataPoints.push_back(newDataPoint);

}

bool MainClass::areCirclesColliding(sf::Vector2f coordA, double radiusA, sf::Vector2f coordB, double radiusB){

  //lets save computation;
  double neededDistance{(radiusA+radiusB)*(radiusA+radiusB)};

  double actualDistance{
    (coordA.x-coordB.x)*(coordA.x-coordB.x)+
    (coordA.y-coordB.y)*(coordA.y-coordB.y)
  };
  
  if(actualDistance<=neededDistance){
    return true;
  }

  return false;
  
}

void MainClass::saveDataPoints(){
  std::ofstream file;
  
  std::string filePath{"datapoints-"};
  filePath+=std::to_string(std::time(nullptr));
  filePath+=".csv";

  file.open(filePath);
  
  file << "totalDistanceError,averageDistanceError,inputtedPointsCount,timeMiliseconds,shortestPathLength,inputtedPathLength,percentErrorInLength,pointAX,pointAY,pointBX,pointBY\n";

  for(auto& dataPoint : dataPoints){
    file << dataPoint.totalDistanceError<< ",";
    file << dataPoint.averageDistanceError<< ",";
    file << dataPoint.inputtedPointsCount << ",";
    file << dataPoint.timeMiliseconds << ",";
    file << dataPoint.shortestPathLength << ",";
    file << dataPoint.inputtedPathLength << ",";
    file << dataPoint.percentErrorInLength << ",";
    file << dataPoint.pointAX << ",";
    file << dataPoint.pointAY << ",";
    file << dataPoint.pointBX << ",";
    file << dataPoint.pointBY << "\n";
  }

  file.close();
}


