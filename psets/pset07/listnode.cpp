/*
*  On my honor, I pledge that I have neither received nor provided improper assistance in my completion on this assignment.
*  Signed: Kim Woo Bin   Student Number: 21600124
*/

#include <iomanip>
#include <cstdlib>
#include <stack>
#include "listnode.h"

#if 0
// a basic stack functinality only provided for pedagogical purpose
// To use STL stack, just comment out this section and inclucde <stack> above.
#include <vector>
template <typename T>
struct stack {
	vector<T> data;

	bool empty() const {
		return data.empty();
	}
	auto size() const {
		return data.size();
	}
	void push(T const& item) {
		data.push_back(item);
	}
	void pop() {
		if (data.empty())
			throw out_of_range("stack<>::pop(): pop stack");
		data.pop_back();
	}
	T top() const {
		if (data.empty())
			throw out_of_range("stack<>::top(): top stack");
		return data.back();
	}
};
#endif

// and leaving the container nullptr or its size to 0.
pNode clear(pNode p) {
	if (empty(p)) return nullptr;
	DPRINT(cout << "clear: ";);

	pNode curr = p;
	while (curr != nullptr) {
		pNode prev = curr;
		curr = curr->next;
		DPRINT(cout << prev->data << " ";);
		delete prev;
	}
	cout << "\n\tAll things are cleared. Happy Coding!\n";
	return nullptr;
}

int size(pNode p) {
	if (empty(p)) return 0;
	int count = 0;
	for (pNode c = p; c != nullptr; c = c->next, count++);
	return count;
}

pNode last(pNode p) {
	if (empty(p)) return nullptr;
	while (p->next != nullptr) p = p->next;
	return p;
}

bool empty(pNode p) {
	return p == nullptr;
}

Node* push_front(Node* p, int val) {
	DPRINT(cout << "><push_front val=" << val << endl;);
	if (empty(p)) return new Node{ val };
	return new Node{ val, p };
}

pNode push_back(pNode p, int val) {
	DPRINT(cout << "><push_back val=" << val << endl;);
	pNode head = p;
	if(empty(p)) return new Node{val, nullptr};
	while(p -> next != nullptr)
		p = p -> next;
	p -> next = new Node{val, nullptr};;
	return head;
}

pNode push(pNode p, int val, int x) {
	if (empty(p)) return push_front(p, val);
	if (p->data == x) return push_front(p, val);
	pNode curr = p;
	pNode prev = nullptr;
	while(curr -> data != x){
		prev = curr;
		curr = curr -> next;
		if(curr == nullptr) return p;
	}
	prev -> next = new Node{ val, curr };
	return p;
}

unsigned long rand_extended(int range) {
	if (range < RAND_MAX) return rand();
	return rand() * RAND_MAX + rand();
}

Node* push_frontN(Node* p, int N) {
	DPRINT(cout << ">push_front N = " << N << endl;);

	int range = N + size(p);
	srand((unsigned)time(nullptr));

	for(int i = 0; i < N; i++){
		p = push_front(p, rand_extended(rand()) % range);
	}

	DPRINT(cout << "<push_front N = " << N << endl;);
	return p;
}

pNode push_backN(pNode p, int N) {
	DPRINT(cout << ">push_backN N=" << N << " RAND_MAX=" << RAND_MAX << endl;);

	int range = N + size(p);
	srand((unsigned)time(NULL));

	for(int i = 0; i < N; i++){
		p = push_back(p, rand_extended(rand()) % range);
	}

	DPRINT(cout << "<push_backN size=" << size(p) << endl;);
	return p;
}

Node* push_N(Node* p, int N, Node* (*push_fp)(Node*, int)) {
	DPRINT(cout << ">push_N = " << N << endl;);

	int range = N + size(p);
	srand((unsigned)time(nullptr));

	for(int i = 0; i < N; i++){
		p = push_fp(p, rand_extended(rand()) % range);
	}

	DPRINT(cout << "<push_N = " << N << endl;);
	return p;
}

