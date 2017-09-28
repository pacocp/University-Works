#include <iostream>
using namespace std;
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <string>
#include <fstream>
//#include <algorithm>
#include <vector>
#include <chrono>
using namespace std::chrono;
high_resolution_clock::time_point tantes, tdespues;
duration<double> transcurrido;


int main(int argc, char * argv[])
{

  if (argc != 3)
    {
      cerr << "Formato " << argv[0] << "<ruta_del_archivo_de_entrada> <num_vect>" << endl;
      return -1;
    }

    /*
    Lo que haremos será leer cual es el archivo de entrada, la cantidad de filas y la cantidad de elementos por fila


    */
  int n = atoi(argv[2]);
  int k=n;
  int a=0;
  int num;
  string ruta=argv[1];
  ifstream archivo(ruta.c_str());
  vector<int> gigante ;
  while(a<n*k){
  archivo >> num;
  gigante.push_back(num);
  a++;
}
tantes = high_resolution_clock::now();

 for(int i=0;i<gigante.size()-1;i++)
    for (int j=i+1; j<gigante.size(); j++)
      if(gigante.at(i) > gigante.at(j)){
        num=gigante.at(i);
        gigante.at(i) = gigante.at(j);
        gigante.at(j) = num;
      }
  tdespues = high_resolution_clock::now();
  transcurrido = duration_cast<duration<double>>(tdespues - tantes);
  cout <<  n << " "<< transcurrido.count() << endl;

}
