#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void type_text(const char *text, int delay_ms)
{
    for (int i = 0; text[i] != '\0'; i++) {
        putchar(text[i]);
        usleep(delay_ms * 1000);
    }
}

void flicker_text(const char *text, int times)
{
    for (int i = 0; i < times; i++) {
        printf("\033[?25l");  // Hide cursor
        printf("\033[2J");    // Clear screen
        printf("\033[H");     // Move to top-left
        usleep(100000);       // 100ms delay
        
        printf("\033[31m%s\033[0m", text);  // Red text
        usleep(50000);        // 50ms delay
        
        printf("\033[2J");    // Clear screen
        printf("\033[H");     // Move to top-left
        usleep(30000);        // 30ms delay
    }
    
    // Final display
    printf("\033[31m%s\033[0m", text);
    printf("\033[?25h");      // Show cursor again
}

void baner() {

    const char *horror_banner = 
	"\033[1;31m"
		"\n"
		"    ███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗"
		"\033[38;5;196m\n"
		"    ████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║"
		"\033[38;5;160m\n"
		"    ██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║"
		"\033[38;5;124m\n"
		"    ██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║"
		"\033[38;5;88m\n"
		"    ██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗"
		"\033[38;5;52m\n"
		"    ╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝"
		"\033[38;5;16m\n"
		"\n"
		"\033[0m";
        
    const char *creepy_messages[] = {
        "\033[31mYour terminal is bleeding...\033[0m",
        "\033[31mWelcome to the depths of your system...\033[0m",
        "\033[31mEvery command has consequences...\033[0m",
        "\033[31mDo you trust this shell?\033[0m",
        "\033[31mListen carefully, the system is whispering...\033[0m"
    };

    printf("\033[2J");
    printf("\033[H");
    printf("\033[?25l");

    type_text("\033[31mInitializing system access...\033[0m\n", 30);
    usleep(500000);
    type_text("\033[31mBreaching security protocols...\033[0m\n", 30);
    usleep(500000);
    type_text("\033[31mAccess granted. Welcome to the nightmare...\033[0m\n", 30);
    usleep(1000000);

    printf("\033[2J");
    printf("\033[H");

    flicker_text(horror_banner, 3);

    printf("\n");
    int random_msg = rand() % 5;
    type_text(creepy_messages[random_msg], 50);
    printf("\n\n");

    printf("\033[31m╔══[root@nightmare]—[/dev/null]\n");
    printf("╚═\033[5m♱\033[0m\033[31m> \033[0m");

    printf("\033[?25h");

}

void while_baner()
{
	printf("\033[31m╔══[root@nightmare]—[/dev/null]\n");
    printf("╚═\033[5m♱\033[0m\033[31m> \033[0m");
}