#include <iostream>

using namespace std;

// Fills knapsack, prints which items were selected,
// returns max value of knapsack
void knapsack(int T, int C, int n, string name[], int weight[], int value[])
{
  int K[n + 1][T + 1];
  bool keep[n][T+1];

  //initialize knapsack
  for (int i = 0; i <= n; i++)
  {
    for (int x = 0; x <= T; x++)
    {
      K[i][x] = 0;
      keep[i][x] = false;
    }
  }
  // fill knapsack
  for (int i = 1; i <= n; i++)
  {
    for (int x = 0; x <= T; x++)
    {
      if (weight[i - 1] > x) {
        K[i][x] = K[i - 1][x];
      }
      else {
        int yes = value[i - 1] + K[i - 1][x - weight[i - 1]];
        int no = K[i - 1][x];
        //Second clause checks that new value brings total calories closer to desired, not further from
        if(yes > no && (C - yes) < (C - K[i][x-1])) {
          keep[i-1][x] = true;
          K[i][x] = yes;
        }
        //Again check that new value brings total closer before adding
        else if((C - no) < (C - K[i][x-1]))
          K[i][x] = no;
        //If total is not brought closer, add same value as before as new workout is not added
        else K[i][x]= K[i-1][x];
      }
    }
  }


  // Print selected items using boolean array
  cout << "Workout plan: " << endl;
  int k = T;
  int time = 0;
  for(int i=n-1; i>=0; i--) {
    if(keep[i][k]) {
      cout << name[i] << " Calories burned: " << value[i]
      << " Time: " << weight[i] << endl;
      time+=weight[i];
      k = k-weight[i];
    }
  }
  cout << "Total calories burned: " << K[n][T] << endl;
  cout << "Total time: " << time << endl;
}

// Run program: take input, call knapsack function
int main()
{
  cout << "Enter the number of workouts:";
  int n, T, C;
  cin >> n;
  int val[n], wt[n];
  string nam[n];
  for (int i = 0; i < n; i++)
  {
    cout << "Details for workout number " << i+1 << endl;
    cout << "Enter the name of workout:";
    cin >> nam[i];
    cout << "Enter calories burned in workout:";
    cin >> val[i];
    cout << "Enter time (min) of workout:";
    cin >> wt[i];
  }
  cout << "Enter the desired total calories burned: ";
  cin >> C;
  cout << "Enter the total time (min) for workout: ";
  cin >> T;

  knapsack(T, C, n, nam, wt, val);

  return 0;
}
