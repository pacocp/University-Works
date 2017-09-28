# encoding: UTF-8
#
#   Programación y diseño orientado a objetos
#   Grado en Ingeniería Informática
#
#  Ángela Castro Jimenez
#  Francisco Carrillo Pérez

module Napakalaki
  require 'singleton'
  require_relative 'Treasure'
  require_relative 'Monster'
  require_relative 'TreasureKind'
  require_relative 'Cultist.rb'
  require_relative 'Card'
  class CardDealer
   include Singleton 
   attr_accessor :usedTreasures, :unusedTreasures, :usedMonsters, :unusedMonsters, :unusedcultists, :usedcultists
  def initialize 
      @usedMonsters=Array.new
      @unusedMonsters=Array.new
      @usedTreasures=Array.new
      @unusedTreasures=Array.new
      @unusedcultists = Array.new
  end

  def initTreasureCardDeck
        @unusedTreasures << Treasure.new("Si mi amo", 0, 4, 7, TreasureKind::HELMET)
        @unusedTreasures << Treasure.new("Botas de investigacion", 600, 3, 4, TreasureKind::SHOE)
        @unusedTreasures << Treasure.new("Capucha de Cthulhu", 500, 3, 5, TreasureKind::HELMET)
        @unusedTreasures << Treasure.new("A prueba de babas", 400, 2, 5, [TreasureKind::ARMOR])
        @unusedTreasures << Treasure.new("Botas de lluvia acida", 800, 1, 1, TreasureKind::BOTHHAND)
        @unusedTreasures << Treasure.new("Casco Minero", 400, 2, 4, TreasureKind::HELMET)
        @unusedTreasures << Treasure.new("Ametralladora Thompson", 600, 4, 8, TreasureKind::BOTHHAND)
        @unusedTreasures << Treasure.new("Camiseta de la UGR", 100, 1, 7, TreasureKind::ARMOR)
        @unusedTreasures << Treasure.new("Clavo de rail ferroviario", 400, 3, 6, TreasureKind::ONEHAND)
        @unusedTreasures << Treasure.new("Cuchillo de sushi arcano", 300, 2, 3, TreasureKind::ONEHAND)
        @unusedTreasures << Treasure.new("Fez alopodo", 700, 3, 5, TreasureKind::HELMET)
        @unusedTreasures << Treasure.new("Hacha prehistorica", 500, 2, 5, TreasureKind::ONEHAND)
        @unusedTreasures << Treasure.new("El aparato de Pr.Tesla", 900, 4, 8, TreasureKind::ARMOR)
        @unusedTreasures << Treasure.new("Gaita", 500, 4, 5, TreasureKind::BOTHHAND)
        @unusedTreasures << Treasure.new("Insecticida", 300, 2, 3, TreasureKind::ONEHAND)
        @unusedTreasures << Treasure.new("Escopeta de 3 canones", 700, 4, 6, TreasureKind::BOTHHAND)
        @unusedTreasures << Treasure.new("Garabato Mistico", 300, 2, 2, TreasureKind::ONEHAND)
        @unusedTreasures << Treasure.new("La fuerza de Mr.T", 1000, 0, 0, TreasureKind::NECKLACE)
        @unusedTreasures << Treasure.new("La rebeca metalica", 400, 2, 3, TreasureKind::ARMOR)
        @unusedTreasures << Treasure.new("Mazo de los antiguos", 200, 3, 4, TreasureKind::ONEHAND)
        @unusedTreasures << Treasure.new("Necro-playboycon", 300, 3, 5, TreasureKind::ONEHAND)
        @unusedTreasures << Treasure.new("Lanzallamas", 800, 4, 8, TreasureKind::BOTHHAND)
        @unusedTreasures << Treasure.new("Necro-comicon", 100, 1, 1, TreasureKind::ONEHAND)
        @unusedTreasures << Treasure.new("Necronomicon", 800, 5, 7, TreasureKind::BOTHHAND)
        @unusedTreasures << Treasure.new("Linterna a 2 manos", 400, 3, 6, TreasureKind::BOTHHAND)
        @unusedTreasures << Treasure.new("Necro-gnomicon", 200, 2, 4, TreasureKind::ONEHAND)
        @unusedTreasures << Treasure.new("Necrotelecom", 300, 2, 3, TreasureKind::HELMET)
        @unusedTreasures << Treasure.new("Porra preternatural", 200, 2, 3, TreasureKind::ONEHAND)
        @unusedTreasures << Treasure.new("Tentaculo de pega", 200, 0, 1, TreasureKind::HELMET)
        @unusedTreasures << Treasure.new("Zapato deja-amigos", 500, 0, 1, TreasureKind::SHOE)
        @unusedTreasures << Treasure.new("Shogulador", 600, 1, 1, TreasureKind::BOTHHAND)
        @unusedTreasures << Treasure.new("Varita de atizamiento", 400, 3, 4, TreasureKind::ONEHAND)
        shuffleTreasures
  end
  
  def initMonsterCardDeck
    
        #El rey rosa
        badConsequence = BadConsequence.newLevelNumberOfTreasures("Pierdes 5 niveles y 3 tesoros visibles", 5, 3, 0)
        prize = Prize.new(4,2)
        @unusedMonsters << Monster.new("El rey de rosa", 13, badConsequence, prize,0)
      
        
        #Byajhees de bonanza
        tvp=Array.new
        tvp << TreasureKind::ARMOR
        thp=Array.new
        thp << TreasureKind::ARMOR
        badConsequence1 =BadConsequence.newLevelSpecificTreasures("Pierdes tu armadura visible y otra oculta", 0, tvp, thp)
        prize1 = Prize.new(2,1)
        @unusedMonsters << Monster.new("Byajhees de bonanza", 8, badConsequence1, prize1,0)
        
        
        #Chibithulhu
        tvp=Array.new
        tvp << TreasureKind::HELMET
        thp=Array.new
        badConsequence = BadConsequence.newLevelSpecificTreasures("Embobado con el lindo primigenenio te descargas de tu casco visible", 0, tvp,thp)
        prize = Prize.new(1,1)
        @unusedMonsters << Monster.new("Chibithulhu", 2, badConsequence, prize,0)

        
        #El Sopor de Dunwich
        tvp=Array.new
        tvp << TreasureKind::SHOE
        thp=Array.new
        badConsequence = BadConsequence.newLevelSpecificTreasures("El primordial bostezo contagioso, pierdes el calzado visible", 5, tvp, thp)
        prize = Prize.new(1,1)
        @unusedMonsters << Monster.new("El Sopor de Dunwich", 2, badConsequence, prize,0)
        
        
        #Angeles de la noche ibicenca
        
        tvp=Array.new
        tvp << TreasureKind::ONEHAND
        thp=Array.new
        thp << TreasureKind::ONEHAND
        badConsequence = BadConsequence.newLevelSpecificTreasures("Te atrapan para llevarte de fiesta y te dejan caer en mitad del vuelo, descarta una mano visible y una oculta",
        0, tvp, thp)
        prize = Prize.new(4,1)
        @unusedMonsters << Monster.new("Angeles de la noche ibicenca", 14, badConsequence, prize,0)
      
        
        #La que redacta en las tinieblas
        badConsequence = BadConsequence.newLevelNumberOfTreasures("Toses los pulmones y pierdes 2 niveles", 2,0,0)
        prize = Prize.new(1,1)
       @unusedMonsters << Monster.new("La que redacta en las tinieblas", 2, badConsequence, prize,0)

        
        #El gorrón en el umbral
        badConsequence = BadConsequence.newLevelNumberOfTreasures("Pierdes todos tus tesoros visibles",0, 6, 0)
        prize = Prize.new(3,1)
        @unusedMonsters << Monster.new("El gorron en el umbral", 10, badConsequence, prize,0)
      
        
        #H.P Munchcraft
        tvp=Array.new
        tvp << TreasureKind::ARMOR
        thp=Array.new
        badConsequence = BadConsequence.newLevelSpecificTreasures("Pierdes la armadura visible",0, tvp, thp)
        prize = Prize.new(2,1)
        @unusedMonsters << Monster.new("H.P Munchcraft", 6, badConsequence, prize,0)
        
        
        #Bichgooth
        tvp=Array.new
        tvp << TreasureKind::ARMOR
        thp=Array.new
        badConsequence = BadConsequence.newLevelSpecificTreasures("Sientes bichos debajo de la ropa. Descarta la armadura visible", 0, tvp, thp)
        prize = Prize.new(1,1)
        @unusedMonsters << Monster.new("Bichgooth", 2, badConsequence, prize,0)
      
        
        #Los Hondos
        badConsequence =BadConsequence.newDeath("Estos monstruos resultan bastante superficiales y te aburren mortalmente. Estas muerto")
        prize = Prize.new(2,1)
        @unusedMonsters << Monster.new("Los Hondos", 8, badConsequence, prize,0)
       
        
        #Semillas Cthulhu
        badConsequence = BadConsequence.newLevelNumberOfTreasures("Pierdes dos niveles y dos tesoros ocultos", 2, 0, 2)
        prize = Prize.new(2,1)
        @unusedMonsters << Monster.new("Semillas Cthulhu", 4, badConsequence, prize,0)
        
        
        #Dameargo
        tvp=Array.new
        tvp << TreasureKind::ONEHAND
        thp=Array.new
        badConsequence = BadConsequence.newLevelSpecificTreasures("Te intentas escaquear. Pierdes una mano visible",0, tvp, thp)
        prize = Prize.new(2,1)
        @unusedMonsters << Monster.new("Dameargo", 1, badConsequence, prize,0)
        
        
        #Pollipólipo volante
        badConsequence = BadConsequence.newLevelNumberOfTreasures("Da mucho asquito. Pierdes tres niveles", 3, 0, 0)
        prize = Prize.new(1,1)
        @unusedMonsters << Monster.new("Pollipolipo volante", 3, badConsequence, prize,0)
        
    
        #YskhtihyssgGoth
        badConsequence =BadConsequence.newDeath("No le hace gracia que pronuncies mal su nombre.Estas muerto")
        prize= Prize.new(3,1)
        @unusedMonsters << Monster.new("YskhtihyssgGoth", 12, badConsequence, prize,0)
      
        
        #Familia feliz
        badConsequence =BadConsequence.newDeath("La familia te atrapa. estas muerto")
        prize = Prize.new(4,1)
        @unusedMonsters << Monster.new("Familia feliz", 1, badConsequence, prize,0)
       
        
        #Roboggoth
        tvp=Array.new
        tvp << TreasureKind::ONEHAND
        thp=Array.new
        badConsequence = BadConsequence.newLevelSpecificTreasures("La quinta directiva primaria te obliga a perder 2 niveles y un tesoro 2 manos visibles", 2, tvp, thp)
        prize = Prize.new(2,1)
        @unusedMonsters << Monster.new("Roboggoth", 8, badConsequence, prize,0)
       
        
        #El espía
        tvp=Array.new
        tvp << TreasureKind::HELMET
        thp=Array.new
        badConsequence = BadConsequence.newLevelSpecificTreasures("Te asusta la noche.Pierdes un casco visible", 0,tvp, thp)
        prize = Prize.new(1,1)
        @unusedMonsters << Monster.new("El espia", 5, badConsequence, prize,0)
        
        
        #El Lenguas
        badConsequence = BadConsequence.newLevelNumberOfTreasures("menudo susto te llevas.Pierdes 2 niveles y 5 tesoros visibles", 2, 5, 0)
        prize = Prize.new(1,1)
        @unusedMonsters << Monster.new("El Lenguas", 20, badConsequence, prize,0)
        
        
        #Bicéfalo
        tvp=Array.new
        tvp << TreasureKind::ONEHAND
        tvp << TreasureKind::BOTHHAND
        thp=Array.new
        badConsequence =BadConsequence.newLevelSpecificTreasures("Te faltan manos para tanta cabeza. Pieres tres niveles y tus tesoros visibles de las manos", 3,tvp, thp)
        prize = Prize.new(1,1)
        @unusedMonsters << Monster.new("Bicefalo", 20, badConsequence, prize,0)
         #Montruos contra sectarios
        v = Array.new
        tvp = Array.new
        v << TreasureKind::ONEHAND
        badConsequence = BadConsequence.newLevelSpecificTreasures("Pierdes 1 mano visible.",0, v, tvp);
        prize = Prize.new(3,1)
        @unusedMonsters << Monster.new("El mal indecible impronunciable", 10, badConsequence, prize, -2)


        v = Array.new
        tvp = Array.new
        v << TreasureKind::SHOE
        v << TreasureKind::ONEHAND
        v << TreasureKind::NECKLACE
        v << TreasureKind::HELMET
        v << TreasureKind::BOTHHAND
        v << TreasureKind::ARMOR
        badConsequence = BadConsequence.newLevelSpecificTreasures("Pierdes tus tesoros visibles. Jajaja.",0, v, tvp)
        prize = Prize.new(2,1)
        @unusedMonsters << Monster.new("Testigos Oculares", 6, badConsequence, prize, +2)


        badConsequence = BadConsequence.newDeath("Hoy no es tu dia de suerte. Mueres.")
        prize = Prize.new(2,5)
        @unusedMonsters << Monster.new("El gran cthulhu", 20,badConsequence, prize, +4)


        v = Array.new
        tvp = Array.new
        badConsequence = BadConsequence.newLevelSpecificTreasures("Rajoy te recorta 2 niveles.", 2, v, tvp)
        prize = Prize.new(2,1)
        @unusedMonsters << Monster.new("Serpiente Político", 8, badConsequence, prize, -2)



        v = Array.new
        v << TreasureKind::HELMET
        v << TreasureKind::ARMOR
        tvp = Array.new
        tvp<< TreasureKind::BOTHHAND
        tvp << TreasureKind::ONEHAND

        badConsequence = BadConsequence.newLevelSpecificTreasures("Pierdes tu casco y tu armadura visible. Pierdes tus manos ocultas.", 0, v, tvp)
        prize = Prize.new(1,1)
        @unusedMonsters << Monster.new("Felpuggoth", 2, badConsequence, prize, +5)


        v = Array.new
        tvp = Array.new

        badConsequence = BadConsequence.newLevelSpecificTreasures("Pierdes 2 niveles.", 2, v, tvp)
        prize = Prize.new(4,2);
        @unusedMonsters << Monster.new("Shoggoth", 16,  badConsequence, prize, -4)

        v = Array.new
        tvp = Array.new

        badConsequence = BadConsequence.newLevelSpecificTreasures("Pintalabios negro. Pierdes 2 niveles.", 2, v, tvp)
        prize = Prize.new(1,1)
        @unusedMonsters << Monster.new("Lolitagooth", 2, badConsequence, prize, +3)
        shuffleMonsters
    
  end
  
  def initCultistCardDeck
      
      
      @unusedcultists << Cultist.new(1)
      @unusedcultists << Cultist.new(2)
      @unusedcultists << Cultist.new(1)
      @unusedcultists << Cultist.new(2)
      @unusedcultists << Cultist.new(1)
      @unusedcultists << Cultist.new(1)
      
    end
    
  
    def shuffleCultists
      @unusedcultists = @unusedcultists.shuffle!
    end
    
  def shuffleTreasures
    @unusedTreasures.shuffle!
  end
  
  def shuffleMonsters
    @unusedMonsters.shuffle!
  end
  
  def giveTreasureBack(t)
    @usedTreasures << t
  end
  
  def giveMonsterBack(m)
    @usedMonsters.push(m)
  end
     
   def initCards
        initTreasureCardDeck
        shuffleTreasures
        initMonsterCardDeck
        shuffleMonsters
        initCultistCardDeck  
        shuffleCultists
    end
   
    
 
  def nextTreasure
        tesoro=@unusedTreasures.at(0)
        @unusedTreasures.delete_at(0)      
        if(@unusedTreasures.empty?)
          @unusedTreasures=@usedTreasures.clone
          shuffleTreasures
          @usedTreasures.clear
        end
        return tesoro
    end
      
    def nextMonster
        monstruo=@unusedMonsters.at(0)
        @unusedMonsters.delete_at(0)      
        if(@unusedMonsters.empty?)
          @unusedMonsters=@usedMonsters.clone 
          @unusedMonsters=@usedMonsters.clone
          @usedMonsters.clear
        end
        return monstruo
    end
    
    def nextCultist
      
      if @unusedcultists.empty?     
        initCultistCardDeck
        shuffleCultists
      end
        
      c = @unusedcultists.at(0)
      @unusedccultists.delete(c);
      return c
    end
end 
end



