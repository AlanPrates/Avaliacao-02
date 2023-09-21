#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

class Passageiro
{
public:
    string CPF;
    string Nome;
    string DtNascimento;
};

class Roteiro
{
public:
    int Codigo;
    string Data_Horaprevista;
    int Duracao_prevista;
    string Origem;
    string Destino;
};

class Embarque
{
public:
    bool Realizado;
    string Data_Hora;
    int Duracao;
    Passageiro *passageiro;
    Roteiro *roteiro;
};

vector<Passageiro> passageiros;
vector<Roteiro> roteiros;
vector<Embarque> embarques;

void IncluirPassageiro()
{
    Passageiro novoPassageiro;
    cout << "Digite o CPF do Passageiro: ";
    cin >> novoPassageiro.CPF;
    cout << "Digite o Nome do Passageiro: ";
    cin.ignore();
    getline(cin, novoPassageiro.Nome);
    cout << "Digite a Data de Nascimento do Passageiro: ";
    cin >> novoPassageiro.DtNascimento;

    passageiros.push_back(novoPassageiro);
    cout << "Passageiro cadastrado com sucesso.\n";
}

void ListarPassageiros()
{
    cout << "Lista de Passageiros:\n";
    for (const Passageiro &p : passageiros)
    {
        cout << "CPF: " << p.CPF << ", Nome: " << p.Nome << ", Data de Nascimento: " << p.DtNascimento << "\n";
    }
}

void IncluirRoteiro()
{
    Roteiro novoRoteiro;
    cout << "Digite o Código do Roteiro: ";
    cin >> novoRoteiro.Codigo;
    cout << "Digite a Data e Hora Prevista do Roteiro (formato dd/mm/yyyy HH:mm): ";
    cin.ignore();
    getline(cin, novoRoteiro.Data_Horaprevista);
    cout << "Digite a Duração Prevista do Roteiro (em minutos): ";
    cin >> novoRoteiro.Duracao_prevista;
    cout << "Digite a Origem do Roteiro: ";
    cin.ignore();
    getline(cin, novoRoteiro.Origem);
    cout << "Digite o Destino do Roteiro: ";
    getline(cin, novoRoteiro.Destino);

    roteiros.push_back(novoRoteiro);
    cout << "Roteiro cadastrado com sucesso.\n";
}

void ListarRoteiros()
{
    cout << "Lista de Roteiros:\n";
    for (const Roteiro &r : roteiros)
    {
        cout << "Código: " << r.Codigo << ", Data/Hora Prevista: " << r.Data_Horaprevista << ", Duração Prevista: " << r.Duracao_prevista << " minutos, Origem: " << r.Origem << ", Destino: " << r.Destino << "\n";
    }
}

void IncluirEmbarque()
{
    string cpf;
    int codigo;

    cout << "Digite o CPF do Passageiro: ";
    cin >> cpf;

    bool passageiroEncontrado = false;
    for (Passageiro &p : passageiros)
    {
        if (p.CPF == cpf)
        {
            passageiroEncontrado = true;
            break;
        }
    }

    if (!passageiroEncontrado)
    {
        cout << "CPF não encontrado. Embarque cancelado.\n";
        return;
    }

    cout << "Digite o Código do Roteiro: ";
    cin >> codigo;

    bool roteiroEncontrado = false;
    for (Roteiro &r : roteiros)
    {
        if (r.Codigo == codigo)
        {
            roteiroEncontrado = true;
            break;
        }
    }

    if (!roteiroEncontrado)
    {
        cout << "Código do Roteiro não encontrado. Embarque cancelado.\n";
        return;
    }

    Embarque novoEmbarque;
    novoEmbarque.Realizado = false;

    time_t t = time(0);
    novoEmbarque.Data_Hora = ctime(&t);

    novoEmbarque.passageiro = &passageiros.back();
    novoEmbarque.roteiro = &roteiros.back();

    embarques.push_back(novoEmbarque);

    cout << "Embarque registrado com sucesso.\n";
}

void ExcluirEmbarque()
{
    int codigo;

    cout << "Digite o Código do Roteiro: ";
    cin >> codigo;

    cout << "Passageiros embarcados no roteiro " << codigo << ":\n";
    for (const Embarque &e : embarques)
    {
        if (e.roteiro->Codigo == codigo)
        {
            cout << "CPF: " << e.passageiro->CPF << ", Nome: " << e.passageiro->Nome << "\n";
        }
    }

    string cpf;
    cout << "Digite o CPF do passageiro que não embarcará: ";
    cin >> cpf;

    for (auto it = embarques.begin(); it != embarques.end(); ++it)
    {
        if (it->roteiro->Codigo == codigo && it->passageiro->CPF == cpf)
        {
            embarques.erase(it);
            cout << "Embarque excluído com sucesso.\n";
            return;
        }
    }

    cout << "Embarque não encontrado.\n";
}

