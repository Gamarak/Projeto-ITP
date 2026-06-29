#include "paleta.h"
#include <iostream>
#include <fstream>
using namespace std;

int Paleta::hexParaRgb(const std::string& hexString) {
  int resultado = 0;
  for (char c : hexString) {
    int valorCaractere = 0;
     c = std::toupper(c); 
    if (c >= '0' && c <= '9') {
         valorCaractere = c - '0';
     } else if (c >= 'A' && c <= 'F') {
          valorCaractere = c - 'A' + 10;
     } else {
        continue; 
     }
    resultado = (resultado * 16) + valorCaractere;
  }
return resultado;
}

Paleta::Paleta(){}
Paleta::Paleta(std::string nomeArquivo) {
  std::ifstream arquivo(nomeArquivo);
  if (!arquivo.is_open()){
    std::cout << "Erro ao abrir o arquivo" << std::endl;
    return;
  }
  std::string linha;

  while (std::getline(arquivo, linha)) {
    if (!linha.empty() && linha[0] == '#' && linha.size() >= 7) {
    int r = hexParaRgb(linha.substr(1, 2));
    int g = hexParaRgb(linha.substr(3, 2));
    int b = hexParaRgb(linha.substr(5, 2));
    Cor novaCor(r, g, b);
    cores.push_back(novaCor);
    }
  }
  arquivo.close();
}

void Paleta::adicionarCor(Cor c) {
  cores.push_back(c);
}

int Paleta::obterTamanho() {
  return cores.size();
}

Cor Paleta::obterCor(int indice) {
  if(indice < 0 || indice >= cores.size()){
    return Cor();
  } 
  return cores[indice];
}