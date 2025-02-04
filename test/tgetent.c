#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <term.h>

// compile gcc tgetent.c -o test -lreadline -lncurses
int main() {
    char buffer[2048]; // Buffer pour stocker l'entrée de tgetent
    int status;
    int col;
    int line;


    // Récupération du type de terminal depuis la variable d'environnement TERM
    char *term_type = getenv("TERM");
    if (term_type == NULL) {
        fprintf(stderr, "Erreur : la variable TERM n'est pas définie.\n");
        return EXIT_FAILURE;
    }

    // Initialisation de la base de données du terminal
    status = tgetent(buffer, term_type);
    if (status < 0) {
        fprintf(stderr, "Erreur : impossible d'accéder à la base de données des terminaux.\n");
        return EXIT_FAILURE;
    } else if (status == 0) {
        fprintf(stderr, "Erreur : type de terminal inconnu : %s\n", term_type);
        return EXIT_FAILURE;
    }

    // Récupération et affichage de quelques capacités du terminal
    col = tgetnum("co"); // Nombre de colonnes
    line = tgetnum("li");   // Nombre de lignes
    int auto_wrap = tgetflag("am"); // Support du retour à la ligne automatique

    printf("Type de terminal : %s\n", term_type);
    printf("Nombre de colonnes : %d\n", columns);
    printf("Nombre de lignes : %d\n", lines);
    printf("Retour à la ligne automatique : %s\n", auto_wrap ? "Oui" : "Non");

    // Exemple de récupération d'une séquence de contrôle (clear screen)
    // char *clear = tgetstr("cl", NULL);
    // if (clear) {
    //     printf("Séquence pour effacer l'écran : %s\n", clear);
    // } else {
    //     printf("Impossible de récupérer la séquence pour effacer l'écran.\n");
    // }

    return EXIT_SUCCESS;
}
