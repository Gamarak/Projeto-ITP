#ifndef imagem_h
#define imagem_h
#include "paleta.h"
#include <string>
#include <algorithm>
typedef Cor Pixel;

class Imagem {
  private:
    int largura;
    int altura;
    Pixel* pixels;

  public:
    Imagem();
    Imagem(int l, int a);
    ~Imagem();
    int obterLargura() const;
    int obterAltura() const;
    Pixel& operator()(int coluna, int linha);
    const Pixel& operator()(int coluna, int linha) const;
    bool lerPPM(string nomeArquivo);
    bool salvarPPM(string nomeArquivo);
    
};

#endif