#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

vector<int> generate(int n, int s) {
   vector<int> answer;
   for (int i = 0; i < n; i++) {
      answer.push_back((rand() % 1000));
   }
   vector<int> sorted = answer;
   sort(sorted.begin(), sorted.end());
   int starosta = sorted.at(s - 1);
   for (int i = 0; i < n; i++) {
      if (answer.at(i) == starosta) {
         int temp = answer.at(i);
         answer.at(i) = answer.at(s - 1);
         answer.at(s - 1) = temp;
      }
   }
   return answer;
}

int main() {
   int n = 50;
   int s = 1;
   int l = 10000;
   vector<int> array = generate(n, s);
   cout << n << " " << s << " " << l << endl;
   for (int move : array) {
      cout << move << " ";
   }
   cout << endl;
   return 0;
}
