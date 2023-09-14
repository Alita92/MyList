#include <iostream>


template <typename T>
class MyList
{
public:
    struct Node
    {
        T _data;
        Node* prev_node = nullptr;
        Node* next_node = nullptr;

        Node(T data) : _data(data)
        {};
    };

public:
    MyList()
    {
        _head = nullptr;
        _tail = nullptr;
        _size = 0;
    }

    void Push_front(T data)
    {
        Node* new_node = new Node(data);
        new_node->_data = data;

        if (_head == nullptr)
        {
            _head = new_node;
            _tail = new_node;
        }
        else
        {
            // 기존 헤드 포인터 존재 시 포인터 바꿔치기로 새로운 노드를 헤드로 올린다
            _head->prev_node = new_node;
            new_node->next_node = _head;
            _head = new_node;
        }

        ++_size;
    }

    void Push_back(T data)
    {
        MyList<T>::Node* new_node = new MyList<T>::Node(data);
        new_node->_data = data;

        if (_head == nullptr)
        {
            _head = new_node;
            _tail = new_node;
        }
        else
        {
            // 기존 테일 포인터 존재 시 포인터 바꿔치기로 새로운 노드를 헤드로 올린다
            _tail->next_node = new_node;
            new_node->prev_node = _tail;
            _tail = new_node;
        }

        ++_size;
    }

    void Insert(Node* node, T data)
    {
        Node* new_node = new MyList::Node(data);
        new_node->_data = data;

        if (_head == nullptr)
        {
            _head = new_node;
            _tail = new_node;
        }
        else
        {
            // 새로운 노드를 대상 노드의 다음 노드로 삽입한다
            new_node->prev_node = node;
            new_node->next_node = node->next_node;
            node->next_node = new_node;
        }

        ++_size;
    }


    Node* GetNode(int iter_count)
    {
        Node* iter = _head;

        for (int index = 0; index < iter_count; ++index)
        { 
            iter = iter->next_node;
        }

        return iter;
    }

    int Size()
    {
        return _size;
    }

private:
    Node* _head;
    Node* _tail;
    int _size;
};


class Test
{
public:
    int int_data;
    float float_data;
    char char_data;

    Test(int a, float b, char c)
        : int_data(a), float_data(b), char_data(c)
    {

    }

    void Func()
    {
        return;
    }
};

int main()
{
    MyList<Test> list;
   list.Push_back(Test(100, 0.1f, 'A'));
   list.Push_back(Test(200, 0.2f, 'B'));
   list.Push_back(Test(300, 0.3f, 'C'));
   list.Push_back(Test(400, 0.4f, 'D'));
   list.Push_back(Test(500, 0.5f, 'E'));
   list.Push_front(Test(50, 0.05f, 'b'));
   list.Push_front(Test(10, 0.01f, 'a'));
  
   list.Insert(list.GetNode(3), Test(3333, 33.3f, 'Q'));
  
   
   for (int index = 0; index < list.Size(); ++index)
   {
       int data1 = list.GetNode(index)->_data.int_data;
       float data2 = list.GetNode(index)->_data.float_data;
       char data3 = list.GetNode(index)->_data.char_data;
   
       printf("Index %d data : %d, %f, %c \n", index, data1, data2, data3);
   }
}
