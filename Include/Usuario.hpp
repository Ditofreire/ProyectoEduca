#ifndef Usuario_HPP
#define Usuario_HPP
#include <ostream>//sobrecarga
#include<string>
 
class Fecha{
    private:
    int dia;
    int mes;
    int anio;
    public:
    //Constructor y Destructor
    Fecha(int d, int m, int a);
    ~Fecha() = default;

    //getters
    int getdia() const;
    int getmes() const;
    int getanio() const;
    //setters
    void setfecha(int d,int m, int a);
    //Metodo sobrecarga de Op y validadcion de fecha
    bool FechaValida(int d, int m, int a)const;
    friend std::ostream& operator<<(std::ostream& salida, const Fecha& fecha);//Permisos especiales a ostream
};
// clase abstracta////////////////////////////////////
class Usuarios{
    protected:
    std::string nombre;
    std::string apodo;
    std::string contrasenia; //No setter. especial
    int Edad;
    const int ID;
    static int siguienteID; // En este caso es para decir que pertenece a la clase en si. no al objeto individual.
    Fecha Fechanacimiento;
   
    public:
     //Constructor y Destructor
    Usuarios(const std::string &N, const std::string &A,const std::string &C, int E, const Fecha& F);
    virtual ~Usuarios() = default; //
    //getters
    const std::string& getNombre() const; //aqui no pasamos por valor >:()
    const std::string& getApodo() const;
    int getEdad() const;
    int getID() const;
    const Fecha& getFechaNacimiento() const;
    const std::string& getContrasenia() const;
    //setters
    void setNombre(std::string const &NuevoNombre);
    void setApodo (const std::string& NuevoApodo);
    void setEdad(int NuevaEdad);
    void setContrasenia(const std::string& actual, const std::string& nueva);
    // Metodos
    //Contrasnia init
    bool VerificarContrasenia(const std::string& intento)const;
    //constrasenia fin
    //Usuario y nombre init
    bool VerificarApodo(const std::string& intento) const;
    bool Apodovalido(std::string const &NuevoNombre) const;
    //Usuario y nombre fin

    virtual void imprimirUsuario() const = 0;
};

class Publisher : public Usuarios{
    private:
    std::string Correo;
    public:
    //Construct y destruct
    Publisher(const std::string &N, const std::string &A,const std::string &C, int E, const Fecha& F, const std::string &Corr);
    ~Publisher() override=default;
    //Setter
    void setCorreo(const std::string &NuevoCorreo);
    //Getter
    const std::string& getCorreo() const;
    //Metodos
    void PublicarContenido ();//Despues
    void CargarContenido();//Despues
    //Correo init
    bool VerificarCorreo(const std::string& Ocupado)const;
    //Correo fin

    void imprimirUsuario() const override;

};

class Estudiante : public Usuarios{
    private:
    std::string Institucion;
    public:
    //Construct y destruct
    Estudiante(const std::string &N, const std::string &A,const std::string &C, int E, const Fecha& F, const std::string& I);
    ~Estudiante() override=default;
    //setter
    void setInstitucion(const std::string& Inst);
    //Getter
    const std::string& getInstitucion() const; 
    //Metodos
    bool ValidarInstitucion(const std::string& I) const;
    void AccederContenido(); //Despeues
    void imprimirUsuario() const override;
   
};

#endif