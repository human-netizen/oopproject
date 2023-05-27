# Social Media Application

This is a simple social media application implemented in C++. It allows users to create posts, delete posts, like posts, and add comments to posts. Users can also view their timeline to see all the posts they have created.

## Features

- User authentication: Users can login or signup with their username and password.
- Create post: Users can create a new post by providing the content.
- Delete post: Users can delete a post by specifying the post index.
- Like post: Users can like a post by specifying the post index.
- Comment on post: Users can add comments to a post by specifying the post index and providing the comment.
- Show timeline: Users can view their timeline to see all the posts they have created.

## Getting Started

To get started with this application, follow these steps:

1. Clone the repository:

git clone https://github.com/human-netizen/oopproject.git

2. Compile the source code:

g++ social.cpp -o social

3. Run the application:

./social

## Usage

1. Login or Signup: Upon running the application, you will be prompted to login or signup with your username and password.

2. Menu Options: Once logged in, you will see a menu with the following options:

- Create post: Create a new post by providing the content.
- Delete post: Delete a post by specifying the post index.
- Like post: Like a post by specifying the post index.
- Comment on post: Add a comment to a post by specifying the post index and providing the comment.
- Show timeline: View your timeline to see all the posts you have created.
- Logout: Logout from the application.

3. Perform Actions: Choose the desired option from the menu and follow the prompts to perform the corresponding action.

4. Save and Load: User data is automatically saved to a file with the username as the filename. The data can be loaded upon login to retrieve the previous state.

