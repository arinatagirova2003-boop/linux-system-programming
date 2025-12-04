#include <iostream>
#include <cstdlib>
#include <cstring>
#include <pwd.h>
#include <grp.h>
#include <sys/stat.h>
#include <unistd.h>

using namespace std;

// Print information about a user
void printUserInfo(const char* username) {
    passwd* pw = getpwnam(username);
    if (!pw) {
        cerr << "User '" << username << "' not found." << endl;
        exit(EXIT_FAILURE);
    }

    cout << "User Information:\n";
    cout << "Username: " << pw->pw_name << endl;
    cout << "UID: " << pw->pw_uid << endl;
    cout << "GID: " << pw->pw_gid << endl;
    cout << "Home Directory: " << pw->pw_dir << endl;
    cout << "Login Shell: " << pw->pw_shell << endl;
}

// Print information about a file
void printFileInfo(const char* filename) {
    struct stat st {};
    if (stat(filename, &st) != 0) {
        perror("Error calling stat");
        exit(EXIT_FAILURE);
    }

    passwd* owner = getpwuid(st.st_uid);
    if (!owner) {
        perror("Failed to retrieve file owner name");
        exit(EXIT_FAILURE);
    }

    cout << "File Information:\n";
    cout << "Filename: " << filename << endl;
    cout << "Hard Links Count: " << st.st_nlink << endl;
    cout << "Owner UID: " << st.st_uid << endl;
    cout << "Group GID: " << st.st_gid << endl;
    cout << "File Size (bytes): " << st.st_size << endl;
    cout << "Owner Name: " << owner->pw_name << endl;
}

// Main entry point
int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " -u <username> or -f <filename>" << endl;
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "-u") == 0) {
        printUserInfo(argv[2]);
    }
    else if (strcmp(argv[1], "-f") == 0) {
        printFileInfo(argv[2]);
    }
    else {
        cerr << "Unknown parameter: " << argv[1] << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
