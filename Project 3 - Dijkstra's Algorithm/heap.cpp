/*
        Mark Koszykowski
        ECE365 - DSA II
        Programming Assignment 3
*/

#include "heap.h"
#include <iostream>

using namespace std;

heap::heap(int cap) {
        capacity = cap;
        size = 0;
        data.resize(capacity + 1);
        myHash = new hashTable(capacity * 2);
}

int heap::insert(const string &id, int key, void *pv) {
        if(size >= capacity) {
                return 1;
        }
        else if(myHash->contains(id)) {
                return 2;
        }
        else {
                size += 1;
                data[size].id = id;
                data[size].key = key;
                data[size].ptr = pv;
                myHash->insert(id, &data[size]);
                percolateUp(size);

                return 0;
        }
}

int heap::setKey(const string &id, int key) {
        bool b;
        node *temp = static_cast<node *>(myHash->getPointer(id, &b));
        if(b == false) {
                return 1;
        }
        else {
                int pos, oldKey;

                oldKey = temp->key;
                temp->key = key;
                pos = findPos(temp);

                if(oldKey > key) {
                        percolateUp(pos);
                }
                else if(oldKey < key) {
                        percolateDown(pos);
                }
                return 0;
        }
}

int heap::deleteMin(string *pId, int *pKey, void *ppData) {
        if(size == 0) {
                return 1;
        }
        else {
                if(pId) {
                        *pId = data[1].id;
                }
                if(pKey) {
                        *pKey = data[1].key;
                }
                if(ppData) {
                        *(static_cast<void **>(ppData)) = data[1].ptr;
                }
                myHash->remove(data[1].id);
                data[1] = data[size];
                size -= 1;
                percolateDown(1);
                return 0;
        }
}

int heap::remove(const string &id, int *pKey, void *ppData) {
        bool b;
        node *temp = static_cast<node *>(myHash->getPointer(id, &b));
        if(b == false) {
                return 1;
        }
        else {
                int pos, oldKey;

                if(pKey) {
                        *pKey = temp->key;
                }
                if(ppData) {
                        *(static_cast<void **>(ppData)) = temp->ptr;
                }
                
                myHash->remove(id);
                oldKey = temp->key;
                *temp = data[size];
                size -= 1;
                pos = findPos(temp);
                
                if(oldKey > temp->key) {
                        percolateUp(pos);
                }
                else if(oldKey < temp->key) {
                        percolateDown(pos);
                }
                return 0;
        }
}

void heap::percolateUp(int pos) {
        node inserted = data[pos];
        while(pos > 1) {
                if(inserted.key < data[pos/2].key) {
                        data[pos] = data[pos/2];
                        myHash->setPointer(data[pos].id, &data[pos]);
                        pos /= 2;
                }
                else {
                        break;
                }
        }
        data[pos] = inserted;
        myHash->setPointer(data[pos].id, &data[pos]);
}

void heap::percolateDown(int pos) {
        int child;
        node removed = data[pos];
        while((child = pos * 2) <= size) {
                if(child < size && data[child].key > data[child + 1].key) {
                        child += 1;
                }
                if(removed.key > data[child].key) {
                        data[pos] = data[child];
                        myHash->setPointer(data[pos].id, &data[pos]);
                        pos = child;
                }
                else {
                        break;
                }
        }
        data[pos] = removed;
        myHash->setPointer(data[pos].id, &data[pos]);
}

int heap::findPos(node *ptr) {
        return (ptr - &data[0]);
}
