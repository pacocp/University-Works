/*  
 *  Programación y diseño orientado a objetos
 *  Grado en Ingeniería Informática
 * 
 *  
 *
 *  Angela Castro Jiménez
 *  Francisco Carrillo Pérez
 */
package NapakalakiGame;

import GIU.NapakalakiView;
import GIU.PlayerNamesCapture;
import NapakalakiGame.Napakalaki;
import NapakalakiGame.Dice;
import Test.GameTester;
import java.util.ArrayList;

public class EjemploMain {

    public static void main(String[] args) {
      ArrayList<String> names = new ArrayList();
      Napakalaki game = Napakalaki.getInstance();
      GameTester test = GameTester.getInstance();
      Napakalaki napakalakiModel = Napakalaki.getInstance();
      NapakalakiView napakalakiView = new NapakalakiView();
      PlayerNamesCapture namesCapture = new PlayerNamesCapture(napakalakiView,true);
      napakalakiView.setNapakalaki(napakalakiModel);
      Dice.createInstance(napakalakiView);
      
      names = namesCapture.getNames();
      napakalakiModel.initGame(names);
      napakalakiView.showView();





      // Poner el numero de jugadores con el que se quiera probar
      //test.play(game, 2); 
              
    }
}
