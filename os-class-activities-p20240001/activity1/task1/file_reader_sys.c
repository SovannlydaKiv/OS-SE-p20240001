/* file_reader_sys.c */
#include <fcntl.h>    // open(), O_RDONLY
#include <unistd.h>   // read(), write(), close()

int main() {
    int fd = open("output.txt", O_RDONLY);
    if (fd == -1) {
        const char *err = "Error opening file\n";
        write(2, err, 19); 
        return 1;
    }

    char buffer[256];
    int bytesRead;
    while ((bytesRead = read(fd, buffer, sizeof(buffer))) > 0) {
        write(1, buffer, bytesRead);
    }

    close(fd);
    return 0;
}