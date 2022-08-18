#include "LinkedList.h"

bool LinkedList::isEmpty()
{
    return (head == NULL);
}

LinkedList::LinkedList()
{
    head = NULL;
    tail = NULL;
}
