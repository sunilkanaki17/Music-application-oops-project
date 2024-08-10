#include <bits/stdc++.h>

using namespace std;

// Base class for User
class User {
protected:
    string username;
    string password; // In a real application, use proper encryption

public:
    User(const string& uname, const string& pwd) : username(uname), password(pwd) {}

    string getUsername() const { return username; }

    bool checkPassword(const string& pwd) const {
        return password == pwd;
    }
};


// Utility function to trim whitespace from both ends of a string
string trim(const string& str) {
    size_t first = str.find_first_not_of(' ');
    if (first == string::npos)
        return "";
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

// Function to validate password strength
bool isPasswordStrong(const string& password) {
    if (password.length() < 8) return false;
    bool hasUpper = false, hasLower = false, hasDigit = false, hasSymbol = false;
    for (char ch : password) {
        if (isupper(ch)) hasUpper = true;
        else if (islower(ch)) hasLower = true;
        else if (isdigit(ch)) hasDigit = true;
        else hasSymbol = true;
    }
    return hasUpper && hasLower && hasDigit && hasSymbol;
}

// Song class to store song details
class Song {
public:
    string name;
    string language;
    string genre;
    string artist;
    string album;
    string duration;
    string lyrics;
    string rating;

    Song(const vector<string>& details) {
        if (details.size() == 8) {
            name = details[0];
            language = details[1];
            genre = details[2];
            artist = details[3];
            album = details[4];
            duration = details[5];
            lyrics = details[6];
            rating = details[7];
        }
    }

    void displayLyrics() const {
        cout << "Lyrics of " << name << ":\n" << lyrics << endl;
    }

    void displayDetails() const {
        cout << "Song: " << name << ", Language: " << language << ", Genre: " << genre
             << ", Artist: " << artist << ", Album: " << album << ", Rating: " << rating << endl;
    }
};

// Base class for FileHandler
class FileHandler {
protected:
    string filename;

public:
    FileHandler(const string& file) : filename(file) {}

    virtual vector<Song> readSongs() {
        vector<Song> songs;
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Error opening " << filename << "\n";
            return songs;
        }

        string line;
        vector<string> details;
        while (getline(file, line)) {
            details.push_back(trim(line));
            if (details.size() == 8) {
                songs.push_back(Song(details));
                details.clear();
            }
        }
        file.close();
        return songs;
    }

    virtual ~FileHandler() = default;
};


// MusicLibrary class
class MusicLibrary {
private:
    FileHandler* fileHandler;
    vector<Song> songs;

public:
    MusicLibrary(FileHandler* handler) : fileHandler(handler) {
        songs = fileHandler->readSongs();
    }

    void knowLyrics() {
        string songName;
        cout << "Enter the song name to know the lyrics: ";
        cin.ignore();
        getline(cin, songName);

        bool found = false;
        for (const auto& song : songs) {
            if (trim(song.name) == trim(songName)) {
                song.displayLyrics();
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Song not found.\n";
        }
    }

    void knowSongsAvailable() {
        cout << "Available songs:\n";
        for (const auto& song : songs) {
            cout << song.name << endl;
        }
    }

    void knowTotalNumberOfSongs() {
        cout << "Total number of songs: " << songs.size() << endl;
    }

    void getArtistsNames() {
        set<string> artists;
        for (const auto& song : songs) {
            artists.insert(trim(song.artist));
        }

        cout << "Artists:\n";
        for (const auto& artist : artists) {
            cout << artist << endl;
        }
    }

    void getAlbumNames() {
        set<string> albums;
        for (const auto& song : songs) {
            albums.insert(trim(song.album));
        }

        cout << "Albums:\n";
        for (const auto& album : albums) {
            cout << album << endl;
        }
    }

    void getPlaylistDetails() {
        string language;
        cout << "Enter the language to filter songs: ";
        cin.ignore();
        getline(cin, language);

        bool found = false;
        for (const auto& song : songs) {
            if (trim(song.language) == trim(language)) {
                song.displayDetails();
                found = true;
            }
        }

        if (!found) {
            cout << "No songs found in " << language << " language.\n";
        }
    }

    void searchByArtist() {
        search("artist");
    }

    void searchByName() {
        search("name");
    }

    void searchByRating() {
        search("rating");
    }
    
    void searchByGenre() {
        search("genre");
    }

private:
    void search(const string& criteria) {
        string query;
        cout << "Enter the " << criteria << " to search: ";
        cin.ignore();
        getline(cin, query);

        bool found = false;
        for (const auto& song : songs) {
            if ((criteria == "artist" && trim(song.artist) == trim(query)) ||
                (criteria == "name" && trim(song.name) == trim(query)) ||
                (criteria == "rating" && trim(song.rating) == trim(query)) ||
                (criteria == "genre" && trim(song.genre) == trim(query))) {
                song.displayDetails();
                found = true;
            }
        }

        if (!found) {
            cout << "No songs found with " << criteria << " " << query << endl;
        }
    }
};

// MusicManager class to manage user interactions
class MusicManager {
private:
    vector<User*> users; // Vector to store users
    User* currentUser; // Pointer to current user
    MusicLibrary musicLibrary; // Instance of MusicLibrary

public:
    MusicManager(FileHandler* handler) : currentUser(nullptr), musicLibrary(handler) {}

