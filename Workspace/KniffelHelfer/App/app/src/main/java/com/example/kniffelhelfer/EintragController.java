package com.example.kniffelhelfer;

import android.util.Log;
import android.view.View;
import android.widget.AdapterView;

import androidx.annotation.NonNull;
import androidx.fragment.app.Fragment;

import java.util.ArrayList;
import java.util.List;

public class EintragController implements Manager.Listener, ManagedFragment.Listener, Model.Listener, View.OnClickListener {
    private Manager manager;
    private EintragFragment eintragFragment;

    private Eintrag eintrag;
    private String name;
    private int indexSpieler = 0;

    public EintragController(Manager m){
        manager = m;

        setEintrag(new Eintrag(Kategorie.Type.Einsen)); //default
        setSpieler("*ERROR*", 0);

        m.addListener(this);
    }

    public void setEintrag(Eintrag eintrag){
        if(this.eintrag != null)
            this.eintrag.remListener(this);

        this.eintrag = eintrag;

        if(this.eintrag != null)
            this.eintrag.addListener(this);

        redraw();
    }
    public void setSpieler(String name, int indexSpieler){
        this.name = name;
        this.indexSpieler = indexSpieler;
        redraw();
    }

    public void redraw(){
        if(eintragFragment==null)
            return;

        eintragFragment.setSpielerText(name);
        eintragFragment.setKategorieLocale(Kategorie.getLocale(eintrag.kategorie));
        eintragFragment.setPunkteText(eintrag.getPunkte());

        int w0 = eintrag.getWuerfel().getWuerfel(0).getAugenzahl();
        int w1 = eintrag.getWuerfel().getWuerfel(1).getAugenzahl();
        int w2 = eintrag.getWuerfel().getWuerfel(2).getAugenzahl();
        int w3 = eintrag.getWuerfel().getWuerfel(3).getAugenzahl();
        int w4 = eintrag.getWuerfel().getWuerfel(4).getAugenzahl();
        eintragFragment.setWuerfelText(
                (w0>0)?""+w0:"",
                (w1>0)?""+w1:"",
                (w2>0)?""+w2:"",
                (w3>0)?""+w3:"",
                (w4>0)?""+w4:""
        );
    }

    @Override
    public void onFragmentAdded(Fragment f) {
        if(f instanceof EintragFragment){
            eintragFragment = (EintragFragment) f;
            eintragFragment.addListener(this);
            eintragFragment.setAugenButtonListener(this);
            redraw();
        }
    }

    @Override
    public void onFragmentRemoved(Fragment f) {
        if(f instanceof EintragFragment){
            EintragFragment eintragFragment = (EintragFragment) f;
            eintragFragment.remListener(this);
            this.eintragFragment = null;
        }

    }

    @Override
    public void onFragmentDone(Fragment f) {
        manager.getDatabase().getCurrent().setEintrag(indexSpieler, eintrag);
        manager.getTabellenController().resetSpielerIndex();
    }

    @Override
    public void modelChanged(Object o) {
        redraw();
    }

    @Override
    public void onClick(View view) {
        int augenzahl = (int) view.getTag();
        int indexWuerfel = eintragFragment.getSelectedWuerfel();
        eintrag.getWuerfel().setAugenzahl(indexWuerfel, augenzahl);
        eintragFragment.setSelectedWuerfel((indexWuerfel+1)%5);
    }
}
