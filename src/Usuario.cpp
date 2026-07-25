#include "../Include/Usuario.hpp"//".." significan subir el nivel en la struct de carpetas.
#include <iostream>
#include <string>
#include <iomanip>//esto es para usar setw y setfill en fechas.
int Usuarios::siguienteID = 1;//No error en 
////////Fecha///////////
// constructor
    Fecha::Fecha(int d, int m, int a): dia(1), mes(1), anio(2000) {//Inicializacion valida
        setfecha(d, m, a);
    }
    //getters

    int Fecha::getdia() const{
        return dia;
    }
    int Fecha::getmes() const {
        return mes;
    }
    int Fecha::getanio() const{
        return anio;
    }

    //setters

    void Fecha::setfecha(int d,int m, int a){
        if (FechaValida(d, m, a)) {
            dia=d;
            mes=m;
            anio=a;
            return;
    }
    return;
    }
    //Metodo sobrecarga de operadores
   bool Fecha::FechaValida(int d, int m, int a)const{
    int diasPorMes[12] = {
    31, 28, 31, 30, 31, 30,
    31, 31, 30, 31, 30, 31
    };
    if(m<1 || m>12){
        std::cout<<"Error: Mes invalido\n"
                <<"Usando Fecha Predefinida(01/01/2000) o fecha valida anterior\n";
        return false;
    }else if(d<1 || d>diasPorMes[m-1]){
        std::cout<<"Error: Dia invalido\n"
                <<"Usando Fecha Predefinida(01/01/2000) o fecha valida anterior\n";
        return false;
    }else if(a<1909 || a>2013){
        std::cout<<"Error: anio invalido\n"
                <<"Usando Fecha Predefinida(01/01/2000) o fecha valida anterior\n";
        return false;
    }
        std::cout<<"Fecha de nacimiento establecida\n";
        return true;
    
   }
   //Para esto es iomanip setfill y setw
    std::ostream& operator<<(std::ostream& salida, const Fecha& fecha){
        salida << std::setfill('0')
           << std::setw(2) << fecha.dia << "/"
           << std::setw(2) << fecha.mes << "/"
           << std::setw(4) << fecha.anio;

    return salida;
    }
///////////////Usuarios
//constuctor
    Usuarios::Usuarios(const std::string &N, const std::string &A,const std::string &C, int E, const Fecha& F)
    : nombre("Sin nombre"), apodo("Usuario"), contrasenia(""), Edad(13), ID(siguienteID++), Fechanacimiento(F)
{
    setNombre(N);
    setApodo(A);
    setEdad(E);
    setContrasenia("", C);
    
}

    //getters
    const std::string& Usuarios::getNombre() const{
        return nombre;
    } 
    const std::string& Usuarios::getApodo() const{
        return apodo;
    }
    int Usuarios::getEdad() const{
        return Edad;
    }
    int Usuarios::getID() const{
        return ID;
    }
    //setters
    void Usuarios::setNombre(std::string const &NuevoNombre){
            nombre=NuevoNombre;
    }
    void Usuarios::setApodo (const std::string& NuevoApodo){
        if(VerificarApodo(NuevoApodo)){
            std::cout<<"Nombre de Usuario Ocupado\n";
            return;
        }else if(Apodovalido(NuevoApodo)){
            apodo=NuevoApodo;
            return;
        }
    }
    void Usuarios::setEdad(int NuevaEdad){
        if(NuevaEdad<13 || NuevaEdad>117){
            std::cout<<"Edad no valio, ciao\n";
            return;
        }
        Edad=NuevaEdad;
    }
    void Usuarios::setContrasenia(const std::string& actual, const std::string& nueva){
        if(nueva.empty()){
            std::cout<<"Contrasenia no fue establecida\n";
            return;
        }
        if(contrasenia.empty()){
            contrasenia=nueva;
            std::cout<<"Contrasenia fue establecida\n";
            return;
        }else if(VerificarContrasenia(actual)){
            contrasenia=nueva;
            return;
        }

        return;
    }
    // Metodos
    //Contrasnia init
    bool Usuarios::VerificarContrasenia(const std::string& intento)const{
        if(intento.empty()){
            return false;
        }
        if (intento == contrasenia){
            return true;
        }else{
            return false;
        }
    }
    //constrasenia fin
    //Usuario y nombre init
    bool Usuarios::VerificarApodo(const std::string& intento) const{
        if(intento.empty()){
            return false;
        }
        if (intento == apodo){
            return true;
        }else{
            return false;
        }
    }
    bool Usuarios::Apodovalido(std::string const &intento) const{
        return true;
    }
    //Usuario y nombre fin

    void Usuarios::imprimirUsuario() const {
        std::cout<<"Datos Usuario:\n" <<"Nombre: "<<nombre<<"\n" <<"Nombre de Usuario: "<<apodo<<"\n"
                <<"Fecha de Nacimiento: "<<Fechanacimiento<<"\n"<<"Edad: "<<Edad<<"\n";
    }
///////////////Publisher//////////////////////////////////
///constructor

    Publisher::Publisher(const std::string &N, const std::string &A,const std::string &C, int E, const Fecha& F, const std::string &Corr)
    : Usuarios(N,A,C,E,F), Correo("Hola@ejemplo.com"){
        setCorreo(Corr);
    }

    //Setter
    void Publisher::setCorreo(const std::string &NuevoCorreo){
        if(VerificarCorreo(NuevoCorreo)){
            Correo=NuevoCorreo;
            return;
        }else{
            std::cout<<"Correo de Usuario no valio/Ocupado\n";
            return;
        }
        }
    
    //Getter
    const std::string& Publisher::getCorreo() const{
        return Correo;
    }
    //Metodos no implementados todavia
    //Correo init
    bool Publisher::VerificarCorreo(const std::string& Ocupado)const{
            return true;
    }
    //Correo fin

    void Publisher::imprimirUsuario() const {
        std::cout<<"Datos Usuario:\n" <<"Nombre: "<<nombre<<"\n" <<"Nombre de Usuario: "<<apodo<<"\n"
                <<"Fecha de Nacimiento: "<<Fechanacimiento<<"\n"<<"Edad: "<<Edad<<"\n"<<"Correo: "
                <<Correo<<"\n";
    }
///////////////Estudiantes
///constructor
    Estudiante::Estudiante(const std::string &N, const std::string &A,const std::string &C, int E, const Fecha& F, const std::string& I)
    : Usuarios(N,A,C,E,F), Institucion("Usfq"){
        setInstitucion(I);
    }
    //setter
    void Estudiante::setInstitucion(const std::string& Inst){
        if(ValidarInstitucion(Inst)){
            Institucion=Inst;
            return;
        }else{
            std::cout<<"Institucion no validada\n";
            return;
        }
    }
    //Getter
    const std::string& Estudiante::getInstitucion() const{
        return Institucion;
    } 

    //Metodos 
    bool Estudiante::ValidarInstitucion(const std::string& I) const{
        return true;
    }
    void Estudiante::imprimirUsuario() const {
        std::cout<<"Datos Usuario:\n" <<"Nombre: "<<nombre<<"\n" <<"Nombre de Usuario: "<<apodo<<"\n"
                <<"Fecha de Nacimiento: "<<Fechanacimiento<<"\n"<<"Edad: "<<Edad<<"\n"<<"Institucion: "
                <<Institucion<<"\n";
    }