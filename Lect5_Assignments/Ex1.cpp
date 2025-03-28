#include<iostream>

using namespace std;

const int N = 1000;

struct treeNode { 
    int data;
    treeNode* firstChild; // chỉ đến con cả
    treeNode* nextSibling; // chỉ đến anh chị em của con cả cùng cấp
    // constructor
    treeNode(int val):data(val), firstChild(nullptr), nextSibling(nullptr) {}
};

class Tree {
    public:

    treeNode* root; //gốc
    treeNode* nodeList[N]; // tạo mảng lưu các giá trị của node
    bool isChild[N]; // mảng quản lý các node con

    //constructor
    Tree():root(nullptr) { //khi khởi tạo Tree thì sẽ tạo luôn biến root và gán giá trị cho root là nullptr 
        for(int i = 0; i < N; i++) {
            nodeList[i] = nullptr; //đảm bảo trong nodeList ko chứa địa chỉ rác
            isChild[i] = false;
        }
    }

    // tìm và cập nhập root cho tree 
    void updateRoot() {
        for(int i = 0; i < N; i++) {
            if(nodeList[i] != nullptr && !isChild[i]) { // kiểm tra xem đã có node nào đã được tạo ra chưa & có phải con của node nào ko 
                root = nodeList[i]; // cập nhập giá trị cho root
                return; // trả về root 
            }
        }
    }

    // thêm con vào node
    void addChild(int parent, int child) {
        // kiểm tra node đã tồn tại trong nodeList chưa
        if(!nodeList[parent]) nodeList[parent] = new treeNode(parent); // nếu chưa thì tạo node cha
        if(!nodeList[child]) nodeList[child] = new treeNode(child); // nếu chưa thì tạo node con

        treeNode* parentNode = nodeList[parent]; // dùng con trỏ parentNode để node có giá trị parent trong nodeList
        treeNode* childNode = nodeList[child];

        if(parentNode->firstChild == nullptr) { 
            parentNode->firstChild = childNode; // gán childNode thành firstChild
        }
        else { // có firstChild rồi
            treeNode* tmp = parentNode->firstChild; // gán node tmp giá trị của firstChild 
            while(tmp->nextSibling != nullptr) { // duyệt đến node con cuối cùng của firstChild
                tmp = tmp->nextSibling;
            }
            tmp->nextSibling = childNode;
        }
        isChild[child] = true; // đánh dấu node con
    }

    // Hàm lấy chiều cao
    int getHeight(treeNode* node) { // node đây là chiều cao của cây con đang xét
        if(node == nullptr) { // điều kiện dừng 
            return 0; // trả giá trị = 0
        }

        int maxChildHeight = 0; // tạo giá trị biến đếm
        treeNode* child = node->firstChild;
        while(child != nullptr) {
            maxChildHeight = max(maxChildHeight, getHeight(child)); // cập nhập giá trị lớn nhất cho biến đếm
            child = child->nextSibling;
        }
        return maxChildHeight + 1; // thêm chiều cao của root
    }

    //duyệt trước preorder
    void preorder(treeNode* node) {
        if(node == nullptr) {
            return;
        }
        cout << node->data << " "; // in giá trị root
        treeNode* child = node->firstChild;
        while(child != nullptr) {
            preorder(child);
            child = child->nextSibling;
        }
    }

    //duyệt sau postorede
    void postorder(treeNode* node) {
        if (node == nullptr) {
            return;
        }
        treeNode* child = node->firstChild;
        while (child != nullptr) {
            postorder(child); // gọi đệ quy để duyệt cây con của từng node con
            // nếu node con có cây con thì sẽ quay lại và bắt đầu duyệt từ node con đó
            // nếu ko có cây con sẽ in ra giá trị hiện tại và chuyển sang duyệt node anh chị em 
            child = child->nextSibling;
        }
        cout << node->data << " ";
    }

    bool isBinaryTree(treeNode* node) {
        if(node == nullptr) {
            return true;
        }

        int childCount = 0;
        treeNode* child = node->firstChild;
        while(child != nullptr){
            childCount++;
            if(childCount > 2) { // nếu có hơn 2 con thì sai
                return false;
            }
            child = child->nextSibling; // nếu <= 2 thì chuyển sang node tiếp theo
        }

        child = node->firstChild; // bắt đầu từ node con đầu tiên
        while(child != nullptr) {
            if(!isBinaryTree(child)) { // duyệt qua tất cả cây con xem có hợp lệ ko
                return false;
            }
            child = child->nextSibling; // nếu ko thì chuyển sang node tiếp theo
        }

        return true;
    }

    void inorder(treeNode* node) {
        if (node == nullptr) {
            return;
        }
        
        treeNode* leftChild = node->firstChild;
        treeNode* rightChild = (leftChild) ? leftChild->nextSibling : nullptr;

        inorder(leftChild);
        cout << node->data << " ";
        inorder(rightChild);
    }

    void process() {
        if (root == nullptr) {
            return;
        }

        // In chiều cao của cây
        cout << getHeight(root) - 1 << endl;

        // Duyệt trước
        preorder(root);
        cout << endl;

        // Duyệt sau
        postorder(root);
        cout << endl;

        // Kiểm tra cây nhị phân và duyệt giữa
        if (isBinaryTree(root)) {
            inorder(root);
            cout << endl;
        } else {
            cout << "NOT BINARY TREE" << endl;
        }
    }
};

int main() {
    int N, M;
    cin >> N >> M;

    Tree tree;

    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        tree.addChild(u, v);
    }

    tree.updateRoot(); 
    tree.process();
    return 0;
}