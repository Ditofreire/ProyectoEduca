#include "../Include/GestorTXT.hpp"
#include "../Include/GestorUsuarios.hpp"
#include "../include/Usuario.hpp"

#include <fstream>//Trabajar archivos
#include <iostream>

 // Constructor y destructor
    explicit GestorTXT::GestorTXT(const std::string& ruta): rutaUsuarios(ruta){}
    

    // Getter
    const std::string& GestorTXT::getRutaUsuarios() const{
        return rutaUsuarios;
    }

    // Setter
    void GestorTXT::setRutaUsuarios(const std::string& nuevaRuta){
        if(archivoExiste(nuevaRuta)){
            rutaUsuarios=nuevaRuta;
            return;
        }
        std::cout<<"No existe ruta\n";
    }

    // Métodos de persistencia
    bool GestorTXT::guardarUsuarios(const GestorUsuarios& gestor) const{
        
        std::ofstream archivo(rutaUsuarios); //Crea un obj llamado archivo para escribir datos en un txt.

        if (!archivo.is_open()) {
            std::cout << "Error: no se pudo abrir el archivo de usuarios\n";
            return false;
        }

        for (int i = 0; i < gestor.getCantidad(); i++) {

        Usuarios* usuario = gestor.getUsuario(i);

        if (usuario == nullptr) {
            continue;//ignore
        }

        const Fecha& fecha = usuario->getFechaNacimiento();

        Estudiante* estudiante =
            dynamic_cast<Estudiante*>(usuario);

        if (estudiante != nullptr) {
            archivo << "ESTUDIANTE" << "|"
                    << usuario->getNombre() << "|"
                    << usuario->getApodo() << "|"
                    << usuario->getContrasenia() << "|"
                    << usuario->getEdad() << "|"
                    << fecha.getdia() << "|"
                    << fecha.getmes() << "|"
                    << fecha.getanio() << "|"
                    << estudiante->getInstitucion()
                    << "\n";

            continue;
        }

        Publisher* publisher =
            dynamic_cast<Publisher*>(usuario);

        if (publisher != nullptr) {
            archivo << "PUBLISHER" << "|"
                    << usuario->getNombre() << "|"
                    << usuario->getApodo() << "|"
                    << usuario->getContrasenia() << "|"
                    << usuario->getEdad() << "|"
                    << fecha.getdia() << "|"
                    << fecha.getmes() << "|"
                    << fecha.getanio() << "|"
                    << publisher->getCorreo()
                    << "\n";

            continue;
        }
    }

    archivo.close();

    std::cout << "Usuarios guardados correctamente\n";
    return true;

    }
    bool GestorTXT::cargarUsuarios(GestorUsuarios& gestor) const{

    }

    // Comprobación
    bool GestorTXT::archivoExiste(const std::string& ruta) const{

    }