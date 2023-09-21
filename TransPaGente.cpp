#include <iostream>
#include <vector>
#include <ctime>

class Passageiro {
public:
    std::string CPF;
    std::string Nome;
    std::string DtNascimento;
};

class Roteiro {
public:
    int Codigo;
    std::string Data_Horaprevista;
    int Duracao_prevista;
    std::string Origem;
    std::string Destino;
};

class Embarque {
public:
    bool Realizado;
    std::string Data_Hora;
    int Duracao;
    Passageiro* passageiro;
    Roteiro* roteiro;
    struct Ocorrencia {
        std::string Descricao;
        std::string Data_Hora;
        int Num_Apolice;
    } ocorrencia;
};

std::vector<Passageiro> passageiros;
std::vector<Roteiro> roteiros;
std::vector<Embarque> embarques;

void IncluirPassageiro() {
    Passageiro novoPassageiro;
    std::cout << "Digite o CPF do Passageiro: ";
    std::cin >> novoPassageiro.CPF;
    std::cout << "Digite o Nome do Passageiro: ";
    std::cin.ignore();
    std::getline(std::cin, novoPassageiro.Nome);
    std::cout << "Digite a Data de Nascimento do Passageiro: ";
    std::cin >> novoPassageiro.DtNascimento;

    passageiros.push_back(novoPassageiro);
    std::cout << "Passageiro cadastrado com sucesso.\n";
}

void ListarPassageiros() {
    std::cout << "Lista de Passageiros:\n";
    for (const Passageiro& p : passageiros) {
        std::cout << "CPF: " << p.CPF << ", Nome: " << p.Nome << ", Data de Nascimento: " << p.DtNascimento << "\n";
    }
}

void IncluirRoteiro() {
    Roteiro novoRoteiro;
    std::cout << "Digite o Código do Roteiro: ";
    std::cin >> novoRoteiro.Codigo;
    std::cout << "Digite a Data e Hora Prevista do Roteiro (formato dd/mm/yyyy HH:mm): ";
    std::cin.ignore();
    std::getline(std::cin, novoRoteiro.Data_Horaprevista);
    std::cout << "Digite a Duração Prevista do Roteiro (em minutos): ";
    std::cin >> novoRoteiro.Duracao_prevista;
    std::cout << "Digite a Origem do Roteiro: ";
    std::cin.ignore();
    std::getline(std::cin, novoRoteiro.Origem);
    std::cout << "Digite o Destino do Roteiro: ";
    std::getline(std::cin, novoRoteiro.Destino);

    roteiros.push_back(novoRoteiro);
    std::cout << "Roteiro cadastrado com sucesso.\n";
}

void ListarRoteiros() {
    std::cout << "Lista de Roteiros:\n";
    for (const Roteiro& r : roteiros) {
        std::cout << "Código: " << r.Codigo << ", Data/Hora Prevista: " << r.Data_Horaprevista << ", Duração Prevista: " << r.Duracao_prevista << " minutos, Origem: " << r.Origem << ", Destino: " << r.Destino << "\n";
    }
}

void IncluirEmbarque() {
    std::string cpf;
    int codigo;

    std::cout << "Digite o CPF do Passageiro: ";
    std::cin >> cpf;

    bool passageiroEncontrado = false;
    for (Passageiro& p : passageiros) {
        if (p.CPF == cpf) {
            passageiroEncontrado = true;
            break;
        }
    }

    if (!passageiroEncontrado) {
        std::cout << "CPF não encontrado. Embarque cancelado.\n";
        return;
    }

    std::cout << "Digite o Código do Roteiro: ";
    std::cin >> codigo;

    bool roteiroEncontrado = false;
    for (Roteiro& r : roteiros) {
        if (r.Codigo == codigo) {
            roteiroEncontrado = true;
            break;
        }
    }

    if (!roteiroEncontrado) {
        std::cout << "Código do Roteiro não encontrado. Embarque cancelado.\n";
        return;
    }

    Embarque novoEmbarque;
    novoEmbarque.Realizado = false;

    std::time_t t = std::time(0);
    novoEmbarque.Data_Hora = std::ctime(&t);

    novoEmbarque.passageiro = &passageiros.back(); 
    novoEmbarque.roteiro = &roteiros.back(); 

    embarques.push_back(novoEmbarque);

    std::cout << "Embarque registrado com sucesso.\n";
}

void ExcluirEmbarque() {
    int codigo;

    std::cout << "Digite o Código do Roteiro: ";
    std::cin >> codigo;

    std::cout << "Passageiros embarcados no roteiro " << codigo << ":\n";
    for (const Embarque& e : embarques) {
        if (e.roteiro->Codigo == codigo) {
            std::cout << "CPF: " << e.passageiro->CPF << ", Nome: " << e.passageiro->Nome << "\n";
        }
    }

    std::string cpf;
    std::cout << "Digite o CPF do passageiro que não embarcará: ";
    std::cin >> cpf;

    for (auto it = embarques.begin(); it != embarques.end(); ++it) {
        if (it->roteiro->Codigo == codigo && it->passageiro->CPF == cpf) {
            embarques.erase(it);
            std::cout << "Embarque excluído com sucesso.\n";
            return;
        }
    }

    std::cout << "Embarque não encontrado.\n";
}

