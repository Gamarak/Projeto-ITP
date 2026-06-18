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

Pixel& Imagem::operator()(int x, int y) {
  int indice = y * largura + x;
  return pixels[indice];
}
const Pixel& Imagem::operator()(int x, int y) const {
  int indice = y * largura + x;
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

  for (int y = 0; y < altura; y++) {
    for (int x = 0; x < largura; x++){
      const Pixel& pixel = (*this)(x, y);
      arquivo << pixel.r << " " << pixel.g << " " << pixel.b;
      if (y == altura - 1 && x == largura - 1) {
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
  if (!(arquivo >> tipo) || tipo != "P3") {
    arquivo.close();
    return false;
  }

  int novaLargura, novaAltura, nCor;
  if (!(arquivo >> novaLargura >> novaAltura >> nCor)) {
    arquivo.close();
    return false;
  }

  if (novaLargura != largura || novaAltura != altura) {
    if (pixels != nullptr) {
      delete[] pixels;
    }
    largura = novaLargura;
    altura = novaAltura;
    if (largura > 0 && altura > 0) {
      pixels = new Pixel[largura * altura];
    } else {
      pixels = nullptr;
    }
  }

  for (int y = 0; y < altura; y++) {
    for (int x = 0; x < largura; x++) {
      int r, g, b;
      if (arquivo >> r >> g >> b) {
        (*this)(x, y) = Pixel(r, g, b);
      } else {
        arquivo.close();
        return false;
      }
    }
  }
  arquivo.close();
  return true;
}
