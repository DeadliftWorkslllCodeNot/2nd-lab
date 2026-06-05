#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

class Track {
private:
    string name;
    string auther;
    string genre;
    int duration; // в секундах
    double rating;

public:
    Track(string n = "", string a = "", string g = "", int d = 0, double r = 0) {
        name = n;
        auther = a;
        genre = g;
        duration = d;
        rating = r;
    }

    string get_name() const { return name; }
    string get_auther() const { return auther; }
    string get_genre() const { return genre; }
    int get_dur() const { return duration; }
    double get_rat() const { return rating; }

    void set_name(string n) { name = n; }
    void set_auther(string a) { auther = a; }
    void set_genre(string g) { genre = g; }
    void set_dur(int d) { duration = d; }
    void set_rat(double r) { rating = r; }

    void print_info() {
        cout << "\"" << name << "\" " << auther << " [" << genre << "] "
             << "(" << duration / 60 << ":" << (duration % 60 < 10 ? "0" : "") << duration % 60 << ") "
             << "r: " << rating << endl;
    }
};

class Node {
public:
    Track data;
    Node* pre;
    Node* next;

    Node(Track track) {
        data = track;
        pre = nullptr;
        next = nullptr;
    }
};

class Playlist {
private:
    int size;
    Node* head;
    Node* curr;
    Node* tail;
    enum RepMode { no_rep, one_rep, all_rep };
    RepMode repmode;

public:
    Playlist() {
        head = nullptr;
        curr = nullptr;
        tail = nullptr;
        size = 0;
        repmode = no_rep;
    }

    Node* add_1st(Track track) {
        Node* ptr = new Node(track);

        if (head == nullptr) {
            head = curr = tail = ptr;
        } else {
            ptr->next = head;
            head->pre = ptr;
            head = ptr;
        }
        size++;
        cout << "Track \"" << track.get_name() << "\" was successfully added to Playlist start!" << endl;
        cout << endl;
        return ptr;
    }

    Node* add_last(Track track) {
        Node* ptr = new Node(track);

        if (tail == nullptr) {
            tail = head = curr = ptr;
        } else {
            tail->next = ptr;
            ptr->pre = tail;
            tail = ptr;
        }
        size++;
        cout << "Track \"" << track.get_name() << "\" was successfully added to Playlist end!" << endl;
        cout << endl;
        return ptr;
    }

