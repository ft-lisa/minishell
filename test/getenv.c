#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <VARIABLE_ENV>\n", argv[0]);
        return 1;
    }

    char *value = getenv(argv[1]);

    if (value) {
        printf("Valeur de %s : %s\n", argv[1], value);
    } else {
        printf("La variable d'environnement %s n'existe pas.\n", argv[1]);
    }

    return 0;
}
