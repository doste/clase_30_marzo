#include <iostream>
#include <list>
#include <algorithm>

using namespace std;

using uint = unsigned int;

// Pre: 0 <= mes < 12
uint dias_en_mes(uint mes) {
    uint dias[] = {
        // ene, feb, mar, abr, may, jun
        31, 28, 31, 30, 31, 30,
        // jul, ago, sep, oct, nov, dic
        31, 31, 30, 31, 30, 31
    };
    return dias[mes - 1];
}

// Ejercicio 7, 8, 9 y 10

// Clase Fecha
class Fecha {
  public:
    Fecha(int mes, int dia);
    int mes();
    int dia();
    #if EJ >= 9 // Para ejercicio 9
    bool operator==(Fecha o);
    #endif
    void incrementar_dia();

  private:
    int mes_;
    int dia_;
};

Fecha::Fecha(int mes, int dia): mes_(mes) , dia_(dia) {}

int Fecha::mes() {
    return mes_;
}
int Fecha::dia() {
    return dia_;
}

// ostream Fecha
ostream& operator<<(ostream& os, Fecha fecha) {
    os << fecha.dia() << "/" << fecha.mes() ;
    return os;
}

#if EJ >= 9
bool Fecha::operator==(Fecha o) {
    //bool igual_dia = this->dia() == o.dia();
    //bool igual_mes = this ->mes() == o.mes();
    bool igual_dia = dia() == o.dia();
    bool igual_mes = mes() == o.mes();
    return igual_dia && igual_mes;
}
#endif

void Fecha::incrementar_dia() {
    // voy a tener que ver a parte los casos donde:
    // estoy en un mes con 31 dias y estoy en el dia 31. si hago dia_++ deberia modificar dia_ a 1 y sumarle uno al mes_
    // estoy en un mes con 30 dias y estoy en el dia 31. si hago dia_++ deberia modificar dia_ a 1 y sumarle uno al mes_
    // estoy en el mes de febrero y estoy en el dia 28 . si hago dia_++ deberia modificar dia_ a 1 y sumarle uno al mes_
    // en cualquier otro caso, hago dia_++ y mes_++

    // veo cada caso con un if:
    /*
    if (dias_en_mes(mes_) == 31 && dia_ == 31) {
        dia_ = 1;
        mes_++;
    } else if (dias_en_mes(mes_) == 30 && dia_ == 30) {
        dia_ = 1;
        mes_++;
    } else if (dias_en_mes(mes_) == 28  && dia_ == 28) {
        dia_ = 1;
        mes_++;
    } else {
        dia_++;
    }
    */

    // REESCRITURA : (funcionan ambas formas)
    // mas simple pero no mas facil de entender
    if (dias_en_mes(mes_) == dia_) {
        dia_ = 1;
        mes_++;
    } else {
        dia_++;
    }

}

// Ejercicio 11, 12

// Clase Horario
class Horario {
    public:
        Horario(uint hora, uint min);
        uint hora();
        uint min();
        bool operator==(Horario h);
        bool operator<(Horario h);
    private:
        uint hora_;
        uint min_;
};

Horario::Horario(uint hora, uint min): hora_(hora) , min_(min) {}

uint Horario::hora() {
    return hora_;
}
uint Horario::min() {
    return min_;
}

// sobreescritura comparación por igualdad
bool Horario::operator==(Horario h) {
    bool igual_hora = hora() == h.hora();
    bool igual_min = min() == h.min();
    return igual_hora && igual_min;
}

// ostream Horario
ostream& operator<<(ostream& os, Horario horario) {
    os << horario.hora() << ":" << horario.min() ;
    return os;
}

// sobreescritura comparación por menor
bool Horario::operator<(Horario h) {
    // si los horarios a comparar tienen igual hora, entonces comparo los minutos
    if (this->hora() == h.hora()) {
        return this->min() < h.min();
    } else { // si las horas son distintas, entonces con solo compararlas ya esta
        return this->hora() <  h.hora();
    }
}

// Ejercicio 13

// Clase Recordatorio

class Recordatorio {
public:
    Recordatorio(Fecha fecha, Horario horario, string mensaje);
    Fecha fecha();
    Horario horario();
    string mensaje();
    bool operator<(Recordatorio r);
private:
    Fecha fecha_;
    Horario horario_;
    string mensaje_;
};

Recordatorio::Recordatorio(Fecha fecha, Horario horario, string mensaje) : fecha_(fecha) , horario_(horario) , mensaje_(mensaje) {}

Fecha Recordatorio::fecha() {
    return fecha_;
}
Horario Recordatorio::horario() {
    return horario_;
}
string Recordatorio::mensaje() {
    return mensaje_;
}

// ostream Recordatorio
ostream& operator<<(ostream& os, Recordatorio recordatorio) {
    os << recordatorio.mensaje() << " @ " << recordatorio.fecha() << " " << recordatorio.horario();
    return os;
}
// Recordatorio r(Fecha(10, 6), Horario(9, 45), "Cumple March");
// cout << r << endl; // Cumple March @ 10/6 9:45

bool Recordatorio::operator<(Recordatorio r) {
    return this->horario() < r.horario();
}


// Ejercicio 14

// Clase Agenda
class Agenda {
public:
    Agenda(Fecha fecha_inicial);
    void agregar_recordatorio(Recordatorio rec);
    void incrementar_dia();
    list<Recordatorio> recordatorios_de_hoy();
    Fecha hoy();

private:
    Fecha fecha_inicial_;
    //Fecha fecha_actual_;
    list<Recordatorio> recordatorios_;
};

Agenda::Agenda(Fecha fecha_inicial) : fecha_inicial_(fecha_inicial) {}

void Agenda::incrementar_dia() {
    fecha_inicial_.incrementar_dia();
}

Fecha Agenda::hoy() {
    return fecha_inicial_;
}

void Agenda::agregar_recordatorio(Recordatorio rec) {
    recordatorios_.push_back(rec);
}

list<Recordatorio> Agenda::recordatorios_de_hoy() {
    list<Recordatorio> result;
    for (Recordatorio rec : recordatorios_) {
        if (rec.fecha() == fecha_inicial_) {
            result.push_back(rec);
        }
    }
    return result;
}


// ostream Agenda
ostream& operator<<(ostream& os, Agenda agenda) {
    os << agenda.hoy() << endl;
    os << "=====" << endl;

    list<Recordatorio> listaRecordatorios = agenda.recordatorios_de_hoy();
    listaRecordatorios.sort();
    for (Recordatorio rec : listaRecordatorios) {
        os << rec << endl;
    }
    return os;
}

/*
Agenda a(Fecha(5, 10));
a.agregar_recordatorio(Recordatorio(Fecha(5, 10), Horario(9, 0), "Clase Algo2"));
a.agregar_recordatorio(Recordatorio(Fecha(5, 10), Horario(11, 0), "Labo Algo2"));
cout << a << endl;

 10/5
 =====
 Clase Algo2 @ 10/5 9:0
 Labo Algo2 @ 10/5 11:0
*/