void AlterarEmbarque() {
    int codigo;

    std::cout << "Digite o Código do Roteiro: ";
    std::cin >> codigo;

    std::cout << "Passageiros embarcados no roteiro " << codigo << ":\n";
    for (Embarque& e : embarques) {
        if (e.roteiro->Codigo == codigo) {
            std::cout << "CPF: " << e.passageiro->CPF << ", Nome: " << e.passageiro->Nome << "\n";
        }
    }

    std::string cpf;
    std::cout << "Digite o CPF do passageiro: ";
    std::cin >> cpf;

    for (Embarque& e : embarques) {
        if (e.roteiro->Codigo == codigo && e.passageiro->CPF == cpf) {
            int novaDuracao;
            std::cout << "Digite a nova duração do Embarque (em minutos): ";
            std::cin >> novaDuracao;
            e.Duracao = novaDuracao;
            std::cout << "Embarque alterado com sucesso.\n";
            return;
        }
    }

    std::cout << "Embarque não encontrado.\n";
}

void ListarEmbarques() {
    std::cout << "Lista de Embarques:\n";
    for (const Embarque& e : embarques) {
        std::cout << "Passageiro: " << e.passageiro->Nome << ", Roteiro: " << e.roteiro->Codigo << ", Realizado: " << (e.Realizado ? "Sim" : "Não") << ", Data/Hora: " << e.Data_Hora << ", Duração: " << e.Duracao << " minutos\n";
    }
}

void IncluirOcorrencia() {
    std::string cpf;
    int codigo;

    std::cout << "Digite o CPF do Passageiro: ";
    std::cin >> cpf;

    bool passageiroEncontrado = false;
    for (Passageiro& p : passageiros) {
        if (p.CPF == cpf) {
            passageiroEncontrado = true;
            break;
        }
    }

    if (!passageiroEncontrado) {
        std::cout << "CPF não encontrado. Inclusão de ocorrência cancelada.\n";
        return;
    }

    std::cout << "Digite o Código do Roteiro: ";
    std::cin >> codigo;

    bool roteiroEncontrado = false;
    for (Roteiro& r : roteiros) {
        if (r.Codigo == codigo) {
            roteiroEncontrado = true;
            break;
        }
    }

    if (!roteiroEncontrado) {
        std::cout << "Código do Roteiro não encontrado. Inclusão de ocorrência cancelada.\n";
        return;
    }

    for (Embarque& e : embarques) {
        if (e.passageiro->CPF == cpf && e.roteiro->Codigo == codigo) {
            std::cin.ignore(); // Limpa o buffer de entrada
            std::cout << "Digite a Descrição da Ocorrência: ";
            std::getline(std::cin, e.ocorrencia.Descricao);
            std::cout << "Digite a Data e Hora da Ocorrência (formato dd/mm/yyyy HH:mm): ";
            std::cin >> e.ocorrencia.Data_Hora;
            std::cout << "Digite o Número da Apólice: ";
            std::cin >> e.ocorrencia.Num_Apolice;

            std::cout << "Ocorrência registrada com sucesso.\n";
            return;
        }
    }

    std::cout << "Embarque não encontrado para registrar a ocorrência.\n";
}

void ExcluirOcorrencia() {
    std::string cpf;
    int codigo;

    std::cout << "Digite o CPF do Passageiro: ";
    std::cin >> cpf;

    bool passageiroEncontrado = false;
    for (Passageiro& p : passageiros) {
        if (p.CPF == cpf) {
            passageiroEncontrado = true;
            break;
        }
    }

    if (!passageiroEncontrado) {
        std::cout << "CPF não encontrado. Exclusão de ocorrência cancelada.\n";
        return;
    }

    std::cout << "Digite o Código do Roteiro: ";
    std::cin >> codigo;

    bool roteiroEncontrado = false;
    for (Roteiro& r : roteiros) {
        if (r.Codigo == codigo) {
            roteiroEncontrado = true;
            break;
        }
    }

    if (!roteiroEncontrado) {
        std::cout << "Código do Roteiro não encontrado. Exclusão de ocorrência cancelada.\n";
        return;
    }

    for (Embarque& e : embarques) {
        if (e.passageiro->CPF == cpf && e.roteiro->Codigo == codigo) {
            e.ocorrencia = {}; // Limpa a ocorrência
            std::cout << "Ocorrência excluída com sucesso.\n";
            return;
        }
    }

    std::cout << "Embarque não encontrado para excluir a ocorrência.\n";
}

