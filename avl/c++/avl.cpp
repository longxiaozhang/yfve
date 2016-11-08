/*
*	avl tree implement in c plus plus
*/
template<typename D> class AVL{
private:
	typedef struct node__{
	public:
		Node* parent;
		Node* left;
		Node* right;
		size_t height;
		D data;
	}Node;
	
public:
	AVL();
	~AVL();
	
	/*
	*	@return:
		failed   -1 (mainly with there already have exsisted a same data)
		succeed  0 
	*/
	int Insert(const D& data);
	void Print();
	int Find(const D& data);
	void dataPrint()
	
private:
	AVL(const AVL&);
	/*
	*	height calculate function:max(leftheight,rightheight).
	*/
	size_t calHeight(const Node* node) const;
	
	/*
	*   the value we try to get is calculate through -leftheavy+ rightheavy.
		As the tree always need to be balance,the factor must between -2 and 2.
	*/
	int calFactor(const Node* node) const;
	int insert(Node* curNode,const D& data);
	void print();
	void balance(Node* node,const D& data);
	void llBalance(Node* node);
	void lrBalance(Node* node);
	void rrBalance(Node* node);
	void rlBalance(Node* node);
	
private:
	Node* m_root;
};

inline size_t AVL::calHeight(const Node* node) const
{
	if (NULL == node->left & NULL node->right) return 1;
	if (NULL == node->right) return node->left->height + 1;
	if (NULL == node->left) return node->right->height + 1;
	return node->left->height > node->right->height ? node->left->height:node->right->height;
}

inline int AVL::calFactor(const Node* node) const 
{
	if (NULL == node->left & NULL node->right) return 0;
	if (NULL == node->right) return -node->left->height;
	if (NULL == node->left) return node->right->height;
	return -node->left->height + node->right->height;
}

int template<typename D> AVL::insert(Node* curNode,const D& data)
{
	int ret;
	if (NULL == curNode) return 0;
	if (data == pCur->data) return -1;
	ret = insert(data < pCur->data ? pCur->left : pCur->right, data);
	if (ret < 0) return ret;
	if (0 == ret) { // do insert
		Node* pNew = new Node;
		pNew->data = data;
		pNew->parent = pCur;
		pNew->left = pNew->right = NULL;
		pNew->height = 1;
		pCur->right = pNew;
	}

	pCur->height = calHeight(pCur);
	if (height == 3 ) {
		int factor = calFactor(pCur);
		if (fator >=2 || factor <= -2) {
			balance(pCur, data);
			ret = 2;
		}
	}

	return ret;
}

int template<typename D> AVL::Insert(const D& data)
{
	Node* pCur = NULL;
	int ret = 0;
	if (NULL == m_root) {
		Node* pNew = new Node;
		pNew->data = data;
		pNew->height = 1;
		pNew->parent = pNew->left = pNew->right = NULL;
		m_root = pNew;
		return 1;
	}
	
	return insert(m_root, data);
}

void template<typename D> AVL::balance(Node* node,const D& data)
{
	if (data < node->data) { //first left subtree
		if (data < node->left ) { //second left 
			llBalance(node);
		}
		else {	//second right 
			lrBalance(node);
		}
	}
	else {	//first right subtree
		if (data < node->left) {
			rlBalance(node); //second left
		}
		else {
			rrBalance(node); //second right
		}
	}
}

void AVL::llBalance(Node* node)
{
	Node* tmp = NULL;

	tmp = node->left;
	tmp->right = node;
	tmp->parent = node->parent;
	
	node->left = node->right = NULL;
	node->parent = tmp;
	
	if (tmp->parent == NULL) m_root = tmp;
	else tmp->parent->left = tmp;
}

void AVL::lrBalance(Node* node)
{
	Node* tmp = NULL;
	tmp = node->left->right;
	tmp->left = node->left;
	tmp->right = node;
	tmp->parent = node->parent;
	
	node->left->right = node->left->left = NULL;
	node->left->parent = tmp;
	
	node->left = node->right = NULL;
	node->parent = tmp;
	
	if (tmp->parent == NULL) m_root = tmp;
	else tmp->parent->left = tmp;
}

void AVL::rlBalance(Node* node)
{
	Node* tmp = NULL;
	tmp = node->right->left;
	tmp->right = node->right;
	rmp->left = node;
	tmp->parent = node->parent;
	
	node->right->left = node->right->right = NULL;
	node->right->parent = tmp;
	
	node->left = node->right = NULL;
	node->parent = tmp;
	
	if (tmp->parent == NULL) m_root = tmp;
	else tmp->parent->left = tmp;
}

void AVL::rrBalance(Node* node)
{
	Node* tmp = NULL;
	tmp = node->right;
	tmp->parent = node->parent;
	
	node->left = node->right = NULL;
	node->parent = tmp;	
	
	if (tmp->parent == NULL) m_root = tmp;
	else tmp->parent->left = tmp;
}

void AVL::Print()
{
	if (NULL == m_root) {
		return;
	}
	print(m_root);
}

void AVL::print(Node* node)
{
	if (NULL != node) {
		print(node->left);
	}
	//node->data.print();
}

