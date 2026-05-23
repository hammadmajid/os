// g++ -std=c++17 linked_free_space.cpp -o linked_free_space

#include <iostream>
using namespace std;

struct FreeBlock {
    int blockNumber;
    int nextBlock;  // -1 if last
};

int main() {
    const int DISK_BLOCKS = 32;
    // Note: In a real system, this would be a linked list of blocks on disk
    // Here we simulate it with an array
    // Assume blocks 3, 4, 7, 8, 9, 11, 16-31 are free
    int freeBlocks[] = {3, 4, 7, 8, 9, 11, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31};
    int freeBlockCount = 22;
    
    cout << "=== LINKED-LIST FREE SPACE MANAGEMENT ===" << endl;
    cout << "Total disk blocks: " << DISK_BLOCKS << endl;
    cout << "Free blocks: " << freeBlockCount << endl << endl;
    
    // Build linked list
    cout << "Building free block linked list..." << endl;
    int freeListHead = freeBlocks[0];
    
    for (int i = 0; i < freeBlockCount; i++) {
        int block = freeBlocks[i];
        if (i < freeBlockCount - 1) {
            cout << "Block " << block << " -> Block " << freeBlocks[i + 1] << endl;
        } else {
            cout << "Block " << block << " -> END" << endl;
        }
    }
    
    cout << "\nFree list head: " << freeListHead << endl;
    
    // Allocate blocks
    cout << "\nAllocating 3 blocks..." << endl;
    int currentBlock = freeListHead;
    
    for (int i = 0; i < 3; i++) {
        if (currentBlock >= 0 && currentBlock < DISK_BLOCKS) {
            cout << "Allocated block " << currentBlock << endl;
            // Find next in list (simplified)
            for (int j = 0; j < freeBlockCount; j++) {
                if (freeBlocks[j] == currentBlock) {
                    if (j + 1 < freeBlockCount) {
                        currentBlock = freeBlocks[j + 1];
                    }
                    break;
                }
            }
        }
    }
    
    cout << "\nNew free list head: " << currentBlock << endl;
    
    cout << "\nLinked-list characteristics:" << endl;
    cout << "- Simple linear traversal of free blocks" << endl;
    cout << "- Efficient allocation (O(1) for first free block)" << endl;
    cout << "- Requires traversal for fragmentation analysis" << endl;
    
    return 0;
}
