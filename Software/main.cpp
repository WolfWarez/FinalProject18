#define DATA_LENGTH 64

#include "include/SerialPort.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <time.h>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <conio.h>

using namespace std;

//Set Port
char* portName = "\\\\.\\COM4";

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



int main()
{
  //Variables: File Stuff
  string fileName;
  string fileExtension = ".csv";
  ofstream outputFile;
  string serialInput;
  //Variables: Visual Stuff-Not Working
  /*
  sf::CircleShape RCircle(100);
  RCircle.setPosition(100,300);
  RCircle.setFillColor(sf::Color(255,0,0));
  sf::CircleShape LCircle(100);
  LCircle.setPosition(500,300);
  LCircle.setFillColor(sf::Color(255,0,0));
  */
  //Variables: Serial Stuff
  arduino = new SerialPort(portName);
  string delimiter = "\n";
  string input;
  string output;
  string serialBuffer;
  string hold;
  int inputLength;
  int hasRead;
  size_t found;

  //End of Variables


  if (arduino->isConnected())
  {
    //Generating the File
    cout << "currentDateTime()=" << currentDateTime() << endl;
    fileName = currentDateTime()+fileExtension;
    cout << fileName << endl;
    outputFile.open(fileName);
    outputFile << "Side, Time\n";



    while(true)
    {

      //Receive Serial Data
        hasRead = arduino->readSerialPort(receivedString, DATA_LENGTH);
        if(hasRead)
        {
            serialBuffer.assign((const char*) receivedString, hasRead);
            cout << "sB:  " << serialBuffer << endl;

            input = input+serialBuffer;
            serialBuffer.clear();

            found = input.find(delimiter);
            if(found!=string::npos)
            {
                //Writing to the File
                cout << "input:  " << input << endl;
                output = input.substr(0,found + 1);
                outputFile << output;
                output.clear();
                inputLength = input.length();
                hold.clear();
                hold = input.substr(found + 1, inputLength);
                input.clear();
                input = hold;
            }
//          hasRead = 0;
        }
        if(_kbhit()) break;
    }
  outputFile.close();
  }
}
    //Visual Representation-Not Working
    /*
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
      //Receive Serial Data
      int hasRead = arduino->readSerialPort(receivedString, DATA_LENGTH);
      if (hasRead) printf("%s ", receivedString);
      //Writing to the File
      input.assign((const char*) receivedString, 255);
      cout << input << endl;
      outputFile << input;
      window.clear();
      //Right Circle
      size_t found = input.find("RN");
      if (found!=std::string::npos)
      {
        RCircle.setFillColor(sf::Color(0,255,0));
      }
      found = input.find("RF");
      if (found!=std::string::npos)
      {
        RCircle.setFillColor(sf::Color(255,0,0));
      }
      //Left Circle
      found = input.find("LN");
      if (found!=std::string::npos)
      {
        LCircle.setFillColor(sf::Color(0,255,0));
      }
      found = input.find("LF");
      if (found!=std::string::npos)
      {
        LCircle.setFillColor(sf::Color(255,0,0));
      }
      window.draw(RCircle);
      window.draw(LCircle);
      window.display();
    }

 }
 */
