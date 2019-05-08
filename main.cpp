//
//  main.cpp
//  BinaryTree
//
//  Created by Mahmoud Ezzat on 4/16/19.
//  Copyright © 2019 Mahmoud Ezzat. All rights reserved.
//
#include <stdio.h>
#include <iostream>
#include <queue>
#include <stack>
#include <string.h>
#include <stdio.h>
#include<fstream>
#include <string.h>
using namespace std;

struct Node {
    string key;
    struct Node* left;
    struct Node* right;
};

struct Node* newNode(string key) {
    struct Node* n = new Node;
    n->key = key;
    n->left = NULL;
    n->right = NULL;
    
    return n;
}


//lets make our string compare!!!
//if str1 > str2 ---------> return 1
//if str1 < str2 ---------> return -1
// if str1 == str2 -------> return 0
int stringcmp(string str1,string str2) {
    int size1 = 0;
    int size2 = 0;
    while (str1[size1] != '\0') size1++;
    while (str2[size2] != '\0') size2++;
    
    int i = 0;
    while (str1[i] != '\0' || str2[i] != '\0') {
        if (str1[i] > str2[i]) return 1;
        else if (str1[i] < str2[i]) return -1;
        
        if (i == size1-1 || i == size2-1) break;
        i++;
    }
    
    if (size1 < size2) return -1;
    else if (size1 > size2) return 1;
    
    return 0;
}

//recursive function to insert string values in the BST using stringcmp().
struct Node* insert(struct Node* node, string value) {
    if (node == NULL) return newNode(value);
    
    if (stringcmp(value, node->key) == -1) node->left = insert(node->left, value);
    else if (stringcmp(value,node->key) == 1) node->right = insert(node->right, value);
    
    return node;
}

//testing
void inorder(struct Node *node) {
    if (node == NULL) return;
    
    inorder(node->left);
    cout << node->key << endl;
    inorder(node->right);
}

//function to get the height recursively
//return an integer
//checked....
int getHeight(struct Node* node) {
    if (node == NULL) return 0;
    else {
        int left = getHeight(node->left);
        int right = getHeight(node->right);
        
        if (left > right) return(left+1);
        else return (right+1);
    }
}

//recusrive function to count the number of elements in the BST
//checked....
int countBinaryTree(struct Node* node) {
    int count = 1;
    if (node == NULL) return 0;
    else {
        count += countBinaryTree(node->left);
        count += countBinaryTree(node->right);
        return count;
    }
}

//function to get the words from the file and insert into the BST
//checked....
struct Node* insertWords(string filePath,struct Node* root) {
    ifstream myReadFile;
    myReadFile.open(filePath);
    string words[100000];
    string output;
    int i = 0;
    if (myReadFile.is_open()) {
        while (!myReadFile.eof()) {
            myReadFile >> output;
            words[i] = output;
            i++;
        }
    } else {
        //if file not existed the program will close.
        cout << "File not found" << endl;
        exit(1);
    }
    myReadFile.close();
    
    cout << "number of elements in the file is: " << i << endl;
    //inserting the words in the tree
    root = insert(root,words[0]);
    for (int j = 1; j < i; j++) insert(root,words[j]);
    
    return root;
}


struct Node* findMin(struct Node* node) {
    if(node == NULL) return NULL;
    while(node->left != NULL) node = node->left;
    return node;
}


struct Node* Getsuccessor(struct Node* root,struct Node* node) {
    
    struct Node* current = node;
    if(current == NULL) return NULL;
    if(current->right != NULL) {
        return findMin(current->right);
    } else {
        struct Node* successor = NULL;
        struct Node* ancestor = root;
        
        while(ancestor != current) {
            if (stringcmp(current->key, ancestor->key) == -1) {
                successor = ancestor;
                ancestor = ancestor->left;
            } else ancestor = ancestor->right;
        }
        return successor;
    }
}


//--------------------------------------------------------------------



struct Node* findMax(struct Node* node) {
    if(node == NULL) return NULL;
    while(node->right != NULL) node = node->right;
    return node;
}

//checked
struct Node* Getpredeccessor(struct Node* root,struct Node* node) {
    
    //struct Node* current = Find(root,data);
    struct Node* current = node;
    if(current == NULL) return NULL;
    if(current->left != NULL) {
        return findMax(current->left);
    } else {
        struct Node* successor = NULL;
        struct Node* ancestor = root;
        
        while(ancestor != current) {
            if (stringcmp(current->key, ancestor->key) == 1) {
                successor = ancestor;
                ancestor = ancestor->right;
            } else ancestor = ancestor->left;
        }
        return successor;
    }
}

//iterative searching the BST for the keyword
//if found return true
// if not found return false.
//checked....
void search(struct Node* node, string keyword) {
    struct Node* current = node;
    struct Node* previous = NULL;
    while (current != NULL) {
        if (stringcmp(keyword,current->key) == 0) {
            cout << keyword << " - CORRECT" << endl;
            return;
        } else if (stringcmp(keyword,current->key) == -1) {
            previous = current;
            current = current->left;
        }
        else if (stringcmp(keyword,current->key) == 1) {
            previous = current;
            current = current->right;
        }
    }
    
    //print current Node.
    
    struct Node* predeccessor = Getpredeccessor(node,previous);
    struct Node* successor = Getsuccessor(node,previous);
    
    cout << keyword << " - " << previous->key << ", " << successor->key << ", " << predeccessor->key << endl;
    
}

void spell_checking_system() {
    struct Node* root = NULL;
    string filePath = "/Users/mahmoudezzat/Desktop/asignment 3/EN-US-randomized.txt";
    
    //passing the File Path and the initialized node root
    root = insertWords(filePath,root);
    
    //printing the height of the tree by passing the updated root from insertWords();
    int height = getHeight(root);
    cout << "Height of the BST is: " << height << endl;
    
    //printing number of elements in the BST
    int num = countBinaryTree(root);
    cout << "number of elements in the BST is: " << num << endl;
    
    
    char str[100];
    cout << "Enter a sentence" << endl;
    gets(str);
    
    char* temp;
    temp = strtok(str, " ");
    while (temp != NULL) {
        
        search(root,temp);
        temp = strtok(NULL, " ");
    }
    
    
}

int main() {
    
    
    spell_checking_system();
    
    return 0;
}



























