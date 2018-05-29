#define DATA_LENGTH 255

#include "include/SerialPort.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <time.h>
#include <fstream>
#include <SFML/Graphics.hpp>

using namespace std;

//Set Port
char* portName = "\\\\.\\COM10";

//Declare a global object
SerialPort *arduino;

//Here '\n' is a delimiter
char receivedString[DATA_LENGTH];

const string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d_%H-%M", &tstruct);

    return buf;
}

sf::CircleShape RCircleMaker(string);
sf::CircleShape LCircleMaker(string);

int main()
{
  //Variables: Time Stuff
  time_t rawtime;
  struct tm*timeinfo;
  //Variables: File Stuff
  string fileName;
  string fileExtension = ".csv";
  ofstream outputFile;
  string serialInput;
  //Variables: Visual Stuff
  sf::CircleShape RCircle;
  sf::CircleShape LCircle;
  //Variables: Serial Stuff
  arduino = new SerialPort(portName);
  //End of Variables


  if (arduino->isConnected())
  {
    //Generating the File
    cout << "currentDateTime()=" << currentDateTime() << endl;
    fileName = currentDateTime()+fileExtension;
    cout << fileName << endl;
    outputFile.open(fileName);
    //Visual Representation
    sf::RenderWindow window(sf::VideoMode(800, 600), "JWFIN Newton's Cradle");
    while(window.isOpen())
    {
      sf::Event event;
        while(window.pollEvent(event))
        {
          if(event.type == sf::Event::Closed)
          {
            window.close();
          }
      int hasRead = arduino->readSerialPort(receivedString, DATA_LENGTH);
      if (hasRead) printf("%s ", receivedString);
      //Writing to the File
      outputFile << receivedString;
      window.clear();
      RCircle = RCircleMaker(receivedString);
      RCircle = LCircleMaker(receivedString);
      window.draw(RCircle);
      window.draw(LCircle);
      window.display();
    }
    outputFile.close();
  }
}

sf::CircleShape RCicleMaker(string input)
{

}

sf::CircleShape LCicleMaker(string input)
{

}
