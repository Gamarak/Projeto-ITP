#include <iostream>
#include <string>
#include <ctime>
#include "terreno.h"
#include "imagem.h"
#include "paleta.h"

int main() {
  srand(time(NULL));
  std::string nomePaleta, nomeImagem;
  int escolha;

  std::cout << "Escolha uma opcao:\n";
  std::cout << "1 - Gerar um novo mapa.\n";
  std::cout << "2 - Ler um mapa de um arquivo existente.\n";
  std::cout << "Digite sua escolha (1 ou 2): ";
  std::cin >> escolha;

  std::cout << "Digite o nome do arquivo da paleta de cores: ";
  std::cin >> nomePaleta;
  std::cout << "Digite o nome do arquivo de imagem que sera gerada (.ppm): ";
  std::cin >> nomeImagem;

  Paleta paleta (nomePaleta);
  Terreno terreno;

  if (escolha == 1) {
    int n;
    double rugosidade;
    std::cout << "Digite o tamanho do terreno, n, (onde tamanho = 2^n + 1): ";
    std::cin >> n;
    std::cout << "Digite a rugosidade do terreno: ";
    std::cin >> rugosidade;

    terreno.gerarMapaAltitudes(n, rugosidade);

  } else if (escolha == 2) {
    std::string nomeArquivoMapa;
    std::cout << "Digite o nome do arquivo do mapa de altitudes (.txt): ";
    std::cin >> nomeArquivoMapa;

    if (!terreno.lerMapaAltitudes(nomeArquivoMapa)) {
      std::cout << "Erro ao ler o mapa." << std::endl;
      return 1;
    }
  } else {
    std::cout << "Escolha invalida." << std::endl;
    return 1;
  }
  
  Imagem imagem = terreno.gerarImagem(paleta);

  if (imagem.salvarPPM(nomeImagem)) {
    std::cout << "Imagem salva com sucesso em " << nomeImagem << std::endl;
  } else {
    std::cout << "Erro ao salvar a imagem em " << nomeImagem << std::endl;
  }
  return 0;
}