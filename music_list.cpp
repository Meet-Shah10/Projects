#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>

using namespace std;

struct song
{
    string name;
    struct song *next;
    struct song *prev;
};
class Playlist
{
private:
    struct song *current_song = nullptr;

public:
    void add(string song_name)
    {
        struct song *add;
        add = new song;
        add->name = song_name;
        add->next = add->prev = nullptr;
        if (!current_song)
        {
            current_song = add;
            current_song->next = current_song->prev = current_song;
        }
        else
        {
            struct song *last = current_song->prev;
            last->next = add;
            add->prev = last;
            add->next = current_song;
            current_song->prev = add;
        }
        cout << song_name << " added to the playlist." << "\n"
             << endl;
    }
    void Delete()
    {
        if (!current_song)
        {
            cout << "Playlist is empty!" << endl;
            return;
        }

        cout << "Deleted: " << current_song->name << "\n"
             << endl;

        if (current_song->next == current_song) // Only one song
        {
            delete current_song;
            current_song = nullptr;
        }
        else
        {
            song *nextsong = current_song->next;
            song *prevsong = current_song->prev;

            prevsong->next = nextsong;
            nextsong->prev = prevsong;

            delete current_song;
            current_song = nextsong;
        }
    }

    void playNext()
    {
        if (!current_song)
        {
            cout << "The Playlist is empty!" << endl;
            return;
        }
        current_song = current_song->next;
        cout << "Now Playing: " << current_song->name << "\n"
             << endl;
    }
    void playPrev()
    {
        if (!current_song)
        {
            cout << "The playlist is empty!" << endl;
            return;
        }
        current_song = current_song->prev;
        cout << "Now Playing : " << current_song->name << "\n"
             << endl;
    }
    void show_playlist()
    {
        if (!current_song)
        {
            cout << "The playlist is empty!" << endl;
            return;
        }
        song *temp;
        temp = current_song;
        do
        {
            cout << temp->name << endl;
            temp = temp->next;
        } while (temp != current_song);
    }
    void shuffle()
    {
        if (!current_song)
        {
            cout << "The playlist is empty!" << endl;
            return;
        }
        if (current_song->next == current_song)
        {
            cout << "Nothing to shuffle!" << endl;
            return;
        }
        vector<song *> songs;
        song *temp = current_song;

        do
        {
            songs.push_back(temp);
            temp = temp->next;
        } while (temp != current_song);

        auto rng = default_random_engine(static_cast<unsigned>(time(0)));
        std :: shuffle(songs.begin(), songs.end(), rng);

        int n = songs.size();
        for (int i = 0; i < n; ++i)
        {
            songs[i]->next = songs[(i + 1) % n];
            songs[i]->prev = songs[(i - 1 + n) % n];
        }
        current_song = songs[0];

        cout << "Playlist shuffled successfully!\n"
             << endl;
    }
};

int main()
{
    Playlist p;
    int c;
    string song_name;
    cout << "--------Music Playlisst Simulator--------" << endl;
    while (1)
    {
        cout << "1. Add song\n2.Delete current song\n3.Play next\n4.Play previous\n5.Shuffle Playlist\n6.Show Playlist\n7.Exit\nEnter your choice: ";
        cin >> c;
        cin.ignore();
        cout << "\n";
        switch (c)
        {
        case 1:
            cout << "Enter the song name: ";
            getline(cin, song_name);
            p.add(song_name);
            break;
        case 2:
            p.Delete();
            break;
        case 3:
            p.playNext();
            break;
        case 4:
            p.playPrev();
            break;
        case 5:
            p.shuffle();
            break;
        case 6:
            p.show_playlist();
            break;
        case 7:
            return 0;
        default:
            cout << "Please enter a valid choice." << endl;
            break;
        }
    }
}