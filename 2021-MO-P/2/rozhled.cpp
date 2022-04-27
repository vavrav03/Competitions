#include <chrono>
#include <cmath>
#include <fstream>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Vertice {
  public:
   int leftCoor;
   int rightCoor;
   int height;
   int minToLeft;
   int closestGreaterIndexLeft = -1;
   int minToClosestIndexLeft = -1;
   int closestGreaterIndexRight = -1;
   int minToClosestIndexRight = -1;
   Vertice(int cleftCoor, int crightCoor, int cheight, int cminToLeft) {
      leftCoor = cleftCoor;
      rightCoor = crightCoor;
      height = cheight;
      minToLeft = cminToLeft;
   }
   string to_string() {
      return ("L: " + std::to_string(leftCoor) + " " +
              "R: " + std::to_string(rightCoor) +
              ", height: " + std::to_string(height) + ", minToLeft: " +
              std::to_string(minToLeft) + ", closestGreaterIndex: " + " L: " +
              std::to_string(closestGreaterIndexLeft) +
              " R: " + std::to_string(closestGreaterIndexRight));
   }
};

vector<Vertice> vertices;

void findClosestFromLeft() {
   stack<int> stack;
   stack.push(0);
   int fromStack;
   int starting;
   for (int i = 1; i < vertices.size(); i++) {
      while (!stack.empty()) {
         if (vertices[i].height > vertices[(fromStack = stack.top())].height) {
            vertices[fromStack].closestGreaterIndexRight = i;
            stack.pop();
         } else {
            break;
         }
      }
      stack.push(i);
   }
}

void findClosestFromRight() {
   stack<int> stack;
   stack.push(vertices.size() - 1);
   int fromStack;
   int starting;
   for (int i = vertices.size() - 2; i >= 0; i--) {
      while (!stack.empty()) {
         if (vertices[i].height > vertices[(fromStack = stack.top())].height) {
            // if (vertices[fromStack].closestGreaterIndex == -1 ||
            // vertices[vertices[fromStack].closestGreaterIndex].leftCoor -
            // vertices[fromStack].rightCoor >) { //pokud jsou stejne, je nutne
            // vybrat tu s vyssim minimem
            vertices[fromStack].closestGreaterIndexLeft = i;
            stack.pop();
         } else {
            break;
         }
      }
      stack.push(i);
   }
}

void constructTree(int segmentTree[], int left, int right, int pos) {
   if (left == right) {
      segmentTree[pos] = left;
      return;
   }
   int mid = (left + right) / 2;
   constructTree(segmentTree, left, mid, 2 * pos + 1);
   constructTree(segmentTree, mid + 1, right, 2 * pos + 2);
   if (vertices[segmentTree[2 * pos + 1]].minToLeft <
       vertices[segmentTree[2 * pos + 2]].minToLeft) {
      segmentTree[pos] = segmentTree[2 * pos + 1];
   } else {
      segmentTree[pos] = segmentTree[2 * pos + 2];
   }
   return;
}

int rangeMinQuery(int segmentTree[], int qleft, int qright, int left, int right,
                  int pos) {
   if (qleft <= left && qright >= right) {  // totalni prekryti
      return vertices[segmentTree[pos]].minToLeft;
   }
   if (qleft > right || qright < left) {  // zadne prekryti
      return 2000000000;
   }
   int mid = (left + right) / 2;
   return min(
       rangeMinQuery(segmentTree, qleft, qright, left, mid, 2 * pos + 1),
       rangeMinQuery(segmentTree, qleft, qright, mid + 1, right, 2 * pos + 2));
}

int findMinInInterval(int segmentTree[], int left, int right) {
   return rangeMinQuery(segmentTree, left, right - 1, 0, vertices.size() - 2,
                        0);
}

