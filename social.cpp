#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>

class Post {
private:
    std::string content;
    int likeCount;
    int commentCount;
    std::vector<std::string> comments;

public:
Post(const std::string& content, int likeCount, int commentCount, const std::vector<std::string>& comments)
    : content(content), likeCount(likeCount), commentCount(commentCount), comments(comments) {}

    Post(const std::string& content) : content(content), likeCount(0), commentCount(0) {}

    std::string getContent() const {
        return content;
    }

    int getLikeCount() const {
        return likeCount;
    }

    int getCommentCount() const {
        return commentCount;
    }

    const std::vector<std::string>& getComments() const {
        return comments;
    }

    void setLikeCount(int count) {
        likeCount = count;
    }

    void setCommentCount(int count) {
        commentCount = count;
    }

    void addComment(const std::string& comment) {
        comments.push_back(comment);
        commentCount++;
    }
};

class User {
private:
    std::string username;
    std::string password;
    std::vector<Post> posts;

public:
    User(const std::string& username, const std::string& password) : username(username), password(password) {}
    User(const std::string& username, const std::string& password, const std::vector<Post>& posts)
    : username(username), password(password), posts(posts) {}


    std::string getUsername() const {
        return username;
    }

    std::string getPassword() const {
        return password;
    }

    const std::vector<Post>& getPosts() const {
        return posts;
    }

    void createPost(const std::string& content) {
        posts.emplace_back(content);
    }

    void deletePost(int index) {
        if (index >= 0 && index < posts.size()) {
            posts.erase(posts.begin() + index);
        }
    }

    void likePost(int index) {
        if (index >= 0 && index < posts.size()) {
            Post& post = posts[index];
            post.setLikeCount(post.getLikeCount() + 1);
        }
    }

    void addComment(int index, const std::string& comment) {
        if (index >= 0 && index < posts.size()) {
            Post& post = posts[index];
            post.addComment(comment);
        }
    }

    void showTimeline() const {
        std::cout << "Timeline for user " << username << ":" << std::endl;
        for (const auto& post : posts) {
            std::cout << "Content: " << post.getContent() << std::endl;
            std::cout << "Likes: " << post.getLikeCount() << std::endl;
            std::cout << "Comments: " << post.getCommentCount() << std::endl;
            const auto& comments = post.getComments();
            for (const auto& comment : comments) {
                std::cout << " - " << comment << std::endl;
            }
            std::cout << std::endl;
        }
    }
};

void saveUserToFile(const User& user) {
    std::ofstream file(user.getUsername() + ".txt");
    if (file.is_open()) {
        file << user.getUsername() << std::endl;
        file << user.getPassword() << std::endl;

        for (const auto& post : user.getPosts()) {
            file << post.getContent() << std::endl;
            file << post.getLikeCount() << std::endl;
            file << post.getCommentCount() << std::endl;

            const auto& comments = post.getComments();
            for (const auto& comment : comments) {
                file << comment << std::endl;
            }
        }

        file.close();
        std::cout << "User data saved to file." << std::endl;
    } else {
        std::cout << "Error: Unable to open file." << std::endl;
    }
}

User loadUserFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cout << "Failed to open file: " << filename << std::endl;
        return User("", ""); // Return a default User object
    }

    std::string username, password;
    getline(file, username);
    getline(file, password);

    std::vector<Post> posts;
    std::string line;
    while (getline(file, line)) {
        std::string content = line;
        int likeCount, commentCount;
        file >> likeCount;
        file >> commentCount;
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::vector<std::string> comments;
        for (int i = 0; i < commentCount; i++) {
            std::string comment;
            getline(file, comment);
            comments.push_back(comment);
        }

        Post post(content, likeCount, commentCount, comments);
        posts.push_back(post);
    }

    return User(username, password, posts);
}



int main() {
    int choice;
    std::cout << "1. Login" << std::endl;
    std::cout << "2. Signup" << std::endl;
    std::cout << "Enter your choice: ";
    std::cin >> choice;

    if (choice == 1) {
        std::string username, password;
        std::cout << "Enter username: ";
        std::cin >> username;

        std::cout << "Enter password: ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        getline(std::cin, password);
        User user = loadUserFromFile(username);
        if (user.getPassword() == password) {
            while (true) {
                std::cout << std::endl;
                std::cout << "1. Create post" << std::endl;
                std::cout << "2. Delete post" << std::endl;
                std::cout << "3. Like post" << std::endl;
                std::cout << "4. Comment on post" << std::endl;
                std::cout << "5. Show timeline" << std::endl;
                std::cout << "6. Logout" << std::endl;
                std::cout << "Enter your choice: ";
                std::cin >> choice;

                switch (choice) {
                    case 1: {
                        std::string content;
                        std::cout << "Enter post content: ";
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        getline(std::cin, content);
                        user.createPost(content);
                        saveUserToFile(user);
                        break;
                    }
                    case 2: {
                        int index;
                        std::cout << "Enter post index to delete: ";
                        std::cin >> index;
                        user.deletePost(index);
                        saveUserToFile(user);
                        break;
                    }
                    case 3: {
                        int index;
                        std::cout << "Enter post index to like: ";
                        std::cin >> index;
                        user.likePost(index);
                        saveUserToFile(user);
                        break;
                    }
                    case 4: {
                        int index;
                        std::string comment;
                        std::cout << "Enter post index to comment on: ";
                        std::cin >> index;
                        std::cout << "Enter comment: ";
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        getline(std::cin, comment);
                        user.addComment(index, comment);
                        saveUserToFile(user);
                        break;
                    }
                    case 5:
                        user.showTimeline();
                        break;
                    case 6:
                        std::cout << "Logging out." << std::endl;
                        return 0;
                    default:
                        std::cout << "Invalid choice." << std::endl;
                        break;
                }
            }
        } else {
            std::cout << "Invalid password." << std::endl;
        }
    } else if (choice == 2) {
        std::string username, password;
        std::cout << "Enter username: ";
        std::cin >> username;
        std::cout << "Enter password: ";
        std::cin >> password;

        User user(username, password);
        saveUserToFile(user);
    } else {
        std::cout << "Invalid choice." << std::endl;
    }

    return 0;
}
