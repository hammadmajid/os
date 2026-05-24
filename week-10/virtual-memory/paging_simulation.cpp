// g++ -std=c++17 paging_simulation.cpp -o paging_simulation

#include <iostream>
using namespace std;

int main() {
    const int PAGE_SIZE = 4;      // 4 bytes per page
    const int VIRTUAL_PAGES = 16; // 16 virtual pages
    const int PHYSICAL_FRAMES = 4; // 4 physical frames in RAM
    
    // Page table: maps virtual page to physical frame (-1 = not in RAM)
    int pageTable[VIRTUAL_PAGES];
    for (int i = 0; i < VIRTUAL_PAGES; i++) {
        pageTable[i] = -1;  // Initially, no pages in RAM
    }
    
    // Physical memory (4 frames * 4 bytes = 16 bytes total)
    int physicalMemory[PHYSICAL_FRAMES * PAGE_SIZE] = {0};
    
    cout << "=== PAGING SIMULATION ===" << endl;
    cout << "Virtual memory: " << VIRTUAL_PAGES << " pages × " << PAGE_SIZE << " bytes = " 
         << VIRTUAL_PAGES * PAGE_SIZE << " bytes" << endl;
    cout << "Physical memory: " << PHYSICAL_FRAMES << " frames × " << PAGE_SIZE << " bytes = " 
         << PHYSICAL_FRAMES * PAGE_SIZE << " bytes" << endl;
    
    cout << "\nSimulating page loading..." << endl;
    
    // Simulate loading pages into frames
    int nextFrame = 0;
    for (int vpn = 0; vpn < 6 && nextFrame < PHYSICAL_FRAMES; vpn++) {
        pageTable[vpn] = nextFrame;
        
        // Store page data in physical memory
        for (int offset = 0; offset < PAGE_SIZE; offset++) {
            physicalMemory[nextFrame * PAGE_SIZE + offset] = vpn * 100 + offset;
        }
        
        cout << "Page " << vpn << " -> Frame " << nextFrame << " [Data: ";
        for (int offset = 0; offset < PAGE_SIZE; offset++) {
            cout << physicalMemory[nextFrame * PAGE_SIZE + offset];
            if (offset < PAGE_SIZE - 1) cout << ", ";
        }
        cout << "]" << endl;
        nextFrame++;
    }
    
    cout << "\nPage Table:" << endl;
    cout << "Virtual Page | Physical Frame" << endl;
    for (int i = 0; i < VIRTUAL_PAGES; i++) {
        if (pageTable[i] != -1) {
            cout << "      " << i << "      |       " << pageTable[i] << endl;
        }
    }
    
    cout << "\nAddress Translation Example:" << endl;
    int virtualAddress = 18;  // Byte address in virtual memory
    int vpn = virtualAddress / PAGE_SIZE;  // Virtual page number
    int offset = virtualAddress % PAGE_SIZE;  // Offset within page
    
    cout << "Virtual address: " << virtualAddress << endl;
    cout << "  VPN: " << vpn << ", Offset: " << offset << endl;
    
    if (pageTable[vpn] != -1) {
        int physicalAddress = pageTable[vpn] * PAGE_SIZE + offset;
        cout << "  -> Physical Frame: " << pageTable[vpn] << endl;
        cout << "  -> Physical address: " << physicalAddress << endl;
        cout << "  -> Data at address: " << physicalMemory[physicalAddress] << endl;
    } else {
        cout << "  -> Page fault! (page not in RAM)" << endl;
    }
    
    return 0;
}
