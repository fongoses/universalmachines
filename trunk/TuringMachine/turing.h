#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <map>

using namespace std;

class Entrada;
class Saida;
class TuringMachine;

class Entrada
{
      public:
             string estado;
             string simbolo;
             
             Entrada()
             {
                      
             }
             
             Entrada(string estado, string simbolo)
             {
                    this->estado = estado;
                    this->simbolo = simbolo;
             }
             
             friend bool operator== (const Entrada& e1, const Entrada& e2);
             friend bool operator< (const Entrada& e1, const Entrada& e2);
};

bool operator== (const Entrada& e1, const Entrada& e2)
{
     return (e1.estado==e2.estado)&&(e1.simbolo==e2.simbolo);
}

bool operator< (const Entrada& e1, const Entrada& e2)
{
     if (e1.estado<e2.estado)
        return true;
     else
     {
         if ((e1.estado==e2.estado)&&(e1.simbolo<e2.simbolo))
            return true;
     }
     return false;
          
}


class Saida
{
      public:
             string estado;
             string simbolo;
             string movimento;
             
             Saida()
             {
                    
             }
             
             Saida(string estado, string simbolo, string movimento)
             {
                    this->estado = estado;
                    this->simbolo = simbolo;
                    this->movimento = movimento;
             }
             
             int move()
             {
                 if (movimento=="L") return -1;
                 if (movimento=="R") return 1;
                 if (movimento=="P") return 0;
                 return 2;
             }
           
             
             friend bool operator== (const Saida& s1, const Saida& s2);
};

bool operator== (const Saida& s1, const Saida& s2)
{
     return (s1.estado==s2.estado)&&(s1.simbolo==s2.simbolo)&&(s1.movimento==s2.movimento);
}

class TuringMachine
{
      public:
             vector<string> fita;
             string estado;
             int posicao; //posicao da cabeca
             set<string> finais;
             map<Entrada,Saida> delta;
             
             
             
             TuringMachine()
             {
                  posicao = 0;
                  
             }
             
             bool executa()
             {
                  Entrada entrada(estado,fita[posicao]);
                  if (delta.find(entrada) != delta.end())
                  {
                      Saida saida = delta[entrada];
                      //imprimeRegra(entrada,saida);
                      estado = saida.estado;
                      fita[posicao] = saida.simbolo;
                      posicao += saida.move();
                      if (posicao== (int)fita.size())
                      {
                         fita.push_back("B");                     
                      }
                  }
                  else
                  {
                      return false;
                  }
                  return false;
             }
             
             void imprimeFita()
             {
                  cout << "(" << estado << ")   ";
                  for (int i=0; i<(int)fita.size(); i++)
                  {
                      if (i==posicao)
                         cout << "[" << fita[i] << "] ";
                      else
                         cout << fita[i] << " ";
                  }
                  cout << endl;     
             }
             
             void imprimeRegra (Entrada entrada, Saida saida)
             {
                  cout << "delta(" << entrada.estado << ", " << entrada.simbolo << ") = ";
                  cout << "(" << saida.estado << ", " << saida.simbolo << ", " << saida.movimento << ")" << endl;     
             }
             
             bool final()
             {
                  if (finais.find(estado)!=finais.end())
                     return true;
                  else
                      return false;
             }
             
             
};

