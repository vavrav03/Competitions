#include <iostream>
#include <vector>

using namespace std;
#include <fstream>
#include <iostream>
#include <vector>

void generateDifferent(int n) {
   ofstream outputFile;
   outputFile.open("different200000.txt");
   outputFile << n << endl;
   vector<int> possibleHeights(n);
   for(int i = 0; i < n; i++){
      possibleHeights[i] = i * 100;
   }
   int index;
   while(possibleHeights.size() != 0){
      index = rand() % possibleHeights.size();
      outputFile << possibleHeights[index] << " ";
      possibleHeights.erase(possibleHeights.begin() + index);
   }
   outputFile.close();
}

void generateSame(int n) {
   ofstream outputFile;
   outputFile.open("possiblySame200000.txt");
   outputFile.close();
   return;
}
﻿
int main() {
   int n = 20;
   generateDifferent(n);
   return 0;
}
