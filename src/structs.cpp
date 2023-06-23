//--- 2022-2023 Fall Semester Data Structure Assignment 2 ---//
//--------------------------//
//---Name & Surname: İbrahim Taha Tüzgen
//---Student Number: 150210717
//--------------------------//

//-------------Do Not Add New Libraries-------------//
//-------------All Libraries Needed Were Given-------------//
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>

#include "structs.h"

using namespace std;

//-------------Complete The Functions Below-------------//

//-------------Initialize Priority Queue-------------//
PriorityQueue::PriorityQueue()
{
    head = 0;
};

//-------------Insert New Node To Priority Queue-------------//
void PriorityQueue::enque(Node *newnode)
{
    if (head == 0) // If the queue is empty,
    {
        head = newnode;
        newnode->next = 0;
    }    // the head of the queue is the newnode.
    else // Otherwise,
    {
        if (newnode->token.val < head->token.val)
        {
            newnode->next = head;
            head = newnode;
            return;
        }
        Node *curr = head; // a new node is created to be used to travel across the queue
        Node *prev = curr;
        while (curr->token.val <= newnode->token.val)
        {
            prev = curr;
            if(curr->next)
                curr = curr->next;
            else{
                curr->next = newnode;
                return;
            }
        }
        if (head->next)
            prev->next = newnode;
        if (!head->next && !curr)
        {
            head->next = newnode;
        }
        else
        {
            newnode->next = curr;
        }
    }
};

//-------------Remove Node From Priority Queue-------------//
Node *PriorityQueue::dequeue()
{
    Node *prevHead = head; // this is a temp to keep the information about the head of the queue to be returned to this function.
    if (head != 0)
        head = head->next; // the new head will be the second node in the queue.
    prevHead->next = 0;    // next of the previous head should be null to work properly.
    return prevHead;
};

//-------------Initialize Tree-------------//
Tree::Tree()
{
    root = 0;
};

//-------------Delete Tree Nodes From Memory-------------//
Tree::~Tree(){
    // TODO
};

//-------------Delete Tree From Memory-------------//
void Tree::deleteTree(Node *node)
{
    //-------------This Function Is Not Necessary-------------//
    //-----------------Use It At Your Own Will----------------//
    return;
}

//-------------Merges Two Node Into One-------------//
Node *Tree::mergeNodes(Node *temp1, Node *temp2)
{
    Node *parent = new Node();                                        // a new node is created to be the merged node.
    parent->token.val = temp1->token.val + temp2->token.val;          // the value of the merged node has the value as the sum of the values of coming nodes.
    parent->token.symbol = temp1->token.symbol + temp2->token.symbol; // the symbol of the merged node has the symbol as the sum of the symbols of coming nodes.
    parent->left = temp1;
    parent->right = temp2; // coming nodes will be the children of the merged node.
    return parent;         // the merged node is returned.
};

void Tree::printTree(Node *traverse, int level)
{
    cout << level << "\t";
    for (int i = 0; i < level; i++)
        cout << "\t";

    cout << traverse->token.symbol << "(" << traverse->token.val << ")" << endl;

    if (traverse->left)
        printTree(traverse->left, level + 1);
    if (traverse->right)
        printTree(traverse->right, level + 1);
};