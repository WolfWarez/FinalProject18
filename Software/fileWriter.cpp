#include <iostream>
#include <string>
#include <stdio.h>
#include <time.h>
#include <fstream>

using namespace std;


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
  time_t rawtime;
  struct tm*timeinfo;
  string fileName;
  string fileExtension = ".csv";
  ofstream outputFile;

  cout << "currentDateTime()=" << currentDateTime() << endl;
  fileName = currentDateTime()+fileExtension;
  cout << fileName << endl;
  outputFile.open(fileName);
  outputFile << "1,2,3\n";
  outputFile << "4,5,6\n";
  outputFile.close();
}

