#ifndef paleta_h
#define paleta_h
#include <string>
#include <vector>
#include <algorithm>

struct Cor {
  int r, g, b;

  Cor() : r(0), g(0), b(0){}

  Cor(int vermelho, int verde, int azul){
  r = std::max(0, std::min(255, vermelho));
  g = std::max(0, std::min(255, verde));
  b = std::max(0, std::min(255, azul));
  }
};

class Paleta {
  private:
    std::vector<Cor> cores;
    int hexParaRgb(const std::string& hexString);

  public:
    Paleta();
    Paleta(std::string nomeArquivo);
    void adicionarCor(Cor c);
    int obterTamanho();
    Cor obterCor(int indice);
};

#endif
