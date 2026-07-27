#include "../Include/Usuario.hpp"
#include "../Include/GestorUsuarios.hpp"
#include "../Include/GestorTXT.hpp"

#include <iostream>

int main()
{
    // El gestor inicia con capacidad para dos usuarios.
    GestorUsuarios gestorOriginal(2);

    Fecha fecha1(10, 5, 2000);
    Fecha fecha2(20, 8, 2002);
    Fecha fecha3(15, 3, 1998);

    gestorOriginal.setUsuario(
        new Estudiante(
            "Gerardo",
            "Dito",
            "clave123",
            25,
            fecha1,
            "USFQ"
        )
    );

    gestorOriginal.setUsuario(
        new Publisher(
            "Carlos",
            "Carlitos",
            "clave456",
            23,
            fecha2,
            "carlos@ejemplo.com"
        )
    );

    std::cout << "\nCapacidad antes del tercer usuario: "
              << gestorOriginal.getCapacidad() << "\n";

    // Al insertar el tercer usuario, el arreglo pasa de capacidad 2 a 4.
    gestorOriginal.setUsuario(
        new Estudiante(
            "Andrea",
            "Andy",
            "clave789",
            27,
            fecha3,
            "Universidad Central"
        )
    );

    std::cout << "Cantidad de usuarios: "
              << gestorOriginal.getCantidad() << "\n";

    std::cout << "Capacidad despues del tercer usuario: "
              << gestorOriginal.getCapacidad() << "\n\n";

    std::cout << "Usuarios originales:\n";

    for (int i = 0; i < gestorOriginal.getCantidad(); i++) {
        Usuarios* usuario = gestorOriginal.getUsuario(i);

        if (usuario != nullptr) {
            usuario->imprimirUsuario();
            std::cout << "\n";
        }
    }

    // La carpeta Datos debe existir previamente.
    GestorTXT gestorTXT("datos/usuarios.txt");

    if (!gestorTXT.guardarUsuarios(gestorOriginal)) {
        std::cout << "No fue posible guardar los usuarios\n";
        return 1;
    }

    // Este segundo gestor comienza vacío.
    GestorUsuarios gestorCargado(2);

    if (!gestorTXT.cargarUsuarios(gestorCargado)) {
        std::cout << "No fue posible cargar los usuarios\n";
        return 1;
    }

    std::cout << "\nUsuarios reconstruidos desde el TXT:\n";

    for (int i = 0; i < gestorCargado.getCantidad(); i++) {
        Usuarios* usuario = gestorCargado.getUsuario(i);

        if (usuario != nullptr) {
            usuario->imprimirUsuario();
            std::cout << "\n";
        }
    }

    return 0;
}