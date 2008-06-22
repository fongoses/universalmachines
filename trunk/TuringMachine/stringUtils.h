#include <string>
#include <vector>
#include <fstream>
#include <algorithm>


class StringUtils
{
	public:
		static string toLower (string S)
		{
			string L="";
			for (int i=0; i<(int)S.size(); i++) L+= tolower(S[i]);
			return L;
		}
		
		static char* toChar (string s)
		{
			char* v = (char *) malloc((s.size()+1)*sizeof(char));
			for (int i=0; i<(int)s.size(); i++)
			{
				v[i] = s[i];
			}
			v[s.size()]='\0';
			return v;
		}
		
		static bool inicioCoincidente(string s1, string s2)
		{
			int t = min(s1.size(), s2.size());
			for (int i=0; i<t; i++)
			{
				if (s1[i]!=s2[i]) return false;
			}
			return true;
		}
		
		//tokenizador generico
		static vector<string> tokenize (string S, string d = " ")
		{
			vector<string> resposta;
			int i=0, j;
			
			while(i<(int)S.size())
			{
				j = S.find_first_of(d,i);
				if (i==j) i++;
				else
				{
					resposta.push_back(S.substr(i,j-i));
					//cout << i << ", " << j << "  -  " << S.substr(i,j-i) << endl;
					if (j== -1) break;
					i=j+1;
				}
			}
			
			return resposta;
		}
		
		
		//tokenizador com delimitadores {} ou ()
		static vector<string> tokenizeD (string S, char abre = '{', char fecha = '}') throw (string)
		{
			vector<string> resposta;
			int i=0, j;
			
			while(i<(int)S.size())
			{
				j = S.find_first_of(" ",i);
				while ((j<(int)S.size())&&(!ehFechada(S.substr(i,j-i),abre,fecha)))
				{
					j = S.find_first_of(" ",j+1);
				}
				if (!ehFechada(S.substr(i,j-i),abre,fecha)) throw string("Expressao mal formada!");
				
				if (i==j) i++;
				
				else
				{
					resposta.push_back(S.substr(i,j-i));
					//cout << i << ", " << j << "  -  " << S.substr(i,j-i) << endl;
					if (j== -1) break;
					i=j+1;
				}
			}
			
			return resposta;
		}

		static bool ehFechada (string S, char abre, char fecha)
		{
			int nAbre=0, nFecha=0;
			for (int i=0; i<(int)S.size(); i++)
			{
				if (S[i]==abre) nAbre++;
				if (S[i]==fecha) nFecha++;
			}
			if (nAbre == nFecha) return true;
			else return false;
		}
		
		static string tiraDelimitadores(string S, char abre = '{', char fecha = '}')
		{
			int i = S.find_first_of(abre);
			int j = S.find_last_of(fecha);
			return S.substr(i+1,j-i-1);
		}
		
		static bool contem(string S, string t)
		{
			if (S.find_first_of(t)<S.size()) 
				return true;
			else return false;
		}
		
		//Operadores basicos sao operadores sem delimitadores como %casa ou $sn e operadores
		//compostos sao aqueles com delimitadores, por exemplo, ?{$sn} ou +{%ou %e}
		static vector<string> operadorOperandos (string S, vector<string> OperadorBasico, vector<string> OperadorComposto, char abre = '{', char fecha = '}') throw (string)
		{
			vector<string> resposta;
			
			for (int i=0; i<(int)OperadorBasico.size(); i++)
			{
				if (inicioCoincidente(S,OperadorBasico[i]))
				{
					
					int j = OperadorBasico[i].size();
					
					resposta.push_back(S.substr(0,j));
					
					if (j<(int)S.size())
						resposta.push_back(S.substr(j,S.size()-j));
					
					if (contem(resposta[1]," ")||contem(resposta[1],"{")||contem(resposta[1],"}"))
					{
						throw string("Erro de sintaxe!");
					}
					
					return resposta;
				}
			}
			
			for (int i=0; i<(int)OperadorComposto.size(); i++)
			{
				if (inicioCoincidente(S,OperadorComposto[i]))
				{
					int j = OperadorComposto[i].size();
					
					resposta.push_back(S.substr(0,j));
					
					vector<string> u = tokenizeD(tiraDelimitadores(S));
					
					for (int i=0; i<(int)u.size(); i++)
					{
						resposta.push_back(u[i]);
					}
					
					return resposta;
				}
			}
			
			throw string("Erro de sintaxe!");
		}
		
};
