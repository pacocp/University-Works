# encoding: UTF-8
#
#   Programación y diseño orientado a objetos
#   Grado en Ingeniería Informática
#
#  Ángela Castro Jimenez
#  Francisco Carrillo Pérez

require_relative "Napakalaki"
require_relative "game_tester"

module Test

  class EjemploMain
   
      def prueba
        
       test = GameTester.instance
     
       game = Napakalaki::Napakalaki.instance
   
       #Se prueba el juego con 2 jugadores
   
       test.play(game, 2);
       
      end
      
  end
  
    e = EjemploMain.new
    e.prueba()

end
