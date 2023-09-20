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

    int novaDuracao;
    std::cout << "Digite a nova duração (em minutos): ";
    std::cin >> novaDuracao;

    for (Embarque& e : embarques) {
        if (e.roteiro->Codigo == codigo && e.passageiro->CPF == cpf) {
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

void GestaoEmbarques() {
    int escolha;
    do {
        std::cout << "\nMenu de Embarques:\n";
        std::cout << "1. Incluir Embarque\n";
        std::cout << "2. Excluir um Embarque\n";
        std::cout << "3. Alterar Embarque\n";
        std::cout << "4. Listar todos os Embarques\n";
        std::cout << "0. Sair\n";
        std::cout << "Escolha uma opção: ";
        std::cin >> escolha;

        switch (escolha) {
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
                std::cout << "Opção inválida. Tente novamente.\n";
        }
    } while (escolha != 0);
}

int main() {
    Passageiro p1 = {"12345678900", "Joao Silva", "01/01/1990"};
    Passageiro p2 = {"98765432100", "Maria Oliveira", "05/05/1985"};
    passageiros.push_back(p1);
    passageiros.push_back(p2);

    Roteiro r1 = {1, "20/09/2023 10:00", 120, "Cidade A", "Cidade B"};
    Roteiro r2 = {2, "21/09/2023 15:00", 90, "Cidade B", "Cidade C"};
    roteiros.push_back(r1);
    roteiros.push_back(r2);

    int escolha;
    do {
        std::cout << "\nMenu Inicial:\n";
        std::cout << "1. Gestão de Passageiros\n";
        std::cout << "2. Gestão de Roteiros\n";
        std::cout << "3. Gestão de Embarques\n";
        std::cout << "0. Sair do Programa\n";
        std::cout << "Escolha uma opção: ";
        std::cin >> escolha;

        switch (escolha) {
            case 1:
                int escolhaPassageiros;
                do {
                    std::cout << "\nMenu de Gestão de Passageiros:\n";
                    std::cout << "1. Incluir Passageiro\n";
                    std::cout << "2. Listar Passageiros\n";
                    std::cout << "0. Voltar\n";
                    std::cout << "Escolha uma opção: ";
                    std::cin >> escolhaPassageiros;

                    switch (escolhaPassageiros) {
                        case 1:
                            IncluirPassageiro();
                            break;
                        case 2:
                            ListarPassageiros();
                            break;
                        case 0:
                            break;
                        default:
                            std::cout << "Opção inválida. Tente novamente.\n";
                    }
                } while (escolhaPassageiros != 0);
                break;
            case 2:
                int escolhaRoteiros;
                do {
                    std::cout << "\nMenu de Gestão de Roteiros:\n";
                    std::cout << "1. Incluir Roteiro\n";
                    std::cout << "2. Listar Roteiros\n";
                    std::cout << "0. Voltar\n";
                    std::cout << "Escolha uma opção: ";
                    std::cin >> escolhaRoteiros;

                    switch (escolhaRoteiros) {
                        case 1:
                            IncluirRoteiro();
                            break;
                        case 2:
                            ListarRoteiros();
                            break;
                        case 0:
                            break;
                        default:
                            std::cout << "Opção inválida. Tente novamente.\n";
                    }
                } while (escolhaRoteiros != 0);
                break;
            case 3:
                GestaoEmbarques();
                break;
            case 0:
                break;
            default:
                std::cout << "Opção inválida. Tente novamente.\n";
        }
    } while (escolha != 0);

    return 0;
}
