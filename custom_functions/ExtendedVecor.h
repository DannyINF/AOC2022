#include <vector>
#include <iostream>

// Define a new class that derives from vector
template <typename T>
class ExtendedVector : public std::vector<T>
{
public:

    // Add a new pop() method that behaves like pop_back() but returns the value of the popped element
    T pop()
    {
        // Get a reference to the last element in the vector
        T& lastElement = this->back();

        // Remove the last element from the vector
        this->pop_back();

        // Return the value of the popped element
        return lastElement;
    }

    // Add a new pop_front() method that behaves like pop_front() but returns the value of the popped element
    T pop_front()
    {
        // Get a reference to the first element in the vector
        T firstElement = this->front();

        // Remove the first element from the vector
        this->erase(this->begin());

        // Return the value of the popped element
        return firstElement;
    }

    // Add a new push_front() method that allows you to insert an element at the beginning of the vector
    void push_front(const T& element)
    {
        // Insert the element at the beginning of the vector
        this->insert(this->begin(), element);
    }
};