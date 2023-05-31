#include <bits/stdc++.h>
using namespace std;
class Post
{
private:
    string content;
    int likeCount;
    int commentCount;
    vector<string> comments;

public:
    Post(const string &content, int likeCount, int commentCount, const vector<string> &comments)
        : content(content), likeCount(likeCount), commentCount(commentCount), comments(comments) {}

    Post(const string &content) : content(content), likeCount(0), commentCount(0) {}

    string getContent() const
    {
        return content;
    }

    int getLikeCount() const
    {
        return likeCount;
    }

    int getCommentCount() const
    {
        return commentCount;
    }

    const vector<string> &getComments() const
    {
        return comments;
    }

    void setLikeCount(int count)
    {
        likeCount = count;
    }

    void setCommentCount(int count)
    {
        commentCount = count;
    }

    void addComment(const string &comment)
    {
        comments.push_back(comment);
        commentCount++;
    }
};
class User
{
private:
    string username;
    string password;
    vector<Post> posts;
    vector<string> friends;

public:
    User(const string &username, const string &password) : username(username), password(password) {}
    User(const string &username, const string &password, const vector<Post> &posts)
        : username(username), password(password), posts(posts) {}

    User(const string &username, const string &password, const vector<Post> &posts, const vector<string> &friends)
        : username(username), password(password), posts(posts), friends(friends) {}

    string getUsername() const
    {
        return username;
    }

    string getPassword() const
    {
        return password;
    }

    const vector<Post> &getPosts() const
    {
        return posts;
    }

    void createPost(const string &content)
    {
        posts.emplace_back(content);
    }

    void deletePost(int index)
    {
        if (index >= 0 && index < posts.size())
        {
            posts.erase(posts.begin() + index);
        }
    }

    void likePost(int index)
    {
        if (index >= 0 && index < posts.size())
        {
            Post &post = posts[index];
            post.setLikeCount(post.getLikeCount() + 1);
        }
    }

    void addComment(int index, const string &comment)
    {
        if (index >= 0 && index < posts.size())
        {
            Post &post = posts[index];
            post.addComment(comment);
        }
    }
    void addFriend(string username)
    {
        friends.push_back(username);
    }
    const vector<string> &getFriends() const
    {
        return friends;
    }
    friend void showTimeline(User u)
    {
        cout << "Timeline for user " << u.username << ":" << endl;
        for (const auto &post : u.posts)
        {
            cout << "Content: " << post.getContent() << endl;
            cout << "Likes: " << post.getLikeCount() << endl;
            cout << "Comments: " << post.getCommentCount() << endl;
            const auto &comments = post.getComments();
            for (const auto &comment : comments)
            {
                cout << " - " << comment << endl;
            }
            cout << endl;
        }
    }
    
    void showFriends()
    {
        for (string fren : friends)
            cout << fren << " ";
        cout << endl;
    }
    void timeline();
};

void saveUserToFile(const User &user)
{
    ofstream file("users/" + user.getUsername() + ".txt");
    if (file.is_open())
    {
        // username aar password file e dilo
        file << user.getUsername() << endl;
        file << user.getPassword() << endl;
        // friend list file e dilo
        for (string fren : user.getFriends())
        {
            file << fren << " ";
        }
        file << endl;
        // post sob file e dilo
        for (const auto &post : user.getPosts())
        {
            file << post.getContent() << endl;
            file << post.getLikeCount() << endl;
            file << post.getCommentCount() << endl;

            const auto &comments = post.getComments();
            for (const auto &comment : comments)
            {
                file << comment << endl;
            }
        }

        file.close();
        cout << "User data saved to file." << endl;
    }
    else
    {
        cout << "Error: Unable to open file." << endl;
    }
}

User loadUserFromFile(const string &filename)
{
    ifstream file("users/" + filename + ".txt");
    if (!file)
    {
        cout << filename << "not found"<<endl;
        return User("", ""); // Return a default User object
    }

    string username, password;
    getline(file, username);
    getline(file, password);
    vector<string> friends;
    string frenstring;
    getline(file, frenstring);
    string fren;
    for (int i = 0; i <= frenstring.size(); i++)
    {
        if (frenstring[i] == ' ' || frenstring[i] == '\n')
        {
            friends.push_back(fren);
            fren = "";
        }
        else
            fren += frenstring[i];
    }

    vector<Post> posts;
    string line;
    while (getline(file, line))
    {
        string content = line;
        int likeCount, commentCount;
        file >> likeCount;
        file >> commentCount;
        file.ignore(numeric_limits<streamsize>::max(), '\n');

        vector<string> comments;
        for (int i = 0; i < commentCount; i++)
        {
            string comment;
            getline(file, comment);
            comments.push_back(comment);
        }

        Post post(content, likeCount, commentCount, comments);
        posts.push_back(post);
    }

    return User(username, password, posts, friends);
}
void User::timeline(){
        for(string fren:friends){
            User u = loadUserFromFile(fren);
            showTimeline(u);
        }
    }

int main()
{
    int choice;
    cout << "1. Login" << endl;
    cout << "2. Signup" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 1)
    {
        string username, password;
        cout << "Enter username: ";
        cin >> username;

        cout << "Enter password: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, password);
        User user = loadUserFromFile(username);
        if (user.getPassword() == password)
        {
            while (true)
            {
                cout << endl;
                cout << "1. Create post" << endl;
                cout << "2. Delete post" << endl;
                cout << "3. Like post" << endl;
                cout << "4. Comment on post" << endl;
                cout << "5. Show timeline" << endl;
                cout << "6. Add friend " << endl;
                cout<< "7. Show friend"<<endl;
                cout << "8. Logout" << endl;
                cout << "Enter your choice: ";
                cin >> choice;

                switch (choice)
                {
                case 1:
                {
                    string content;
                    cout << "Enter post content: ";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    getline(cin, content);
                    user.createPost(content);
                    saveUserToFile(user);
                    break;
                }
                case 2:
                {
                    int index;
                    cout << "Enter post index to delete: ";
                    cin >> index;
                    user.deletePost(index);
                    saveUserToFile(user);
                    break;
                }
                case 3:
                {
                    int index;
                    cout << "Enter post index to like: ";
                    cin >> index;
                    user.likePost(index);
                    saveUserToFile(user);
                    break;
                }
                case 4:
                {
                    int index;
                    string comment;
                    cout << "Enter post index to comment on: ";
                    cin >> index;
                    cout << "Enter comment: ";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    getline(cin, comment);
                    user.addComment(index, comment);
                    saveUserToFile(user);
                    break;
                }
                case 5:
                    user.timeline();
                    break;
                case 8:
                    cout << "Logging out." << endl;
                    return 0;
                case 6:
                {
                    cout << "Enter friend name: ";
                    string s;
                    cin >> s;
                    user.addFriend(s);
                    saveUserToFile(user);
                    break;
                }
                case 7:{
                    cout<<"Friend list "<<endl;
                    for(string fren:user.getFriends()){
                        cout<<fren<<endl;
                    }
                    break;
                }
                default:
                    cout << "Invalid choice." << endl;
                    break;
                }
            }
        }
        else
        {
            cout << "Invalid password." << endl;
        }
    }
    else if (choice == 2)
    {
        string username, password;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        User user(username, password);
        saveUserToFile(user);
    }
    else
    {
        cout << "Invalid choice." << endl;
    }

    return 0;
}