void AlterarEmbarque()
{
    int codigo;

    cout << "Digite o Código do Roteiro: ";
    cin >> codigo;

    cout << "Passageiros embarcados no roteiro " << codigo << ":\n";
    for (Embarque &e : embarques)
    {
        if (e.roteiro->Codigo == codigo)
        {
            cout << "CPF: " << e.passageiro->CPF << ", Nome: " << e.passageiro->Nome << "\n";
        }
    }

    string cpf;
    cout << "Digite o CPF do passageiro: ";
    cin >> cpf;

    int novaDuracao;
    cout << "Digite a nova duração (em minutos): ";
    cin >> novaDuracao;

    for (Embarque &e : embarques)
    {
        if (e.roteiro->Codigo == codigo && e.passageiro->CPF == cpf)
        {
            e.Duracao = novaDuracao;
            cout << "Embarque alterado com sucesso.\n";
            return;
        }
    }

    cout << "Embarque não encontrado.\n";
}

void ListarEmbarques()
{
    cout << "Lista de Embarques:\n";
    for (const Embarque &e : embarques)
    {
        cout << "Passageiro: " << e.passageiro->Nome << ", Roteiro: " << e.roteiro->Codigo << ", Realizado: " << (e.Realizado ? "Sim" : "Não") << ", Data/Hora: " << e.Data_Hora << ", Duração: " << e.Duracao << " minutos\n";
    }
}

void GestaoEmbarques()
{
    int escolha;
    do
    {
        cout << "\nMenu de Embarques:\n";
        cout << "1. Incluir Embarque\n";
        cout << "2. Excluir um Embarque\n";
        cout << "3. Alterar Embarque\n";
        cout << "4. Listar todos os Embarques\n";
        cout << "0. Sair\n";
        cout << "Escolha uma opção: ";
        cin >> escolha;

        switch (escolha)
        {
        case 1:
            IncluirEmbarque();
            break;
        case 2:
            ExcluirEmbarque();
            break;
        case 3:
            AlterarEmbarque();
            break;
        case 4:
            ListarEmbarques();
            break;
        case 0:
            break;
        default:
            cout << "Opção inválida. Tente novamente.\n";
        }
    } while (escolha != 0);
}

int main()
{
    Passageiro p1 = {"12345678900", "Joao Silva", "01/01/1990"};
    Passageiro p2 = {"98765432100", "Maria Oliveira", "05/05/1985"};
    passageiros.push_back(p1);
    passageiros.push_back(p2);

    Roteiro r1 = {1, "20/09/2023 10:00", 120, "Cidade A", "Cidade B"};
    Roteiro r2 = {2, "21/09/2023 15:00", 90, "Cidade B", "Cidade C"};
    roteiros.push_back(r1);
    roteiros.push_back(r2);

    int escolha;
    do
    {
        cout << "\nMenu Inicial:\n";
        cout << "1. Gestão de Passageiros\n";
        cout << "2. Gestão de Roteiros\n";
        cout << "3. Gestão de Embarques\n";
        cout << "0. Sair do Programa\n";
        cout << "Escolha uma opção: ";
        cin >> escolha;

        switch (escolha)
        {
        case 1:
            int escolhaPassageiros;
            do
            {
                cout << "\nMenu de Gestão de Passageiros:\n";
                cout << "1. Incluir Passageiro\n";
                cout << "2. Listar Passageiros\n";
                cout << "0. Voltar\n";
                cout << "Escolha uma opção: ";
                cin >> escolhaPassageiros;

                switch (escolhaPassageiros)
                {
                case 1:
                    IncluirPassageiro();
                    break;
                case 2:
                    ListarPassageiros();
                    break;
                case 0:
                    break;
                default:
                    cout << "Opção inválida. Tente novamente.\n";
                }
            } while (escolhaPassageiros != 0);
            break;
        case 2:
            int escolhaRoteiros;
            do
            {
                cout << "\nMenu de Gestão de Roteiros:\n";
                cout << "1. Incluir Roteiro\n";
                cout << "2. Listar Roteiros\n";
                cout << "0. Voltar\n";
                cout << "Escolha uma opção: ";
                cin >> escolhaRoteiros;

                switch (escolhaRoteiros)
                {
                case 1:
                    IncluirRoteiro();
                    break;
                case 2:
                    ListarRoteiros();
                    break;
                case 0:
                    break;
                default:
                    cout << "Opção inválida. Tente novamente.\n";
                }
            } while (escolhaRoteiros != 0);
            break;
        case 3:
            GestaoEmbarques();
            break;
        case 0:
            break;
        default:
            cout << "Opção inválida. Tente novamente.\n";
        }
    } while (escolha != 0);

    return 0;
}