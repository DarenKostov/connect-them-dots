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
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>

void MainClass::draw(){

  window.clear();
  window.setView(mainView);
  



  sf::CircleShape circle;

  circle.setFillColor(sf::Color::Transparent);

  circle.setOutlineThickness(2);
  circle.setRadius(circleRadius);
  circle.setOrigin(circle.getRadius(), circle.getRadius());

  circle.setOutlineColor(sf::Color(0xff8800ff));
  circle.setPosition(pointA);
  window.draw(circle);

  circle.setOutlineColor(sf::Color(0x00ffffff));
  circle.setPosition(pointB);
  window.draw(circle);



  circle.setOutlineThickness(1);
  circle.setRadius(circleRadius/2);
  circle.setOrigin(circle.getRadius(), circle.getRadius());
  
  circle.setOutlineColor(sf::Color(0xff880033));
  circle.setPosition(pointA);
  window.draw(circle);

  circle.setOutlineColor(sf::Color(0x00ffff33));
  circle.setPosition(pointB);
  window.draw(circle);

  if(mouseCoordinates.size()>=2){
    for(auto coordinate=mouseCoordinates.begin()+1; coordinate!=mouseCoordinates.end(); coordinate++){

      sf::Vertex line[2];

      line[0].position=*coordinate;
      line[1].position=*(coordinate-1);
      line[0].color=sf::Color::White;
      line[1].color=sf::Color::White;

      window.draw(line, 2, sf::PrimitiveType::LineStrip);
  
    }
  }
  

  window.display();
  
}
