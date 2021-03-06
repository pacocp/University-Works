/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package GIU;

import NapakalakiGame.BadConsequence;
import NapakalakiGame.Treasure;
import NapakalakiGame.TreasureKind;
import java.awt.Component;
import java.util.ArrayList;
import javax.swing.JLabel;
import javax.swing.JPanel;

/**
 *
 * @author paco
 */
public class BadConsequenceView extends javax.swing.JPanel {

    /**
     * Creates new form BadConsequenceView
     */
    BadConsequence badconsequenceModel = new BadConsequence();
    public BadConsequenceView() {
        initComponents();
    }
    public void setBadConsequence(BadConsequence b)
    {
        badconsequenceModel = b;
        Texto.setText(badconsequenceModel.getText());
        Muerte.setText("Muerte = " + Boolean.toString(badconsequenceModel.getDeath()));
        NTesorosVisibles.setText("Pierdes " + Integer.toString(b.getnVisibleTreasures()) + " tesoros visibles");
        NTesorosOcultos.setText("Pierdes  " + Integer.toString(b.getnHiddenTreasures()) + " tesoros ocultos");
        if( badconsequenceModel.getSpecificVisibleTreasures() != null)
            fillTreasurePanel(Nvisibles,  badconsequenceModel.getSpecificVisibleTreasures());
        if( badconsequenceModel.getSpecificHiddenTreasures() != null)
            fillTreasurePanel(Nocultos, badconsequenceModel.getSpecificHiddenTreasures());
        
        
    }
    public void fillTreasurePanel (JPanel aPanel, ArrayList<TreasureKind> aList) {
        // Se elimina la información antigua
        aPanel.removeAll();
        // Se recorre la lista de tesoros construyendo y añadiendo sus vistas
        //al panel
        for (TreasureKind t : aList) {
            
            JLabel t_label = new JLabel();
            t_label.setText(t.name());
            t_label.setVisible (true);
            aPanel.add(t_label);
           }
        // Se fuerza la actualización visual del panel
        aPanel.repaint();
        aPanel.revalidate();
}

    public ArrayList<Treasure> getSelectedTreasures(JPanel aPanel) {
    // Se recorren los tesoros que contiene el panel,
    // almacenando en un vector aquellos que están seleccionados.
    // Finalmente se devuelve dicho vector.
    TreasureView tv;
    ArrayList<Treasure> output = new ArrayList();
    for (Component c : aPanel.getComponents()) {
            tv = (TreasureView) c;
            if ( tv.isSelected() )
            output.add ( tv.getTreasure() );
            }
    return output;
    }
//    public void fillTreasurePanel (JPanel aPanel, ArrayList<TreasureKind> aList) {
//        // Se elimina la información antigua
//        aPanel.removeAll();
//        // Se recorre la lista de tesoros construyendo y añadiendo sus vistas
//        //al panel
//        for (TreasureKind t : aList) {
//            Tr aTreasureView = new TreasureView();
//            aTreasureView.setTreasure (t);
//            aTreasureView.setVisible (true);
//            aPanel.add (aTreasureView);
//           }
//        // Se fuerza la actualización visual del panel
//        aPanel.repaint();
//        aPanel.revalidate();
//}
    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        NTesorosVisibles = new javax.swing.JLabel();
        Muerte = new javax.swing.JLabel();
        Nvisibles = new javax.swing.JPanel();
        Nocultos = new javax.swing.JPanel();
        jScrollPane1 = new javax.swing.JScrollPane();
        Texto = new javax.swing.JLabel();
        NTesorosOcultos = new javax.swing.JLabel();

        NTesorosVisibles.setText("NTesorosVisibles");

        Muerte.setText("Muerte");

        javax.swing.GroupLayout NvisiblesLayout = new javax.swing.GroupLayout(Nvisibles);
        Nvisibles.setLayout(NvisiblesLayout);
        NvisiblesLayout.setHorizontalGroup(
            NvisiblesLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 204, Short.MAX_VALUE)
        );
        NvisiblesLayout.setVerticalGroup(
            NvisiblesLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 0, Short.MAX_VALUE)
        );

        javax.swing.GroupLayout NocultosLayout = new javax.swing.GroupLayout(Nocultos);
        Nocultos.setLayout(NocultosLayout);
        NocultosLayout.setHorizontalGroup(
            NocultosLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 0, Short.MAX_VALUE)
        );
        NocultosLayout.setVerticalGroup(
            NocultosLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 63, Short.MAX_VALUE)
        );

        Texto.setText("Texto");
        jScrollPane1.setViewportView(Texto);

        NTesorosOcultos.setText("NTesorosOcultos");

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(this);
        this.setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(Muerte)
                        .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                    .addGroup(layout.createSequentialGroup()
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(jScrollPane1)
                            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                    .addComponent(NTesorosVisibles, javax.swing.GroupLayout.PREFERRED_SIZE, 187, javax.swing.GroupLayout.PREFERRED_SIZE)
                                    .addComponent(Nvisibles, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                                .addGap(18, 18, 18)
                                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                    .addComponent(NTesorosOcultos, javax.swing.GroupLayout.DEFAULT_SIZE, 187, Short.MAX_VALUE)
                                    .addComponent(Nocultos, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))))
                        .addContainerGap())))
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(jScrollPane1, javax.swing.GroupLayout.DEFAULT_SIZE, 27, Short.MAX_VALUE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(Muerte)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(NTesorosVisibles, javax.swing.GroupLayout.PREFERRED_SIZE, 18, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(NTesorosOcultos))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                    .addComponent(Nocultos, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .addComponent(Nvisibles, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                .addContainerGap())
        );
    }// </editor-fold>//GEN-END:initComponents


    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JLabel Muerte;
    private javax.swing.JLabel NTesorosOcultos;
    private javax.swing.JLabel NTesorosVisibles;
    private javax.swing.JPanel Nocultos;
    private javax.swing.JPanel Nvisibles;
    private javax.swing.JLabel Texto;
    private javax.swing.JScrollPane jScrollPane1;
    // End of variables declaration//GEN-END:variables
}
