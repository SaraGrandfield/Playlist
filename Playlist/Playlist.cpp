// Playlist.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
using namespace std;

int idnum = 0;
class Playlist;
class Song;
int Menu(Playlist &myPlaylist);

class Song
{
protected:
	string artist;
	string title;
	int id;
	Song *next;
public:
	Song(string a, string t)
	{
		artist = a;
		title = t;
		id = idnum++;
		next = NULL;
	}
	friend class Playlist;
	friend ostream& operator<<(ostream& os, const Song& dt);
};

ostream& operator<<(ostream& os, const Song& dt)
{
	os << dt.title << ", " << dt.artist;
	return os;
}

class Playlist
{
	Song *head;
	Song *tail;

public:
	Song *current;
	Playlist()
	{
		head = NULL;
		tail = NULL;
		current = NULL;
	}
	void skip() 
	{
		//IF current is tail go back to head
		if (current == tail)
		{
			current = head;
			return;
		}
		else
		current = current->next;
		return;
	};
	void play() 
	{
		char an;
		cout << *current << endl;
		cout << "Continue? Y/N:";
		cin >> an;
		if (an == 'Y' || an == 'y')
		{
			skip();
			play();
		}
		else if (an == 'N' || an == 'n')
		{
			return;
		}
		else
			cout << "Invalid response" << endl;
	};
	int deleteS() 
	{
		char ans;
		int i = current->id;
		Song *ptr = head;
		cout << "Are you sure wish to delete " << *current << " ?Y/N:";
		cin >> ans;
		if (ans=='n'||ans=='N')
		{
			return -1;
		}


		if (ptr == NULL)  // empty list
			return -1;

		// if node is at the head
		if (head->id == i)
		{
			//if only 1 node in the list
			if (head == tail)
			{
				head = NULL;
				tail = NULL;
			}
			else
				head = head->next;
			delete ptr;
			current = head;
			return 0;
		}

		while (ptr != NULL)
		{
			if (ptr->next && (ptr->next)->id == i)
			{
				if (tail == ptr->next)
					tail = ptr;
				Song *tbd = ptr->next;
				ptr->next = (ptr->next)->next;
				current = tbd->next;
				delete tbd;
				return 0;
			}
			ptr = ptr->next;
		}
		return -1;
	};
	void addSong(Song *newSong)
	{
		// if list is empty
		if (head == NULL)
		{
			head = newSong;
			tail = newSong;
		}
		else
		{
			tail->next = newSong;
			tail = newSong;
		}
	};
	void getPlaylist() 
	{
		string tittle;
		string artist;
		string fileName;

		cout << "Please Enter a Full File Path for the Playlist you Would Like to open:" << "\n";
		cin >> fileName;
		ifstream datafile(fileName);
		if (!datafile)
		{
			cerr << "ERROR: could not open file" << endl;
			return;
		}

		// read data from file
		while (!datafile.eof())
		{
			getline(datafile, artist, ',');
			getline(datafile, tittle);
			addSong(new Song(artist, tittle));
		}
		datafile.close();
		current = head;
	};

	void showsPlaylist() 
	{
		int x = 1;
		Song *ptr;
		ptr = head;
		cout << "****  PlayList Contents *****" << endl;
		if (ptr == NULL)
		{
			cout << "list is empty " << endl;
			return;
		}
		cout << "(First Song is " << *head << " Last Song is " << *tail << ")" << endl;
		while (ptr != NULL)
		{
			cout << x <<". " << *ptr << endl;
			ptr = ptr->next;
			x++;
		}
	};

};

int main()
{
	Playlist myPlaylist;
	myPlaylist.getPlaylist();
	while (Menu(myPlaylist) != 4)
	{
		Menu(myPlaylist);
	}

	
    return 0;
}

int Menu(Playlist &myPlaylist)
{
	bool invalid = true;
	string start = "Please Input just the Number of the action you would like to Perform : \n 1. Play \n 2. Skip \n 3. Delete \n 4. Exit";
	//Main menu powered by cases and a while loop, DOES NOT perfectly catch errors breaks if user types a char or string instead of a number
	int choice;
	while (invalid != false)
	{
		cout << "The current Song is " << *myPlaylist.current << "." << endl;
		cout << start << endl;
		cin >> choice;

		switch (choice)
		{
		case 1:
			myPlaylist.play();
			return 1;
		case 2:
			myPlaylist.skip();
			return 2;
		case 3:
			myPlaylist.deleteS();
			return 3;
		case 4:
			cout << "End of Program.\n";
			return 4;
		default:
			cout << "Not a Valid Choice. \n";
			cout << "Choose again.\n";
			cin >> choice;
			break;
		}
	}
}

