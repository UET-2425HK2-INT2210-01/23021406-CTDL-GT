#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Định nghĩa Node trong Heap
class Node {
public:
    int data;       // Giá trị của node
    Node* left;     // Con trái
    Node* right;    // Con phải
    Node* parent;   // Node cha

    // Constructor khởi tạo giá trị và trỏ các con về nullptr
    Node(int val) : data(val), left(nullptr), right(nullptr), parent(nullptr) {}
};

// Lớp Heap (Min-Heap)
class MinHeap {
private:
    Node* root;               // Gốc của Heap
    vector<Node*> nodeList;   // Lưu danh sách node để dễ dàng truy cập vị trí cuối

    // Hoán đổi giá trị của hai node (không đổi vị trí con trỏ)
    void swap(Node* a, Node* b) {
        int temp = a->data;
        a->data = b->data;
        b->data = temp;
    }

    // Heapify Up: Duy trì tính chất Min-Heap sau khi chèn node mới
    void heapifyUp(Node* node) {
        while (node->parent && node->data < node->parent->data) { // Nếu node nhỏ hơn node cha thì hoán đổi
            swap(node, node->parent);
            node = node->parent; // Di chuyển lên cha để tiếp tục kiểm tra
        }
    }

    // Heapify Down: Duy trì tính chất Min-Heap sau khi xóa node
    void heapifyDown(Node* node) {
        while (node) {
            Node* smallest = node; // Giả sử node hiện tại là nhỏ nhất
            if (node->left && node->left->data < smallest->data) 
                smallest = node->left; // So sánh với con trái
            if (node->right && node->right->data < smallest->data) 
                smallest = node->right; // So sánh với con phải

            if (smallest != node) { // Nếu tìm thấy con nhỏ hơn, hoán đổi và tiếp tục xuống dưới
                swap(node, smallest);
                node = smallest;
            } else {
                break; // Nếu không cần hoán đổi nữa thì dừng lại
            }
        }
    }

    // Tìm vị trí của một giá trị trong Heap
    int findIndex(int value) {
        for (int i = 0; i < nodeList.size(); i++) {
            if (nodeList[i]->data == value)
                return i; // Trả về vị trí trong nodeList
        }
        return -1; // Không tìm thấy
    }

public:
    MinHeap() : root(nullptr) {} // Constructor khởi tạo Heap rỗng

    // Chèn một giá trị vào Heap
    void insert(int value) {
        Node* newNode = new Node(value);
        nodeList.push_back(newNode); // Thêm node vào danh sách nodeList

        if (nodeList.size() == 1) {
            root = newNode; // Nếu là node đầu tiên, đặt làm root
        } else {
            // Xác định node cha của node mới
            Node* parent = nodeList[(nodeList.size() - 2) / 2];
            if (!parent->left)
                parent->left = newNode; // Nếu cha chưa có con trái, gán vào con trái
            else
                parent->right = newNode; // Nếu có rồi, gán vào con phải

            newNode->parent = parent; // Cập nhật liên kết với node cha
        }

        heapifyUp(newNode); // Điều chỉnh Min-Heap
    }

    // Xóa một giá trị khỏi Heap
    void remove(int value) {
        int index = findIndex(value); // Tìm vị trí cần xóa
        if (index == -1) return; // Không tìm thấy thì thoát

        Node* lastNode = nodeList.back(); // Lấy node cuối cùng
        Node* delNode = nodeList[index];  // Node cần xóa

        // Hoán đổi giá trị với node cuối
        swap(delNode, lastNode);
        nodeList.pop_back(); // Xóa node cuối khỏi danh sách

        // Cập nhật con của node cuối (tránh trỏ đến node đã xóa)
        if (lastNode->parent) {
            if (lastNode->parent->left == lastNode)
                lastNode->parent->left = nullptr;
            else
                lastNode->parent->right = nullptr;
        }

        if (delNode == root) 
            root = (nodeList.empty() ? nullptr : nodeList[0]); // Nếu xóa root, cập nhật lại root

        delete delNode; // Giải phóng bộ nhớ

        if (!nodeList.empty()) 
            heapifyDown(lastNode); // Điều chỉnh lại Heap
    }

    // In Heap theo thứ tự level-order
    void printHeap() {
        for (Node* node : nodeList)
            cout << node->data << " ";
        cout << endl;
    }
};

int main() {
    MinHeap heap;
    int n, a, b;
    string command;
    cin >> n;  // Nhập số lượng phần tử ban đầu

    // Nhập các giá trị và chèn vào Heap
    for (int i = 0; i < n; i++) {
        int val;
        cin >> val;
        heap.insert(val);
    }

    heap.printHeap();  // In heap sau khi chèn các giá trị ban đầu

    // Xử lý các lệnh "Insert", "Remove" hoặc "Insert and remove"
    while (cin >> command) {
        if (command == "Insert") {  // Nếu lệnh là "Insert"
            cin >> a;
            for (int i = 0; i < a; i++) {
                int val;
                cin >> val;
                heap.insert(val);
            }
            heap.printHeap();
        }

        if (command == "Remove") {  // Nếu lệnh là "Remove"
            cin >> b;
            for (int i = 0; i < b; i++) {
                int val;
                cin >> val;
                heap.remove(val);
            }
            heap.printHeap();
        }

        if (command == "Insert and remove") {  // Nếu lệnh là "Insert and remove"
            cin >> a >> b;
            for (int i = 0; i < a; i++) {
                int val;
                cin >> val;
                heap.insert(val);
            }
            heap.printHeap();

            for (int i = 0; i < b; i++) {
                int val;
                cin >> val;
                heap.remove(val);
            }
            heap.printHeap();
        }
    }

    return 0;
}
