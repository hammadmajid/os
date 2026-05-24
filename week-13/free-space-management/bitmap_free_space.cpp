// g++ -std=c++17 bitmap_free_space.cpp -o bitmap_free_space

#include <iostream>
using namespace std;

int main() {
    const int DISK_BLOCKS = 32;
    int bitmap[DISK_BLOCKS / 8 + 1];  // Using byte array as bitmap
    
    // Initialize bitmap (0 = free, 1 = used)
    for (int i = 0; i < DISK_BLOCKS / 8 + 1; i++) {
        bitmap[i] = 0;
    }
    
    // Helper to set bit
    auto setBit = [&](int block) {
        int byteIndex = block / 8;
        int bitIndex = block % 8;
        bitmap[byteIndex] |= (1 << bitIndex);
    };
    
    // Helper to check bit
    auto getBit = [&](int block) {
        int byteIndex = block / 8;
        int bitIndex = block % 8;
        return (bitmap[byteIndex] >> bitIndex) & 1;
    };
    
    cout << "=== BITMAP FREE SPACE MANAGEMENT ===" << endl;
    cout << "Total disk blocks: " << DISK_BLOCKS << endl << endl;
    
    // Mark some blocks as used
    cout << "Marking blocks as used..." << endl;
    int usedBlocks[] = {0, 1, 2, 5, 6, 10, 15};
    for (int block : usedBlocks) {
        setBit(block);
    }
    cout << "Marked blocks: ";
    for (int block : usedBlocks) cout << block << " ";
    cout << endl << endl;
    
    // Display bitmap
    cout << "Bitmap visualization (1=used, 0=free):" << endl;
    for (int i = 0; i < DISK_BLOCKS; i++) {
        cout << getBit(i);
        if ((i + 1) % 8 == 0) cout << " ";
    }
    cout << endl << endl;
    
    // Find free blocks
    cout << "Finding free blocks..." << endl;
    cout << "Free blocks: ";
    int freeCount = 0;
    for (int i = 0; i < DISK_BLOCKS; i++) {
        if (!getBit(i)) {
            cout << i << " ";
            freeCount++;
        }
    }
    cout << endl;
    cout << "Total free blocks: " << freeCount << " out of " << DISK_BLOCKS << endl;
    
    // Allocate new blocks
    cout << "\nAllocating 5 new blocks..." << endl;
    int allocated = 0;
    for (int i = 0; i < DISK_BLOCKS && allocated < 5; i++) {
        if (!getBit(i)) {
            setBit(i);
            cout << "Allocated block " << i << endl;
            allocated++;
        }
    }
    
    cout << "\nUpdated free blocks: ";
    freeCount = 0;
    for (int i = 0; i < DISK_BLOCKS; i++) {
        if (!getBit(i)) {
            freeCount++;
        }
    }
    cout << freeCount << " out of " << DISK_BLOCKS << endl;
    
    return 0;
}
