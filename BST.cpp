// Created by yujitai

#include <queue>

#include <iostream>
using namespace std;

template<typename Key, typename Value>
class BST {
public:
	// 构造函数
	BST() {
		_root = nullptr;
		_size = 0;
	}

	// 析构函数
	~BST() {
		destroy(_root);
	}

	// 二叉树大小
	int size() {
		return _size;
	}

	// 二叉树是否为空
	bool is_empty() {
		return _size == 0;
	}

	// 向二叉树插入节点(key,value)
	void insert(Key key, Value value) {
		_root = insert(_root, key, value);	
	}

	// 在二叉树中查找是否存在键值为key的节点
	bool contain(Key key) {
		return contain(_root, key);
	}

	// 在二叉树中查找以key为键的节点的值
	Value* search(Key key) {
		return search(_root, key);
	}

	// 前序遍历
	void pre_order() {
		pre_order(_root);
	}

	// 中序遍历
	void in_order() {
		in_order(_root);
	}

	// 后序遍历
	void post_order() {
		post_order(_root);
	}

	// 层序遍历
	void level_order() {
		level_order(_root);
	}

	// 寻找最小的键值
	Key minimum() {
		assert(_size != 0);
		Node* min_node = minimum(_root);
		return min_node->key;
	}

	// 寻找最大的键值
	Key maximum() {
		assert(_size != 0);
		Node* max_node = maximum(_root);
		return max_node->key;
	}

	// 从二叉树中删除最小值所在的节点
	void remove_min() {
		if (_root)
			_root = remove_min(_root);
	}

	// 从二叉树中删除最大值所在的节点
	void remove_max() {
		if (_root)
			_root = remove_max(_root);
	}

	// 从二叉树中删除键值为key的节点
	void remove(Key key) {
		if (_root)
			_root = remove(_root, key);
	}

private:
	struct Node;

	// 向以node为根的二叉搜索树中,插入节点(key, value)
    // 返回插入新节点后的二叉搜索树的根
	Node* insert(Node* node, Key key, Value value) {
		if (node == nullptr) {
			_size++;
			return new Node(key, value);
		}

		if (key == node->key) {
			node->value = value;
		} else if (key < node->key) {
			node->left = insert(node->left, key, value);
		} else { // key > node->key
			node->right = insert(node->right, key, value);
		}

		return node;
	}

	// 查看以node为根的二叉搜索树中是否包含键值为key的节点
	bool contain(Node* node, Key key) {
		if (node == nullptr) 
			return false;

		if (key == node->key) {
			return true;
		} else if (key > node->key) {
			return contain(node->right, key);
		} else { // key > node->key
			return contain(node->left, key);
		}
	}

	// 在以node为根的二叉搜索树中查找key所对应的value
	Value* search(Node* node, Key key) {
		if (node == nullptr)
			return nullptr;

		if (key == node->key) {
			return &(node->value);
		} else if (key < node->key) {
			return search(node->left, key);
		} else { // key > node->key
			return search(node->right, key);
		}
	}

	// 对以node为根的二叉搜索树进行前序遍历
	void pre_order(Node* node) {
		if (node != nullptr) {
			cout << node->key << endl;
			pre_order(node->left);
			pre_order(node->right);
		}
	}
	
	// 对以node为根的二叉搜索树进行中序遍历
	void in_order(Node* node) {
		if (node != nullptr) {
			in_order(node->left);
			cout << node->key << endl;
			in_order(node->right);
		}
	}

	// 对以node为根的二叉搜索树进行后序遍历
	void post_order(Node* node) {
		if (node != nullptr) {
			post_order(node->left);
			post_order(node->right);
			cout << node->key << endl;
		}
	}

	// 对以node为根的二叉搜索树进行层序遍历
	void level_order(Node* node) {
		std::queue<Node*> q;
		q.push(node);

		while(!q.empty()) {
			Node* node = q.front();
			q.pop();

			cout << node->key << endl;

			if (node->left)
				q.push(node->left);
			if (node->right)
				q.push(node->right);
		}
	}

	// 在以node为根的二叉搜索树中返回最小键值的节点
	Node* minimum(Node* node) {
		if (node->left == nullptr)
			return node;

		return minimum(node->left);
	}

	// 在以node为根的二叉搜索树中返回最大键值的节点
	Node* maximum(Node* node) {
		if(node->right == nullptr)
            return node;

        return maximum(node->right);
	}

