#include <iostream>
#include <random>


namespace ga{
  

  


  template<typename P> struct type_traits{
    typedef P::value_type::genome_type  genome_type;
  };


  template<typename G> struct individual{
    typedef g::value_type genome_type;
    G& genome;    
    double evaluation;   
  };


  struct takesGenome<G,G::operator()(G& g)


  template<C> struct individualOrGenome{
    
  }


  template<typename P,
           typename Evaluation,
           typename Selection,
           typename Crossover,
           typename Mutation,
           class Config=DefaultConfig           
           >
  

  void step(P& nextPop,const P& currPop,
            const Evaluation& evaluation,
            const Selection& selection, 
            const Crossover& crossover,
            const Mutation& mutation,
            const Elitarism& elitarism
            ){
    
    for (size_t i=0;i<currPop.size();i++){
      currPop[i].evaluation=oldPop[evaluation(currPop[i].genome)];      
    }
    
    std::pair<int,int> match=selection(currPop);
    elitarism.init();
    size_t i=0;
    for (;i<nextPop.size()&&elitarism(nextPop[i]);i++);
    selection.init();
    for (i=0;i<nextPop.size();i++){
      crossover(nextPop[i],currPop[match.first],currPop[match.second]);
      mutation(nextPop[i]);
    }    
  }

  
  

  class PropoptionalSelection{

    void init(){}

    template<typename P> std::pair<int,int> operator()(const P& p){
      double tot=0;
      for (int i=0;i<p.size();i++){
        tot+=p[i].evaluation;
      }
      double target= tot*rand()/RAND_MAX;
      std::pair<int,int> ret;
      double sum=0;
      for (ret.first=0;;ret.first++){
        sum+=p[ret.first].evaluation;
        if (sum>=target) break;
      }
      target= tot*rand()/RAND_MAX;
      for (ret.second=0;;ret.second++){
        sum+=p[ret.second].evaluation;
        if (sum>=target&&ret.second!=ret.first) break;
      }
      return ret;
    }
    
    
  };
          
  class OnePointCrossover{

    template<typename G> operator()(G& g,const G& g1,const G& g2){
      int split=g.length()*rand()/RAND_MAX;
      int i=0;
      for (;i<split;i++){
        g[i]=g1[i];
      }
      for (;i<g.length();i++){
        g[i]=g2[i];
      }
    }

  };


  class GaussianMutation{
    double p;
    std::default_random_engine generator;
    std::normal_distribution normal;
  public:
    Mutation(double _p,double _std):
      p(_p),normal(0,_std)
    {
    }

    temaplate<typename G> void operator()(G& g){
      for (size_t i=0;i<g.size();i++){
        if (static_cast<double>(rand())/RAND_MAX<p){
          g[i]+=normal(generator);
        }        
      }
    }
    
  };


  
  class NoElitarism{
  public:
    template<typename G> void operator
    
  };
  


int main(){
  std::vector<std::vector<double> > pop;





}
