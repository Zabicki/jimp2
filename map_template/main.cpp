#include <iostream>

using std::string;
using std::endl;
using std::cout;

template<class Key, class Value>
class Node {
public:
    Key key;
    Value value;
    Node* next;
    Node() {
        next = NULL;
    }
};

template<class Key, class Value>
class map {
private:
    Node<Key, Value>* head;
public:
    map();
    ~map();
    Value & operator[](const Key & a) {
        Node<Key, Value> *w, *wp, *wn;
        wp = NULL;
        for (w = this->head; w != 0; w = w->next) {
            if (w->key == a) return w->value;
            wp = w;
        }
        wn = new Node<Key, Value>;
        wn->key = a;
        wn->next = NULL;
        if (wp == NULL) {
            head = wn;
        }
        else wp->next = wn;
        return wn->value;
    }
    
    void sortByKey() {
        Node<Key, Value>* tmp = head;
        Node<Key, Value>* tmp2 = head;
        while (tmp != NULL) {
            while (tmp2 != NULL) {
                tmp2 = tmp2->next;
            }

            tmp = tmp->next;
        }
    }
    class iterator {
        friend class map;
    private:
        //pointer points at current Node from map class
        Node<Key, Value>* pointer;
    public:
        bool operator!=(const iterator & it) {
            if (pointer != it.pointer) {
                return true;
            }
            return false;
        }

        iterator & operator++(void) {
            pointer = pointer->next;
            return *this;
        }

        Node<Key, Value>* operator->(void) {
            return pointer;
        }

        iterator& operator=(const iterator& it) {
            if (this == &it) {
                return *this;
            }
            this->pointer = it.pointer;
            return *this;
        }
    };
    iterator begin(void) {
        iterator it;
        it.pointer = head;
        return it;
}
    iterator end(void) {
        iterator it;
        it.pointer = NULL;
        return it;
    }
};
template <class Key, class Value>
map<Key, Value>::map() {
    head = NULL;
}

template <class Key, class Value>
map<Key, Value>::~map() {
    Node<Key, Value>* tmp = head;
    Node<Key, Value>* delTmp;
    while (tmp != NULL) {
    delTmp = tmp;
    tmp = tmp->next;
    delete delTmp;
    }
    head = NULL;
}



int main() {
    map<string, string> map1;
    map1["foo"] = "bar";
    map1["pies"] = "dog";
    map1["kot"] = "cat";
    for (map<string,string>::iterator it = map1.begin(); it != map1.end(); ++it) {
        cout << it->key << " " << it->value << endl;
    }
    return 0;
}
