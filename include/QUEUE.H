/**********|**********|**********|
Program: QUEUE.H
Course: Object Oriented Programming and Data Structures
Trimester: 2430
Name: YEE SI SHUN , GOH CHUN YONG , CHEAH CHUN YONG , LOKE KAR HEI
ID: 241UC24157 , 241UC24158 , 241UC2417G , 241UC24168
Lecture Section: TC1L
Tutorial Section: TT4L
Email: yee.si.shun@gstudent.mmu.edu.my , goh.chun.yong@student.mmu.edu.my , cheach.chun.yong@student.mmu.edu.my , loke.kar.hei@student.mmu.edu.my
Phone: 011-63303212 , 011-10758049 , 011-59252689 , 017-2900377
**********|**********|**********/

#ifndef QUEUE_H
#define QUEUE_H
#include "../include/SHIP.H"
#include "../include/NODE.H"
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