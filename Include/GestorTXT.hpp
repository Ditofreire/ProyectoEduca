#ifndef GESTOR_TXT_HPP
#define GESTOR_TXT_HPP

#include <string>

// Declaración anticipada para evitar includes circulares
class GestorUsuarios; //Esto solo dice: Existe una clase con ese nombre y su definicion aparecera despues.

class GestorTXT {
private:
    std::string rutaUsuarios;

public:
    // Constructor y destructor
    explicit GestorTXT(const std::string& ruta);
    ~GestorTXT() = default;

    // Getter
    const std::string& getRutaUsuarios() const;

    // Setter
    void setRutaUsuarios(const std::string& nuevaRuta);

    // Métodos de persistencia
    bool guardarUsuarios(const GestorUsuarios& gestor) const;
    bool cargarUsuarios(GestorUsuarios& gestor) const;

    // Comprobación
    bool archivoExiste(const std::string& ruta) const;
};

#endif

/*
    Include Circular

Ocurre cuando 2 headers se incluyen mutuamente
Los #ifndef evitan que el preprocesador entre en un ciclo infinito, pero no solucionan completamente el problema. 
El fallo habitual es que una clase intenta usar a la otra antes de que su definición esté completa.

Resumen es magia.
*/