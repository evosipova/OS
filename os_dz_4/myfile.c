#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define BUF_SIZE 1024

int main(int argc, char *argv[]) {
    int fd_in, fd_out, nread;
    char buf[BUF_SIZE];
    mode_t mode;
    struct stat stat_buf;

    // Check that the correct number of arguments were passed in
    if (argc != 3) {
        printf("Usage: %s <input_file> <output_file>\n", argv[0]);
        exit(1);
    }

    // Open the input file for reading
    fd_in = open(argv[1], O_RDONLY);
    if (fd_in < 0) {
        perror("Error opening input file");
        exit(1);
    }

    // Get the access mode for the input file
    if (fstat(fd_in, &stat_buf) < 0) {
        perror("Error getting file status");
        exit(1);
    }
    mode = stat_buf.st_mode;

    // Open the output file for writing, with the same access mode as the input file
    fd_out = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, mode);
    if (fd_out < 0) {
        perror("Error opening output file");
        exit(1);
    }

    // Read from the input file, using a buffer of limited size
    while ((nread = read(fd_in, buf, BUF_SIZE)) > 0) {
        // Write to the output file
        if (write(fd_out, buf, nread) != nread) {
            perror("Error writing to output file");
            exit(1);
        }
    }

    // Check for errors during the read operation
    if (nread < 0) {
        perror("Error reading input file");
        exit(1);
    }

    // Close the files
    close(fd_in);
    close(fd_out);

    return 0;
}
