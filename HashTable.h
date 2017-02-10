#define TABLE_SIZE 20


template <typename V>
class Node {
public:
    Node(int key,V value) :
            key(key), value(value), next(NULL) {
    }

    int key;
    V value;
    Node *next;
};


template <typename V>
class HashMap {
public:
    HashMap() {
        table = new Node<V> *[TABLE_SIZE]();
        lastInsertKey = -1;
    }

    ~HashMap() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            Node<V> *entry = table[i];
            Node<V> *prev = nullptr;
            while (entry != NULL) {
                prev = entry;
                entry = entry->next;
                delete prev;
            }
            table[i] = NULL;
        }
        delete [] table;
    }

    V search(int key) {
        int hashValue = hashFunc(key);
        Node<V> *entry = table[hashValue];

        while (entry != NULL) {
            if (entry->key == key) {
                return entry->value;
            }
            entry = entry->next;
        }
        return nullptr;
    }


    int search(V value) {
        Node<V> *entry = nullptr;

        for(int i = 0;i<TABLE_SIZE;i++) {
            entry = table[i];
            while (entry != NULL) {
                if (entry->value->name == value->name) {
                    return entry->key;
                }
                entry = entry->next;
            }
        }


        return -1;
    }

    int insert(V value) {
        int key = ++lastInsertKey;
        int hashValue = hashFunc(key);
        Node<V> *prev = NULL;
        Node<V> *entry = table[hashValue];

        while (entry != NULL && entry->key != key) {
            prev = entry;
            entry = entry->next;
        }

        if (entry == NULL) {
            entry = new Node<V>(key, value);
            if (prev == NULL) {
                table[hashValue] = entry;
            } else {
                prev->next = entry;
            }
        } else {
            entry->value = value;
        }
        return key;
    }

    void print() {
        Node<V> *entry = nullptr;
        for(int i = 0;i<TABLE_SIZE;i++) {
            entry = table[i];
            while (entry != NULL) {
                std::cout<<entry->value;
                entry = entry->next;
            }
        }

    }


private:
    Node<V> **table;
    int lastInsertKey;
    int hashFunc(int key) {
        return key % TABLE_SIZE;
    }
};