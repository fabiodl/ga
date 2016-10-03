#include "ga.h"

 class All7Evaluation{
  public:
    template<typename V>
    double operator()(const V& d){
      double t=0;
      for (size_t i=0;i<d.size();i++){
        t+=abs(d[i]-7);
      }
      return 1.0/(1+abs(t));
    }

  };



template<typename V>
void print(const V& v){
  for (auto i=v.begin();i!=v.end();++i){
    std::cout<<*i<<" ";
  }
}

int main(){
  
  typedef  std::vector<int> Genome;
  
  All7Evaluation evaluation;
  PropoptionalSelection selection;
  OnePointCrossover crossover;
  GaussianMutation mutation(0.3,3);
  BestElitism elitism;
  
  GaussianInitializer init(10,5,10);
  FixedCountTermination termination(40);
  PrintBestElement<Genome,print> log;

  ga::ga<std::vector<Genome > >(init,termination,evaluation,
     selection,crossover,mutation,elitism,log);



}