    ~MusicManager() {
        for (auto user : users) {
            delete user;
        }
    }

    void run() {
        bool running = true;
        while (running) {
            if (currentUser) {
                cout << "Logged in as: " << currentUser->getUsername() << endl;
            } else {
                cout << "Not logged in.\n";
            }

            displayMenu();

            int choice;
            cin >> choice;

            if (currentUser) {
                handleLoggedInChoice(choice, running);
            } else {
                handleLoggedOutChoice(choice, running);
            }
        }
    }

private:
    void displayMenu() {
        cout << "===== Main Menu =====\n";
        if (currentUser) {
            cout << "1. Log Out\n";
            cout << "2. Know the lyrics\n";
            cout << "3. Know the songs available\n";
            cout << "4. Know the total number of songs\n";
            cout << "5. Get artist names\n";
            cout << "6. Get album names\n";
            cout << "7. Get playlists details\n";
            cout << "8. Search\n";
            cout << "9. Exit\n";
            cout << "Enter your choice: ";
        } else {
            cout << "1. Sign Up\n";
            cout << "2. Log In\n";
            cout << "3. Exit\n";
            cout << "Enter your choice: ";
        }
    }

    void handleLoggedInChoice(int choice, bool& running) {
        switch (choice) {
            case 1: {
                currentUser = nullptr;
                cout << "User logged out successfully!\n";
                break;
            }
            case 2: {
                musicLibrary.knowLyrics();
                break;
            }
            case 3: {
                musicLibrary.knowSongsAvailable();
                break;
            }
            case 4: {
                musicLibrary.knowTotalNumberOfSongs();
                break;
            }
            case 5: {
                musicLibrary.getArtistsNames();
                break;
            }
            case 6: {
                musicLibrary.getAlbumNames();
                break;
            }
            case 7: {
                musicLibrary.getPlaylistDetails();
                break;
            }
            case 8: {
                displaySearchMenu();
                break;
            }
            case 9: {
                cout << "Exiting...\n";
                running = false;
                break;
            }
            default:
                cout << "Invalid choice.\n";
                break;
        }
    }

    void displaySearchMenu() {
        cout << "Search by:\n";
        cout << "1. Artist\n";
        cout << "2. Name\n";
        cout << "3. Rating\n";
        cout << "4. Genre\n";
        cout << "Enter your choice: ";
        int searchChoice;
        cin >> searchChoice;
        switch (searchChoice) {
            case 1:
                musicLibrary.searchByArtist();
                break;
            case 2:
                musicLibrary.searchByName();
                break;
            case 3:
                musicLibrary.searchByRating();
                break;
            case 4:
                musicLibrary.searchByGenre();
                break;
            default:
                cout << "Invalid choice.\n";
                break;
        }
    }

    void handleLoggedOutChoice(int choice, bool& running) {
        switch (choice) {
            case 1: {
                string username, password;
                cout << "Enter username: ";
                cin >> username;
                while (true) {
                    cout << "Enter password (at least 8 characters, including one symbol, one digit, one uppercase and one lowercase letter): ";
                    cin >> password;
                    if (isPasswordStrong(password)) {
                        break;
                    } else {
                        cout << "Password is too weak. Please try again.\n";
                    }
                }
                users.push_back(new User(username, password));
                cout << "User signed up successfully!\n";
                break;
            }
            case 2: {
                string username, password;
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter password: ";
                cin >> password;
                auto it = find_if(users.begin(), users.end(), [&username, &password](User* user) {
                    return user->getUsername() == username && user->checkPassword(password);
                });
                if (it != users.end()) {
                    currentUser = *it;
                    cout << "User logged in successfully!\n";
                } else {
                    cout << "Invalid username or password!\n";
                }
                break;
            }
            case 3: {
                cout << "Exiting...\n";
                running = false;
                break;
            }
            default:
                cout << "Invalid choice.\n";
                break;
        }
    }
};

void printWelcomeMessage() {
    cout << "*******************************************************************************\n";
    cout << "*                                                                             *\n";
    cout << "*                      WELCOME TO THE MUSIC PLAYER                     *\n";
    cout << "*                                                                             *\n";
    cout << "*                   Your music, your way. Enjoy the best of Music.           *\n";
    cout << "*                                                                             *\n";
    cout << "*******************************************************************************\n\n";
}

// Main function
int main() {
    printWelcomeMessage();
    FileHandler* fileHandler = new FileHandler("songs_file.txt");  //constructor with argument passed
    MusicManager manager(fileHandler); //constructor with argument passed
    manager.run();
    delete fileHandler;
    return 0;
}
