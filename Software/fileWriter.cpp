#include <iostream>
#include <fstream>
#include <ctime>
#include <time.h>

using namespace std;

int main()
{
  time_t rawtime;
  struct tm*timeinfo;
  char fileName[25];
  string date;

  time(&rawtime);
  timeinfo = localtime(&rawtime);
  ofstream outputFile;
  date = asctime(timeinfo);
  printf(date);
  sprintf(fileName, "%s.csv", date);
  printf(fileName);
  outputFile.open(fileName);
  outputFile << "1,2,3\n";
  outputFile << "4,5,6\n";
  outputFile.close();
}