pNode pop_front(pNode p) {
	DPRINT(cout << ">pop_front size=" << size(p) << endl;);
	if(empty(p)) return nullptr;
	pNode zap = p;
	p = p -> next;
	delete zap;
	return p;
}

pNode pop_back(pNode p) {
	DPRINT(cout << ">pop_back size=" << size(p) << endl;);
	if(empty(p)) return nullptr;
	if(size(p) == 1) return pop_front(p);
	pNode curr = p;
	pNode prev = nullptr;
	while(curr -> next != nullptr){
		prev = curr;
		curr = curr -> next;
	}
	prev -> next = nullptr;
	delete curr;
	DPRINT(cout << "<pop_back size=" << size(p) << endl;);
	return p;
}

pNode pop_backN(pNode p, int N) {
	DPRINT(cout << ">pop_backN N=" << N << endl;);

	int psize = size(p);
	if (N <= 0 || N > psize) N = psize;
	for (int i = 0; i < N; i++) {
		if (i % 1000 == 0 || i < 1000)
			cout << setw(7) << "\r\tpoping[" << psize - i - 1 << "]            ";
		p = pop_back(p);
	}
	cout << "\n";

	DPRINT(cout << "<pop_backN size=" << size(p) << endl);
	return p;
}

Node* pop_frontN(Node* p, int N) {
	DPRINT(cout << ">pop_frontN N=" << N << endl;);

	int psize = size(p);
	if (N <= 0 || N > psize) N = psize;
	for (int i = 0; i < N; i++) {
		if (i % 1000 == 0 || i < 1000)
			cout << setw(7) << "\r\tpoping[" << psize - i - 1 << "]            ";
		p = pop_front(p);
	}
	cout << "\n";

	DPRINT(cout << "<pop_backN size=" << size(p) << endl);
	return p;
}

Node* pop_N(Node* p, int N, Node* (*pop_fp)(Node*)) {
	DPRINT(cout << ">pop_N N=" << N << endl;);

	int psize = size(p);
	if (N <= 0 || N > psize) N = psize;
	for (int i = 0; i < N; i++) {
		if (i % 1000 == 0 || i < 1000)
			cout << setw(7) << "\r\tpoping[" << psize - i - 1 << "]            ";
		p = pop_fp(p);
	}
	cout << "\n";

	DPRINT(cout << "<pop_N size=" << size(p) << endl);
	return p;
}

pNode pop(pNode p, int val) {
	DPRINT(cout << ">pop val=" << val << endl;);
	if (empty(p)) return nullptr;    // nothing to delete
	if (p->data == val) return pop_front(p);
	pNode curr = p;
	pNode prev = nullptr;
	while(curr -> data != val){
		prev = curr;
		curr = curr -> next;
	}
	prev -> next = curr -> next;
	delete curr;
	DPRINT(cout << "<pop size=" << size(p) << endl;);
	return p;
}

Node* reverse_using_stack(Node* head) {
	if (empty(head)) return nullptr;
	stack<Node*> s;
	Node* curr = head;

		while(curr -> next != nullptr){
			s.push(curr);
			curr = curr -> next;
		}
		head = curr;
		while(!s.empty()){
			curr -> next = s.top();
			s.pop();
			curr = curr -> next;
		}
		curr -> next = nullptr;

	return head;
}

Node* reverse_in_place(Node* head) {
	if (empty(head)) return nullptr;    // nothing to reverse
	Node* prev = nullptr;
	Node* curr = head;

	while(head != nullptr){
		curr = head -> next;
		head -> next = prev;
		prev = head;
		head = curr;
	}
	return prev;
}

