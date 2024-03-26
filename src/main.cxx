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

#include <iostream>
#include <csignal>

//prints the licence
void printLicence();
//prints all flags
void printHelp();
//prints the version
void printVersion();


//at exit free the MainClass object 
void atExitFree(MainClass*);

static void freeVariable(){

  std::cout << "\e[93mAbout to Free Main\n\e[0m";
  atExitFree(NULL);
}

void atExitFree(MainClass* in){

  //store a static pointer to our Main
  static MainClass* eternalPtr;


  //if we give it a valid pointer, store it; if not, delete it
  if(in){
    std::cout << "\e[93mStoring Main\n\e[0m";
    eternalPtr=in;
    atexit(freeVariable);
  }else{
    std::cout << "\e[93mFreeing Main\n\e[0m";
    delete eternalPtr;
  }
}




void signal_handler(int signal_num){

  std::cout << "\n\e[93mSignal Handler!\n";
  std::cout << "Signal: " << signal_num << "\n\e[0m";
  exit(signal_num);
}


int main(int argc, char **argv){


  //check all flags
  for(int i=0; i<argc; i++){
    std::string thisArg=std::string(argv[i]);
    if(thisArg=="-l" || thisArg=="--licence"){
      printLicence();
      return 0;
    }else if(thisArg=="-h" || thisArg=="--help"){
      printHelp();
      return 0;
    }else if(thisArg=="-v" || thisArg=="--version"){
      printVersion();
      return 0;
    }
  }


  std::cout << "\e[93mstart of program\n\e[0m";

  signal(SIGINT, signal_handler);


  MainClass* mainInstance=new MainClass();
  atExitFree(mainInstance);

  mainInstance->startProgram();
  

}

//FUNCTION DEFINITION


void printHelp(){
  std::cout << "-h, --help: this help\n";
  std::cout << "-l, --licence: print the licence\n";
  std::cout << "-v, --version: prints the version\n";
  
  std::cout << "\nHow to use:\n";
  std::cout << "1. Left click and hold on the center of orange circle\n";
  std::cout << "2. Drag, while holding, to the cyan circle\n";
  std::cout << "3. Relase the button when the center of the cyan circle is reached\n";
  std::cout << "4. Repeat, while trying to take the shortest path\n";

  std::cout << "\nData:\n";
  std::cout << "Upon closing a \"datapoints-{UNIX TIME IN SECONDS}.csv\" file will be created";
  std::cout << "containg information about the successful attempts to connect the 2 points";
}


void printVersion(){
  std::cout << "Copyright (c) Daren Kostov\n";
  std::cout << "GPLv3\n";
  std::cout << "connect-them-dots\n";
    
  //Version Major.Minor.Patch
  std::cout << "Version 1.0.0\n";

}
