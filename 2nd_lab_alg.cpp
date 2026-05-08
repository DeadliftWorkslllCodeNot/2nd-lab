#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct { //струкртура трека
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

void del(Playlist* playlist) {
	
}

void shuffle() {}

void repeat_one() {}

void repeat_all() {}

void main() {

}
/*Добавление трека
Удаление трека
Перемешивание(shuffle)
Повтор(repeat one / repeat all)*/
