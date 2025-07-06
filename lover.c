#include "minishell.h"


void shy_emoji_banner() {
    const char *shy_emoji = 
        "\033[1;96m"  // Cyan moderne
        "\n"
        "        > <"
        "\n"
        "         ᵕ"
        "\n"
        "   I LOVE YOU TOO\n\n\033[0m";
    
    printf("%s", shy_emoji);
}