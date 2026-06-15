#include "imagem.h"
#include <iostream>
#include <fstream>
using namespace std;

Imagem::Imagem() {
  largura = 0;
  altura = 0;
  pixels = nullptr;
}

Imagem::Imagem(int l, int a) {
  largura = l;
  altura = a;
  if (largura > 0 && altura > 0){
    pixels = new Pixel[largura * altura];
  } else {
    pixels = nullptr;
  }
}

Imagem::~Imagem() {
  if (pixels != nullptr) {
    delete[] pixels;
  }
}

int Imagem::obterLargura() const {
  return largura;
}
int Imagem::obterAltura() const {
  return altura;
}

Pixel& Imagem::operator()(int coluna, int linha) {
  int indice = linha * largura + coluna;
  return pixels[indice];
}
const Pixel& Imagem::operator()(int coluna, int linha) const {
  int indice = linha * largura + coluna;
  return pixels[indice];
}

bool Imagem::salvarPPM(string nomeArquivo) {
  ofstream arquivo(nomeArquivo);
  if (!arquivo.is_open()) {
    return false;
  }
  arquivo << "P3" << endl;
  arquivo << largura << " " << altura << endl;
  arquivo << "255" << endl;

  for (int l = 0; l < altura; l++) {
    for (int c = 0; c < largura; c++){
      int indice = l * largura + c;
      arquivo << pixels[indice].r << " " << pixels[indice].g << " " << pixels[indice].b;
      if (l == altura - 1 && c == largura - 1) {
      } else {
        arquivo << endl;
      }
    }
  }
  arquivo.close();
  return true;
}

bool Imagem::lerPPM(string nomeArquivo) {
  ifstream arquivo(nomeArquivo);
  if (!arquivo.is_open()) {
    return false;
  }
  string tipo;
  int nLargura, nAltura, mCor;

  arquivo >> tipo;
  if (tipo != "P3") {
    arquivo.close();
    return false;
  }

  arquivo >> nLargura >> nAltura;
  arquivo >> mCor;
  if (nLargura != largura || nAltura != altura) {
    if (pixels != nullptr) {
      delete[] pixels;
    }
    largura = nLargura;
    altura = nAltura;
    pixels = new Pixel[largura * altura];
  }

  for (int l = 0; l < altura; l++) {
    for (int c = 0; c < largura; c++) {
      int r, g, b;
      if (arquivo >> r >> g >> b) {
        int indice = l * largura + c;
        pixels[indice] = Pixel(r, g, b);
      }
    }
  }
  arquivo.close();
  return true;
}
