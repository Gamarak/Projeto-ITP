#ifndef terreno_h
#define terreno_h 
#include <vector>
#include <string>

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
    int getLinhasY();
    int getColunasX();
    void salvarMapaAltitudes(const std::string& nomeArquivo);
    bool lerMapaAltitudes(const std::string& nomeArquivo);
    bool definirAltitudes(const std::vector<std::vector<double>>& altitudes);
  
};

#endif //terreno_h