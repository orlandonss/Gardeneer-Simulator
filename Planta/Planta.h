#ifndef TPPOO2_PLANTA_H
#define TPPOO2_PLANTA_H

#include <string>
#include "../Settings/Settings.h"
#include <sstream>

class Solo;

class Planta {
public:

    //caracterizacao das plantas
    enum class Beleza { FEIA, BONITA, NEUTRA };
    static std::string belezaToString(Beleza b);

    ///CONSTRUTOR
    Planta( int agua, int nutrientes,Beleza beleza);

    ///FUNCOES VIRTUAIS PURAS
    virtual void atualizar(Solo &solo) = 0;
    virtual char getTipo() const = 0;
    virtual std::string getInfoPlanta()const =0;

    ///GETTERS
    Beleza getBeleza() const {return  beleza;}
    int getAgua_planta()const noexcept {return agua;}
    int getNutrientes_planta()const noexcept {return nutrientes;}
    bool getEstado() const noexcept{return  viva;}

    ///SETTERS
    void setAgua(int newAgua);
    void setNutrientes(int nutriente);
    void setEstado( bool estado);

    virtual ~Planta();
private:
    int agua;
    int nutrientes;
    bool viva;
    Beleza beleza;
};

#endif
