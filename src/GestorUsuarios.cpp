#include "../Include/GestorUsuarios.hpp"
#include <iostream>

// Constructor
GestorUsuarios::GestorUsuarios(int capacidadInicial): usuarios(nullptr), cantidad(0), capacidad(capacidadInicial > 0 ? capacidadInicial : 1){
   
    usuarios = new Usuarios*[capacidad];
    // Inicializamos las posiciones como punteros nulos para evitar wild pointers
    for (int i = 0; i < capacidad; i++) {
        usuarios[i] = nullptr;
    }
}

// Destructor
GestorUsuarios::~GestorUsuarios(){
    // Eliminamos cada objeto almacenado
    for (int i = 0; i < cantidad; i++) {
        delete usuarios[i];       //Esa posición conserva temporalmente la dirección del objeto eliminado, así que se convierte en un dangling pointer.
        usuarios[i] = nullptr;   // A no ser ...
    }

    // Eliminamos el arreglo de punteros
    delete[] usuarios;
     usuarios = nullptr;
} 

// Aumentar capacidad
void GestorUsuarios::redimensionar(){
    int nuevaCapacidad = capacidad * 2;

    Usuarios** nuevoArreglo = new Usuarios*[nuevaCapacidad];

    // Ctrl+C usuarios existentes
    for (int i = 0; i < cantidad; i++) {
        nuevoArreglo[i] = usuarios[i];    // "talon de aquiles" depende del tamnio, mayor complijidad de momento O(n) -lineal-. Para el bucle.
    }

    // Inicializamos las posiciones nuevas
    for (int i = cantidad; i < nuevaCapacidad; i++) {
        nuevoArreglo[i] = nullptr;
    }

    // Eliminamos solamente el arreglo anterior,
    // no los objetos apuntados
    delete[] usuarios;

    usuarios = nuevoArreglo;
    capacidad = nuevaCapacidad;
}


void GestorUsuarios::setUsuario(Usuarios* nuevo){
    if (nuevo == nullptr) {
        std::cout << "Error: usuario nulo\n";
        return;
    }

    if (cantidad == capacidad) {
        redimensionar();
    }

    usuarios[cantidad] = nuevo;
    cantidad++;

    return;
}


int GestorUsuarios::getCantidad() const{
    return cantidad;
}

int GestorUsuarios::getCapacidad() const{
    return capacidad;
}

// Obtener usuario según su posición
Usuarios* GestorUsuarios::getUsuario(int posicion) const{
    if (posicion < 0 || posicion >= cantidad) {
        std::cout << "Error: posicion fuera de rango\n";
        return nullptr;
    }

    return usuarios[posicion];
}