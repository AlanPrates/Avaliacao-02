#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <unistd.h>
using namespace std;
#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Passageiro 
{
    string cpf;
    string nome;
    string dtNascimento;
    int numAutorizacao;
};


struct Roteiro 
{
    int codigo;
    string data_hora;
    string origem;
    string destino;
};

struct Embarque
{
    string cpf_passageiro;
    int codigo_roteiro;
    string data_embarque;
    bool embarque;
};

// Funções do menu Passageiros

void IncluirPassageiro(vector<Passageiro>& passageiros) 
{
    Passageiro novo;
    cout << "CPF: ";
    cin >> novo.cpf;
    cout << "Nome: ";
    cin.ignore();
    getline(cin, novo.nome);
    cout << "Data de Nascimento: ";
    cin >> novo.dtNascimento;
    cout << "Numero de Autorizacao: "<<(novo.numAutorizacao = rand() % 9999); //Rand gera um numero aleatorio para a autorização
    passageiros.push_back(novo); //funçao nativa que aloca os dados inserisos no vector
}

void ExcluirPassageiro(vector<Passageiro>& passageiros) 
{
    string Cpf;
    cout << "Digite o CPF do passageiro a ser excluido: ";
    cin >> Cpf;
    for (auto it = passageiros.begin(); it != passageiros.end(); ++it) 
    {
        if (it->cpf == Cpf) {
            passageiros.erase(it);
            cout << "Passageiro excluido com sucesso!" << endl;
            return;
        }
    }
    cout << "Passageiro nao encontrado." << endl;
}

void AlterarPassageiro(vector<Passageiro>& passageiros) 
{
    string Cpf;
    cout << "Digite o CPF do passageiro a ser alterado: ";
    cin >> Cpf;
    for (auto& passageiro : passageiros) 
    {
        if (passageiro.cpf == Cpf) 
        {
            cout << "Novo Nome (ou pressione Enter para manter o mesmo): ";
            cin.ignore();
            getline(cin, passageiro.nome);
            cout << "Nova Data de Nascimento (ou pressione Enter para manter a mesma): ";
            getline(cin, passageiro.dtNascimento);
            cout << "Passageiro alterado com sucesso!" << endl;
            return;
        }
    }
    cout << "Passageiro nao encontrado." << endl;
}

void ListarPassageiros(const vector<Passageiro>& passageiros) 
{
    for (const auto& passageiro : passageiros) 
    {
        cout<<"CPF: " << passageiro.cpf <<endl;
        cout<<"Nome: " << passageiro.nome <<endl; 
        cout<<"Data de Nascimento: " << passageiro.dtNascimento<<endl;
        cout<< "Numero de Autorizacao: " << passageiro.numAutorizacao << endl;
    }
}

void LocalizarPassageiro(const vector<Passageiro>& passageiros) 
{
    string Cpf;
    cout << "Digite o CPF do passageiro a ser localizado: ";
    cin >> Cpf;
    for (const auto& passageiro : passageiros) 
    {
        if (passageiro.cpf == Cpf) 
        {
            cout<<"CPF: " << passageiro.cpf <<endl;
            cout<<"Nome: " << passageiro.nome <<endl; 
            cout<<"Data de Nascimento: " << passageiro.dtNascimento<<endl;
            cout<< "Numero de Autorizacao: " << passageiro.numAutorizacao << endl;
            return;
        }
    }
    cout << "Passageiro nao encontrado." << endl;
}

// Funções do menu de Roteiros

void IncluirRoteiro(vector<Roteiro>& roteiros) 
{
    Roteiro rota;
    cout << "Codigo: "<<(rota.codigo = rand() % 999)<<endl;
    cout << "Data e Hora Prevista (dia/mes/ano hora:minutos): ";
    cin.ignore();
    getline(cin, rota.data_hora);
    cout << "Origem: ";
    getline(cin, rota.origem);
    cout << "Destino: ";
    getline(cin, rota.destino);
    roteiros.push_back(rota);
}

void ExcluirRoteiro(vector<Roteiro>& roteiros) 
{
    int cod;
    cout << "Digite o Codigo do roteiro a ser excluido: ";
    cin >> cod;
    for (auto it = roteiros.begin(); it != roteiros.end(); ++it) 
    {
        if (it->codigo == cod) 
        {
            roteiros.erase(it);
            cout << "Roteiro excluido com sucesso!" <<endl;
            return;
        }
    }
    cout << "Roteiro nao encontrado." <<endl;
}

void AlterarRoteiro(vector<Roteiro>& roteiros) 
{
    int cod;
    cout << "Digite o Codigo do roteiro a ser alterado: ";
    cin >> cod;
    for (auto& roteiro : roteiros) 
    {
        if (roteiro.codigo == cod) 
        {
            cout << "Nova Data e Hora Prevista (ou pressione Enter para manter a mesma): ";
            cin.ignore();
            getline(cin, roteiro.data_hora);
            cout << "Nova Origem (ou pressione Enter para manter a mesma): ";
            getline(cin, roteiro.origem);
            cout << "Novo Destino (ou pressione Enter para manter o mesmo): ";
            getline(cin, roteiro.destino);
            cout << "Roteiro alterado com sucesso!" << endl;
            return;
        }
    }
    cout << "Roteiro nao localizado!" << endl;
}

void ListarRoteiros(const vector<Roteiro>& roteiros) 
{
    for (const auto& roteiro : roteiros) 
    {
        cout << "Codigo: " << roteiro.codigo <<endl;
        cout<<"Data e Hora Prevista: " << roteiro.data_hora <<endl;
        cout<<"Origem: " << roteiro.origem<<endl;
        cout<< "Destino: " << roteiro.destino <<endl;
    }
}

