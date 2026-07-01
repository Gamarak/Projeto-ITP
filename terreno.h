#ifndef terreno_h
#define terreno_h 
#include <vector>
#include <string>
#include "imagem.h"
#include "paleta.h"

class Terreno {
  private:
    std::vector<std::vector<double>> mapaAltitudes;
    int totalLinhas;
    int totalColunas;
    void etapaDiamond(int tamanho, double deslocamento);
    void etapaSquare(int tamanho, double deslocamento);
    
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
    void definirAltitude(int linha, int coluna, double valor);
    Imagem gerarImagem(Paleta& paleta);
};

#endif