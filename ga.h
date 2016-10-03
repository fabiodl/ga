#include <iostream>
#include <random>
#include <cstdbool>
#include <algorithm>

namespace ga{

  template<typename Evaluation,
    typename Pop,
    typename Score>
    void evaluate(Score& score,const Pop& currPop,Evaluation& evaluation){
      for (size_t i=0;i<currPop.size();i++){
        score[i]=evaluation(currPop[i]);      
      }    
    }
  
  template<typename Evaluation,
           typename Selection,
           typename Crossover,
           typename Mutation,
           typename Elitism,
           typename Pop,
           typename Score
    >
    void step(Pop& nextPop, const Score& score,const Pop& currPop,
                Evaluation& evaluation,
                Selection& selection, 
                Crossover& crossover,
                Mutation& mutation,
                Elitism& elitism
              ){   

    elitism.init(currPop,score);
    size_t i=0;
    for (;i<nextPop.size()&&elitism(nextPop[i],currPop,score);i++);
    selection.init(currPop,score);
    for (;i<nextPop.size();i++){
      std::pair<int,int> match=selection(currPop,score);
      crossover
        (
         nextPop[i],
         currPop[match.first],score[match.first],
         currPop[match.second],score[match.second]
         );
      mutation(nextPop[i]);
    }    
  }

  
  class GaussianInitializer{       
    std::default_random_engine generator;
    std::normal_distribution<double> normal;
    size_t popSize,genomeSize;
  public:
    GaussianInitializer(size_t _popSize,size_t _genomeSize,double std):
      normal(std),popSize(_popSize),genomeSize(_genomeSize){
    }
    
    template<typename V> void operator()(V& v){
      v.resize(popSize);
      for (size_t i=0;i<popSize;i++){
        v[i].resize(genomeSize);
        for (size_t j=0;j<genomeSize;j++){
          v[i][j]=normal(generator);
        }
      }
    }
    
  };


  class FixedCountTermination{
    size_t iters,count;   
  public:
    FixedCountTermination(size_t _iters):
      iters(_iters),count(0){
    }    
    template<typename P,typename S>
    bool operator()(const P&,const S&){
      return (count++)>iters;
    }
  };



  template<typename G,void(*print)(const G&)>
  class PrintBestElement{
  public:
    template<typename P,typename S>
    void operator()(const P& p, const S& s){
      int idx= std::max_element(s.begin(),s.end())-s.begin();
      std::cout<<s[idx]<<":";
      print(p[idx]);
      std::cout<<std::endl;
    }
  };


 template<
   typename Pop,
   typename Evaluation,
   typename Selection,
   typename Crossover,
   typename Mutation,
   typename Elitism,
   typename Init,
   typename Termination,
   typename Log,
   typename Score=std::vector<double>          
   >
 void ga(Init& init,
         Termination& termination,
         Evaluation& evaluation,
         Selection& selection, 
         Crossover& crossover,
         Mutation& mutation,
         Elitism& elitism,
         Log& log
         ){
   Pop pop[2];
   Score score;
   init(pop[0]);
   score.resize(pop[0].size());
   pop[1]=pop[0];
   
   int curr=0;

   while(true){
     evaluate(score,pop[curr],evaluation);  
     if (termination(pop,score)) break;
     step(pop[1-curr],score,pop[curr],evaluation,selection,crossover,mutation,elitism);
     log(pop[curr],score);
     curr=1-curr;
  }
   
   

 }
  

  class PropoptionalSelection{

  public:
     template<typename P,typename S> void init(const P& ,const S& s){}

     template<typename P,typename S> std::pair<int,int> operator()(const P& ,const S& s){     
       double tot=0;
       for (size_t i=0;i<s.size();i++){
         tot+=s[i];
       }
       double target= tot*rand()/RAND_MAX;
       std::pair<int,int> ret;
       double sum=0;
       for (ret.first=0;;ret.first++){
         sum+=s[ret.first];
         if (sum>=target) break;
       }
       while(true){
         target= tot*rand()/RAND_MAX;
         sum=0;
         for (ret.second=0;ret.second<s.size();ret.second++){
           sum+=s[ret.second];
           if (sum>=target&&ret.second!=ret.first) break;
         }
         if (ret.second<s.size()) break;
       }
       //std::cout<<"selected "<<ret.first<<" and "<<ret.second<<std::endl;
       return ret;
     }
     
     
  };
          
  

  class OnePointCrossover{
  public:
    template<typename G,typename S> void operator()(G& g,const G& g1,const S&,const G& g2,const S&){    
      int split=g.size()*rand()/RAND_MAX;
      int i=0;
      for (;i<split;i++){
        g[i]=g1[i];
      }
      for (;i<g.size();i++){
        g[i]=g2[i];
      }    
    }
    
  };


  class GaussianMutation{
    double p;
    std::default_random_engine generator;
    std::normal_distribution<double> normal;
    std::uniform_real_distribution<> uniform;
  public:
    GaussianMutation(double _p,double _std):
      p(_p),normal(0,_std),uniform(0,1)
    {
    }

    template<typename G> void operator()(G& g){
      for (size_t i=0;i<g.size();i++){

        if (uniform(generator)<p){
          g[i]+=normal(generator);
        }        
      }
    }
    
  };


  
  class NoElitism{
  public:
    
    template<typename P,typename S> void init(const P&,const S&){
    }

    template<typename G,typename P,typename S> bool operator()(G&,const P&,const S&){
      return false;
    }
    
  };
  

  class BestElitism{
    bool noMore;
  public:

    template<typename P,typename S> void init(const P&,const S&){
      noMore=false;      
    }

    template<typename G,typename P,typename S> bool operator()(G& g,const P& p,const S& s){
      if (noMore){
        return false;
      }else{
        int idx= std::max_element(s.begin(),s.end())-s.begin();
        g=p[idx];
        noMore=true;
        return true;
      }
    }


  };




}//ns ga




