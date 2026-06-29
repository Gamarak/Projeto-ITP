#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "terreno.h"
#include <fstream>

TEST_CASE("Teste 1: Construtor com inicialização padrão (5x5)") {
    // N = 2 gera uma matriz de (2^2 + 1) = 5x5
    Terreno t(2);
    
    REQUIRE(t.obterLinhasY() == 5);
    REQUIRE(t.obterColunasX() == 5);
    
    // Todas as células devem começar com o valor default (0.0)
    for (int l = 0; l < 5; ++l) {
        for (int c = 0; c < 5; ++c) {
            CHECK(t.obterAltitude(l, c) == 0.0);
        }
    }
}

TEST_CASE("Teste 2: Salvar mapa padrão 5x5 em arquivo") {
    Terreno t(2);
    std::string arquivoTeste = "test_mapa_5x5.txt";
    
    REQUIRE(t.salvarMapaAltitudes(arquivoTeste) == true);
    
    std::ifstream arquivo(arquivoTeste);
    REQUIRE(arquivo.is_open() == true);
    
    int linhas, colunas;
    arquivo >> linhas >> colunas;
    CHECK(linhas == 5);
    CHECK(colunas == 5);
    
    // Garante que todos os 25 valores salvos são 0.0
    double valor;
    for (int i = 0; i < 25; ++i) {
        arquivo >> valor;
        CHECK(valor == 0.0);
    }
    arquivo.close();
}

TEST_CASE("Teste 3: Leitura de uma matriz 3x3 a partir de arquivo") {
    std::string arquivoLeitura = "test_mapa_3x3.txt";
    
    // Cria um arquivo terreno 3x3 para leitura
    std::ofstream arquivoSaida(arquivoLeitura);
    arquivoSaida << "3 3\n";
    arquivoSaida << "10.5 15.0 20.5\n";
    arquivoSaida << "30.0 35.5 40.0\n";
    arquivoSaida << "50.5 55.0 60.5\n";
    arquivoSaida.close();
    
    Terreno t; // Construtor sem parâmetros (0x0)
    REQUIRE(t.lerMapaAltitudes(arquivoLeitura) == true);
    
    CHECK(t.obterLinhasY() == 3);
    CHECK(t.obterColunasX() == 3);
    
    // Verifica pontos estratégicos lidos do arquivo
    CHECK(t.obterAltitude(0, 0) == 10.5);
    CHECK(t.obterAltitude(1, 1) == 35.5);
    CHECK(t.obterAltitude(2, 2) == 60.5);
    CHECK(t.obterAltitude(0, 2) == 20.5);
}

TEST_CASE("Teste 4: Consistência do Diamond-Square com rugosidade 0.0 (9x9)") {
    // N = 3 gera uma matriz 9x9 (2^3 + 1)
    Terreno t(3);
    
    // Inicializa manualmente os quatro cantos com uma altura fixa
    double alturaFixa = 42.0;
    t.definirAltitude(0, 0, alturaFixa);
    t.definirAltitude(0, 8, alturaFixa);
    t.definirAltitude(8, 0, alturaFixa);
    t.definirAltitude(8, 8, alturaFixa);
    
    // Executa a geração com rugosidade 0.0 (sem deslocamento aleatório)
    t.gerarMapaAltitudes(3, 0.0);
    
    // O algoritmo deve resultar em um mapa completamente plano com o valor inicial
    for (int l = 0; l < 9; ++l) {
        for (int c = 0; c < 9; ++c) {
            CHECK(t.obterAltitude(l, c) == alturaFixa);
        }
    }
}