    Node* add_after_curr(Track track) {
        Node* ptr = new Node(track);

        if (curr == nullptr) {
            cout << "No curr track. Track'll be added to end" << endl;
            return add_last(track);
        }

        ptr->pre = curr;
        ptr->next = curr->next;

        if (curr->next != nullptr) {
            curr->next->pre = ptr;
        } else {
            tail = ptr;
        }

        curr->next = ptr;
        size++;
        cout << "Track \"" << track.get_name() << "\" was successfully added to Playlist after \"" 
             << curr->data.get_name() << "\"" << endl;
        cout << endl;
        return ptr;
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
        } else {
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
        } else {
            head = nullptr;
            curr = nullptr;
        }
        if (ptr_del == curr) {
            curr = tail;
        }
        delete ptr_del;
        size--;
        cout << "Track \"" << del_name << "\" was successfully deleted from end!" << endl;
        cout << endl;
    }

    void show() {
        if (head == nullptr) {
            cout << "Playlist is empty!" << endl;
            return;
        }

        auto print_sep = []() {
            cout << "|----|----------------------|----------------------|----------------------|-------|--------|" << endl;
        };

        print_sep();
        printf("| %-2s | %-20s | %-20s | %-20s | %-5s | %-6s |\n", 
               "No", "Name", "Auther", "Genre", "Time", "Rating");
        print_sep();

        Node* current = head;
        int num = 1;
        while (current != nullptr) {
            int minutes = current->data.get_dur() / 60;
            int seconds = current->data.get_dur() % 60;
            printf("| %-2d | %-20s | %-20s | %-20s | %02d:%02d | %-6.2f |\n",
                   num++,
                   current->data.get_name().c_str(),
                   current->data.get_auther().c_str(),
                   current->data.get_genre().c_str(),
                   minutes, seconds,
                   current->data.get_rat());
            current = current->next;
        }
        print_sep();
        cout << endl;
    }

    void shuffle() {
        if (size <= 1) {
            cout << "Only one track in Playlist!" << endl;
            return;
        }

        srand(time(nullptr));
        
        Node** arr = new Node*[size];
        Node* current = head;
        for (int i = 0; i < size; i++) {
            arr[i] = current;
            current = current->next;
        }

        for (int i = size - 1; i > 0; i--) {
            int j = rand() % (i + 1);
            Track temp = arr[i]->data;
            arr[i]->data = arr[j]->data;
            arr[j]->data = temp;
        }

        delete[] arr;
        cout << "Playlist shuffled!" << endl;
        cout << endl;
    }

    void search_tracks_for_time() {
        if (head == nullptr) {
            cout << "Playlist is empty!" << endl;
            return;
        }

        int min, max;
        cout << "Tracks with duration (put minutes diaposon in way: min - max): ";
        cin >> min >> max;

        Node* current = head;
        int found = 0;
        int num = 1;
		auto print_sep = []() {
            cout << "|----|----------------------|----------------------|----------------------|-------|--------|" << endl;
        };

        print_sep();
        printf("| %-2s | %-20s | %-20s | %-20s | %-5s | %-6s |\n", 
               "No", "Name", "Auther", "Genre", "Time", "Rating");
        print_sep();

        while (current != nullptr) {
            int dur_sec = current->data.get_dur();
            if (dur_sec >= min * 60 && dur_sec <= max * 60) {
                found++;
                int minutes = dur_sec / 60;
                int seconds = dur_sec % 60;
                printf("| %-2d | %-20s | %-20s | %-20s | %02d:%02d | %-6.2f |\n",
                       num,
                       current->data.get_name().c_str(),
                       current->data.get_auther().c_str(),
                       current->data.get_genre().c_str(),
                       minutes, seconds,
                       current->data.get_rat());
            }
            current = current->next;
            num++;
        }
        print_sep();

        if (found == 0) {
            cout << "No tracks with such duration" << endl;
        } else {
            cout << "Found " << found << " track(s)" << endl;
        }
        cout << endl;
    }

    void settings_mode() {
        int mode;
        cout << "Choose the mode: " << endl 
             << "1. No Repeat   2. One track repeat   3. All tracks repeat   ";
        cin >> mode;
        switch (mode) {
        case 1:
            repmode = no_rep;
            cout << "Repeat mode: OFF" << endl;
            break;
        case 2:
            repmode = one_rep;
            cout << "Repeat mode: One track" << endl;
            break;
        case 3:
            repmode = all_rep;
            cout << "Repeat mode: All tracks" << endl;
            break;
        default:
            cout << "Invalid mode, keeping current" << endl;
        }
        cout << endl;
    }

    Node* next_to_play() {
        if (curr == nullptr) { return nullptr; }
        switch (repmode) {
        case no_rep:
            return curr->next;
        case one_rep:
            return curr;
        case all_rep:
            if (curr->next == nullptr) {
                cout << "Repeating playlist from start" << endl;
                return head;
            }
            return curr->next;
        }
        return curr->next;
    }

    void get_rep_info() {
        if (curr == nullptr) {
            cout << "No track playing" << endl;
            return;
        }
        
        cout << "Now playing:" << endl;
        curr->data.print_info();

        if (repmode == one_rep) {
            cout << "Repeating this track" << endl;
        } else if (repmode == all_rep && curr->next == nullptr) {
            cout << "Last track - will loop to start" << endl;
        }
    }

    void set_curr(Node* node) {
        curr = node;
    }

    Node* get_head() { return head; }
    Node* get_tail() { return tail; }
    Node* get_curr() { return curr; }
    int get_size() { return size; }
};


   
    return 0;
}
