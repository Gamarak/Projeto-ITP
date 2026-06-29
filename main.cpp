#include <iostream>
#include <string>
#include <ctime>
#include "terreno.h"
#include "imagem.h"
#include "paleta.h"

int main() {
  srand(time(NULL));
  std::string nomePaleta, nomeImagem;
  int n;
  
  std::cin >> nomePaleta >> nomeImagem >> n;

  Paleta paleta (nomePaleta);
  Terreno terreno (n);
  terreno.gerarMapaAltitudes(n, 0.5);
  Imagem imagem = terreno.gerarImagem(paleta);

  if (imagem.salvarPPM(nomeImagem)) {
    std::cout << "Imagem salva com sucesso em " << nomeImagem << std::endl;
  } else {
    std::cout << "Erro ao salvar a imagem em " << nomeImagem << std::endl;
  }
  return 0;
}