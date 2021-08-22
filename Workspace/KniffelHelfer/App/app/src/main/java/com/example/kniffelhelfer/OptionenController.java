package com.example.kniffelhelfer;

import android.util.Log;

import androidx.fragment.app.Fragment;

import java.util.ArrayList;
import java.util.Collection;
import java.util.LinkedList;
import java.util.List;

public class OptionenController implements Manager.Listener, ManagedFragment.Listener, Model.Listener {
    private Manager manager;
    private Spielstand spielstand = null;
    private OptionenFragment optionenFragment = null;
    private NamenFragment namenFragment = null;
    public OptionenController(Manager m){
        manager = m;

        manager.addListener(this);
    }

    public void setSpielstand(Spielstand spielstand){
        if(this.spielstand != null)
            this.spielstand.remListener(this);

        this.spielstand = spielstand;

        if(this.spielstand != null)
            this.spielstand.addListener(this);

        redraw();
    }

    private void redraw(){

        if(optionenFragment!=null) {
            if (spielstand == null) {
                optionenFragment.setName("Neues Spiel");
                optionenFragment.setPlayerCount(4, true);
                optionenFragment.setSimulate(false);
            } else { //spielstand != null
                optionenFragment.setName(spielstand.getName());
                optionenFragment.setPlayerCount(spielstand.getSpielerAnzahl(), false);
                optionenFragment.setSimulate(spielstand.getWuerfelSim());
            }
        }
        if(namenFragment!=null){

            if (spielstand == null) {

                namenFragment.setNamen(new ArrayList<String>());
            } else { //spielstand != null

                Collection<String> spielerNamen = new ArrayList<String>(spielstand.getSpielerAnzahl());
                for(int i = 0; i<spielstand.getSpielerAnzahl(); i++)
                    spielerNamen.add(spielstand.getSpielerName(i));

                namenFragment.setNamen(spielerNamen);
            }
        }
    }

    @Override
    public void onFragmentAdded(Fragment f) {
        if(f instanceof OptionenFragment) {
            optionenFragment = (OptionenFragment) f;
            optionenFragment.addListener(this);
            redraw();
        }

        if(f instanceof NamenFragment) {
            namenFragment = (NamenFragment) f;
            namenFragment.addListener(this);
            redraw();
        }
    }

    @Override
    public void onFragmentRemoved(Fragment f) {
        if(f instanceof OptionenFragment) {
            OptionenFragment optionenFragment = (OptionenFragment) f;
            optionenFragment.remListener(this);
            this.optionenFragment = null;
        }

        if(f instanceof NamenFragment) {
            NamenFragment namenFragment = (NamenFragment) f;
            namenFragment.remListener(this);
            this.optionenFragment = null;
        }
    }

    @Override
    public void onFragmentDone(Fragment f) {
        if(f instanceof OptionenFragment) {
            OptionenFragment optionenFragment = (OptionenFragment) f;

            String name = optionenFragment.getName();
            boolean simulate = optionenFragment.getSimulate();
            int playerCount = optionenFragment.getPlayerCount();

            if(playerCount < 1)
                playerCount = 2;

            if (spielstand == null) {
                setSpielstand(new Spielstand(name, simulate, playerCount)); //triggers redraw()
            } else {
                spielstand.setName(name); //triggers redraw()
                spielstand.setWuerfelSim(simulate); //triggers redraw()
                //playerCount cannot be altered after the fact!
            }
        }

        if(f instanceof NamenFragment){
            NamenFragment namenFragment = (NamenFragment) f;

            if (spielstand == null) {
                throw new IllegalStateException("es Existiert ein Namen-Fragment ohne gewählten Spielstand!");
            } else {
                List<String> spielerNamen = namenFragment.getNamen();
                for(int i = 0; i<spielstand.getSpielerAnzahl() && i<spielerNamen.size(); i++)
                    spielstand.setSpielerName(i, spielerNamen.get(i)); //triggers redraws!
            }

            manager.getDatabase().setCurrent(spielstand);
        }
    }

    @Override
    public void modelChanged(Object o) {
        redraw();
    }
}
