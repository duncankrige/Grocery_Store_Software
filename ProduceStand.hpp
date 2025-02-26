// ProduceStand.hpp

#ifndef PRODUCE_STAND_HPP
#define PRODUCE_STAND_HPP
#include "Produce.hpp"                                  // This includes the Produce class provided to us in canvas
#include <iostream>
using namespace std;

class ProduceStand {

    public:
                                                                        // This is where our default constructor will go we need to initializes an array with space for 5 items 
        ProduceStand();                                                 // Default constructor
        ProduceStand(istream& inStream);                                // Constructor to initialize from input - this is our input stream constructor it takes an istream and reads in Produce items line by line.  
        ~ProduceStand();                                                // Destructor to free memory 
        bool sell(const string& name, int quantity);                    // Bool - gives us a true or false boolean, true the item was found and enough. Flase items wasnt found or not enough.  The sell function allows us to sell a specific quantity of the produce item based on its name.The string represents the produce items name and int the number you want to sell. 
        int size() const;                                               // Declaration of the size method
        void clear();                                                   // helps us clear the array without deleting it. 
        int emptySpots() const;                                         // Returns the number of empty spots in the stand
        void addProduce(const std::string& name, float cost, int quantity);  // Adds a new Produce item
        //Produce* find(const string& name);                              // Declaration of the find method


        ProduceStand& operator=(const ProduceStand& other);             // Assignment operator
        ProduceStand& operator+=(const Produce& item);                  // Overloading the += Operator for adding produce or increasing quatity of exsisting item.
        ProduceStand& operator+=(const ProduceStand& other);            // For another ProduceStand
        ProduceStand& operator-=(const Produce& item);                  // Overloading -= Operator for removing produce/ reducing the quatity if enough of the item is in stock 
        ProduceStand operator+(const ProduceStand& other) const;        // Declaration for operator+

        //friend ProduceStand operator+(const ProduceStand& stand1, const ProduceStand& stand2);
        friend std::ostream& operator<<(std::ostream& os, const ProduceStand& stand);               // Output stream operator
        friend std::istream& operator>>(std::istream& is, ProduceStand& stand);                     // Input stream operator


    private:
                                                                        // Rember only Private members will go here, like the array to store the Produce items
        Produce* produceItems;                                          // This is a pointer to an array of Produce objects
        int capacity;                                                   // We must make the total capacity of the array (how many items it can hold)
        int count;                                                      // We could also use count to find the current number of Produce items makes code a lot simpler
        void resizeArray();                                             // Declacing ARRAY
        int findProduceIndex(const string& name) const;                 // Finds the index of a Produce item by name
    };



#endif
