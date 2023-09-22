// Atividade avaliativa em grupo
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
    struct Ocorrencia
    {
        string Descricao;
        string Data_Hora;
        int Num_Apolice;
    } ocorrencia;
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

    for (Embarque &e : embarques)
    {
        if (e.roteiro->Codigo == codigo && e.passageiro->CPF == cpf)
        {
            int novaDuracao;
            cout << "Digite a nova duração do Embarque (em minutos): ";
            cin >> novaDuracao;
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

void IncluirOcorrencia()
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
        cout << "CPF não encontrado. Inclusão de ocorrência cancelada.\n";
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
        cout << "Código do Roteiro não encontrado. Inclusão de ocorrência cancelada.\n";
        return;
    }

    for (Embarque &e : embarques)
    {
        if (e.passageiro->CPF == cpf && e.roteiro->Codigo == codigo)
        {
            cin.ignore(); // Limpa o buffer de entrada
            cout << "Digite a Descrição da Ocorrência: ";
            getline(cin, e.ocorrencia.Descricao);
            cout << "Digite a Data e Hora da Ocorrência (formato dd/mm/yyyy HH:mm): ";
            cin >> e.ocorrencia.Data_Hora;
            cout << "Digite o Número da Apólice: ";
            cin >> e.ocorrencia.Num_Apolice;

            cout << "Ocorrência registrada com sucesso.\n";
            return;
        }
    }

    cout << "Embarque não encontrado para registrar a ocorrência.\n";
}

void ExcluirOcorrencia()
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
        cout << "CPF não encontrado. Exclusão de ocorrência cancelada.\n";
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
        cout << "Código do Roteiro não encontrado. Exclusão de ocorrência cancelada.\n";
        return;
    }

    for (Embarque &e : embarques)
    {
        if (e.passageiro->CPF == cpf && e.roteiro->Codigo == codigo)
        {
            e.ocorrencia = {}; // Limpa a ocorrência
            cout << "Ocorrência excluída com sucesso.\n";
            return;
        }
    }

    cout << "Embarque não encontrado para excluir a ocorrência.\n";
}

void AlterarOcorrencia()
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
        cout << "CPF não encontrado. Alteração de ocorrência cancelada.\n";
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
        cout << "Código do Roteiro não encontrado. Alteração de ocorrência cancelada.\n";
        return;
    }

    for (Embarque &e : embarques)
    {
        if (e.passageiro->CPF == cpf && e.roteiro->Codigo == codigo)
        {
            Embarque::Ocorrencia &ocorrencia = e.ocorrencia;

            cout << "Descrição atual: " << ocorrencia.Descricao << "\n";
            cout << "Deseja alterar a Descrição? (s/n): ";
            char opcao;
            cin >> opcao;
            if (opcao == 's' || opcao == 'S')
            {
                cin.ignore(); // Limpa o buffer de entrada
                cout << "Digite a nova Descrição: ";
                getline(cin, ocorrencia.Descricao);
            }

            cout << "Data e Hora atual: " << ocorrencia.Data_Hora << "\n";
            cout << "Deseja alterar a Data e Hora? (s/n): ";
            cin >> opcao;
            if (opcao == 's' || opcao == 'S')
            {
                cout << "Digite a nova Data e Hora (formato dd/mm/yyyy HH:mm): ";
                cin >> ocorrencia.Data_Hora;
            }

            cout << "Número da Apólice atual: " << ocorrencia.Num_Apolice << "\n";
            cout << "Deseja alterar o Número da Apólice? (s/n): ";
            cin >> opcao;
            if (opcao == 's' || opcao == 'S')
            {
                cout << "Digite o novo Número da Apólice: ";
                cin >> ocorrencia.Num_Apolice;
            }

            cout << "Ocorrência alterada com sucesso.\n";
            return;
        }
    }

    cout << "Embarque não encontrado para alterar a ocorrência.\n";
}

