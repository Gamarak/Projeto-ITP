#include "terreno.h"
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

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

