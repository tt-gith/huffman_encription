//--- 2022-2023 Fall Semester Data Structure Assignment 2 ---//
//--------------------------//
//---Name & Surname: İbrahim Taha Tüzgen
//---Student Number: 150210717
//--------------------------//

//-------------Do Not Add New Libraries-------------//
//-------------All Libraries Needed Were Given-------------//
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string.h>
#include <bits/stdc++.h>

#include "huffman.h"
#include "structs.h"

using namespace std;

//-------------Complete The Functions Below-------------//

//-----------------------------------------------------//
//-----------Reads the key from text file--------------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::readKey(const char *argv)
{
    ifstream readKeyFile;
    readKeyFile.open(argv);

    if (readKeyFile.is_open())
    {
        while (!readKeyFile.eof())
        {
            readKeyFile >> key;
        }
    }
    readKeyFile.close();
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//---------Sorts the key in an alpabetic order---------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::sortKey()
{
    sortedKey = key;
    sort(sortedKey.begin(), sortedKey.end());
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//-------Finds the frequency of the characters---------//
//-----------------------------------------------------//
void Huffman::findFrequency()
{
    // DO NOT CHANGE THIS
    sortKey();
    // DO NOT CHANGE THIS
    int i = 0;                             // this variable is used for counting the frequency of an element
    for (int q = 0; sortedKey[q + 1]; q++) // this loop is executed until the end of the sorted key string.
    {
        Node *newNode = new Node();                   // every different char in the key will be stored in a new node in the huffman tree, such nodes are created here.
        newNode->token.symbol = sortedKey[q];         // the symbol of the new token is assigned from the sorted key.
        for (; sortedKey[q + 1] == sortedKey[q]; q++) // this loop increases the index until find a new element in the sorted key.
        {
            i++; // i is also increased to find the frequency of the current character.
        }
        i++;
        newNode->token.val = i; // frequency is stored in the value property of the token.
        queue.enque(newNode);   // after finishing the creation of the node, it is pushed to the queue to be used.
        i = 0;                  // to be used for a new node the frequency of a node is set as 0;
    }
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//----------------Creates Huffman Tree-----------------//
//-----------------------------------------------------//
void Huffman::createHuffmanTree()
{
    findFrequency(); // firstly find frequency function is executed because it creates the queue which is used for creating the huffman tree.

    while (queue.head->next != NULL) // until the queue has only 1 node, which is the root of the huffman tree.
    {
        Node *nLeft = queue.dequeue();
        Node *nRight = queue.dequeue();                           // the first 2 items in the queue is taken.
        Node *parentNode = huffmanTree.mergeNodes(nLeft, nRight); // these two nodes are merged,
        queue.enque(parentNode);                                  // the merged node is added to the queue to be merged with another node again.
    }
    huffmanTree.root = queue.head; // the last node in the queue is assigned as a root to the huffman tree.
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//---------------Prints the Huffman Tree---------------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::printHuffmanTree()
{
    huffmanTree.printTree(huffmanTree.root, 0);
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//-------------Finds and returns the binary------------//
//----------------value to given character-------------//
//-----------------------------------------------------//
string Huffman::getTokenBinary(char tokenChar, Node *traverse, string tokenBinary)
{
    if (traverse->token.symbol.length() != 1) // if the token symbol of the node is not 1-char string, this conditional checks if it is a leaf in the tree.
    {                                         // if the node traverse is a leaf it means that the searched symbol is found.
        if (traverse->right->token.symbol.find(tokenChar) != std::string::npos)
        {
            tokenBinary = getTokenBinary(tokenChar, traverse->right, tokenBinary + "1"); // the token binary will take a "0", and it will continue to search the given character in the left subtree.
        }
        else
        {
            tokenBinary = getTokenBinary(tokenChar, traverse->left, tokenBinary + "0");
        }
    }
    return tokenBinary; // if we reached a leaf of the tree we find the given char and should start to return the binary value
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//--------------Encodes the given password-------------//
//-----------------------------------------------------//
void Huffman::encodePassword(string password)
{
    encodedBinaryPassword = "";               // encoded binary password is started as an empty string and it will be filled in this function.
    encodedValPassword = "";                  // encoded binary password is started as an empty string and it will be filled in this function.
    for (int i = 0; password[i] != '\0'; i++) // until the password is finish every character in the password will be encoded.
    {
        encodedValPassword = encodedValPassword + (char)(getTokenBinary(password[i], huffmanTree.root, "").length() + '0'); // the length of the binary value is added to the encodedValPassword as a char.
        encodedBinaryPassword = encodedBinaryPassword + getTokenBinary(password[i], huffmanTree.root, "");                  // the binary value is added to the encodedBinaryPassword.
    }
    return;
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//-------------Prints the encoded password-------------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::printEncodedPassword()
{
    cout << "Encoded Password Binary: " << encodedBinaryPassword << endl;
    cout << "Encoded Password Value: " << encodedValPassword << endl;
};

//-----------------------------------------------------//
//--------------Decodes the given password-------------//
//-----------------------------------------------------//
void Huffman::decodePassword(string encodedBinaryPassword, string encodedValPassword)
{
    int charIndex = 0, binIndex = 0, length;
    Node *tempNode = huffmanTree.root;

    for (int valIndex = 0; encodedValPassword[valIndex]; valIndex++) // until the encoded password finish.
    {
        length = (encodedValPassword[valIndex] - 48); // the integer value of the val password is stored in the variable "val"
        while (charIndex < length)                    // val times executed
        {
            if (encodedBinaryPassword[binIndex + charIndex] == 48) // if the current binary is 0, go to the left subtree
            {
                tempNode = tempNode->left;
            }
            else // if it is 1 go to the right subtree
            {
                tempNode = tempNode->right;
            }
            charIndex++;
        }
        decodedPassword = decodedPassword + tempNode->token.symbol; // the symbol of the leaf is added to the decoded password.
        binIndex = binIndex + charIndex;                     // q is added to t because t should be in the beginning of the binary of the next character.
        charIndex = 0;
        tempNode = huffmanTree.root; // n is again goes to the root
    }
};

//-----------------------------------------------------//

//-----------------------------------------------------//
//---------------Decodes the given binary--------------//
//-----------------------------------------------------//
void Huffman::decodeToken(string encodedToken){
    // TODO
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//-------------Prints the decoded password-------------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::printDecodedPassword()
{
    cout << "Decoded Password: " << decodedPassword << endl;
};