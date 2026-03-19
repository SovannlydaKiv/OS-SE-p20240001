/* file_reader_sys.c */
#include <fcntl.h>    // open(), O_RDONLY
#include <unistd.h>   // read(), write(), close()

int main() {
    // 1. Open "output.txt" for reading
    int fd = open("output.txt", O_RDONLY);
    if (fd == -1) {
        const char *err = "Error opening file\n";
        write(2, err, 19);  // fd 2 = stderr
        return 1;
    }

    // 2 & 3. Read in a loop and write each chunk to terminal
    char buffer[256];
    int bytesRead;
    while ((bytesRead = read(fd, buffer, sizeof(buffer))) > 0) {
        write(1, buffer, bytesRead);
    }

    // 4. Close the file
    close(fd);
    return 0;
}