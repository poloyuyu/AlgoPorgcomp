#include<iostream>
#include<math.h>
#include<string>

using namespace std;
#define tElem int
#define tElemNull -1
#define CAPACITY 1000

class HashTable {
  private:
    unsigned int count;
    struct Ranura {
      string key;
      tElem value;
    };
    class LinkedList {
      private:
        struct Node {
          Ranura ranura;
          Node* next;
          Node(Ranura a, Node* b) : ranura(a), next(b) {}
        };
        Node* head = nullptr; Node* tail = nullptr;
      public:
        void Insert(string key, tElem value) 
        {
          Node* newNode = new Node(Ranura{key, value}, nullptr);
          if(head == nullptr) {
            head = newNode;
            tail = newNode;
            return;
          }
          tail->next = newNode;
          tail = newNode;
        }
        Ranura* Search(string key) 
        {
          Node* current = head;
          for(int k = 0; current != nullptr; k++) {
            if(current->ranura.key == key) return &current->ranura;
            current = current->next;
          }
          return nullptr;
        }
        void Free() 
        {
          Node* current = head;
          while(current != nullptr) {
            Node* aux = current->next;
            delete(current);
            current = aux;
          }
        }
    };
    LinkedList table[CAPACITY];
  public:
    HashTable() 
      : count(0) {}
    ~HashTable() {}

    int Hash(string key) 
    {
      unsigned long long index = 0;
      int len = key.size();
      for(int k = 0; k < len; k++) {
        index += key[k];
      }
      return index%CAPACITY;
    }
    void Insert(string key, tElem value) 
    {
      int index = Hash(key);
      if(table[index].Search(key) != nullptr) {
        cout<<"ELEMENTO YA EXISTE"<<endl;
        return;
      }
      table[index].Insert(key ,value);
    }
    tElem Search(string key)
    {
      int index = Hash(key);
      Ranura* ranura = table[index].Search(key);
      if(ranura == nullptr) {
        cout<<"NO EXISTE"<<endl;
        return tElemNull;
      }
      return ranura->value;
    }
    void FreeHashTable() {
      for (int k = 0; k < CAPACITY; k++) {
        table[k].Free();
      }
    }
};

int main()
{
  HashTable table;
  table.Insert("papas_fritas", 2400);
  table.Insert("helado", 1000);
  table.Insert("arroz", 3000);
  cout<<"papas_fritas"<<" "<<table.Search("papas_fritas")<<endl;
  cout<<"cazuela"<<" "<<table.Search("cazuela")<<endl;
  table.Insert("papas_fritas", 2400);
  table.FreeHashTable();
  return 0;
}