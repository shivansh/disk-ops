#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

// We define a highly restricted constraint on the main
// memory size for the sake of demostration. However, a
// realistic limit will be much much higher than this.
#define MEMORY 20
#define INPUT_FILE "input_file"

// Returns top N elements from a file containing list of numbers.
// Constraint: N elements can be held in memory.
void
topN(int N)
{
    int element;  // Individual element read from disk.
    int memory_limit = MEMORY / sizeof(element);
    // Maximum number of elements allowed in heap.
    int limit = min(N, memory_limit);
    bool heap_modified = false;  // Tracks whether 'min_heap' was modified.
    vector<int> buffer;          // Buffer for holding elements read from disk.
    priority_queue<int, vector<int>, greater<int>> min_heap;
    // Maximum number of elements that can be held in memory at a time.
    ifstream infile(INPUT_FILE);

    // Initialize 'min_heap'.
    while (limit--)
        min_heap.push(0);

    while (infile >> element) {
        buffer.push_back(element);
        if (buffer.size() == memory_limit) {
            heap_modified = true;
            while (!buffer.empty()) {
                if (min_heap.top() < buffer.back()) {
                    min_heap.pop();  // Remove the smallest element.
                    min_heap.push(buffer.back());
                }
                buffer.pop_back();
            }
        }
    }
    infile.close();

    // Buffer might still be partially filled.
    if (!buffer.empty()) {
        if (!heap_modified) {
            // All the elements from disk are now loaded in memory,
            // hence it's safe to perform in-memory operations on them.
            sort(buffer.begin(), buffer.end(), greater<int>());
            for (auto i = buffer.begin();
                 i < buffer.begin() + N, i != buffer.end(); i++)
                cout << *i << ' ';
            cout << endl;
            return;
        } else {
            while (!buffer.empty()) {
                if (min_heap.top() < buffer.back()) {
                    min_heap.pop();
                    min_heap.push(buffer.back());
                }
                buffer.pop_back();
            }
        }
    }

    // Print the elements to stdout.
    while (!min_heap.empty()) {
        cout << min_heap.top() << ' ';
        min_heap.pop();
    }
    cout << endl;
}

int
main()
{
    topN(5);
    return 0;
}
