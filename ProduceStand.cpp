//ProduceStand.cpp

#include "ProduceStand.hpp"
#include "Produce.hpp"

// Defualt constructor -----------------------------------------------------------------------------------------------------------------------------------

ProduceStand::ProduceStand()                                    // Defualt constructor - it is called whenever a ProduceStand object is created without specified input (for example ProduceStand stand;). It initializes a ProduceStand with an array that can hold up to 5 Produce items, with no items arev added initially.
    {
        capacity = 5;                                           // Initial capacity of 5 produce items 
        produceItems = new Produce[capacity];                   // This allocate memeory for the array of produce items with this size of the capacity we set for 5 items
        count = 0;                                              // No items added yet
    }


//Constructor that reads from an input stream -----------------------------------------------------------------------------------------------------------------------------

ProduceStand::ProduceStand(istream& inStream) : ProduceStand()   // Calls default constructor first - This makes sure capacity, produceItems, and count are already initialized(5, an empty array, and 0 respectively)
    {
        Produce temp;                                           //This is a temporary Produce object. We are using this to hold each Produce item as it’s read from the input stream before adding it to the produceItems array. 
        
        while (inStream >> temp)                                // while loop reades all the Produce items from the input stream into temp. The >> operator allows us to read directly into a Produce object from a stream. 
            {
               if (count >= capacity)                           // If count reaches capacity, we need to double the array’s size to make room for more items
                {
                    resizeArray();
                                            
                }

                produceItems[count++] = temp;                   // Add temp to produceItems and increase count                                                 
                                                                
            }
    }


//Destructor -----------------------------------------------------------------------------------------------------------------------------------

ProduceStand::~ProduceStand()                                   // This is called automatically when the ProduceStand object goes out of scope. We are using it to free up dynamic memory used by the ProduceStand object,  this will be preventing memory leaks.
    {
        delete[] produceItems;                                  //freeing up dynamilcally located memeory 
    } 


//Double the array SIZE -----------------------------------------------------------------------------------------------------------------------------------

void ProduceStand::resizeArray()                                // We need to declare resizeArray as a private member function in ProduceStand.hpp
    {
        int newCapacity = capacity * 2;                         // Double the current capacity.
        
        Produce* newArr = new Produce[newCapacity];             // This is creating a new array with the doubled capacity.The newArr Dynamically allocates a new array of Produce items with the new capacity.
        
            for (int i = 0; i < count; i++)                     // Essintial copying the existing items from the old array to the new array.
                {
                    newArr[i] = produceItems[i];         
                }
        
        delete[] produceItems;                                  // Frees up memory used by the old array, to avoid memory leaks.
        
        produceItems = newArr;                                  // Makes sure the class references the new array and capacity.
        capacity = newCapacity;
    }    

// size () -----------------------------------------------------------------------------------------------------------------------------------

int ProduceStand::size() const 
    {
        return count; 
    }

//Find Produce Items by Name -----------------------------------------------------------------------------------------------------------------------------------

int ProduceStand::findProduceIndex(const string& name) const 
    {
        for (int i = 0; i < count; i++)                         // Loop through the existing items up to count Because the current number of items in stock is equal to count.
            {
                if (produceItems[i].get_name() == name)         // Compare item names. For each item, it compares the name parameter with the name of the item at the current index using get_name()
                    {
                        return i;                               // Return the index if a match is found
                    }
            }
        return -1;                                              // Returns -1 if the Produce item is not found.
    }

 //Find() -----------------------------------------------------------------------------------------------------------------------------------


// addProduce -----------------------------------------------------------------------------------------------------------------------------------

void ProduceStand::addProduce(const std::string& name, float cost, int quantity) 
    {
        int index = findProduceIndex(name);                                 // Use findProduceIndex to check if the produce item already exists. I didnt do this initial and ran into problems on test5 

        if (index != -1) 
            {
                int currentQuantity = produceItems[index].get_quantity();   // If the item exists, increase its quantity
                produceItems[index].set_quantity(currentQuantity + quantity);
            } 
                else 
                {
                    if (count == capacity)                                  // Check if the array is full
                        {
                            resizeArray();                                  // Use the resizeArray method if array is full
                        }

                    produceItems[count] = Produce(name, cost, quantity);    // create an add the new Produce item

                    ++count;                                                // Increment the count
                }
    }

// Empty spots Method -----------------------------------------------------------------------------------------------------------------------------------

int ProduceStand::emptySpots() const                            
    {
        return capacity - count;                                // This works out total of capacity minus the items currently in the stand. Returns a INTEGER
    }

// clear -----------------------------------------------------------------------------------------------------------------------------------

void ProduceStand::clear()                                      // Resetting the produce stand -  removes all items without having to delete them making the stand empty.  
    {
        count = 0;                                              // Reset count to 0 making array emepty 
    }

