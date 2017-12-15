#include <fstream>
#include <iostream>
#include <memory>
#include <queue>
#include <vector>

// We define a restricted constraint on the main memory
// limit. For the sake of demonstration, it is set to
// 1024 bytes, although a realistic limit will be much
// much higher than this.
#define MEM_LIMIT 1024
#define INPUT_FILE "input_file"    // input file
#define OUTPUT_FILE "output_file"  // output file

using namespace std;

class topNelem {
public:
    void
    topN(int N)
    {
        bool first_pass = true;
        bool done = false;
        ifstream infile(INPUT_FILE);
        int read_value;
        int read_count = 0;
        int n = 0;
        priority_queue<int, vector<int>, greater<int>> min_heap;
        vector<int> buffer;          // buffer for temporarily holding values
        vector<int> first_N_vals;    // vector for storing first N values
        vector<int> remaining_vals;  // vector for storing remaining values

        bool check = true;
        while (infile >> read_value && check) {
            if (read_count < MEM_LIMIT) {
                read_count++;
            } else {
                buffer.clear();
                read_count = 0;
            }

            buffer.push_back(read_value);
            // Wait until the buffer fills up
            if (buffer.size() != MEM_LIMIT)
                continue;

        jump_state:
            for (const auto& i : buffer) {
                if (n < N && first_pass) {
                    first_N_vals.push_back(i);
                    n++;
                } else
                    remaining_vals.push_back(i);
            }
            buffer.clear();

            int counter = 0;
            if (n == N) {
                if (first_pass) {
                    // make a min-heap from the first N values
                    // stored in first_N_vals.
                    for (const auto& i : first_N_vals)
                        min_heap.push(i);

                    counter = N;
                    first_N_vals.clear();
                    first_pass = false;
                } else {
                    for (const auto& i : remaining_vals) {
                        cout << i << ' ';
                        if (!min_heap.empty() && counter == N) {
                            if (i > min_heap.top()) {
                                min_heap.pop();
                                min_heap.push(i);
                            }
                        } else {
                            if (counter == N)
                                continue;
                            min_heap.push(i);
                            counter++;
                        }
                    }
                    // Clearing the vector of currently held "remaining values"
                    // (after first N) will make sure that at a time it will
                    // only contain "memory restricted" number of values.
                    remaining_vals.clear();
                }
            }
        }

        // Since we wait for the buffer to fill up, there might
        // be last few remaining values left in it.
        if (!buffer.empty()) {
            if (min_heap.empty()) {
                n = 0;
                first_pass = true;
                check = false;
                goto jump_state;
            }

            else {
                for (const auto& i : buffer) {
                    if (i > min_heap.top()) {
                        min_heap.pop();
                        min_heap.push(i);
                    }
                }
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

int
main()
{
    // We currently relax the constraints a bit and
    // assume that the main memory can hold N values;
    int N;
    cout << "Enter value of N (less than 1024): ";
    cin >> N;
    if (N < 1024) {
        topNelem topn;
        topn.topN(N);
    } else
        cout << "Please enter a valid value of N!\n";

    return 0;
}
