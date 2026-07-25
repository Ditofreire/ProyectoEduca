#include "../Include/GestorUsuarios.hpp"
#include <iostream>

int main()
{
    Fecha fecha1(10, 5, 2000);
    Fecha fecha2(20, 8, 2002);

    GestorUsuarios gestor(2);

    gestor.setUsuario(
        new Estudiante(
            "Gerardo", 
            "Dito",
            "clave123",
            25,
            fecha1,
            "USFQ"
        )
    );

    gestor.setUsuario(
        new Publisher(
            "Carlos",
            "Carlitos",
            "clave456",
            23,
            fecha2,
            "correo@ejemplo.com"
        )
    );

    std::cout << "Cantidad: "
              << gestor.getCantidad()
              << "\n";

    for (int i = 0; i < gestor.getCantidad(); i++) {
        gestor.getUsuario(i)->imprimirUsuario();
        std::cout << "\n";
    }

    return 0;
}