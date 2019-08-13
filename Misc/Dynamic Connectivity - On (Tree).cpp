// Link-cut tree for online tree dynamic connectivity
// No need to init, simply call link(), cut(), connected()
// with the address of any node, e.g. link(&nos[a],&nos[b])
struct Node {
	Node *left, *right, *parent;
	bool revert;
	Node() : left(0), right(0), parent(0), revert(false) {}

	bool isRoot() {
		return parent == NULL || 
			(parent->left != this && parent->right != this);
	}
	void push() {
		if (revert) {
			revert = false;
			Node *t = left;
			left = right;
			right = t;
			if (left != NULL) left->revert = !left->revert;
			if (right != NULL) right->revert = !right->revert;
		}
	}
} nos[1100000];
void connect(Node *ch, Node *p, bool isLeftChild) {
	if (ch != NULL) ch->parent = p;
	if (isLeftChild) p->left = ch;
	else p->right = ch;
}
void rotate(Node *x) {
	Node *p = x->parent;
	Node *g = p->parent;
	bool isRoot = p->isRoot();
	bool leftChild = x == p->left;

	connect(leftChild ? x->right : x->left, p, leftChild);
	connect(p, x, !leftChild);
	if (!isRoot) connect(x, g, p == g->left);
	else x->parent = g;
}
void splay(Node *x) {
	while (!x->isRoot()) {
		Node *p = x->parent;
		Node *g = p->parent;
		if (!p->isRoot()) g->push();
		p->push();
		x->push();
		if (!p->isRoot()) {
			rotate((x == p->left) == (p == g->left) ? p : x);
		}
		rotate(x);
	}
	x->push();
}
Node *expose(Node *x) {
	Node *last = NULL, *y;
	for (y = x; y != NULL; y = y->parent) {
		splay(y);
		y->left = last;
		last = y;
	}
	splay(x);
	return last;
}
void makeRoot(Node *x) {
	expose(x);
	x->revert = !x->revert;
}
bool connected(Node *x, Node *y) {
	if (x == y) return true;
	expose(x);
	expose(y);
	return x->parent != NULL;
}
bool link(Node *x, Node *y) {
	if (connected(x, y)) return false;
	makeRoot(x);
	x->parent = y;
	return true;
}
bool cut(Node *x, Node *y) {
	makeRoot(x);
	expose(y);
	if (y->right != x || x->left != NULL || x->right != NULL) 
		return false;
	y->right->parent = NULL;
	y->right = NULL;
	return true;
}