void AlterarOcorrencia() {
    std::string cpf;
    int codigo;

    std::cout << "Digite o CPF do Passageiro: ";
    std::cin >> cpf;

    bool passageiroEncontrado = false;
    for (Passageiro& p : passageiros) {
        if (p.CPF == cpf) {
            passageiroEncontrado = true;
            break;
        }
    }

    if (!passageiroEncontrado) {
        std::cout << "CPF não encontrado. Alteração de ocorrência cancelada.\n";
        return;
    }

    std::cout << "Digite o Código do Roteiro: ";
    std::cin >> codigo;

    bool roteiroEncontrado = false;
    for (Roteiro& r : roteiros) {
        if (r.Codigo == codigo) {
            roteiroEncontrado = true;
            break;
        }
    }

    if (!roteiroEncontrado) {
        std::cout << "Código do Roteiro não encontrado. Alteração de ocorrência cancelada.\n";
        return;
    }

    for (Embarque& e : embarques) {
        if (e.passageiro->CPF == cpf && e.roteiro->Codigo == codigo) {
            Embarque::Ocorrencia& ocorrencia = e.ocorrencia;

            std::cout << "Descrição atual: " << ocorrencia.Descricao << "\n";
            std::cout << "Deseja alterar a Descrição? (s/n): ";
            char opcao;
            std::cin >> opcao;
            if (opcao == 's' || opcao == 'S') {
                std::cin.ignore(); // Limpa o buffer de entrada
                std::cout << "Digite a nova Descrição: ";
                std::getline(std::cin, ocorrencia.Descricao);
            }

            std::cout << "Data e Hora atual: " << ocorrencia.Data_Hora << "\n";
            std::cout << "Deseja alterar a Data e Hora? (s/n): ";
            std::cin >> opcao;
            if (opcao == 's' || opcao == 'S') {
                std::cout << "Digite a nova Data e Hora (formato dd/mm/yyyy HH:mm): ";
                std::cin >> ocorrencia.Data_Hora;
            }

            std::cout << "Número da Apólice atual: " << ocorrencia.Num_Apolice << "\n";
            std::cout << "Deseja alterar o Número da Apólice? (s/n): ";
            std::cin >> opcao;
            if (opcao == 's' || opcao == 'S') {
                std::cout << "Digite o novo Número da Apólice: ";
                std::cin >> ocorrencia.Num_Apolice;
            }

            std::cout << "Ocorrência alterada com sucesso.\n";
            return;
        }
    }

    std::cout << "Embarque não encontrado para alterar a ocorrência.\n";
}

void ListarOcorrenciasPorPassageiro() {
    std::string cpf;
    std::cout << "Digite o CPF do Passageiro: ";
    std::cin >> cpf;

    bool passageiroEncontrado = false;
    for (const Embarque& e : embarques) {
        if (e.passageiro->CPF == cpf && e.ocorrencia.Descricao != "") {
            passageiroEncontrado = true;
            std::cout << "Descrição: " << e.ocorrencia.Descricao << ", Data/Hora: " << e.ocorrencia.Data_Hora << ", Número da Apólice: " << e.ocorrencia.Num_Apolice << "\n";
        }
    }

    if (!passageiroEncontrado) {
        std::cout << "Nenhuma ocorrência encontrada para este passageiro.\n";
    }
}

void ListarOcorrenciasPorRoteiro() {
    int codigo;
    std::cout << "Digite o Código do Roteiro: ";
    std::cin >> codigo;

    bool roteiroEncontrado = false;
    for (const Embarque& e : embarques) {
        if (e.roteiro->Codigo == codigo && e.ocorrencia.Descricao != "") {
            roteiroEncontrado = true;
            std::cout << "Descrição: " << e.ocorrencia.Descricao << ", Data/Hora: " << e.ocorrencia.Data_Hora << ", Número da Apólice: " << e.ocorrencia.Num_Apolice << "\n";
        }
    }

    if (!roteiroEncontrado) {
        std::cout << "Nenhuma ocorrência encontrada para este roteiro.\n";
    }
}

void GestaoOcorrencias() {
    int escolha;
    do {
        std::cout << "\nMenu de Ocorrências:\n";
        std::cout << "1. Incluir Ocorrência\n";
        std::cout << "2. Excluir Ocorrência\n";
        std::cout << "3. Alterar Ocorrência\n";
        std::cout << "4. Listar Ocorrências por Passageiro\n";
        std::cout << "5. Listar Ocorrências por Roteiro\n";
        std::cout << "0. Sair\n";
        std::cout << "Escolha uma opção: ";
        std::cin >> escolha;

        switch (escolha) {
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
            case 0:
                break;
            default:
                std::cout << "Opção inválida. Tente novamente.\n";
        }
    } while (escolha != 0);
}

int main() {
    int escolha;
    do {
        std::cout << "\nMenu Inicial:\n";
        std::cout << "1. Gestão de Passageiros\n";
        std::cout << "2. Gestão de Roteiros\n";
        std::cout << "3. Gestão de Embarques\n";
        std::cout << "4. Gestão de Ocorrências\n";
        std::cout << "0. Sair do Programa\n";
        std::cout << "Escolha uma opção: ";
        std::cin >> escolha;

        switch (escolha) {
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
                std::cout << "Opção inválida. Tente novamente.\n";
        }
    } while (escolha != 0);

    return 0;
}