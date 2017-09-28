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

import java.util.ArrayList;


public class BadConsequence {
    
    private String text;
    private int levels;
    private int nVisibleTreasures;
    private int nHiddenTreasures;
    private boolean death;
    
    private ArrayList<TreasureKind> specificHiddenTreasures = new ArrayList();
    private ArrayList<TreasureKind> specificVisibleTreasures = new ArrayList();
    
    public BadConsequence(){
        text = "";
        levels = 0;
        nVisibleTreasures = 0;
        nHiddenTreasures = 0;
    }
    
    public BadConsequence (String t, int l, int nVisible, int nHidden){
        text = t;
        levels = l;
        nVisibleTreasures = nVisible;
        nHiddenTreasures = nHidden;
    }
    
    public BadConsequence (String t, int l, ArrayList<TreasureKind> v, ArrayList<TreasureKind> h){
        text = t;
        levels = l;
        specificVisibleTreasures = v;
        specificHiddenTreasures = h;
    }
    
    public BadConsequence (String t, boolean mideath){
        text = t;
        death = mideath;
    }
    
    
    public String getText(){
        return text;
    }  
    
    public int  getLevels(){
         return levels;
    }
    
    public int  getnVisibleTreasures(){
         return nVisibleTreasures;
    }
    
    public int  getnHiddenTreasures(){
         return nHiddenTreasures;
    }
     
    public boolean getDeath(){
         return death;
    }
     
     
     public ArrayList<TreasureKind>  getSpecificHiddenTreasures(){
         return specificHiddenTreasures;
     }
     
     
      public ArrayList<TreasureKind>  getSpecificVisibleTreasures(){
         return specificVisibleTreasures;
      }
     
    boolean myBadConsequenceIsDeath(){
         return death;
    }
     
    public boolean isEmpty(){
          return (nVisibleTreasures == 0 && nHiddenTreasures == 0 && 
            (specificHiddenTreasures == null || specificHiddenTreasures.isEmpty()) && (specificVisibleTreasures == null || specificVisibleTreasures.isEmpty()) );  
    }
    
    //Actualiza el mal rollo que tiene que cumplir el jugador, en función del tipo de tesoro de t y
    //del tipo de mal rollo que tenga que cumplir el jugador.

    public void substractVisibleTreasure(Treasure t){
        //no tengo claro que sea así
        specificVisibleTreasures.remove(t.getType());
    }
    
    
     public void substractHiddenTreasure(Treasure t){
         specificHiddenTreasures.remove(t.getType());
     }
    
    
     public BadConsequence adjustToFitTreasureLists( ArrayList<Treasure> v, ArrayList<Treasure> h){
         BadConsequence bc;
         if(this.specificHiddenTreasures == null && this.specificVisibleTreasures == null){
             bc=new BadConsequence("",0,this.nVisibleTreasures, this.nHiddenTreasures);
             if(bc.nHiddenTreasures>h.size())
                   bc.nHiddenTreasures = h.size();
             if(bc.nVisibleTreasures> v.size())
                    bc.nVisibleTreasures = v.size();
         }
         else{
            ArrayList<TreasureKind> tVisible = new ArrayList();
            ArrayList<TreasureKind> tHidden = new ArrayList();

           
           for (TreasureKind t: this.specificHiddenTreasures) {
               int cont = 0;
               boolean enc =false;
               while (!enc && cont<h.size()){
                   if(t==h.get(cont).getType())
                       enc = true;
                   cont++;
               }
               if (enc)
                   tHidden.add(t);
           }
           for (TreasureKind t: this.specificVisibleTreasures) {
               int cont = 0;
               boolean enc =false;
               while (!enc && cont<v.size()){
                   if(t==v.get(cont).getType())
                       enc = true;
                   cont++;
               }
               if (enc)
                   tVisible.add(t);
           }
           

         bc = new BadConsequence("", 0, tVisible, tHidden);
         }
           return bc;
     }
     
     public String toString(){
        return "Mal Rollo: "+text
                +" \nPierdes " + Integer.toString(levels)+" niveles."
                +"\nNumero de tesoros visibles perdidos: "+ Integer.toString(nVisibleTreasures)+"."
                +"\nNumero de tesoros ocultos perdidos: "+ Integer.toString(nHiddenTreasures)+"."
                +"\nMuerte: "+ Boolean.toString(death);
     }
     

     
      /* PRUEBA 
        public static void main(String args[]){
           BadConsequence malrollo = new BadConsequence ("Pierdes un turno",2,3,2);
           System.out.println(malrollo.getText());
           System.out.println(malrollo.getLevelsPerdidos());
           System.out.println(malrollo.getnVisiblePerdidos()); 
           System.out.println(malrollo.getnHiddenPerdidos());
           System.out.println(malrollo.toString());
        } */
   
}
    
    
    