// Sell Method -----------------------------------------------------------------------------------------------------------------------------------

bool ProduceStand::sell(const string& name, int quantity)       // Call the function from hpp
    {
        int index = findProduceIndex(name);                     // We use the findProduceIndex function to get the index of the item with the specified name. 

            if (index == -1)                                    // So if the item doesnt exsist or not found the method findProduceIndex returns -1.
                {                      
                    return false;                               // When the item isn't in stock in our stand return false. 
                }

            if (produceItems[index].get_quantity() < quantity)  // Check if enough stock is available of the produce. 
                { 
                    return false;                               // If there isn't enough stock to complete the order it return false. 
                }

        // Update the stock and sold count 
        produceItems[index].set_quantity(produceItems[index].get_quantity() - quantity); // If we have enough produce in stock, we decrease the item’s quantity by the requested quantity. 
        produceItems[index].set_sold(produceItems[index].get_sold() + quantity);         // We also need to increase its sold count by the same amount.
        
            return true;                                        // Return True if Sale was successful
    }    


// = Operator  -----------------------------------------------------------------------------------------------------------------------------------

ProduceStand& ProduceStand::operator=(const ProduceStand& other)   // Overload the assignment operator
    {
        if (this != &other)                                        // Check for self-assignment
        {  
            delete[] produceItems;                                 // Free existing memory

            capacity = other.capacity;                             // Copy capacity
            count = other.count;                                   // Copy current size
            produceItems = new Produce[capacity];                  // Allocate new array

            for (int i = 0; i < count; ++i)                        // Copy each Produce item
                {
                    produceItems[i] = other.produceItems[i];
                }
        }
        return *this;                                               // Return the current object
    }
    
// += Operator  -----------------------------------------------------------------------------------------------------------------------------------    
ProduceStand& ProduceStand::operator+=(const ProduceStand& other)           // Overload the += operator for another ProduceStand
    {
        for (int i = 0; i < other.size(); ++i)                              // Use the size() method defined earlier
            {
                if (count >= capacity)                                      // Ensure capacity before adding
                    {
                        resizeArray();                                      // Resize if needed
                    }
                *this += other.produceItems[i];                             // Add each Produce item
            }
        return *this;                                                       // Return updated ProduceStand
    }
ProduceStand& ProduceStand::operator+=(const Produce& item)                 // Overload the += operator for a single Produce item
    {
        if (count >= capacity)                                              // Ensure there is capacity before adding
            {
                resizeArray();                                              // Resize if needed
            }
        addProduce(item.get_name(), item.get_sold(), item.get_quantity());  // Add the Produce item
        return *this;                                                       // Return updated ProduceStand
    }

// -= Operator -----------------------------------------------------------------------------------------------------------------------------------

ProduceStand& ProduceStand::operator-=(const Produce& item)                                 // Overload the -= operator for a single Produce item
    {
        int index = findProduceIndex(item.get_name());                                      // Find the index of the item
        if (index != -1) 
            {
                int newQuantity = produceItems[index].get_quantity() - item.get_quantity(); // Decrement quantity
                if (newQuantity <= 0) 
                    {
                        produceItems[index].set_quantity(0);                                
                    } 
                        else 
                            {
                                produceItems[index].set_quantity(newQuantity);              // Update quantity
                            }
            }
        return *this;                                                                       // Return updated ProduceStand
    }

// + Operator  -----------------------------------------------------------------------------------------------------------------------------------

ProduceStand ProduceStand::operator+(const ProduceStand& other) const                       // Overload the + operator to combine two ProduceStands
    {
        ProduceStand result;                                                                // Create a new ProduceStand for the result
        result += *this;                                                                    // Add current ProduceStand
        result += other;                                                                    // Add other ProduceStand
        return result;                                                                      // Return combined ProduceStand
    }

// << Operator -----------------------------------------------------------------------------------------------------------------------------------

std::ostream& operator<<(std::ostream& os, const ProduceStand& stand)                       // Overload the << operator for output
    {
        for (int i = 0; i < stand.size(); ++i) 
            {
                os << stand.produceItems[i] << std::endl;                                   // Output each Produce item
            }
        return os;                                                                          // Return the output stream
    }

// >> Operator -----------------------------------------------------------------------------------------------------------------------------------

std::istream& operator>>(std::istream& is, ProduceStand& stand)                             // Overload the >> operator for input
    {
        std::string name;
        float cost;
        int quantity;

        while (is >> name >> cost >> quantity)                                              // Read from input stream and add Produce items
        {
            stand.addProduce(name, cost, quantity);                                         // Add each Produce item
        }
        return is;                                                                          // Return the input stream
    }