void ListarOcorrenciasPorPassageiro()
{
    string cpf;
    cout << "Digite o CPF do Passageiro: ";
    cin >> cpf;

    bool passageiroEncontrado = false;
    for (const Embarque &e : embarques)
    {
        if (e.passageiro->CPF == cpf && e.ocorrencia.Descricao != "")
        {
            passageiroEncontrado = true;
            cout << "Descrição: " << e.ocorrencia.Descricao << ", Data/Hora: " << e.ocorrencia.Data_Hora << ", Número da Apólice: " << e.ocorrencia.Num_Apolice << "\n";
        }
    }

    if (!passageiroEncontrado)
    {
        cout << "Nenhuma ocorrência encontrada para este passageiro.\n";
    }
}

void ListarOcorrenciasPorRoteiro()
{
    int codigo;
    cout << "Digite o Código do Roteiro: ";
    cin >> codigo;

    bool roteiroEncontrado = false;
    for (const Embarque &e : embarques)
    {
        if (e.roteiro->Codigo == codigo && e.ocorrencia.Descricao != "")
        {
            roteiroEncontrado = true;
            cout << "Descrição: " << e.ocorrencia.Descricao << ", Data/Hora: " << e.ocorrencia.Data_Hora << ", Número da Apólice: " << e.ocorrencia.Num_Apolice << "\n";
        }
    }

    if (!roteiroEncontrado)
    {
        cout << "Nenhuma ocorrência encontrada para este roteiro.\n";
    }
}

void RegistrarOcorrênciaPorRoteiro()
{
    int codigo;

    cout << "Digite o Código do Roteiro: ";
    cin >> codigo;

    bool roteiroEncontrado = false;
    for (Embarque &e : embarques)
    {
        if (e.roteiro->Codigo == codigo)
        {
            roteiroEncontrado = true;

            Embarque::Ocorrencia novaOcorrencia;

            cin.ignore(); // Limpa o buffer de entrada
            cout << "Digite a Descrição da Ocorrência: ";
            getline(cin, novaOcorrencia.Descricao);
            cout << "Digite a Data e Hora da Ocorrência (formato dd/mm/yyyy HH:mm): ";
            cin >> novaOcorrencia.Data_Hora;
            cout << "Digite o Número da Apólice: ";
            cin >> novaOcorrencia.Num_Apolice;

            e.ocorrencia = novaOcorrencia;

            cout << "Ocorrência registrada com sucesso para o roteiro " << codigo << ".\n";
        }
    }

    if (!roteiroEncontrado)
    {
        cout << "Nenhum roteiro encontrado com o código fornecido.\n";
    }
}

void GestaoOcorrencias()
{
    int escolha;
    do
    {
        cout << "\nMenu de Ocorrências:\n";
        cout << "1. Incluir Ocorrência\n";
        cout << "2. Excluir Ocorrência\n";
        cout << "3. Alterar Ocorrência\n";
        cout << "4. Listar Ocorrências por Passageiro\n";
        cout << "5. Listar Ocorrências por Roteiro\n";
        cout << "6. Registrar Ocorrência por Roteiro\n"; // Nova opção
        cout << "0. Sair\n";
        cout << "Escolha uma opção: ";
        cin >> escolha;

        switch (escolha)
        {
        case 1:
            IncluirOcorrencia();
            break;
        case 2:
            ExcluirOcorrencia();
            break;
        case 3:
            AlterarOcorrencia();
            break;
        case 4:
            ListarOcorrenciasPorPassageiro();
            break;
        case 5:
            ListarOcorrenciasPorRoteiro();
            break;
        case 6:
            RegistrarOcorrênciaPorRoteiro(); // Nova opção
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
    int escolha;
    do
    {
        cout << "\nMenu Inicial:\n";
        cout << "1. Gestão de Passageiros\n";
        cout << "2. Gestão de Roteiros\n";
        cout << "3. Gestão de Embarques\n";
        cout << "4. Gestão de Ocorrências\n";
        cout << "0. Sair do Programa\n";
        cout << "Escolha uma opção: ";
        cin >> escolha;

        switch (escolha)
        {
        case 1:
            IncluirPassageiro();
            break;
        case 2:
            IncluirRoteiro();
            break;
        case 3:
            IncluirEmbarque();
            break;
        case 4:
            GestaoOcorrencias();
            break;
        case 0:
            break;
        default:
            cout << "Opção inválida. Tente novamente.\n";
        }
    } while (escolha != 0);

    return 0;
}//Fim 
