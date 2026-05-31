# Лабораторная работа №2

**Выполнила:** Пермякова Екатерина Алексеевна, ИДБ-25-02

---

## О проекте

Система управления музыкальным плейлистом с использованием двусвязного списка.


## Содержание
- [Структура данных](#Структура-данных)
- [Архитектура классов](#Архитектура-классов)
- [Функционал](#Функционал)

## Структура данных

При реализации кода использован двусвязный список в связи с:

### Эффективность вставки и удаления

| Операция | Двусвязный список | Массив |
|----------|-------------------|--------|
| Вставка в начало |	O(1)	| O(n) |
| Вставка в конец |	O(1) |	O(1)* |
| Вставка после текущего |	O(1) | O(n) |
| Удаление из начала | O(1) |	O(n) |
| Удаление из конца	| O(1) |	O(1) |

> В плейлисте: пользователь часто добавляет/удаляет треки в разных позициях → список эффективнее.

## Архитектура классов

### _Track_
Базовый класс, хранящий информацию о треках.
```cpp
class Track {
private:
	string name, auther, genre;
	int duration; //sec
	double rating;

public:
	Track(string n="", string a="", string g="", int d=0, double r=0) {
		name = n; auther = a; genre = g; duration = d; rating = r;
	}

	string get_name() const { return name; }
	string get_auther() const { return auther; }
	string get_genre() const { return genre; }
	int get_dur() const { return duration; }
	double get_rat() const { return rating; }
	
	void print_info() {
		cout <<"\"" << name << "\" " << auther << " [" << genre << "] "
			 <<" (" << duration / 60 << ":" << duration % 60 << ") " 
			 << " r: "<< rating<<endl;
	}
};

```

### _Node_
Элемент двусвязного списка.
```cpp
    class Node {
public:
	Track data;
	Node* pre, * next;

	Node(Track track){
		data = track;
		pre = next = nullptr;
	}
};
```

### _Playlist_
Основной класс управления.
```cpp
   class Playlist {
private:
	int size;
	Node* head, * curr, * tail;
	enum RepMode {no_rep, one_rep, all_rep};
	RepMode repmode;

public:
   Playlist();
   Node* add_1st(Track track);
   Node* add_after_curr(Track track);
   Node* add_last(Track track);
   void delete_from_start();
   void del_from_end();
   void show();
   void shuffle();
   void search_tracks_for_time();
   void settings_mode();
   Node* next_to_play();
   void get_rep_info();
};
```

### _RepMode_ (Режим повтора)
Перечисление возможных режимов воспроизведения.
```cpp
enum RepMode {no_rep, one_rep, all_rep};
RepMode repmode;
```

## Функционал

### Обязательная часть
- [Добавление ( в начало/конец/после текущего )](#-Добавление-трека)
- [Удаление (с начала/конца )](#-Удаление)
- [Алгоритм перемешивания (shuffle)](#-Алгоритм-перемешивания-(shuffle))
- [Повтор ( 3 режима: нет/один/все )](#-Повтор)

### Дополнительная часть
- [Вывод в табличном формате](#-Вывод)
- [Поиск по длительности](#-Поиск)


## Добавление

###  _в начало_
```cpp
    Node* add_1st(Track track) {
	Node* ptr = new Node(track);
	
	if (head == nullptr) {
		head = curr = tail = ptr;
	}
	else {
		ptr->next = head;
		head->pre = ptr;
		head = ptr;
	}
	size++;
	cout << "Track \"" << track.get_name() << "\" was successfully added to Playlist start!" << endl;
	return ptr;
	cout << endl;
}
```
### _в конец_

``` cpp
	Node* add_last(Track track) {
		Node* ptr = new Node(track);
		
		if (tail == nullptr) {
			tail = head = curr = ptr;
		}
		else {
			tail->next = ptr;
			ptr->pre = tail;
			tail = ptr;
		}
		size++;
		cout << "Track \"" << track.get_name() << "\" was successfully added to Playlist end!" << endl;
		cout << endl;

		return ptr;
	}

```
### _после текущего_
```cpp
	Node* add_after_curr(Track track){
		Node* ptr = new Node(track);

		if (curr == nullptr) {
			cout << "No curr track. Track'll be added to end" << endl;
			add_last(track);
		}

		ptr->pre = curr;
		ptr->next = curr->next;

		if(curr->next!=nullptr) {
			curr->next -> pre = ptr;
		}
		else {
			tail = ptr;
		}

		curr->next = ptr;

		cout << "Track \"" << track.get_name() << "\" was successfully added to Playlist after \""<< curr->data.get_name() <<"\"" << endl;
		size++;
		return ptr;
		cout << endl;
	}

```

## Удаление

### _с начала_
```cpp
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

```
### _с конца_
```cpp
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

```

## Алгоритм перемешивания (shuffle)
```cpp
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

```
## Повтор
### _Логика повтора (repeat)_
| Режим |	Поведение |
|-------|-------------|
| no_rep|	Обычное последовательное воспроизведение|
|one_rep|	Бесконечное повторение текущего трека|
|all_rep|	Циклическое воспроизведение (после последнего → первый)|

```cpp
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

```

## Вывод 
### _Пример_

| No | Name | Auther | Genre | Time | Rating |
|----|------|--------|-------|------|--------|
| 1 | Für Elise | Beethoven | Classical | 186 | 4.95 |
| 2 | Moonlight Sonata | Beethoven | Classical | 412 | 5.00 |
| 3 | Take Five | Dave Brubeck | Jazz | 324 | 4.90 |
| 4 | Summertime | Ella Fitzgerald | Jazz | 275 | 4.85 |
| 5 | Canon in D | Pachelbel | Classical | 301 | 4.75 |
| 6 | Fly Me To The Moon | Frank Sinatra | Jazz | 157 | 4.80 |

## Поиск
```cpp
	void search_tracks_for_time() {

		Node* curr = head;
		int found = 0;
		int num = 1;

		int min, max;
		cout << "Tracks with durration (puts minutes diaposon in way: min - max): ";
		cin >> min >> max;
		first_line();
		header();
		sep_line();
		while (curr != nullptr) {
			
			if (curr->data.get_dur() >= min*60 && curr->data.get_dur() <= max*60) {
				found++;
				//записываем в таблицу {...}
				if (curr->next!=nullptr && found>1) {
					int more = 0;
					if (curr->next->data.get_dur() >= min && curr->next->data.get_dur() <= max) {
						more = 1;
						break;
					}
					curr->next = curr->next->next;
					if (more) {
						sep_line();
					}
					
				}
			}
			curr = curr->next;
			num++;
		}
		last_line();
		if (head == nullptr) { cout << "Playlist is empty!" << endl; return; }
		if (found == 0) { cout << "No tracks with such duration" << endl; return; }
	}

```

