#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

class Passageiro {
public:
    string CPF;
    string Nome;
    string DtNascimento;
};

class Roteiro {
public:
    int Codigo;
    string Data_Horaprevista;
    int Duracao_prevista;
    string Origem;
    string Destino;
};

class Embarque {
public:
    bool Realizado;
    string Data_Hora;
    int Duracao;
    Passageiro* passageiro;
    Roteiro* roteiro;
};

