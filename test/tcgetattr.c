
#include <stdio.h>
#include <termios.h>
#include <unistd.h>

int main() {
    struct termios oldt, newt;
    char c;

    // Récupérer les paramètres du terminal
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    // Désactiver le mode canonique et l'affichage des caractères
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    printf("Tapez du texte (Ctrl+C pour quitter) :\n");

    while (read(STDIN_FILENO, &c, 1) > 0) {
        printf("%c\n", c);
    }

    // Restaurer les paramètres du terminal
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return 0;
}

