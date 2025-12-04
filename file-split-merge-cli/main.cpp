#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>
#include <cstring>
#include <cstdlib>

void splitFile(const char* inputFile, const char* out1, const char* out2, const char* out3, const char* out4) {
    int in_fd = open(inputFile, O_RDONLY);
    if (in_fd == -1) {
        perror("Failed to open input file");
        exit(EXIT_FAILURE);
    }

    off_t totalSize = lseek(in_fd, 0, SEEK_END);
    lseek(in_fd, 0, SEEK_SET);

    off_t partSize = totalSize / 4;
    off_t remainder = totalSize % 4;

    const char* outs[4] = { out1, out2, out3, out4 };
    off_t sizes[4] = { partSize, partSize, partSize, partSize + remainder };

    char buffer[4096];
    for (int i = 0; i < 4; ++i) {
        int out_fd = open(outs[i], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
        if (out_fd == -1) {
            perror("Failed to create output file");
            exit(EXIT_FAILURE);
        }

        off_t bytesLeft = sizes[i];
        while (bytesLeft > 0) {
            ssize_t toRead = std::min(bytesLeft, (off_t)sizeof(buffer));
            ssize_t bytesRead = read(in_fd, buffer, toRead);
            if (bytesRead <= 0) break;

            write(out_fd, buffer, bytesRead);
            bytesLeft -= bytesRead;
        }
        close(out_fd);
    }

    close(in_fd);
    std::cout << "Splitting completed successfully.\n";
}

void mergeFiles(const char* in1, const char* in2, const char* in3, const char* in4, const char* outputFile) {
    int out_fd = open(outputFile, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (out_fd == -1) {
        perror("Failed to create output file");
        exit(EXIT_FAILURE);
    }

    const char* ins[4] = { in1, in2, in3, in4 };
    char buffer[4096];

    for (int i = 0; i < 4; ++i) {
        int in_fd = open(ins[i], O_RDONLY);
        if (in_fd == -1) {
            perror("Failed to open input part file");
            exit(EXIT_FAILURE);
        }

        ssize_t bytesRead;
        while ((bytesRead = read(in_fd, buffer, sizeof(buffer))) > 0) {
            write(out_fd, buffer, bytesRead);
        }

        close(in_fd);
    }

    close(out_fd);
    std::cout << "Merging completed successfully.\n";
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage:\n"
            << argv[0] << " split input_file part1 part2 part3 part4\n"
            << argv[0] << " merge part1 part2 part3 part4 output_file\n";
        return 1;
    }

    std::string cmd = argv[1];

    if (cmd == "split" && argc == 7) {
        splitFile(argv[2], argv[3], argv[4], argv[5], argv[6]);
    }
    else if (cmd == "merge" && argc == 7) {
        mergeFiles(argv[2], argv[3], argv[4], argv[5], argv[6]);
    }
    else {
        std::cerr << "Invalid arguments.\n";
        return 1;
    }

    return 0;
}
