#include <stdexcept>
using namespace std;

template <typename S>

class Stack
{
    public:
        Stack() : head(nullptr) {}

        void push(const S x)
        {
            Node* new_node = new Node;
            new_node->data = x;
            new_node->prev = head;
            head = new_node;
        }

        bool empty()
        {
            if (head == nullptr)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        S top()
        {
            if (empty())
            {
                throw length_error("stack is empty");
            }
            return head->data;
        }

        void pop()
        {
            if (empty())
            {
                throw length_error("stack is empty");
            }
            Node *temp_prev = head;
            head = temp_prev->prev;
            delete temp_prev;
        }

        ~Stack()
        {
            while (!empty())
            {
                pop();
            }
        }
    private:
        struct Node
        {
            S data;
            Node *prev;
        };
        Node* head;
};
