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
#include <iostream>
#include <unistd.h>


MainClass::MainClass(){
  window.create(sf::VideoMode(123, 123), "connect-them-dots");
  mainView=sf::View(sf::FloatRect(0, 0, 123, 123));
  mainView.setViewport(sf::FloatRect(0, 0, 1, 1));
  window.setView(mainView);
  window.setVerticalSyncEnabled(true);

  hasClicked=false;

  srand(time(NULL));
  
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
    update();
    draw();


  }


}


void MainClass::randomizePoints(double minDistance, double maxDistance){

  double distance{0};

  //lets save some computation
  minDistance*=minDistance;
  maxDistance*=maxDistance;

  do{
    pointA.x=rand()%window.getSize().x;
    pointA.y=rand()%window.getSize().y;

    pointB.x=rand()%window.getSize().x;
    pointB.y=rand()%window.getSize().y;


    std::cout << pointA.x << "\n";
    std::cout << pointA.y << "\n";
    std::cout << "++++\n";
    std::cout << pointB.x << "\n";
    std::cout << pointB.y << "\n";
    std::cout << "====\n";
    
    distance=(pointA.x-pointB.x)*(pointA.x-pointB.x)+(pointA.y-pointB.y)*(pointA.y-pointB.y);

  }while(distance<minDistance || distance>maxDistance);

}

void MainClass::randomizePoints(){
  randomizePoints(100, 200);
}

double MainClass::getAverageDistance(){
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

  //record average distance
  newDataPoint.averageDistance=getAverageDistance();

  //record the points inputted
  newDataPoint.inputtedPointCount=mouseCoordinates.size();

  //record how much time this whole thing took
  newDataPoint.timeMiliseconds=clock.getElapsedTime().asMilliseconds();

  //record the actual shortest path
  newDataPoint.shortestPathLength=std::sqrt(
    (pointA.x-pointB.x)*(pointA.x-pointB.x)+
    (pointA.y-pointB.y)*(pointA.y-pointB.y));

  //record the users shortest path
  if(mouseCoordinates.size()>=2){
    for(auto coordinate=mouseCoordinates.begin()+1; coordinate!=mouseCoordinates.end(); coordinate++){

      sf::Vector2f& coordA{*(coordinate+1)};
      sf::Vector2f& coordB{*(coordinate)};
      
      newDataPoint.inputtedPathLength+=std::sqrt(
        (coordA.x-coordB.x)*(coordA.x-coordB.x)+
        (coordA.y-coordB.y)*(coordA.y-coordB.y));

    }
  }else{
    //how did we get here??????
    //if no points inputted the shortest path would be 0
    newDataPoint.inputtedPathLength=0;
  }

  
  newDataPoint.pointAX=pointA.x;
  newDataPoint.pointAY=pointA.y;
  newDataPoint.pointBX=pointB.x;
  newDataPoint.pointBY=pointB.y;

  dataPoints.push_back(newDataPoint);

}

