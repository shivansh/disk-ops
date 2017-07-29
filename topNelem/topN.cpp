#include <fstream>
#include <iostream>
#include <memory>
#include <queue>
#include <vector>

// We define a restricted constraint on the main memory
// limit. For the sake of demonstration, it is set to
// hold 3 char values at a time, although a realistic
// limit will be much much higher than this.
#define MEM_LIMIT 6
#define INPUT_FILE  "input_file"   // input file
#define OUTPUT_FILE "output_file"  // output file

using namespace std;

class topNelem {
  public:
    void topN(int N) {
      bool first_pass = true;
      ifstream infile(INPUT_FILE);
      int char_val;
      int n = 0;
      priority_queue<int, vector<int>,
                     greater<int>> min_heap;
      string temp;
      unique_ptr<char[]> buffer(new char[MEM_LIMIT]);
      vector<int> first_N_vals;         // vector for storing first N values
      vector<int> remaining_vals;       // vector for storing remaining values

      // TODO: Read integers instead of characters. The
      // current approach works for integers in [0, 9].
      while (infile) {
        infile.read(buffer.get(), MEM_LIMIT);
        temp = buffer.get();

        for (const auto &i : temp) {
          char_val = int(i);
          if (n < N && first_pass) {
            // We ignore space and newline characters.
            if (char_val >= 48 && char_val <= 57) {
              first_N_vals.push_back(char_val - 48);
              n++;
            }
          }
          else if (char_val >= 48 && char_val <= 57)
            remaining_vals.push_back(char_val - 48);

          // If the current line cannot be held in memory, we
          // read a chunk and clear the buffer for next read.
          buffer.reset(new char[MEM_LIMIT]);
        }

        if (first_pass && n == N) {
          // make min-heap from the current state of first_N_vals.
          for (const auto &i : first_N_vals)
            min_heap.push(i);

          first_N_vals.clear();
          first_pass = false;
        }
        else if (n == N) {
          for (const auto &i : remaining_vals) {
            if (i > min_heap.top()) {
              min_heap.pop();
              min_heap.push(i);
            }
          }
          // Clearing the vector of remaining values (after first N)
          // will make sure that at a time it will only contain
          // "memory restricted" number of values.
          remaining_vals.clear();
        }
      }

      cout << "Writing result to " + string(OUTPUT_FILE) << endl;
      ofstream outfile(OUTPUT_FILE);
      while (!min_heap.empty()) {
        outfile << min_heap.top() << ' ';
        min_heap.pop();
      }
      outfile << endl;

      infile.close();
      outfile.close();
    }
};

int main() {
  // We currently relax the constraints a bit and
  // assume that the main memory can hold N values;
  int N;
  cout << "Enter a number between 1 and 9 (inclusive): ";
  cin >> N;
  if (N >= 1 && N <= 9) {
    topNelem topn;
    topn.topN(N);
  }
  else
    cout << "Please enter a valid number!" << endl;

  return 0;
}
