#include <iostream>
#include <string>
#include <stdio.h>
#include <time.h>
#include <fstream>
#include <SFML/Graphics.hpp>

using namespace std;


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
    //End of Variables

    //To Be Added: Serial Input
    serialInput = "R18950";
    //Generating and Writing to the File
    cout << "currentDateTime()=" << currentDateTime() << endl;
    fileName = currentDateTime()+fileExtension;
    cout << fileName << endl;
    outputFile.open(fileName);
    outputFile << "1,2,3\n";
    outputFile << "4,5,6\n";
    outputFile.close();
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
        }
        window.clear();
        RCircle = RCircleMaker(serialInput);
        RCircle = LCircleMaker(serialInput);
        window.draw(RCircle);
        window.draw(LCircle);
        window.display();
    }
}

sf::CircleShape RCicleMaker(string input)
{

}

sf::CircleShape LCicleMaker(string input)
{

}
