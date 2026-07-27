#ifndef GestorUsuarios_HPP
#define GestorUsuarios_HPP

#include "Usuario.hpp"
 

class GestorUsuarios{
private:
    Usuarios** usuarios;//Puntero a un arreglo dinámico cuyos elementos son punteros a Usuarios
    int cantidad;
    int capacidad;

    void redimensionar();

public:
    // Constructor y destructor
    explicit GestorUsuarios(int capacidadInicial);// Impide que un int se convierta implícitamente en un objeto GestorUsuarios
    ~GestorUsuarios();

    // Evitar copias accidentales por ahora
    GestorUsuarios(const GestorUsuarios&) = delete;
    GestorUsuarios& operator=(const GestorUsuarios&) = delete;

    // Setter/agregar
    void setUsuario(Usuarios* nuevo);

    // Getters
    int getCantidad() const;
    int getCapacidad() const;
    Usuarios* getUsuario(int posicion) const;
};

#endif