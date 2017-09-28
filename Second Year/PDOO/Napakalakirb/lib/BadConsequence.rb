# encoding: UTF-8
#
#   Programación y diseño orientado a objetos
#   Grado en Ingeniería Informática
#
#  Ángela Castro Jimenez
#  Francisco Carrillo Pérez
module Napakalaki
  class BadConsequence
    attr_accessor :text, :levels, :nVisibleTreasures, :nHiddenTreasures, :death,:specificHiddenTreasures,:specificVisibleTreasures
    
   #el metodo new no puede ser llamado fuera de un constructor
    private_class_method :new
    def initialize(text,levels,nVisible,nHidden,death,specificHiddenTreasures,specificVisibleTreasures)
      @text = text
      @levels = levels
      @nVisibleTreasures = nVisible
      @nHiddenTreasures = nHidden
      @death = death
      @specificHiddenTreasures = specificHiddenTreasures
      @specificVisibleTreasures = specificVisibleTreasures
    end

    def self.newDeath(t)  
        new(t, 0, 0, 0,true, [], [])
    end

    def self.newLevelNumberOfTreasures(t,l,nVisible,nHidden)
      new(t,l,nVisible,nHidden, [],[],false)
    end
    
    def self.BadConsequence(t,l,v,h)
      new(t,l,nil,nil,nil,v,h)
    end
     def BadConsequence.newLevelSpecificTreasures(text, levels, specificVisibleTreasures, specificHiddenTreasures)
      new(text,levels,0,0,specificVisibleTreasures,specificHiddenTreasures,false)
    end
    
    
    def isEmpty()
      return (nVisibleTreasures == 0 && nHiddenTreasures == 0 && levels == 0 )
    end
  

       def getSpecificVisibleTreasures()
          return @specificVisibleTreasures
       end   
    
      def getSpecificHiddenTreasures()
         return @specificHiddenTreasures
       end
    
  
        def substractVisibleTreasure(t)
           tipo=t.type
          encontrado=false
          for i in (0..@specificHiddenTreasures.size-1)
             break if (encontrado)
            if(@specificHiddenTreasures.at(0)==tipo.at(0))
              @specificHiddenTreasures.delete_at(i)
              encontrado=true
            end
          end
          @nHiddenTreasures=@nHiddenTreasures-1 if(@nHiddenTreasures>0)  
        end
    
    
        def substractHiddenTreasure(t)
           tipo=t.type
           encontrado=false
           for i in (0..@specificHiddenTreasures.size-1)
             break if (encontrado)
              if(@specificHiddenTreasures.at(0)==tipo.at(0))
               @specificHiddenTreasures.delete_at(i)
               encontrado=true
              end
            end
            @nHiddenTreasures=@nHiddenTreasures-1 if(@nHiddenTreasures>0) 
        end
   
    
    def adjustToFitTreasureLists( visible,  hidden)
        encontrado = false
      nh=0
      nv=0
      antiguaBadConsequence = Napakalaki.instance.getCurrentMonster.getBadConsequence
      
      if(antiguaBadConsequence.getNVisibleTreasures > 0 && visible.size > 0 )  
        if(antiguaBadConsequence.getNVisibleTreasures >= visible.size)
          nv=visible.size
        else
          nv=antiguaBadConsequence.getNVisibleTreasures
        end
      end
      
      if(antiguaBadConsequence.getNHiddenTreasures > 0 && hidden.size > 0 )  
        if(antiguaBadConsequence.getNHiddenTreasures >= hidden.size)
          nh=hidden.size
        else
          nh=antiguaBadConsequence.getNHiddenTreasures
        end
      end
      
      nuevaBadConsequence = BadConsequence.newLevelNumberOfTreasures("", 0, nv, nh)
      
      if(antiguaBadConsequence.specificVisibleTreasures.size > 0 || antiguaBadConsequence.specificHiddenTreasures.size > 0)
        for i in (0..visible.size-1)
          encontrado=false
          for j in (0..antiguaBadConsequence.specificVisibleTreasures.size-1)
            break if (encontrado)
            tip1=visible.at(i).type
            tip2=antiguaBadConsequence.specificVisibleTreasures.at(j)
            if(tip1.at(0)==(tip2))
              nuevaBadConsequence.specificVisibleTreasures.push(antiguaBadConsequence.specificVisibleTreasures.at(j))
              antiguaBadConsequence.specificVisibleTreasures.delete_at(j)
              encontrado=true
            end
          end
        end
        
        for i in (0..hidden.size-1)
          encontrado=false
          for j in (0..antiguaBadConsequence.specificHiddenTreasures.size-1)
            break if (encontrado)
            tip1=hidden.at(i).type
            tip2=antiguaBadConsequence.specificHiddenTreasures.at(j)
            if(tip1.at(0)==tip2)
              nuevaBadConsequence.specificHiddenTreasures.push(antiguaBadConsequence.specificHiddenTreasures.at(j))
              antiguaBadConsequence.specificHiddenTreasures.delete_at(j)
              encontrado=true
            end
          end
        end
      end
      
      return nuevaBadConsequence
    end

    def myBadConsequenceIsDeath
        return @death
    end
    def getdeath
      @death
    end

    def to_s 
      "Mal rollo: #{@text} \n Niveles: #{@levels} \n Num. Tesoros Visibles: #{@nVisibleTreasures}
        \n Num. Tesoros Ocultos: #{@nHiddenTreasures} \n Muerte: #{@death}"
    end

  end
end