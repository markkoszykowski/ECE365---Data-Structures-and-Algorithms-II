/*
        Mark Koszykowski
        ECE365 - DSA II
        Programming Assignment 1
*/

#include "hash.h"
#include <iostream>

using namespace std;

hashTable::hashTable(int size): capacity(getPrime(size)), filled(0), data(capacity) {}

int hashTable::insert(const string &key, void *pv) {
        int val = findPos(key);

        if(val == -1) {
                val = hash(key);

                while(data[val].isOccupied) {
                        if(data[val].key == key) {
                                break;
                        }
                        ++val %= capacity;
                }

                data[val].key = key;
                data[val].isOccupied = true;
                data[val].isDeleted = false;
                data[val].pv = pv;
                
                if((++filled) * 2 > capacity) {
                        if(!rehash()) {
                                return 2;
                        }
                }
                return 0;
        }
        else {
                data[val].pv = pv;
                return 1;
        }
}

bool hashTable::contains(const string &key) {
        return (findPos(key) != -1);
}

void *hashTable::getPointer(const string &key, bool *b) {
        int val = findPos(key);

        if(val != -1) {
                *b = true;
                return data[val].pv;
        }
        else {
                *b = false;
                return nullptr;
        }
}

int hashTable::setPointer(const string &key, void *pv) {
        int val = findPos(key);

        if(val != -1) {
                data[val].pv = pv;
                return 0;
        }
        else {
                return 1;
        }
}

bool hashTable::remove(const string &key) {
        int val = findPos(key);

        if(val != -1) {
                data[val].isDeleted = true;
                return true;
        }
        else {
                return false;
        }
}


// Source: https://softwareengineering.stackexchange.com/questions/49550/which-hashing-algorithm-is-best-for-uniqueness-and-speed
// Chose algorithm with lowest times and collisions
int hashTable::hash(const string &key) {
        unsigned int hash = 0;
        unsigned int len = key.length();

        for(int i = 0; i < len; i++) {
                hash = key[i] + (hash << 6) + (hash << 16) - hash;
        }

        return hash % capacity;
}

int hashTable::findPos(const string &key) {
        int val = hash(key);

        while(data[val].isOccupied) {
                if(data[val].key == key) {
                        if(data[val].isDeleted) {
                                return -1;
                        }
                        else {
                                return val;
                        }
                }

                ++val %= capacity;
        }

        return -1;
}

bool hashTable::rehash() {
        vector<hashItem> old = data;

        data.clear();
        capacity = getPrime(capacity);
        data.resize(capacity);
        if(data.size() != capacity) {
                return false;
        }

        filled = 0;
        for(int i = 0; i < old.size(); i++) {
                hashItem oldItem = old[i];
                if(old[i].isOccupied && !(old[i].isDeleted)) {
                        insert(oldItem.key, oldItem.pv);
                }
        }

        return true;
}

unsigned int hashTable::getPrime(int size) {
        unsigned int primes[] = {100003, 200003, 400009, 800011, 1600033, 3200003, 6400013};
        unsigned int len = (sizeof(primes) / sizeof(int));

        for(int i = 0; i < len; i++) {
                if(primes[i] > (2 * size)) {
                        return primes[i];
                }
        }

        return primes[len - 1];
}
