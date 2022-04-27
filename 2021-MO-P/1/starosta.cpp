#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

bool isPossible(int heights[], int n, int s) {
   int numberOfSmallerDancers = 0;
   int numberOfSameDancers = -1;
   for (int i = 0; i < n; i++) {
      if (heights[i] < heights[s]) {
         numberOfSmallerDancers++;
      } else if (heights[i] == heights[s]) {
         numberOfSameDancers++;
      }
   }
   if (numberOfSmallerDancers > s) {
      return false;
   } else if (numberOfSmallerDancers == s ||
              numberOfSmallerDancers + numberOfSameDancers >= s) {
      return true;
   } else {
      return false;
   }
}

string traversePart(int heights[], int leftBound, int rightBound) {
   if (rightBound < leftBound) {
      int temp = leftBound;
      leftBound = rightBound;
      rightBound = temp;
   }
   int half = ceil((rightBound - leftBound) / 2.0);
   int temp;

   int n = 7;
   // for (int i = 0; i < n; i++) {
   //    cout << heights[i] << " ";
   // }
   // cout << endl;
   for (int i = 0; i < half; i++) {
      temp = heights[leftBound + i];
      heights[leftBound + i] = heights[rightBound - i];
      heights[rightBound - i] = temp;
   }
   // cout << std::to_string(leftBound + 1) + " " + std::to_string(rightBound + 1)
   //      << endl;
   // for (int i = 0; i < n; i++) {
   //    cout << heights[i] << " ";
   // }
   // cout << endl;
   // cout << endl;
   return std::to_string(leftBound + 1) + " " + std::to_string(rightBound + 1);
}

int findMinIndex(int heights[], int leftBound, int rightBound, int s) {
   if (rightBound < leftBound) {
      int temp = leftBound;
      leftBound = rightBound;
      rightBound = temp;
   }
   int minIndex = leftBound;
   for (int i = leftBound + 1; i <= rightBound; i++) {
      if (heights[i] < heights[minIndex]) {
         if (s != i) {
            minIndex = i;
         }
      }
   }
   return minIndex;
}

int findMaxIndex(int heights[], int leftBound, int rightBound, int s) {
   if (rightBound < leftBound) {
      int temp = leftBound;
      leftBound = rightBound;
      rightBound = temp;
   }
   int maxIndex = leftBound;
   for (int i = leftBound + 1; i <= rightBound; i++) {
      if (heights[i] > heights[maxIndex]) {
         if (s != i) {
            maxIndex = i;
         }
      }
   }
   return maxIndex;
}

bool shouldStop(int l, int counter) { return l == counter && l != 0; }

void solve(int n, int s, int l, int heights[]) {
   std::vector<string> moves = {};
   int counter = 0;
   if (isPossible(heights, n, s)) {
      if (s <= n / 2) {
         // leva strana mensi
         int minIndex;
         for (int i = 0; i < s; i++) {
            if (shouldStop(l, counter)) {
               cout << "NE" << endl;
               return;
            }
            minIndex = findMinIndex(heights, i, n - 1, s);
            if (minIndex == i) {
               // hotove
            } else if (minIndex < s || s - i + s == minIndex) {
               // ve stejnem podpoli
               counter++;
               moves.push_back(traversePart(heights, i, minIndex));
            } else {
               moves.push_back(traversePart(heights, s - i + s, minIndex));
               moves.push_back(traversePart(heights, i, s - i + s));
               counter += 2;
            }
         }
         for (int i = s + 1; i < n; i++) {
            if (shouldStop(l, counter)) {
               cout << "NE" << endl;
               return;
            }
            minIndex = findMinIndex(heights, i, n - 1, s);
            if (minIndex == i) {
               // hotove
            } else {
               counter++;
               moves.push_back(traversePart(heights, i, minIndex));
            }
         }
      } else {
         // prava strana mensi
         int maxIndex;
         for (int i = n - 1; i > s; i--) {
            if (shouldStop(l, counter)) {
               cout << "NE" << endl;
               return;
            }
            maxIndex = findMaxIndex(heights, 0, i, s);
            if (maxIndex == i) {
               // hotove
            } else if (maxIndex > s || s - (i - s) == maxIndex) {
               // ve stejnem podpoli
               counter++;
               moves.push_back(traversePart(heights, i, maxIndex));
            } else {
               moves.push_back(traversePart(heights, s - (i - s), maxIndex));
               moves.push_back(traversePart(heights, i, s - (i - s)));
               counter += 2;
            }
         }
         for (int i = s - 1; i >= 0; i--) {
            if (shouldStop(l, counter)) {
               cout << "NE" << endl;
               return;
            }
            maxIndex = findMaxIndex(heights, 0, i, s);
            if (maxIndex == i) {
               // hotove
            } else {
               counter++;
               moves.push_back(traversePart(heights, i, maxIndex));
            }
         }
      }
      cout << "ANO" << endl;
      if (l != 0) {
         cout << counter << endl;
         for (string move : moves) {
            cout << move << endl;
         }
      }
   } else {
      cout << "NE" << endl;
   }
   return;
}

int main() {
   int n, s, l;
   cin >> n >> s >> l;
   s = s - 1;  // pro pole
   int heights[n];
   for (int i = 0; i < n; i++) {
      cin >> heights[i];
   }
   solve(n, s, l, heights);
   // int heights[] = {1, 8, 3, 4};
   // n = (sizeof(heights) / sizeof(*heights));
   // cout << isPossible(heights, n, 0) << endl;
   // for (int i = 0; i < n; i++) {
   //    cout << heights[i] << " ";
   // }
   // cout << endl;
   return 0;
}
