#ifdef __linux__
#include "drv_linux_term.h"

static struct termios old_tio, new_tio;

void linuxTermInit(void)
{
    int c;

    // Get the current terminal settings
    tcgetattr(STDIN_FILENO, &old_tio);

    // Copy settings to a new structure
    new_tio = old_tio;

    // Disable canonical mode (ICANON) and echoing (ECHO)
    new_tio.c_lflag &= ~(ICANON | ECHO);

    // Set VMIN (min characters for read) to 1, VTIME (timeout) to 0
    new_tio.c_cc[VMIN] = 1;
    new_tio.c_cc[VTIME] = 0;

    // Apply the new settings immediately
    tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);

#if 0
    while ((c = getchar()) != EOF) {
        // Process character immediately
        putchar(c);
        fflush(stdout); // Ensure immediate output

        if (c == 3) { // Ctrl+C ASCII value
            break;
        }
    }
#endif
}

void linuxTermRestore(void)
{
    // Restore original terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);
}

#endif /* __linux__ */
