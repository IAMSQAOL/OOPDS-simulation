#ifndef QUEUE_H
#define QUEUE_H
#include "SHIP.H"
#include "NODE.H"
class Queue{
    private:
        Node* front;
        Node* rear;
    public:
        Queue();

        ~Queue();

        Queue(const Queue& other);

        Queue& operator=(const Queue& other);

        Queue(Queue&& other) noexcept;

        Queue& operator=(Queue&& other) noexcept;
        void enqueue(Ship* shipPtr);

        void dequeue(Field& field,LinkedList& ships);

        bool WaitTeam(char teamName);

    protected:
        void clear();
};


#endif