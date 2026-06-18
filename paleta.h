#ifndef paleta_h
#define paleta_h
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct Cor {
  int r, g, b;

  Cor() : r(0), g(0), b(0){}

  Cor(int vermelho, int verde, int azul){
  r = max(0, min(255, vermelho));
  g = max(0, min(255, verde));
  b = max(0, min(255, azul));
  }
};

class Paleta {
  private:
    vector<Cor> cores;

  public:
    Paleta();
    Paleta(string nomeArquivo);
    void adicionarCor(Cor c);
    int obterTamanho();
    Cor obterCor(int indice);
};

#endif
