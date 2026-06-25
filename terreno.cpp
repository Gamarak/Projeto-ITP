#include "terreno.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <ctime>

Terreno::Terreno() {
    linhasY = 0;
    colunasX = 0;
}

Terreno::Terreno(int n) {
    int tamanho = pow(2, n) + 1;
    linhasY = tamanho;
    colunasX = tamanho;
    mapaAltitudes.assign(tamanho, std::vector<double>(tamanho, 0.0));
};

Terreno::~Terreno(){}

int Terreno::obterLinhasY() {
    return linhasY;
}

int Terreno::obterColunasX() {
    return colunasX;
}

double Terreno::obterAltitude(int linha, int coluna) {
    if (linha < 0 || linha >= linhasY || coluna < 0 || coluna >= colunasX) {
      return 0.0;
    }
    return mapaAltitudes[linha][coluna];
}

const std::vector<std::vector<double>>& Terreno::obterAltitudes() {
    return mapaAltitudes;
}

void Terreno::gerarMapaAltitudes(int n, double rugosidade) {
    int tamanho = pow(2, n) + 1;
    linhasY = tamanho;
    colunasX = tamanho;
    mapaAltitudes.assign(tamanho, std::vector<double>(tamanho, 0.0));

    mapaAltitudes[0][0] = (rand() % 1001) / 10.0;
    mapaAltitudes[0][tamanho - 1] = (rand() % 1001) / 10.0;
    mapaAltitudes[tamanho - 1][0] = (rand() % 1001) / 10.0;
    mapaAltitudes[tamanho - 1][tamanho - 1] = (rand() % 1001) / 10.0;

    int passo = tamanho - 1;
    double deslocamento = 50.0;

    while (passo > 1) {
      etapaDiamond(passo, deslocamento);
      etapaSquare(passo, deslocamento);
      
      passo /= 2;
      deslocamento *= rugosidade;
    }
}

void Terreno::etapaDiamond(int tamanho, double deslocamento) {
   for (int y = 0; y < linhasY - 1; y += tamanho) {
        for (int x = 0; x < colunasX - 1; x += tamanho) {
            int meioX = x + tamanho / 2;
            int meioY = y + tamanho / 2;

            double supEsq = mapaAltitudes[y][x];
            double supDir = mapaAltitudes[y][x + tamanho];
            double infEsq = mapaAltitudes[y + tamanho][x];
            double infDir = mapaAltitudes[y + tamanho][x + tamanho];
            double media = (supEsq + supDir + infEsq + infDir) / 4.0;

            double aleatorio = ((rand() % 1000) / 1000.0) * deslocamento * 2 - deslocamento;
            mapaAltitudes[meioY][meioX] = media + aleatorio;

            mapaAltitudes[meioY][meioX] = std::max(0.0, std::min(100.0, mapaAltitudes[meioY][meioX]));
        }
    }
}

void Terreno::etapaSquare(int tamanho, double deslocamento) {
  int metade = tamanho/2;
  for (int y = 0; y < linhasY; y += metade) {
        for (int x = (y + metade) % tamanho; x < colunasX; x += tamanho) {
            double soma = 0.0;
            int cont = 0;

            if (y - metade >= 0) {
                soma += mapaAltitudes[y - metade][x];
                cont++;
            }
            if (y + metade < linhasY) {
                soma += mapaAltitudes[y + metade][x];
                cont++;
            }
            if (x - metade >= 0) {
                soma += mapaAltitudes[y][x - metade];
                cont++;
            }
            if (x + metade < colunasX) {
                soma += mapaAltitudes[y][x + metade];
                cont++;
            }

            double media = soma / cont;
            double aleatorio = ((rand() % 1000) / 1000.0) * deslocamento * 2 - deslocamento;
            mapaAltitudes[y][x] = media + aleatorio;
            mapaAltitudes[y][x] = std::max(0.0, std::min(100.0, mapaAltitudes[y][x]));
        }
    }
}

bool Terreno::salvarMapaAltitudes(const std::string& nomeArquivo) {
    std::ofstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        return false;
    }
    arquivo << linhasY << " " << colunasX;
    for (int l = 0; l < linhasY; ++l) {
        for (int c = 0; c < colunasX; ++c) {
            arquivo << mapaAltitudes[l][c];
            if (c < colunasX - 1) {
                arquivo << " ";
            }
        }
        arquivo << std::endl;
    }
    arquivo.close();
    return true;
}

bool Terreno::lerMapaAltitudes(const std::string& nomeArquivo) {
    std::ifstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        return false;
    }
    int novasLinhasY, novasColunasX;
    if (!(arquivo >> novasLinhasY >> novasColunasX)) {
        arquivo.close();
        return false;
    }
    colunasX = novasColunasX;
    linhasY = novasLinhasY;
    mapaAltitudes.assign(linhasY, std::vector<double>(colunasX, 0.0));
    for (int l = 0; l < linhasY; l++) {
        for (int c = 0; c < colunasX; c++) {
            if (!(arquivo >> mapaAltitudes[l][c])) {
                arquivo.close();
                return false;
            }
        }
    }
    arquivo.close();
    return true;
}