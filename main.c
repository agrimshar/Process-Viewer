#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
    printf("%5s CMD\n", "PID");
    
    // Open the /proc directory
    DIR *proc = opendir("/proc");

    if (proc == NULL) {
        //perror("Couldn't open /proc");
        exit(EXIT_FAILURE);    
    }

    // Read the /proc directory
    struct dirent *process;
    while ((process = readdir(proc)) != NULL) {
        // Skip the current and parent directories
        // if (strcmp(process->d_name, ".") == 0 || strcmp(process->d_name, "..") == 0) {
        //     continue;
        // }

        // Get the PID
        int pid = atoi(process->d_name);

        // Open the /proc/PID/status file
        char path[256];
        int j = snprintf(path, sizeof(path), "/proc/%d/status", pid);

        if (j < 0) {
            //perror("Couldn't create /proc/PID/status path");
            continue;
        }

        int status = open(path, O_RDONLY);

        if (status == -1) {
            //perror("Couldn't open /proc/PID/status");
            continue;
        }

        // Read the process name
        char buffer[256];
        ssize_t bytes = read(status, buffer, sizeof(buffer));

        if (bytes == -1) {
            //perror("Couldn't read /proc/PID/status");
            close(status);
            continue;
        }

        // Print the PID and the process name
        buffer[bytes] = '\0';
        char *name = strstr(buffer, "Name:");
        if (name != NULL) {
            name += 6;
            while (*name == ' ') {
                name++;
            }

            // Extract the process name
            char *end = strchr(name, '\n');
            if (end == NULL) {
                end = strchr(name, '\0');
            }

            printf("%5d ", pid);

            for (char *c = name; c < end; c++) {
                putchar(*c);
            }

            printf("\n");
        }

        // Close the /proc/PID/status file
        close(status);
    }

    // Close the /proc directory
    closedir(proc);

    return 0;
}
