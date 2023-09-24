#include <iostream>
#include <crtdbg.h>

template <typename T>
class MyList
{
public:
    // 노드 클래스
    struct Node
    {
        T _data;
        Node* _prev_node;
        Node* _next_node;

        Node(T data) : _data(data), _prev_node(nullptr), _next_node(nullptr)
        {};

        T GetData() { return _data; }
    };

public:
    // 반복자 클래스
    class Iterator
    {
    public:
        friend MyList;
        Node* _cur_node;

        Iterator(Node* node = nullptr)
        {
            this->_cur_node = node;
        }

        bool operator==(const Iterator& iter) { return _cur_node == iter._cur_node; }
        bool operator!=(const Iterator& iter) { return _cur_node != iter._cur_node; }

        Iterator& operator++()
        {
            _cur_node = _cur_node->_next_node;
            return *this;
        }
    };

public:
    MyList()
    {
        _head = nullptr;
        _tail = nullptr;
        _size = 0;
    }

    ~MyList()
    {
        Node* tmp_node = nullptr;

        while (_head != nullptr)
        {
            tmp_node = _head;
            _head = _head->_next_node;
            delete tmp_node;
        }
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
            _head->_prev_node = new_node;
            new_node->_next_node = _head;
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
            _tail->_next_node = new_node;
            new_node->_prev_node = _tail;
            _tail = new_node;
        }

        ++_size;
    }

    void Insert(Iterator position, T data)
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
            new_node->_prev_node = position._cur_node;
            new_node->_next_node = position._cur_node->_next_node;
            position._cur_node->_next_node = new_node;
        }

        ++_size;
    }

    void Insert(int index, T data)
    {
        if (index < 0 || index >= _size)
        {
            return;
        }

        Node* new_node = new MyList::Node(data);
        new_node->_data = data;

        if (index == 0)                 // 맨 앞쪽에 삽입되는 경우 (== Push_Front)
        {
            new_node->_next_node = _head;
            _head->_prev_node = new_node;
            _head = new_node;
        }
        else if (index == _size)        // 맨 뒤쪽에 삽입되는 경우 (== Push_Back)
        {
            _tail->_next_node = new_node;
            new_node->_prev_node = _tail;
            _tail = new_node;
        }
        else if (_head == nullptr)  // 헤드가 없는 경우
        {
            _head = new_node;
            _tail = new_node;
        }
        else// 일반적인 케이스
        {
            Node* cur_node = _head;

            for (int i = 0; i < index; ++i)
            {
                // 인덱스까지 순회 후 해당 노드 포인터 자리에 new node 교체
                cur_node = cur_node->_next_node;
            }

            new_node->_prev_node = cur_node->_prev_node;
            new_node->_next_node = cur_node;
            cur_node->_prev_node->_next_node = new_node;
            cur_node->_prev_node = new_node;
        }


        ++_size;
        return;
    }

    T Find(int index)
    {
        Node* cur_node;

        if (index + 1 <= _size / 2)
        {
            cur_node = _head;
            for (int i = 0; i < index; ++i)
            {
                cur_node = cur_node->_next_node;
            }

        }
        else
        {
            cur_node = _tail;
            for (int i = 0; i < index; ++i)
            {
                cur_node = cur_node->_prev_node;
            }

        }

        return cur_node->GetData();
    }

    int Size()
    {
        return _size;
    }

    Node* Begin() { return _head; }
private:
    Node* _head = nullptr;
    Node* _tail = nullptr;
    int _size = 0;
};


class Test
{
private:
    int _int_data;
    float _float_data;
    char _char_data;

public:
    Test(int a, float b, char c)
        : _int_data(a), _float_data(b), _char_data(c)
    {

    }

    int GetInt() { return _int_data; }
    float GetFloat() { return _float_data; }
    char GetChar() { return _char_data; }
};

int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    int* test = new int();
    // 릭 체크용

    MyList<Test> list;

    // 데이터 푸시백  
    list.Push_back(Test(30, 0.1f, 'C'));
    list.Push_back(Test(40, 0.2f, 'E'));
    list.Push_back(Test(50, 0.3f, 'F'));
    list.Push_back(Test(60, 0.4f, 'G'));
    list.Push_back(Test(70, 0.5f, 'H'));

    // 데이터 푸시 프론트
    list.Push_front(Test(20, 0.05f, 'B'));
    list.Push_front(Test(10, 0.025f, 'A'));

    // 반복자로 노드 포인터 이동
   // MyList<Test>::Iterator iter = MyList<Test>::Iterator(list.Begin());
   // ++iter;
   // ++iter;
   //
    // 반복자의 현재 위치 노드 앞에 데이터 추가
    list.Insert(2, Test(35, 0.15f, 'D'));

    // 반복자 순회로 모든 노드 표시
    //iter = MyList<Test>::Iterator(list.Begin());
   // int index = 0;
    for (int index = 0; index < list.Size(); ++index)
    {
        int data1 = list.Find(index).GetInt();
        float data2 = list.Find(index).GetFloat();
        char data3 = list.Find(index).GetChar();
        printf("Index %d data : %d, %f, %c \n", index, data1, data2, data3);
    }
}