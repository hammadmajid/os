// g++ -std=c++17 fifo_page_replacement.cpp -o fifo_page_replacement

#include <iostream>
using namespace std;

int main() {
    const int FRAME_COUNT = 3;
    const int REFERENCE_STRING[12] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3};
    
    int frames[FRAME_COUNT];
    for (int i = 0; i < FRAME_COUNT; i++) {
        frames[i] = -1;  // Empty frame
    }
    
    int faultCount = 0;
    int nextSlot = 0;  // FIFO pointer
    
    cout << "=== FIFO PAGE REPLACEMENT ===" << endl;
    cout << "Physical frames: " << FRAME_COUNT << endl;
    cout << "Reference string: ";
    for (int i = 0; i < 12; i++) {
        cout << REFERENCE_STRING[i] << " ";
    }
    cout << endl << endl;
    
    cout << "Step | Page | Frames | Fault" << endl;
    cout << "-----|------|--------|-------" << endl;
    
    for (int step = 0; step < 12; step++) {
        int page = REFERENCE_STRING[step];
        bool found = false;
        
        // Check if page is already in memory
        for (int i = 0; i < FRAME_COUNT; i++) {
            if (frames[i] == page) {
                found = true;
                break;
            }
        }
        
        if (!found) {
            // Page fault - replace oldest page (FIFO)
            frames[nextSlot] = page;
            nextSlot = (nextSlot + 1) % FRAME_COUNT;
            faultCount++;
        }
        
        // Display current state
        cout << " " << (step + 1) << "  |  " << page << "   | ";
        for (int i = 0; i < FRAME_COUNT; i++) {
            if (frames[i] == -1) {
                cout << "- ";
            } else {
                cout << frames[i] << " ";
            }
        }
        cout << "|  " << (found ? "HIT" : "MISS") << endl;
    }
    
    cout << "\nTotal Page Faults: " << faultCount << " out of 12" << endl;
    cout << "Hit Ratio: " << ((12 - faultCount) * 100 / 12) << "%" << endl;
    
    return 0;
}