Node* reverse_odd2(Node* head) {
	DPRINT(cout << ">reverse_odd2 begins.\n";);
	if (empty(head)) return nullptr;
	stack<int> ostack;      // odd_stack to save odds temporarily
	Node* head1 = head;     // save the original head to clear later
	Node* head2 = nullptr;  // new list of odds reversed

	while (head != nullptr) {
		if (head->data % 2 == 1) {
			DPRINT(cout << " stack push: " << head->data << endl;);
			ostack.push(head -> data);
			head = head -> next;
			continue;
		}

		while (!ostack.empty()) {
			DPRINT(cout << " head2 push_back(stack): " << ostack.top() << endl;);
			head2 = push_back(head2, ostack.top());
			ostack.pop();
		}
		DPRINT(cout << " head2 push_back(head): " << head->data << endl;);
		head2 = push_back(head2, head -> data);
		head = head -> next;
	}
	DPRINT(cout << " original list all scanned\n";);
	DPRINT(cout << " odds stack size = " << ostack.size() << endl;);

	while(!ostack.empty()){
		head2 = push_back(head2, ostack.top());
		ostack.pop();
	}

	clear(head);
	DPRINT(cout << "<reverse_odd2 returns.\n";);
	return head2;
}

// reverses elements in sub-lists of odd numbers using stack only.
// It does not create new nodes, but recycles the original nodes of
// the list and relink them appropriately. It maintains the head2 node as
// well as tail2 node such that it can relink the existing node at the
// back(or tail) in O(1), while scanning the original list once.
Node* reverse_oddn(Node* head) {
	DPRINT(cout << ">reverse_oddn begins.\n";);
	if (empty(head)) return nullptr;

	stack<Node*> ostack;
	Node* head2 = nullptr;  // new list head of odds reversed
	Node* tail2 = nullptr;  // the last element of head2 list
	while (head != nullptr) {
		if (head->data % 2 == 1) {
			DPRINT(cout << "Case Odd, stack push " << head->data << endl;);
			ostack.push(head);
			head = head -> next;
			continue;
		}

		while (!ostack.empty()) {
			if(head2 == nullptr){
				head2 = ostack.top();
				tail2 = ostack.top();
			}
			// tail2 ?-----------------------------------------------
			tail2 -> next = ostack.top();
			tail2 = tail2 -> next;
			ostack.pop();
			DPRINT(cout << " head2 push_back(stack): " << ostack.top() << endl;);
		}
		if(head2 == nullptr){
			head2 = head;
			tail2 = head;
			head = head -> next;
			continue;
		}
		// tail2 ?-----------------------------------------------
		tail2 -> next = head;
		tail2 = tail2 -> next;
		head = head -> next;
		DPRINT(cout << " head2 push_back(head): " << head->data << endl;);
	}

	while(!ostack.empty()){
		tail2 -> next = ostack.top();
		tail2 = tail2 -> next;
		ostack.pop();
	}
	tail2 -> next = nullptr;
	DPRINT(cout << "<reverse_oddn returns.\n";);
	return head2;
}

void show(pNode p, bool all, int show_n) {
	DPRINT(cout << "show(" << size(p) << ")\n";);
	if (empty(p)) {
		cout << "\n\tThe list is empty.\n";
		return;
	}
	int i;
	pNode curr;
	const int N = size(p);

	if (all || N < show_n * 2) {
		for (i = 1, curr = p; curr != nullptr; curr = curr->next, i++) {
			cout << " -> " << curr->data;
			if (i % show_n == 0) cout << endl;
		}
		return;
	}

	// print the first show_n items
	for (i = 0, curr = p; i < show_n ; curr = curr->next, i++) {
		cout << " -> " << curr->data;
	}

	cout << "\n...left out...\n";
	// print the last show_n items
	// move the pointer to the place where show_n items are left.
	for( i = 0; i < N - (show_n * 2); i++){ curr = curr -> next;}

	while(curr != nullptr){
		cout << " -> " << curr->data;
		curr = curr -> next;
	}

	cout << "\n";
	return;
}
