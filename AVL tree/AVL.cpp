#include<iostream>

using namespace std;

struct NODE {
	int key;
	NODE* p_left;
	NODE* p_right;
	int height;
};

NODE* createNode(int data) {
	auto* pnode = new NODE;
	if (!pnode) return NULL;
	pnode->key = data;
	pnode->p_left = NULL;
	pnode->p_right = NULL;
	pnode->height = 1;
	return pnode;
}

void NLR(NODE* pRoot) {
	if (!pRoot) return;
	cout << pRoot->key << " - " << pRoot->height << " ";
	NLR(pRoot->p_left);
	NLR(pRoot->p_right);
}

void LNR(NODE* pRoot) {
	if (!pRoot) return;
	LNR(pRoot->p_left);
	cout << pRoot->key << " - " << pRoot->height << " ";
	LNR(pRoot->p_right);
}

void LRN(NODE* pRoot) {
	if (!pRoot) return;
	LRN(pRoot->p_left);
	LRN(pRoot->p_right);
	cout << pRoot->key << " - " << pRoot->height << " ";
}

int Height(NODE* pRoot) {
	if (!pRoot) return 0;
	return pRoot->height;
}

int max(int a, int b) { return (a > b) ? a : b; }

int getBalance(NODE* pRoot) {
	if (!pRoot) return 0;
	return Height(pRoot->p_left) - Height(pRoot->p_right);
}

void printLevel(NODE* pRoot, int level) {
	if (!pRoot) return;
	if (1 == level) cout << pRoot->key << " - " << pRoot->height << "\n";
	else if (1 < level) {
		printLevel(pRoot->p_left, level - 1);
		printLevel(pRoot->p_right, level - 1);
	}
}

NODE* rightRoll(NODE* pRoot) {
	auto* a = pRoot->p_left;
	auto* b = a->p_right;

	a->p_right = pRoot;
	pRoot->p_left = b;

	pRoot->height = max(Height(pRoot->p_left), Height(pRoot->p_right)) + 1;
	a->height = max(Height(a->p_left), Height(a->p_right)) + 1;

	return a;
}

NODE* leftRoll(NODE* pRoot) {
	auto* a = pRoot->p_right;
	auto* b = a->p_left;

	a->p_left = pRoot;
	pRoot->p_right = b;

	pRoot->height = max(Height(pRoot->p_left), Height(pRoot->p_right)) + 1;
	a->height = max(Height(a->p_left), Height(a->p_right)) + 1;

	return a;
}

NODE* Insert(NODE* pRoot, int x) {
	if (!pRoot) return createNode(x);

	if (pRoot->key > x) pRoot->p_left = Insert(pRoot->p_left, x);
	else if (pRoot->key < x) pRoot->p_right = Insert(pRoot->p_right, x);
	else return pRoot;
	
	pRoot->height = max(Height(pRoot->p_left), Height(pRoot->p_right)) + 1;
	int balance = getBalance(pRoot);

	if (balance > 1 && x < pRoot->p_left->key) return rightRoll(pRoot);
	if (balance < -1 && x > pRoot->p_right->key) return leftRoll(pRoot);

	if (balance > 1 && x > pRoot->p_left->key) {
		pRoot->p_left = leftRoll(pRoot->p_left);
		return rightRoll(pRoot);
	}
	if (balance < -1 && x < pRoot->p_right->key) {
		pRoot->p_right = rightRoll(pRoot->p_right);
		return leftRoll(pRoot);
	}
	return pRoot;
}

NODE* minValue(NODE* pRoot) {
	NODE* p = pRoot;

	while (p->p_left != NULL)
		p = p->p_left;

	return p;
}

NODE* Remove(NODE* pRoot, int x) {
    if (!pRoot) return pRoot;

    if (x < pRoot->key) pRoot->p_left = Remove(pRoot->p_left, x);
    else if (x > pRoot->key) pRoot->p_right = Remove(pRoot->p_right, x);

    else {
        if ((!pRoot->p_left) || (!pRoot->p_right)) {
			NODE* temp = pRoot->p_left ? pRoot->p_left : pRoot->p_right;

            if (!temp) {
                temp = pRoot;
                pRoot = NULL;
            } else pRoot = temp;

			delete temp;
			temp = NULL;
        }
        else { 
            NODE* temp = minValue(pRoot->p_right);
            pRoot->key = temp->key; 
            pRoot->p_right = Remove(pRoot->p_right, temp->key);
        }
    }
    if (!pRoot) return pRoot;

	pRoot->height = max(Height(pRoot->p_left), Height(pRoot->p_right)) + 1;
    int balance = getBalance(pRoot);
 
    if (balance > 1 && getBalance(pRoot->p_left) >= 0) return rightRoll(pRoot);
	if (balance < -1 && getBalance(pRoot->p_right) <= 0) return leftRoll(pRoot);

    if (balance > 1 && getBalance(pRoot->p_left) < 0) {
        pRoot->p_left = leftRoll(pRoot->p_left);
        return rightRoll(pRoot);
    }
    if (balance < -1 && getBalance(pRoot->p_right) > 0) {
        pRoot->p_right = rightRoll(pRoot->p_right);
        return leftRoll(pRoot);
    }
	return pRoot;
}

void LevelOrder(NODE* pRoot) {
	if (!pRoot) return;
	int h = pRoot->height;
	for (int i = 1; i <= h; i++)
		printLevel(pRoot, i);
}

bool isAVL(NODE* pRoot) {
	if(!pRoot) return true;

	int balance = getBalance(pRoot->p_left) - getBalance(pRoot->p_right);

	if (balance != 0 && balance != -1 && balance != 1) return false;

	return true;
}

int main() {
	NODE* pnode = createNode(10);
	pnode = Insert(pnode, 20);
	pnode = Insert(pnode, 30);
	pnode = Insert(pnode, 40);
	pnode = Insert(pnode, 50);
	pnode = Insert(pnode, 25);

	LevelOrder(pnode);
	cout << isAVL(pnode);

	return 1;
}
