enum Color
{
    RED,
    BLACK
};

template<typename T>
class Node
{
public:
    T data;
    Color color;
    
    Node<T>* left;
    Node<T>* right;
    Node<T>* parent;

    Node(T data)
    {
        this->data = data;
        left = NULL;
        right = NULL;
        parent = NULL;
        color = RED;
    }
};
