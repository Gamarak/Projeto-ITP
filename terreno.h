#ifndef terreno_h
#define terreno_h 
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>


class Terreno {
  private:
    std::vector<std::vector<double>> mapaAltitudes;
    int linhasY;
    int colunasX;
    void etapaDiamond(int x, int y, int tamanho, double deslocamento);
    void etapaSquare(int x, int y, int tamanho, double deslocamento);
    
  public:
    Terreno();
    Terreno(int n);
    ~Terreno();
    void gerarMapaAltitudes(int n, double rugosidade);
    double obterAltitude(int linha, int coluna);
    const std::vector<std::vector<double>>& obterAltitudes();
    int obterLinhasY();
    int obterColunasX();
    bool salvarMapaAltitudes(const std::string& nomeArquivo);
    bool lerMapaAltitudes(const std::string& nomeArquivo);
};

#endif //terreno_h