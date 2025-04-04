#include<iostream>
#include<string>

using namespace std;

// Định nghĩa một Node trong cây nhị phân
class Node {
public:
    int data; 
    Node* left;  
    Node* right; 

    // Hàm constructor
    Node(int val): data(val), left(nullptr), right(nullptr) {}
};

// Định nghĩa cây nhị phân tìm kiếm (BST)
class binarySearchTree {
private:
    Node* root; 

    // Hàm chèn một giá trị vào cây BST
    Node* insert(Node* node, int data) {
        if(node == nullptr) {
            // Nếu cây con là null, tạo một node mới
            return new Node(data);
        }
        if(data < node->data) {
            // Nếu giá trị cần chèn nhỏ hơn giá trị của node hiện tại chèn vào bên trái
            node->left = insert(node->left, data); // Gọi đệ quy để xét tiếp cây con bên trái
        }
        else {
            // Nếu giá trị cần chèn lớn hơn hoặc bằng giá trị của node hiện tại chèn vào bên phải
            node->right = insert(node->right, data); // Gọi đệ quy để xét tiếp cây con bên phải
        }

        // Trả về lại node hiện tại vì có thể đã thay đổi cây con bên trái hoặc phải
        return node;
    }

    // Hàm tìm giá trị nhỏ nhất trong cây con bên phải
    Node* minVal(Node* node) {
        Node* current = node;
        while(current && current->left != nullptr) {
            current = current->left; // Tiến sang trái để tìm giá trị nhỏ nhất
        }

        return current;  // Trả về node có giá trị nhỏ nhất
    }

    // Hàm xóa một node khỏi cây BST
    Node* deleteNode(Node* node, int data) {
        if(node == nullptr) {
            return node;  // Nếu không tìm thấy node cần xóa thì trả về null
        }
        if(data < node->data) {
            // Nếu giá trị cần xóa nhỏ hơn giá trị node hiện tại và xóa trong cây con bên trái
            node->left = deleteNode(node->left, data);
        }
        else if(data > node->data) {
            // Nếu giá trị cần xóa lớn hơn giá trị node hiện tại và xóa trong cây con bên phải
            node->right = deleteNode(node->right, data);
        }
        else {
            // Nếu tìm thấy node cần xóa
            if(node->left == nullptr) {
                // Nếu node chỉ có cây con bên phải
                Node* temp = node->right;  // Lưu cây con bên phải
                delete node;  // Xóa node hiện tại
                return temp;  // Trả về cây con bên phải
            }
            if(node->right == nullptr) {
                // Nếu node chỉ có cây con bên trái
                Node* temp = node->left;  // Lưu cây con bên trái
                delete node;  // Xóa node hiện tại
                return temp;  // Trả về cây con bên trái
            }

            // Nếu node có cả cây con trái và phải thì tìm node có giá trị nhỏ nhất trong cây con phải
            Node* temp = minVal(node->right);
            node->data = temp->data;  // Thay đổi giá trị của node hiện tại thành giá trị của node nhỏ nhất
            node->right = deleteNode(node->right, temp->data);  // Xóa node nhỏ nhất
        }

        return node;  // Trả về lại node sau khi xóa
    }

    // Hàm duyệt cây theo thứ tự trung tố 
    void inorderNode(Node* node) {
        if(node) {
            inorderNode(node->left);  // Duyệt cây con bên trái
            cout << node->data << " "; // In giá trị của node hiện tại
            inorderNode(node->right); // Duyệt cây con bên phải
        }
    }

public:
    binarySearchTree(): root(nullptr) {}  // Khởi tạo cây rỗng

    // Hàm chèn giá trị vào cây
    void insert(int data) {
        root = insert(root, data);  // Gọi hàm insert để chèn vào cây
    }

    // Hàm xóa giá trị khỏi cây
    void remove(int data) {
        root = deleteNode(root, data);  // Gọi hàm deleteNode để xóa giá trị
    }

    // Hàm duyệt cây và in các giá trị ra theo thứ tự tăng dần
    void inorderTravel() {
        inorderNode(root);  // Gọi hàm inorderNode để in cây
        cout << endl;
    }
};

int main() {
    binarySearchTree BST;  // Tạo một đối tượng cây nhị phân tìm kiếm
    int n, a, b;
    string command;
    cin >> n;  // Nhập số lượng phần tử ban đầu

    // Nhập các giá trị và chèn chúng vào cây
    for(int i = 0; i < n; i++) {
        int val;
        cin >> val;
        BST.insert(val);  // Chèn giá trị vào cây
    }

    BST.inorderTravel();  // In cây sau khi chèn các giá trị ban đầu

    // Lặp lại và xử lý các lệnh "Insert", "Remove" hoặc "Insert and remove"
    while(cin >> command) {
        if(command == "Insert") {  // Nếu lệnh là "Insert"
            cin >> a;
            for(int i = 0; i < a; i++) {
                int val;
                cin >> val;
                BST.insert(val);  // Chèn các giá trị mới vào cây
            }
            BST.inorderTravel();  // In cây sau khi chèn
        }

        if(command == "Remove") {  // Nếu lệnh là "Remove"
            cin >> b;
            for(int i = 0; i < b; i++) {
                int val;
                cin >> val;
                BST.remove(val);  // Xóa các giá trị khỏi cây
            }
            BST.inorderTravel();  // In cây sau khi xóa
        }

        if(command == "Insert and remove") {  // Nếu lệnh là "Insert and remove"
            cin >> a >> b;

            // Chèn a phần tử vào cây
            for(int i = 0; i < a; i++) {
                int val;
                cin >> val;
                BST.insert(val);  // Chèn giá trị vào cây
            }
            BST.inorderTravel();  // In cây sau khi chèn

            // Xóa b phần tử khỏi cây
            for(int i = 0; i < b; i++) {
                int val;
                cin >> val;
                BST.remove(val);  // Xóa giá trị khỏi cây
            }
            BST.inorderTravel();  // In cây sau khi xóa
        }
    }

    return 0;
}
