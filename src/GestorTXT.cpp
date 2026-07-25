#include "../Include/GestorTXT.hpp"
#include "../Include/GestorUsuarios.hpp"
#include "../Include/Usuario.hpp"

#include <fstream>    // std::ifstream para leer y std::ofstream para escribir archivos.
#include <sstream>   // std::stringstream para separar una línea en diferentes campos.
#include <iostream>  // std::cout para mostrar mensajes en consola.
#include <vector>    // std::vector para almacenar temporalmente los campos de cada línea.
#include <exception> // std::exception usada en el bloque catch.

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
    
    std::ofstream archivo(rutaUsuarios);// std::ofstream se utiliza para escribir datos en archivos.

    
    if (!archivo.is_open()) {
        std::cout << "Error: no se pudo abrir el archivo de usuarios\n";
        return false;
    }


        for (int i = 0; i < gestor.getCantidad(); i++) {

        Usuarios* usuario = gestor.getUsuario(i);

        if (usuario == nullptr) {
            continue; // ignoramos esa iteración y pasamos al siguiente usuario.
        }

        const Fecha& fecha = usuario->getFechaNacimiento();

        Estudiante* estudiante =
            dynamic_cast<Estudiante*>(usuario);
            // dynamic_cast intenta convertir el puntero base Usuarios*
            // en un puntero de tipo Estudiante*.

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
    
    if (!archivoExiste(rutaUsuarios)) {
        std::cout << "Error: el archivo de usuarios no existe\n";
        return false;
    }

    std::ifstream archivo(rutaUsuarios); //sirve para leer archivos.

    if (!archivo.is_open()) {
        std::cout << "Error: no se pudo abrir el archivo\n";
        return false;
    }

    std::string linea;// Aquí se almacenará temporalmente cada línea leída.
    int usuariosCargados = 0;// contadores usados en try-catch
    int lineasInvalidas = 0;// cont

    while (std::getline(archivo, linea)) {

        if (linea.empty()) {
            continue;
        }

        std::stringstream separador(linea);//va leyendo el contenido del string y separándolo según espacios.
        std::vector<std::string> datos;
        std::string campo;

        while (std::getline(separador, campo, '|')) {
            datos.push_back(campo);
        }

        // Ambos tipos tienen exactamente nueve campos.
        if (datos.size() != 9) {
            std::cout << "Linea invalida: " << linea << "\n";
            lineasInvalidas++;
            continue;
        }

        try {
            std::string tipo = datos[0];
            std::string nombre = datos[1];
            std::string apodo = datos[2];
            std::string contrasenia = datos[3];

            int edad = std::stoi(datos[4]);//stoi=string to int
            int dia = std::stoi(datos[5]);
            int mes = std::stoi(datos[6]);
            int anio = std::stoi(datos[7]);

            std::string datoEspecifico = datos[8];

            Fecha fecha(dia, mes, anio);

            if (tipo == "ESTUDIANTE") {

                Usuarios* nuevo = new Estudiante(
                    nombre,
                    apodo,
                    contrasenia,
                    edad,
                    fecha,
                    datoEspecifico
                );

                gestor.setUsuario(nuevo);
                usuariosCargados++;
            }
            else if (tipo == "PUBLISHER") {

                Usuarios* nuevo = new Publisher(
                    nombre,
                    apodo,
                    contrasenia,
                    edad,
                    fecha,
                    datoEspecifico
                );

                gestor.setUsuario(nuevo);
                usuariosCargados++;
            }
            else {
                std::cout << "Tipo de usuario desconocido: "
                          << tipo << "\n";

                lineasInvalidas++;
            }
        }

        catch (const std::exception& error) {
            std::cout << "Error leyendo linea: "
                      << linea << "\n";

            std::cout << "Detalle: "
                      << error.what() << "\n";// Sirve para tener

            lineasInvalidas++;
        }
    }

    archivo.close();

    std::cout << "Usuarios cargados: "
              << usuariosCargados << "\n";

    std::cout << "Lineas invalidas: "
              << lineasInvalidas << "\n";

    return true;
    }

    // Comprobación
    bool GestorTXT::archivoExiste(const std::string& ruta) const{
    
        std::ifstream archivo(ruta);

    if (archivo.is_open()) {
        archivo.close();
        return true;
    }

    return false;
    }

    /*
    Try, throw y catch
    try   -> intenta ejecutar una operación
    throw -> avisa que ocurrió un error
    catch -> recibe y maneja ese error
    
    sintaxis:
    try {
        // Código que podría fallar
    }
    catch (const TipoDeError& error) {
        // Qué hacer si ocurre el error
    }

Se usó try, throw y catch para separar el manejo de errores del flujo principal y evitar una cadena extensa de if-else;
estas palabras son parte del lenguaje. Esto mejora la lectura, facilita capturar distintos fallos y permite mostrar su detalle
 mediante what(). undertale!
    */