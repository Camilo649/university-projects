#include <stdio.h>
#include <stdlib.h>

#include "data.h"

void
print_data(data_t d) {
    printf("NOMBRE: %s\n"
           "EDAD  : %d años\n"
           "ALTURA: %d cm\n\n",
           d.name, d.age, d.height);
}

void set_name(name_t new_name, data_t *d) {
    unsigned int i = 0u;
    while (new_name[i] != '\0')
    {
        d->name[i] = new_name[i];
        ++i;
    }
}

int main(void) {

    data_t messi = {"Leo Messi", 35, 169};
    print_data(messi);
    name_t messi_full_name = "Lionel Messi";
    data_t *messi_abbreviated_name= NULL; //Declaro una nueva variable del tipo puntero a la estructura data_t, la cual necesito para poder llamar correctamente a la función set_name()
    messi_abbreviated_name = &messi; //y le asigno la dirección de memoria de la variable que quiero modificar con la función.
    set_name(messi_full_name, messi_abbreviated_name);
    print_data(messi);

    return EXIT_SUCCESS;
}