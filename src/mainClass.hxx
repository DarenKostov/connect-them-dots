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

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <sys/types.h>

class MainClass{

  private:
    //variables:

    struct dataPoint{
      double averageDistance;
      size_t inputtedPointCount;
      uint32_t timeMiliseconds;
      double shortestPathLength;
      double inputtedPathLength;
      double pointAX;
      double pointAY;
      double pointBX;
      double pointBY;
    };

    //sfml stuff
    sf::RenderWindow window;
    sf::View mainView;
    sf::Clock clock;


    sf::Vector2f pointA;
    sf::Vector2f pointB;
    
    //the path of the mouse from point A to point B?
    std::vector<sf::Vector2f> mouseCoordinates;
  
    //how well the user did each time they inputted a path and other data
    std::vector<dataPoint> dataPoints;
  
    //did the mouse click?
    bool hasClicked;


    //data that is changable

  public:

    //constructor, like a atSTartUp function
    MainClass();

    //deconstror
    ~MainClass();

    //the function that does all the logic, basically the main function
    void startProgram();

  
    private:
    
    //this performs tasks depending on the actions in the enviroment, like resizing the window 
    void performActions();
  
    //this updates the program, like a "loop" function
    void update();

    //this draws he program, like update but for drawing
    void draw();

    //sets the locations of the point to random coordinates, give it the min and max distance
    void randomizePoints(double, double);
    void randomizePoints();

    //calculates arnd returns the avregae distance from the inputted path from the shorted path
    double getAverageDistance();

    //record the current data point to our records
    void recordDataPoint();

    bool 

};
