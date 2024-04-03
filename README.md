# HW 3 Memory Management and Address


This program demonstrates memory management techniques and address translation using a page/frame table. It simulates a simple memory management system where logical addresses are translated into physical addresses and handles page faults by loading pages into memory when necessary.

# Features
Generates random logical addresses within the range of logical memory.
Translates logical addresses to physical addresses using a page/frame table.
Handles page faults by loading pages into physical memory when required.
Provides page numbers and offsets for translated addresses.

# How it works
To run the program, you simply need an online IDE or you can download the code from Git Hub and move it to your local MSVS application. As soon as you hit run, it will generate random logical addresses and find their physical address alongside their page number and offset. The page fault handler function ensures that things are working as expected, and if not, then it will load the page fault number into the program and display the error output saying that the page fault occurred. After it does this, when there are no errors or issues, it will display your offset and page number using the last 2 digits for offset of the address and the page number for which it uses to get the physical address in hexadecimal form.
 