void solve() {
   findClosestFromLeft();
   findClosestFromRight();
   int segmentTreeSize =
       2 * pow(2, ceil(log(vertices.size() - 1) / log(2))) - 1;
   int segmentTree[segmentTreeSize];  // pouze pro 1, n-1 (kazdy vertice si
                                      // pamatuje jen minimum doleva)
   for (int i = 0; i < segmentTreeSize; i++) {
      segmentTree[i] = -1;
   }
   constructTree(segmentTree, 1, vertices.size() - 1, 0);
   // for(int i = 0; i < segmentTreeSize; i++) {
   //    cout << segmentTree[i] << ", ";
   // }
   // cout << endl;

   // for (int i = 1; i < vertices.size(); i++) {
   //    cout << to_string(0) + ", " + to_string(i) + ": "
   //         << findMinInInterval(segmentTree, 0, i) << endl;
   // }

   for (int i = 0; i < vertices.size(); i++) {
      if (vertices[i].closestGreaterIndexLeft == -1) {
         if (vertices[i].closestGreaterIndexRight == -1) {
            cout << vertices[i].height << endl;
            continue;
         } else {
            cout << (vertices[i].height - findMinInInterval(segmentTree, i,
                                      vertices[i].closestGreaterIndexRight))
                                      << endl;
            continue;
         }
      } else if (vertices[i].closestGreaterIndexRight == -1) {
         if (vertices[i].closestGreaterIndexLeft == -1) {
            cout << vertices[i].height << endl;
            continue;
         } else {
            cout << (vertices[i].height - findMinInInterval(segmentTree,
                                      vertices[i].closestGreaterIndexLeft,
                                      i)) << endl;
            continue;
         }
      } else {
         cout << (vertices[i].height - max(findMinInInterval(segmentTree, i,
                                       vertices[i].closestGreaterIndexRight),
                     findMinInInterval(segmentTree,
                                       vertices[i].closestGreaterIndexLeft,
                                       i))) << endl;
         continue;
      }
   }
   return;
}

int main() {
   int n;
   cin >> n;
   int lastItem;
   cin >> lastItem;
   int leftBoundaryIndex = 0;
   int leftBoundaryHeight = lastItem;
   if (n == 1) {
      cout << lastItem << endl;
      return 0;
   }
   int currentItem;
   int currentMin =
       lastItem;  // pro 0. prvek muze delat paseku, kouknout na to pozdeji

   for (int i = 1; i < n; i++) {
      cin >> currentItem;
      if (currentItem > leftBoundaryHeight) {
         leftBoundaryIndex = i;
      } else if (currentItem == leftBoundaryHeight) {
      } else if (leftBoundaryIndex != -1) {
         vertices.push_back(
             Vertice(leftBoundaryIndex, i - 1, leftBoundaryHeight, currentMin));
         currentMin = currentItem;
         leftBoundaryIndex = -1;
      }
      if (currentItem < currentMin) {
         currentMin = currentItem;
      }
      leftBoundaryHeight = currentItem;
   }
   if (currentItem == leftBoundaryHeight && leftBoundaryIndex != -1) {
      vertices.push_back(
          Vertice(leftBoundaryIndex, n - 1, leftBoundaryHeight, currentMin));
   }
   if (vertices[0].leftCoor == 0) {
      vertices[0].minToLeft = 0;
   }
   if(vertices.size() == 1) {
      cout << vertices[0].height << endl;
      return 0;
   }
   solve();
   // for (Vertice v : vertices) {
   //    cout << v.to_string() << endl;
   // }
   return 0;

   // file input
   // auto start = std::chrono::right_resolution_clock::now();
   // int n;
   // ifstream inputFile;
   // inputFile.open("different200000.txt");
   // // inputFile.open("maybeSame200000.txt");
   // inputFile >> n;
   // int lastItem;
   // inputFile >> lastItem;
   // int leftBoundaryIndex = 0;
   // int leftBoundaryHeight = lastItem;
   // if (n == 1) {
   //    cout << lastItem << endl;
   //    return 0;
   // }
   // int currentItem;
   // int currentMin =
   //     lastItem;  // pro 0. prvek muze delat paseku, kouknout na to pozdeji

   // for (int i = 1; i < n; i++) {
   //    inputFile >> currentItem;
   //    if (currentItem > leftBoundaryHeight) {
   //       leftBoundaryIndex = i;
   //    } else if (currentItem == leftBoundaryHeight) {
   //    } else if (leftBoundaryIndex != -1) {
   //       vertices.push_back(
   //           Vertice(leftBoundaryIndex, i - 1, leftBoundaryHeight,
   //           currentMin));
   //       currentMin = currentItem;
   //       leftBoundaryIndex = -1;
   //    }
   //    if (currentItem < currentMin) {
   //       currentMin = currentItem;
   //    }
   //    leftBoundaryHeight = currentItem;
   // }

   // if (currentItem == leftBoundaryHeight && leftBoundaryIndex != -1) {
   //    vertices.push_back(
   //        Vertice(leftBoundaryIndex, n - 1, leftBoundaryHeight, currentMin));
   // }
   // if (vertices[0].leftCoor == 0) {
   //    vertices[0].minToLeft = 0;
   // }
   // solve();
   // // for (Vertice v : vertices) {
   // //    cout << v.to_string() << endl;
   // // }
   // // auto end = std::chrono::right_resolution_clock::now();
   // // auto duration =
   // std::chrono::duration_cast<std::chrono::microseconds>(end
   // // - start); cout << endl; cout << duration.count() << endl;
   // return 0;
}