	// 删除掉以node为根的二分搜索树中的最小节点
    // 返回删除节点后新的二分搜索树的根
	Node* remove_min(Node* node) {
		if (node->left == nullptr) {
			Node* right_node = node->right;
			delete node;
			_size--;
			return right_node;
		}

		node->left = remove_min(node->left);

		return node;
	}

	// 删除掉以node为根的二分搜索树中的最大节点
    // 返回删除节点后新的二分搜索树的根
	Node* remove_max(Node* node) {
		if (node->right == nullptr) {
			Node* left_node = node->left;
			delete node;
			_size--;
			return left_node;
		}

		node->right = remove_max(node->right);

		return node;
	}

	// 删除掉以node为根的二分搜索树中键值为key的节点
    // 返回删除节点后新的二分搜索树的根
	Node* remove(Node* node, Key key) {
		if (node == nullptr) {
			return nullptr;
		}
		
		if (key < node->key) {
			node->left = remove(node->left, key);
			return node;
		} else if (key > node->key) {
			node->right = remove(node->right, key);
			return node;
		} else { // key == node->key
			if (node->left == nullptr) { // 只有右孩子		
				Node* right_node = node->right;
				delete node;
				_size--;
				return right_node;
			}

			if (node->right == nullptr) { // 只有左孩子
				Node* left_node = node->left;
				delete node;
				_size--;
				return left_node;
			}

			// 左右孩子都存在

			// 找到后继节点
			Node* successor = new Node(minimum(node->right));
			_size++;

			// 给后继节点安排左右子树
			successor->left = node->left;
			successor->right = remove_min(node->right);

			// 删除原节点
			delete node;
			_size--;

			// 返回后继节点
			return successor;
		}
	}

	// 销毁以node为根的二分搜索树
	void destroy(Node* node) {
		if (node !=nullptr) {
			destroy(node->left);
			destroy(node->rightt);
			delete node;
			_size--;
		}
	}

	struct Node {
		Key key;
		Value value;
		Node* left;
		Node* right;

		Node(Key key, Value value) {
			this->key = key;
			this->value = value;
			left = right = nullptr;
		}

		Node(Node* node) {
			key = node->key;
			value = node->value;
			left = node->left;
			right = node->right;
		}
	};

	Node* _root;
	int _size;
};

void shuffle( int arr[], int n ){

    srand( time(NULL) );
    for( int i = n-1 ; i >= 0 ; i -- ){
        int x = rand()%(i+1);
        swap( arr[i] , arr[x] );
    }
}

int main() {
  	srand(time(NULL));
    BST<int,int> bst = BST<int,int>();

    int n = 10;
    for( int i = 0 ; i < n ; i ++ ){
        int key = rand()%n;
        // 为了后续测试方便,这里value值取和key值一样
        int value = key;
        cout<<key<<" ";
        bst.insert(key,value);
    }
    cout<<endl;

    cout<<"size: "<<bst.size()<<endl<<endl;

    cout<<"pre_order: "<<endl;
    bst.pre_order();
    cout<<endl<<endl;

    cout<<"in_order: "<<endl;
    bst.in_order();
    cout<<endl<<endl;

    cout<<"post_order: "<<endl;
    bst.post_order();
    cout<<endl<<endl;

    cout<<"level_order: "<<endl;
    bst.level_order();
    cout<<endl<<endl;

	cout<<"minimum: "<<bst.minimum();
    cout<<endl<<endl;

	cout<<"maximum: "<<bst.maximum();
    cout<<endl<<endl;

	/*
    while(!bst.is_empty()){
        cout<<"min: "<<bst.minimum()<<endl;
        bst.remove_min();
        cout<<"after remove_min, size = "<<bst.size()<<endl;
    }

    while(!bst.is_empty()){
        cout<<"max: "<<bst.maximum()<<endl;
        bst.remove_max();
        cout<<"after remove_max, size = "<<bst.size()<<endl;
    }
	*/

	// test remove
	// remove elements in random order
	int order[n];
	for( int i = 0 ; i < n ; i ++ )
			order[i] = i;
	shuffle( order , n );

	for( int i = 0 ; i < n ; i ++ ) {
		if(bst.contain(order[i])){
			bst.remove(order[i]);
			cout<<"after remove "<<order[i]<<" size = "<<bst.size()<<endl;
		}
	}

	return 0;
}


