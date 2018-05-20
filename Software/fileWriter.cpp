#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;

int main()
{
  ofstream outputFile;
  outputFile.open("example.csv");
  outputFile << "1,2,3\r\n";
  outputFile << "4,5,6\r\n";
  outputFile.close();
}
