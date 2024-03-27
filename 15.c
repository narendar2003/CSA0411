#include <stdio.h>
#include <direct.h>

void createDirectory(const char *dirName) {
    if (_mkdir(dirName) != 0) {
        perror("Error creating directory");
        exit(EXIT_FAILURE);
    }
}

void createFile(const char *fileName) {
    FILE *file = fopen(fileName, "w");
    if (!file) {
        perror("Error creating file");
        exit(EXIT_FAILURE);
    }
    fclose(file);
}

int main() {
    const char* topLevelDir = "TopLevelDir";
    createDirectory(topLevelDir);

    _chdir(topLevelDir);

    const char* subDir1 = "SubDir1";
    const char* subDir2 = "SubDir2";

    createDirectory(subDir1);
    createDirectory(subDir2);

    createFile("SubDir1/File1.txt");
    createFile("SubDir1/File2.txt");
    createFile("SubDir2/File3.txt");

    printf("Files created successfully in the two-level directory structure.\n");

    return 0;
}
