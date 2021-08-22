package com.example.kniffelhelfer;

import android.util.Log;
import android.view.View;
import android.widget.AdapterView;

import androidx.annotation.NonNull;
import androidx.fragment.app.Fragment;

import java.util.ArrayList;
import java.util.List;

public class TabellenController implements Manager.Listener, ManagedFragment.Listener, Model.Listener, AdapterView.OnItemSelectedListener {
    private Manager manager;
    private TabellenFragment tabellenFragment;
    private EintragController eintragController;

    private int indexSpieler = 0;
    public TabellenController(Manager m){
        manager = m;
        eintragController = new EintragController(m);

        m.addListener(this);
    }

    public void resetSpielerIndex(){
        indexSpieler = manager.getDatabase().getCurrent().getNextSpieler();
        redraw();
    }

    public void redraw(){
        if(tabellenFragment == null)
            return;
        Spielstand spielstand = manager.getDatabase().getCurrent();

        List<String> spielerNamen = new ArrayList<String>(spielstand.getSpielerAnzahl());
        for(int i=0; i<spielstand.getSpielerAnzahl(); i++)
            spielerNamen.add(spielstand.getSpielerName(i)+ " -- " + spielstand.getPunkteSumme(i));
        tabellenFragment.setSpielerNamen(spielerNamen);
        tabellenFragment.setSelectedSpieler(indexSpieler);

        List<TabelleviewAdapter.Eintrag> kategorieListe = new ArrayList<TabelleviewAdapter.Eintrag>();
        for(Kategorie kategorie : spielstand){
            int punkte = kategorie.getPunkte(indexSpieler);
            String sPunkte = (punkte>0)?""+punkte:"";
            kategorieListe.add(new TabelleviewAdapter.Eintrag(kategorie.getLocale(), sPunkte));
        }
        tabellenFragment.setEintraege(kategorieListe);
    }

    @Override
    public void onFragmentAdded(Fragment f) {

        if(f instanceof TabellenFragment){
            tabellenFragment = (TabellenFragment) f;
            tabellenFragment.addListener(this);
            tabellenFragment.setSpielerSelectListener(this);
            manager.getDatabase().addListener(this);
            resetSpielerIndex();
            redraw();
        }
    }

    @Override
    public void onFragmentRemoved(Fragment f) {
        if(f instanceof TabellenFragment){
            TabellenFragment tabellenFragment = (TabellenFragment) f;
            tabellenFragment.remListener(this);
            this.tabellenFragment = null;
            manager.getDatabase().remListener(this);
        }

    }

    private static Kategorie getKategorieByIndex(int index, Spielstand spielstand){
        int i = 0;
        for(Kategorie kat : spielstand){
            if(index == i)
                return kat;
            else
                i++;
        }
        return null;
    }
    @Override
    public void onFragmentDone(Fragment f) {
        TabellenFragment tabellenFragment = (TabellenFragment) f;
        int indexSpieler = tabellenFragment.getSelectedSpieler();
        int indexEintrag = tabellenFragment.getSelectedEintrag();

        Spielstand spielstand = manager.getDatabase().getCurrent();
        Eintrag eintrag = getKategorieByIndex(indexEintrag, spielstand).getEintrag(indexSpieler);

        eintragController.setSpieler(spielstand.getSpielerName(indexSpieler), indexSpieler);
        eintragController.setEintrag(eintrag.clone());
    }

    @Override
    public void modelChanged(Object o) {
        resetSpielerIndex(); //includes redraw();
    }

    @Override
    public void onItemSelected(AdapterView<?> adapterView, View view, int i, long l) {
        indexSpieler = i;
        redraw();
    }

    @Override
    public void onNothingSelected(AdapterView<?> adapterView) {
        resetSpielerIndex();
    }
}
