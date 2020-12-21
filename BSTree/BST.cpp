//#include<iostream>
//#include<fstream>
//#include<string>
//
//using namespace std;
//
//#define MAX 1000
//
//struct NODE {
//	int key;
//	NODE* p_left = NULL;
//	NODE* p_right = NULL;
//};
//
//NODE* createNode(int data) {
//	NODE* pnode = new NODE;
//
//	if (!pnode) return NULL;
//
//	pnode->key = data;
//	pnode->p_left = NULL;
//	pnode->p_right = NULL;
//
//	return pnode;
//}
//
//void NLR(NODE* pRoot) {
//	if (!pRoot) return;
//
//	cout << pRoot->key << " ";
//	NLR(pRoot->p_left);
//	NLR(pRoot->p_right);
//}
//
//void LNR(NODE* pRoot) {
//	if (!pRoot) return;
//
//	LNR(pRoot->p_left);
//	cout << pRoot->key << " ";
//	LNR(pRoot->p_right);
//}
//
//void LRN(NODE* pRoot) {
//	if (!pRoot) return;
//
//	LRN(pRoot->p_left);
//	LRN(pRoot->p_right);
//	cout << pRoot->key << " ";
//}
//
//int Height(NODE* pRoot) {
//	if (!pRoot) return 0;
//
//	int lHeight = Height(pRoot->p_left);
//	int rHeight = Height(pRoot->p_right);
//
//	if (lHeight > rHeight) return ++lHeight;
//	else return ++rHeight;
//}
//
//void printGivenLevel(NODE* pRoot, int level) {
//	if (!pRoot) return;
//	if (1 == level) cout << pRoot->key << " ";
//	else if (1 < level) {
//		printGivenLevel(pRoot->p_left, level - 1);
//		printGivenLevel(pRoot->p_right, level - 1);
//	}
//}
//
//void LevelOrder(NODE* pRoot) {
//	if (pRoot == NULL) return;
//	int level = Height(pRoot);
//	for (int i = 1; i <= level; i++)
//		printGivenLevel(pRoot, i);
//}
//
//NODE* Search(NODE* pRoot, int x) {
//	if (!pRoot) return NULL;
//	if (pRoot->key > x) return Search(pRoot->p_left, x);
//	else if (pRoot->key < x) return Search(pRoot->p_right, x);
//	else return pRoot;
//}
//
//void Insert(NODE*& pRoot, int x) {
//	if (!pRoot) {
//		pRoot = new NODE;
//		pRoot->key = x;
//		pRoot->p_left = NULL;
//		pRoot->p_right = NULL;
//	}
//	if (pRoot->key > x) return Insert(pRoot->p_left, x);
//	else if (pRoot->key < x) return Insert(pRoot->p_right, x);
//}
//
//NODE* searchStandFor(NODE*& p, NODE* pnode) {
//	if (p->p_right) return searchStandFor(p->p_right, pnode);
//
//	pnode->key = p->key;
//	auto* pTemp = p;
//	p = p->p_left;
//	return pTemp;
//}
//
//void Delete(NODE*& pnode) {
//	auto* pTemp = pnode;
//	if (!pnode->p_right) pnode = pnode->p_left;
//	else if (!pnode->p_left) pnode = pnode->p_right;
//	else pTemp = searchStandFor(pnode->p_left, pnode);
//	delete pTemp;
//}
//
//void Remove(NODE*& pRoot, int x) {
//	if (!pRoot) return;
//	else if (pRoot->key > x) return Remove(pRoot->p_left, x);
//	else if (pRoot->key < x) return Remove(pRoot->p_right, x);
//	Delete(pRoot);
//}
//
//NODE* createTree(int a[], int n) {
//	auto pnode = createNode(a[0]);
//	for (int i = 1; i < n; i++)
//		Insert(pnode, a[i]);
//	return pnode;
//}
//
//void removeTree(NODE*& pRoot) {
//	if (!pRoot) return;
//	Remove(pRoot, pRoot->key);
//	return removeTree(pRoot);
//}
//
//int countNode(NODE* pRoot) {
//	if (!pRoot) return 0;
//	int left = countNode(pRoot->p_left);
//	int right = countNode(pRoot->p_right);
//	if (pRoot) return 1 + left + right;
//	else return right + left;
//}
//
//void NLR_for_sum(NODE* pRoot, int& sum) {
//	if (!pRoot) return;
//
//	sum += pRoot->key;
//	NLR_for_sum(pRoot->p_left, sum);
//	NLR_for_sum(pRoot->p_right, sum);
//}
//
//int sumNode(NODE* pRoot) {
//	int sum = 0;
//	NLR_for_sum(pRoot, sum);
//	return sum;
//}
//
//int heightNode(NODE* pRoot, int value) {
//	if (!Search(pRoot, value)) return -1;
//	if (pRoot->key == value) return 1;
//	int lHeight = heightNode(pRoot->p_left, value);
//	int rHeight = heightNode(pRoot->p_right, value);
//
//	if (lHeight > rHeight) return ++lHeight;
//	else return ++rHeight;
//}
//
//int Level(NODE* pRoot, NODE* p) { return heightNode(pRoot, p->key); }
//
//int countLeaf(NODE* pRoot) {
//	if (!pRoot) return 0;
//	if (!pRoot->p_left && !pRoot->p_right) return 1;
//	else return countLeaf(pRoot->p_left) + countLeaf(pRoot->p_right);
//}
//
//int countLess(NODE* pRoot, int x) {
//	if (!pRoot) return 0;
//
//	int left = countLess(pRoot->p_left, x);
//	int right = countLess(pRoot->p_right, x); 
//	if (pRoot->key < x) return 1 + left + right;
//	else return left + right;
//}
//
//int countGreater(NODE* pRoot, int x) {
//	if (!pRoot) return 0;
//
//	int left = countGreater(pRoot->p_left, x);
//	int right = countGreater(pRoot->p_right, x);
//	if (pRoot->key > x) return 1 + left + right;
//	else return left + right;
//}
//
//bool isBST(NODE* pRoot) {
//	if (!pRoot) return true;
//	if ((pRoot->p_left && pRoot->p_left->key > pRoot->key) || (pRoot->p_right && pRoot->key > pRoot->p_right->key)) return false;
//	isBST(pRoot->p_left);
//	isBST(pRoot->p_right);
//}
//
//bool isFullBST(NODE* pRoot) {
//	if (!pRoot) return true;
//	if ((pRoot->p_left && !pRoot->p_right) || (!pRoot->p_left && pRoot->p_right)) return false;
//	isFullBST(pRoot->p_left);
//	isFullBST(pRoot->p_right);
//}
//
//int* dataInput(string filename, int& count) {
//	ifstream readFile;
//	int a[MAX], num;
//	readFile.open(filename);
//	if (readFile.fail()) return NULL;
//	while (!readFile.eof()) {
//		readFile >> num;
//		a[count++] = num;
//	}
//	readFile.close();
//	return a;
//}
//
//int main() {
//	int n = 0, *a;
//	a = dataInput("input.txt", n);
//
//	auto* pnode = createTree(a, n);
//
//	cout << "\n1. insert tree";
//	cout << "\n2. NLR, LNR, LRN";
//	cout << "\n3. delete node with key";
//	cout << "\n4. level other";
//	cout << "\n5. delete tree";
//	cout << "\n6. count node";
//	cout << "\n7. sum node";
//	cout << "\n8. height node";
//	cout << "\n9. level of node";
//	cout << "\n10. count leaf";
//	cout << "\n11. count less";
//	cout << "\n12. count greater";
//	cout << "\n13. is BST";
//	cout << "\n14. is full BST";
//	cout << "\n0. exit";
//
//	int choice = -1;
//
//	while (0 != choice) {
//		cout << "\n>> ";
//		cin >> choice;
//		switch (choice) {
//		case 1: {
//			int x;
//			cout << " key : "; cin >> x;
//			Insert(pnode, x);
//			break;
//		}
//		case 2: {
//			NLR(pnode);
//			cout << endl;
//			LNR(pnode);
//			cout << endl;
//			LRN(pnode);
//			cout << endl;
//			break;
//		}
//		case 3: {
//			int key;
//			cout << " key : "; cin >> key;
//			Remove(pnode, key);
//			break;
//		}
//		case 4: {
//			LevelOrder(pnode);
//			break;
//		}
//		case 5: {
//			removeTree(pnode);
//			break;
//		}
//		case 6: {
//			cout << countNode(pnode);
//			break;
//		}
//		case 7: {
//			  cout << sumNode(pnode);
//			  break;
//		}
//		case 8: {
//			int value;
//			cout << " value : "; cin >> value;
//			cout << heightNode(pnode, value);
//			break;
//		}
//		case 9: {
//			int x;
//			cout << " key : "; cin >> x;
//			cout << Level(pnode, createNode(x));
//			break;
//		}
//		case 10: {
//			cout << countLeaf(pnode);
//			break;
//		}
//		case 11: {
//			int x;
//			cout << " x : "; cin >> x;
//			cout << countLess(pnode, x);
//			break;
//		}
//		case 12: {
//			int x;
//			cout << " x : "; cin >> x;
//			cout << countGreater(pnode, x);
//			break;
//		}
//		case 13: {
//			cout << isBST(pnode);
//			break;
//		}
//		case 14: {
//			cout << isFullBST(pnode);
//			break;
//		}
//		case 0:
//			break;
//		}
//	}
//
//	return 1;
//}
