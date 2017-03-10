#pragma once

#define TABLE_SIZE 20


template<typename K, typename V>
class Node {
public:
    Node(K key, V &value) :
            key(key), value(value), next(NULL) {
    }

    K key;
    V value;
    Node *next;
};


template<typename K, typename V>
class HashMap {
public:
    HashMap() {
        table = new Node<K, V> *[TABLE_SIZE]();
    }

    ~HashMap() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            Node<K, V> *entry = table[i];
            Node<K, V> *prev = nullptr;
            while (entry != NULL) {
                prev = entry;
                entry = entry->next;
                delete prev;
            }
            table[i] = NULL;
        }
        delete[] table;
    }

    bool get(K &key, V &value) {
        int hashValue = hashFunc(key);
        Node<K, V> *entry = table[hashValue];

        while (entry != NULL) {
            if (entry->key == key) {
                value = entry->value;
                return true;
            }
            entry = entry->next;
        }
        return false;
    }


    void insert(K &key, V &value) {
        int hashValue = hashFunc(key);
        Node<K, V> *prev = NULL;
        Node<K, V> *entry = table[hashValue];

        while (entry != NULL && entry->key != key) {
            prev = entry;
            entry = entry->next;
        }

        if (entry == NULL) {
            entry = new Node<K, V>(key, value);
            if (prev == NULL) {
                table[hashValue] = entry;
            } else {
                prev->next = entry;
            }
        } else {
            entry->value = value;
        }
    }

    void print() {
        Node<K, V> *entry = nullptr;
        for (int i = 0; i < TABLE_SIZE; i++) {
            entry = table[i];
            while (entry != NULL) {
                std::cout << entry->value.id << "\t" << entry->value << "\n";
                entry = entry->next;
            }
        }

    }


private:
    Node<K, V> **table;

    int hashFunc(K key) {
        //return key % TABLE_SIZE;
        return 2;
    }
};