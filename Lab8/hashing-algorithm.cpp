#include <iostream>

#define SIZE 11

class HashTable{
    int table[SIZE];
    bool occupied[SIZE];
public:
    HashTable(){
        for(int i = 0; i < SIZE; i++){
            table[i] = -1;
            occupied[i] = false;
        }
    }
    int hashFunction(int key){ 
        return key % SIZE; 
    }
    void insert(int key){
        int index = hashFunction(key);
        int startPos = index;
        while(occupied[index]){
            index = (index + 1) % SIZE;
            if(index == startPos){
                std::cout << "Hash table full." << std::endl;
                return;
            }
        }
        table[index] = key;
        occupied[index] = true;
    }
    void search(int key){
        int index = hashFunction(key);
        int startPos = index;
        std::cout << "Searching for: " << key << "..." << std::endl;
        while(occupied[index]){
            if(table[index] == key){
                std::cout << "Key found at index: " << index << std::endl;
            }
            index = (index + 1) % SIZE;
            if(index == startPos){  // Traversed full table
                std::cout << "Key not found" << std::endl;
                break;
            }
        }
    }
    void printHashTable(){
        for(int i = 0; i < SIZE; i++){
            if(occupied[i]) std::cout << i << ": " << table[i] << "\n";
            else std::cout << i << ": empty\n";
        }
    }
};

int main(){
    HashTable hashTable;
    hashTable.insert(10);
    hashTable.insert(20); // Collision with 10
    hashTable.insert(5);
    hashTable.printHashTable();
    std::cout << "-----------" << std::endl;
    std::cout << "Searches:" << std::endl;
    hashTable.search(5);
    return 0;
}
