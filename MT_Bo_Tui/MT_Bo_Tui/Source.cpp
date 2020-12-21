#include<iostream>
#include<cmath>
#include<string>
#include<vector>

using namespace std;


class Stack {
private:
	vector<string> _data;
public:
	Stack() { }

	bool push(const string& element) {
		_data.push_back(element);
		return true;
	}

	bool pop() {
		if (_data.empty()) {
			cout << " Stack is empty";
			return false;
		}
		else _data.pop_back();
		return true;
	}

	bool pop(string& element) {
		if (_data.empty()) {
			cout << " Stack is empty";
			return false;
		}
		else {
			element = _data.back();
			_data.pop_back();
		}
		return true;
	}

	string top() { if (!_data.empty()) return _data.back(); }

	bool isEmpty() { return _data.size() == 0; }

	int size() { return _data.size(); }

};

class Queue {
private:
	vector<string> _data;
public:
	Queue() { }

	bool push(const string& element) {
		_data.push_back(element);
		return true;
	}

	bool pop() {
		if (_data.empty()) {
			cout << " Queue is empty";
			return false;
		}
		else _data.erase(_data.begin());

		return true;
	}

	bool pop(string& element) {
		if (_data.empty()) {
			cout << " Queue is empty";
			return false;
		}
		else {
			element = _data.front();
			_data.erase(_data.begin());
		}
		return true;
	}

	string front() { if (!_data.empty()) return _data.front(); }

	string rear() { if (!_data.empty()) return _data.back(); }

	bool isEmpty() { return _data.size() == 0; }

	int size() { return _data.size(); }

};

bool isOperator(const string& s) { return (s == "+" || s == "-" || s == "*" || s == "/"); }

int priority(const string& c) {
	if (c == "(" || c == ")") return 0;
	if (c == "+" || c == "-") return 1;
	if (c == "*" || c == "/") return 2;
	else return -1;
}

bool isValid(string& s, Queue qInput) {
	Queue q, qTemp = qInput;
	int countOpen = 0, countClose = 0, countNumber = 0, countOperator = 0;

	while (!qTemp.isEmpty()) {
		if (isOperator(qTemp.front())) countOperator++;
		else countNumber++;
		qTemp.pop();
	}

	if (countOperator >= countNumber) return false;

	for (auto i : s) {
		if (i == ')') countClose++;
		else if (i == '(') countOpen++;
	}
	if (countOpen == countClose) {
		if (s[0] == ')' || s[0] == '+' || s[0] == '-' || s[0] == '*' || s[0] == '/') return false;
		else if (s[s.length() - 1] == '+' || s[s.length() - 1] == '-' || s[s.length() - 1] == '*' || s[s.length() - 1] == '/') return false;
		else {
			for (auto i : s) {
				string temp(1, i);
				if (q.isEmpty()) q.push(temp);
				else {
					if ((q.rear() == "(") && (i == ')' || i == '+' || i == '-' || i == '*' || i == '/')) return false;
					else q.push(temp);
				}
			}
		}
	} else return false;

	return true;
}

void handleInput(string input) {
	Stack s;
	Queue q;

	for (int j = 0; j < input.length(); j++) {
		if (isdigit(input[j])) {
			int k = 0;
			while (isdigit(input[j + k])) { k++; }
			q.push(input.substr(j, k));
			j += k - 1;
		}
		else {
			if (s.isEmpty()) {
				string temp(1, input[j]);
				s.push(temp);
			}
			else {
				if (input[j] == '(') {
					string temp(1, input[j]);
					s.push(temp);
				}
				else if (input[j] == ')') {
					while (s.top() != "(") {
						q.push(s.top());
						s.pop();
					}
					s.pop();
				}
				else {
					string temp(1, input[j]);
					if ((priority(s.top()) >= priority(temp)) && !s.isEmpty()) {
						q.push(s.top());
						s.pop();
						j = j - 1;
					}
					else s.push(temp);
				}
			}
		}
	}

	while (!s.isEmpty()) {
		q.push(s.top());
		s.pop();
	}

	if (!isValid(input, q)) cout << "Syntax eror";
	else {
		Stack s2;
		string num_1, num_2;
		double res;

		while (q.size() > 0) {
			if (!isOperator(q.front())) {
				s2.push(q.front());
				q.pop();
			}
			else {
				if (q.front() == "+") {
					q.pop();
					num_1 = s2.top();
					s2.pop();
					num_2 = s2.top();
					s2.pop();
					res = stod(num_2) + stod(num_1);
					s2.push(to_string(res));
				}
				else if (q.front() == "-") {
					q.pop();
					num_1 = s2.top();
					s2.pop();
					num_2 = s2.top();
					s2.pop();
					res = stod(num_2) - stod(num_1);
					s2.push(to_string(res));
				}
				else if (q.front() == "*") {
					q.pop();
					num_1 = s2.top();
					s2.pop();
					num_2 = s2.top();
					s2.pop();
					res = stod(num_2) * stod(num_1);
					s2.push(to_string(res));
				}
				else if (q.front() == "/") {
					q.pop();
					num_1 = s2.top();
					s2.pop();
					num_2 = s2.top();
					s2.pop();
					res = stod(num_2) / stod(num_1);
					s2.push(to_string(res));
				}
			}
		}
		cout << s2.top();
		s2.pop();
	}
}

int main() {

	string Input;

	rewind(stdin);
	getline(cin, Input);

	handleInput(Input);
	
	return 1;
}