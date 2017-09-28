# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.
#encoding utf8
module Napakalaki
require_relative 'bad_consequence' #Uno de los fallos que nos daba es que no poníamos esto
require_relative 'Prize'           #Se pone para que como que nos importe la clase
require_relative 'monster'
require_relative 'treasure_kind'
monster = Array.new

price = Prize.new(4,1)
badConsequence = BadConsequence.newLevelNumberOfTreasures('Pierdes 5 niveles y 3 tesoros visible',5,3,0)
monster << Monster.new('El rey rosa',13,price,badConsequence)


price1 = Prize.new(2,1)
badConsequence1 = BadConsequence.newLevelSpecificTreasures('Pierdes tu armadura visible y otra oculta',0,
  [TreasureKind::ARMOR],[TreasureKind::ARMOR])
monster << Monster.new('Byajhees de bonanza',8,price1,badConsequence1)

price2 = Prize.new(1,1)
badConsequence2 = BadConsequence.newLevelSpecificTreasures('Embobabo con el lindo primigenio te des
  cargas de tu casco visible',0,[TreasureKind::HELMET],nil)
monster << Monster.new('Chibithulhu',2,price2,badConsequence2)

price3 = Prize.new(1,1)
badConsequence3 = BadConsequence.newLevelSpecificTreasures('El primordial bostezo contagioso,
   pierder el calzado visible',5,[TreasureKind::SHOE],nil)
monster << Monster.new('El sopor de Dunwich',2,price3,badConsequence3)

price4 = Prize.new(4,1)
badConsequence4 = BadConsequence.newLevelSpecificTreasures('Te atrapan para llevarte de fiesta
  y te dejan caer en mitad del vuelo, descarta una mano visible y una oculta',0,[TreasureKind::ONEHAND],
  [TreasureKind::ONEHAND])
monster << Monster.new('Angeles de la noche ibicenca',14,price4,badConsequence4)

price5= Prize.new(1,1)
badConsequence5 = BadConsequence.newLevelNumberOfTreasures('Toses los pulmones y pierdes 2 niveles',
  2,1,1)
monster << Monster.new('La que redacta en las tinieblas',2,price5,badConsequence5)

price6 = Prize.new(3,1)
badConsequence6 = BadConsequence.newLevelNumberOfTreasures('Pierdes todos tus tesoros visibles',0,6,0)
monster << Monster.new('El gorron en el umbral',10,price6,badConsequence6)

price7 = Prize.new(2,1)
badConsequence7 = BadConsequence.newLevelSpecificTreasures('Pierdes la armadura visible',0,[TreasureKind::ARMOR],
 nil)
monster << Monster.new('H.P Munchcraft',6,price7,badConsequence7)

price8 = Prize.new(1,1)
badConsequence8 = BadConsequence.newLevelSpecificTreasures('Sientes bichos debajo de la ropa, descarta
  la armadura visible',0,[TreasureKind::ARMOR],nil)
monster << Monster.new('Bichgooth',2,price8,badConsequence8)

price9 = Prize.new(2,1)
death = true
badConsequence9 = BadConsequence.NewDeath('Estos monstruos resultan bastante superficiales
  y te aburren mortalmente. Estas muerto.')
monster << Monster.new('Los Hondos',2,price9,badConsequence9)

price10 = Prize.new(2,1)
badConsequence10 = BadConsequence.newLevelNumberOfTreasures('Pierdes dos niveles y dos
  tesoros ocultos',2,0,2)
monster << Monster.new('Semillas de Cthulhu',4,price10,badConsequence10)

price11 = Prize.new(2,1)
badConsequence11 = BadConsequence.newLevelSpecificTreasures('Te intentas escaquear y pierdes una
  mano visible',0,[TreasureKind::ONEHAND],nil)
monster << Monster.new('Dameargo',1,price11,badConsequence11)

price12 = Prize.new(1,1)
badConsequence12 = BadConsequence.newLevelNumberOfTreasures('Da mucho asquito. pierdes tres
  niveles',3,0,0)
monster << Monster.new('Pollipolipo volante',3,price12,badConsequence12)

price13 = Prize.new(3,1)
badConsequence13 = BadConsequence.NewDeath('No le hace gracia que pronuncies mal su nombre,
  Estas muerto.')
monster << Monster.new('YskhtihyssgGoth',12,price13,badConsequence13)

price14 = Prize.new(4,1)
badConsequence14 = BadConsequence.NewDeath('La familia te atrapa.Estas muerto')
monster << Monster.new('Familia feliz',1,price14,badConsequence14)

price15 = Prize.new(2,1)
badConsequence15 = BadConsequence.newLevelSpecificTreasures('La quinta directiva primaria te obliga
  a perder dos niveles y un tesoro 2 manos viisbles',2,[TreasureKind::BOTHHAND],nil)
monster << Monster.new('Roboggoth',8,price15,badConsequence15)

price16 = Prize.new(1,1)
badConsequence16 = BadConsequence.newLevelSpecificTreasures('te asusta la noche. Pierdes
  un casco visible',0,[TreasureKind::HELMET],nil)
monster << Monster.new('El espia',5,price16,badConsequence16)

price17 = Prize.new(1,1)
badConsequence17 = BadConsequence.newLevelNumberOfTreasures('Menudo susto te llevas, pierdes dos niveles
  y 5 tesoros visibles', 2,5,0)
monster << Monster.new('El lenguas',20,price17,badConsequence17)

price18 = Prize.new(1,1)
badConsequence18 = BadConsequence.newLevelSpecificTreasures('Te faltan manos para tanta cabeza, pierdes
  tres niveles y tus tesoros visibles de las manos',3,[TreasureKind::ONEHAND,TreasureKind::BOTHHAND],nil)
monster << Monster.new('Bicefalo',2,price18,badConsequence18)

#Pruebas

#monster.each { |m| # Así se hace el for, precioso bonito y barato
#   if (m.combatLevel >= 10)
#      puts m.name 
#   end
#}
#/////////////

#monster.each { |m|
#  bc = BadConsequence.NuevaBadC # Creamos un nuevo objeto bc 
#  bc = m.malrollo              # asi copio el del monstruo
#  if(bc.levels > 0)
#    puts m.name
#  end
#}

#//////////////

# monster.each { |m|
# prize = Prize.premvacio  # lo mismo de antes
#  prize= m.premio
#  if(prize.level >1)
#    puts m.name
#  end
#  
#}

#/////////////

monster.each{ |m|
  bc = BadConsequence.NuevaBadC
  bc = m.malrollo
  if(bc.nVisible || bc.nHidden)
    puts m.name
  end
  
}

end