void LocalizarRoteiro(const vector<Roteiro>& roteiros) 
{
    int cod;
    cout << "Digite o Codigo do roteiro a ser localizado: ";
    cin >> cod;
    for (const auto& roteiro : roteiros) 
    {
        if (roteiro.codigo == cod) 
        {
        cout << "Codigo: " << roteiro.codigo <<endl;
        cout<<"Data e Hora Prevista: " << roteiro.data_hora <<endl;
        cout<<"Origem: " << roteiro.origem<<endl;
        cout<< "Destino: " << roteiro.destino <<endl;
        return;
        }
    }
    cout << "Roteiro nao localizado." << endl;
}

//Funções do menu Embarque

void ExcluirEmbarque(vector<Embarque>& embarques) 
{
    string cpf;
    int cod_roteiro;

    cout<<"Informe o codigo do roteiro: ";
    cin>>cod_roteiro;
    
    for (auto it = embarques.begin(); it != embarques.end(); ++it)
    {
        if(it->codigo_roteiro == cod_roteiro)
        {
            ListarPassageiros;
        }
        
    }
    
    cout<<"Informe o CPF do passageiro que nao embarcara: ";
    cin>>cpf;

    for (auto it = embarques.begin(); it != embarques.end(); ++it) 
    {
        if (it->cpf_passageiro == cpf && it->codigo_roteiro == cod_roteiro)
        {
            embarques.erase(it);
            cout << "Embarque excluido com sucesso!" << endl;
            return;
        }
    }
    cout << "Passageiro nao encontrado." << endl;
}



int main() 
{
    vector<Passageiro> passageiros;
    vector<Roteiro> roteiros;
    vector<Embarque>embarques;
    int opcao;
    
    do 
    {
        cout << "Menu de Opcoes:" << endl;
        cout << "1. Gestao de Passageiros" << endl;
        cout << "2. Gestao de Roteiros" << endl;
        cout << "3. Gestao de Embarques" << endl;
        cout << "0. Sair" << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        switch (opcao) 
        {
            case 1:
                int opcaoPassageiros;
                do 
                {
                    cout<<endl;
                    cout << "****** Menu de Opcoes para Passageiros ******" << endl;
                    cout << "1. Incluir" << endl;
                    cout << "2. Excluir" << endl;
                    cout << "3. Alterar" << endl;
                    cout << "4. Listar" << endl;
                    cout << "5. Localizar" << endl;
                    cout << "0. Voltar" << endl<<endl;
                    cout << "Escolha uma opcao: ";
                    cin >> opcaoPassageiros;

                    switch (opcaoPassageiros) {
                        case 1:
                            IncluirPassageiro(passageiros);
                            break;
                        case 2:
                            ExcluirPassageiro(passageiros);
                            break;
                        case 3:
                            AlterarPassageiro(passageiros);
                            break;
                        case 4:
                            ListarPassageiros(passageiros);
                            break;
                        case 5:
                            LocalizarPassageiro(passageiros);
                            break;
                        case 0:
                            cout << "Voltando ao menu principal..." << endl<<endl;
                            break;
                        default:
                            cout << "Opcao invalida. Tente novamente." <<endl<<endl;
                            break;
                    }

                } while (opcaoPassageiros != 0);
                break;

            case 2:
                int opcaoRoteiros;
                do 
                {
                    cout << "Menu de Opcoes para Roteiros:" << endl;
                    cout << "1. Incluir" << endl;
                    cout << "2. Excluir" << endl;
                    cout << "3. Alterar" << endl;
                    cout << "4. Listar" << endl;
                    cout << "5. Localizar" << endl;
                    cout << "0. Voltar" << endl<<endl;
                    cout << "Escolha uma opcao: ";
                    cin >> opcaoRoteiros;

                    switch (opcaoRoteiros) 
                    {
                        case 1:
                            IncluirRoteiro(roteiros);
                            break;
                        case 2:
                            ExcluirRoteiro(roteiros);
                            break;
                        case 3:
                            AlterarRoteiro(roteiros);
                            break;
                        case 4:
                            ListarRoteiros(roteiros);
                            break;
                        case 5:
                            LocalizarRoteiro(roteiros);
                            break;
                        case 0:
                            cout << "Voltando ao menu principal..." << endl<<endl;
                            break;
                        default:
                            cout << "Opcao invalida. Tente novamente." <<endl<<endl;
                            break;
                    }

                } while (opcaoRoteiros != 0);
                break;
                
           case 3:
                int opcaoEmbarques;
                do 
                {
                    cout << "Menu de Opcoes para Roteiros:" << endl;
                    cout << "1. Incluir" << endl;
                    cout << "2. Excluir" << endl;
                    cout << "3. Alterar" << endl;
                    cout << "4. Listar" << endl;
                    cout << "5. Localizar" << endl;
                    cout << "0. Voltar" << endl<<endl;
                    cout << "Escolha uma opcao: ";
                    cin >> opcaoEmbarques;

                    switch (opcaoEmbarques) 
                    {
                     //   case 1:
                     //       IncluirEmbarque(embarques);
                     //       break;
                        case 2:
                            ExcluirEmbarque(embarques);
                            break;
                     // case 3:
                     //     AlterarRoteiro(embarques);
                     //       break;
                    //    case 4:
                     //       ListarRoteiros(embarques);
                     //       break;
                        
                        case 0:
                            cout << "Voltando ao menu principal..." << endl<<endl;
                            break;
                        default:
                            cout << "Opcao invalida. Tente novamente." <<endl<<endl;
                            break;
                    }

                } while (opcaoEmbarques != 0);
                break;

            case 0:
                exit;
                break;

            default:
                cout << "Opcao invalida. Tente novamente." <<endl<<endl;
                break;
        }     
            
    } while (opcao != 0);
   
   return 0;
}








