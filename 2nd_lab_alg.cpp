#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct { 
	char name[50];
	int duration;
	char genre[50];
	float rating;
}Track;

typedef struct { //узел
	Track track;
	Node* pre;
	Node* next;
}Node;

typedef struct {
	Node* head;
	Node* tail;
	Node* curr;
	//repeat
	//shuffle
	int size;
}Playlist;

void Playlist_init(Playlist* playlist) {
	playlist->head = NULL;
	playlist->tail = NULL;
	playlist->curr = NULL;
	playlist->size = 0;
}

Track create_one(char* name, int dur, char* genre, float rating) {
	Track new_t;
	strcpy_s(new_t.name, sizeof(new_t.name)-1, name);
	new_t.name[sizeof(new_t) - 1] = '\0';
	new_t.duration = dur;
	strcpy_s(new_t.genre, sizeof(new_t.genre)-1, genre);
	new_t.name[sizeof(new_t) - 1] = '\0';
	new_t.rating = rating;
	return new_t;
}

Node* create_Node(Track track) {
	Node* new_N = (Node*)malloc(sizeof(Node));
	if (!new_N) {
		printf("Creating error");
		return NULL;
	}
	new_N->track = track;
	new_N->pre = NULL;
	new_N->next = NULL;
	return new_N;
}

void add_to_end(Playlist* playlist, Track track){
	Node* new_Node = create_Node(track);
	if (!new_Node) return;
	
	if (playlist == NULL) {
		playlist->head = new_Node;
		playlist->tail = new_Node;
		playlist->curr = new_Node;
	}
	else{
		new_Node->pre = playlist->tail;
		playlist->tail->next = new_Node;
		playlist->tail = new_Node;
	}
	playlist->size++;
	printf("New track %s is added to playlist", track.name);
}

void add_after_curr(Playlist* playlist, Track track) {
	if (playlist->curr == NULL) {
		add_to_end(playlist, track);
		return;
	}
	Node* new_Node = create_Node(track);
	if (!new_Node) return;

	new_Node->pre = playlist->curr;
	new_Node->next = playlist->curr->next;

	if (playlist->curr->next != NULL) {
		playlist->curr->next->pre = new_Node;
	}
	else {
		playlist->tail = new_Node;
	}
	playlist->curr->next = new_Node;
	playlist->size++;

	printf("New track %s is added to playlist after curr one", track.name);
}

	void delete_from_start() {

		if (head == nullptr) {
			cout << "Playlist is empty!" << endl;
			return;
		}

		Node* ptr_del = head;
		string del_name = ptr_del->data.get_name();

		head = head->next;

		if (head != nullptr) {
			head->pre = nullptr;
		}
		else {
			tail = nullptr;  
			curr = nullptr;
		}
		if (ptr_del == curr) {
			curr = head;
		}
		delete ptr_del;
		size--;
		cout << "Track \"" << del_name << "\" was successfully deleted from start!" << endl;
		cout << endl;
	}

	void del_from_end() {
		if (tail == nullptr) {
			cout << "Playlist is empty!" << endl;
			return;
		}

		Node* ptr_del = tail;
		string del_name = ptr_del->data.get_name();
		tail = tail->pre;

		if (tail != nullptr) {
			tail->next = nullptr;
		}
		else { head = nullptr; }
		if (ptr_del == curr) {
			curr =tail;
		}
		delete ptr_del;
		size--;
		cout << "Track \"" << del_name << "\" was successfully deleted from end!" << endl;
		cout << endl;
	}

void shuffle() {
		if (size <= 1) {
			cout << "Only one track in Playlist!" << endl;
			return;
		}
		Node* curr = head;
		while (curr!=nullptr) {
			Node* randomtr = head;
			int rand_idx = rand() % size;
			for (int i = 0; i < rand_idx; i++) {
				randomtr = randomtr->next;
			}
			Track temp = curr->data;
			curr->data = randomtr->data;
			randomtr->data = temp;
			curr = curr->next;
		}
	}

	void settings_mode() {
		int mode;
		cout << "Choose the mode: " << endl << "1. No Repeat   2. One track repeat   3. All tracks repeat   ";
		cin >> mode;
		switch (mode) {
		case 1: {
			repmode = no_rep;
			cout << "Repeat mode: OFF" << endl;
			break;
		}
		case 2: {
			repmode = one_rep;
			cout << "Repeat mode: One track" << endl;
			break;
		}
		case 3: {
			repmode = all_rep;
			cout << "Repeat mode: All tracks" << endl;
			break;
		}
		}
	}

	Node* next_to_play() {
		if (curr == nullptr) { return nullptr; }
		switch (repmode) {
		case no_rep: 
		case one_rep: { return curr;}
		case all_rep:{
			if (curr->next == nullptr) {
				cout << "Repeating playlist from start";
				return head;
			}
			return curr->next;
		}
		}
		return curr->next;
	}

	void get_rep_info() {
		Node* next_one = next_to_play();
		cout << "Now playing:" << endl;
		curr->data.print_info();

		if (repmode != one_rep) curr->next = next_one;

		if (repmode == one_rep) {
			cout << "Repeating this track" << endl;
		}
		else if (repmode == all_rep && curr->next == nullptr) {
			cout << "Last track - will loop to start" << endl;
		}
	}



