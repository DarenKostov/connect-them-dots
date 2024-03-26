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

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/LineShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>

void MainClass::draw(){

  window.clear();
  window.setView(mainView);
  
  sf::RectangleShape rect(sf::Vector2f(30, 30));
  rect.setFillColor(sf::Color(255, 255, 255, 255));
  rect.setPosition(window.mapPixelToCoords(sf::Mouse::getPosition(window), mainView));
  window.draw(rect);



  sf::CircleShape circleA;
  sf::CircleShape circleB;

  circleA.setFillColor(sf::Color::Transparent);
  circleB.setFillColor(sf::Color::Transparent);

  circleA.setOutlineColor(sf::Color(0xff8800ff));
  circleB.setOutlineColor(sf::Color(0x00ffffff));

  circleA.setOutlineThickness(5);
  circleB.setOutlineThickness(5);
  
  circleA.setRadius(10);
  circleB.setRadius(10);

  circleA.setPosition(pointA);
  circleB.setPosition(pointB);
  
  window.draw(circleA);
  window.draw(circleB);



  if(mouseCoordinates.size()>=2){
    for(auto coordinate=mouseCoordinates.begin()+1; coordinate!=mouseCoordinates.end(); coordinate++){
      sf::LineShape line;

      line.setPoints(*coordinate, *(coordinate-1));
      line.setFillColor(sf::Color::White);
      window.draw(line);
  
    }
  }
  

  window.display();
  
}
