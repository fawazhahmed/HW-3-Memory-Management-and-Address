
#include <iostream>
#include <vector>
#include <iomanip>// For std::hex
#include <ctime>
#include <cstdlib>

const int PAGE_SIZE = 1024;  // Page size in bytes
const int FRAME_SIZE = 1024; // Frame size in bytes
const int NUM_PAGES = 16;    // Number of pages in logical memory
const int NUM_FRAMES = 8;    // Number of frames in physical memory

// Function to generate a random logical address
int generate_logical_address() {
    return rand() % (NUM_PAGES * PAGE_SIZE);// Generates a random logical address within the range of logical memory
}


//handles page faults that may occur
void handle_page_fault(int page_num, std::vector<int>& page_frame_table, std::vector<bool>& physical_memory) {
    for (int i = 0; i < NUM_FRAMES; ++i) {
        if (!physical_memory[i]) { //is frame empty?
            page_frame_table[page_num] = i; //if so, put that into frame
            physical_memory[i] = true; //set new frame to true
            std::cout << "Page fault occurred. Loaded page " << std::hex << std::uppercase << page_num << " into frame " << i << std::endl << std::endl;
            return;
        }
    }
    std::cerr << "Error: No available frames in memory. Unable to load page " << std::hex << std::uppercase << page_num << std::endl << std::endl;
}


//function to get physical address from logical
int translate_address(int logical_address, std::vector<int>& page_frame_table, std::vector<bool>& physical_memory) {
    int page_num = logical_address / PAGE_SIZE;
    int offset = logical_address % PAGE_SIZE; //calculations used in the example

    if (page_num >= NUM_PAGES) { //checks for valid page
        std::cerr << "Error: Invalid page number: " << std::hex << std::uppercase << page_num << std::endl << std::endl;
        return -1; // Return -1 for error
    }

    int frame_number = page_frame_table[page_num]; //get frame 
    if (frame_number == -1) { //if not mapped
        handle_page_fault(page_num, page_frame_table, physical_memory); //send to page fault function
        frame_number = page_frame_table[page_num]; //after page fault, get number
        if (frame_number == -1) { //if it wasn't loaded at all
            std::cerr << "Error: Unable to load page " << std::hex << std::uppercase << page_num << " into memory" << std::endl << std::endl;
            return -1; // Return -1 for error
        }
    }

    int physical_address = frame_number * FRAME_SIZE + offset;

    return physical_address; //get and return physical address
}

int main() {
    srand(time(nullptr)); // Seed random number generator with current time

    std::vector<int> page_frame_table(NUM_PAGES, -1);
    std::vector<bool> physical_memory(NUM_FRAMES, false); //all frames are empty and unmapped initially

    for (int i = 0; i < 10; ++i) {
        int logical_address = generate_logical_address();
        int physical_address = translate_address(logical_address, page_frame_table, physical_memory); //generate and send logical address to be physical


        if (physical_address != -1) { //if it was sucsessful
            int pageNumber = logical_address / PAGE_SIZE; // Calculates the page number from the logical address
            int offset = logical_address % PAGE_SIZE; // Calculates the offset within the page from the logical address
            std::cout << "Logical Address: 0x" << std::hex << logical_address << " => Physical Address: 0x" << physical_address // Prints the logical and physical addresses in hexadecimal format
                << " => Page number: 0x" << std::setw(2) << std::setfill('0') << pageNumber
                << ", Offset: 0x" << std::setw(2) << std::setfill('0') << (offset % 0x100) << std::endl; //print in hexadecimal format and get last 2 digits for offest and page number
        }
    }

    return 0;
}
