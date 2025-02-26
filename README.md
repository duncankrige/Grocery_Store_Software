ProduceStand - C++ Linked List Project
Author: Duncan Krige


Description
ProduceStand is a C++ project that simulates a produce stand using a linked list to manage inventory. The project includes features for adding, removing, searching, and selling produce items while avoiding the use of the C++ Standard Template Library (STL).

Project Structure

/ProduceStand
│── ProduceStand.hpp       # Header file for the ProduceStand class
│── ProduceStand.cpp       # Implementation file for the ProduceStand class
│── ProduceNode.hpp        # Header file for linked list nodes
│── ProduceNode.cpp        # Implementation file for linked list nodes
│── main.cpp               # Main program to test the produce stand
│── README.md              # Project documentation
│── test_input.txt         # Sample input file for testing


Features
Implements a custom linked list to manage produce inventory
Supports adding, removing, searching, and selling produce items
Overloads various operators (+=, -=, =, <<, >>) for enhanced functionality
Uses dynamic memory allocation to efficiently manage items
Provides file I/O support for loading produce data


Getting Started

1. Compile the Code
Use a C++ compiler (like g++) to compile:

g++ -o ProduceStand main.cpp ProduceStand.cpp ProduceNode.cpp

2. Run the Program

./ProduceStand


Usage
Adding Produce: Add new produce items to the stand
Selling Produce: Sell produce and update inventory
Searching for Produce: Check if a specific item is available
Displaying Inventory: View all available produce items
Operator Overloading

Operator	Functionality
+=	Add a new produce item
-=	Remove a produce item
=	Assign one stand to another
<<	Display produce items
>>	Load produce items from input


Example Output

Welcome to Produce Stand!  
1. Add Produce  
2. Sell Produce  
3. Display Inventory  
4. Exit  
Enter choice: 1  
Enter produce name: Apples  
Enter quantity: 10  
Produce added successfully!  


License
This project is open-source and available under the MIT License.
