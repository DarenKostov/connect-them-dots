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
  
  randomizePoints(100, 200);

  
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
