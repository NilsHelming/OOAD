package com.example.kniffelhelfer;

import androidx.annotation.NonNull;

import java.util.Calendar;
import java.util.Date;
import java.util.Iterator;

public class Spielstand extends Model implements Iterable<Kategorie>, Model.Listener{
    private String name = "<Neuer Spielstand>";
    private boolean wuerfelSim = false;
    private final String[] spieler; //constant length! entries can be manipulated
    private Kategorie[] kategorien = new Kategorie[13];

    public Spielstand(String name, boolean wuerfelSim, @NonNull String[] spieler) {
        this.name = name;
        this.wuerfelSim = wuerfelSim;
        this.spieler = new String[spieler.length];
        for(int i=0; i<spieler.length; i++){ //kopiere das Array, statt es einfach zu übernehmen.
            this.spieler[i] = spieler[i]; //(einfach nur zur Sicherheit!)
        }

        kategorien[0] = new Kategorie(Kategorie.Type.Einsen, spieler.length);
        kategorien[1] = new Kategorie(Kategorie.Type.Zweien, spieler.length);
        kategorien[2] = new Kategorie(Kategorie.Type.Dreien, spieler.length);
        kategorien[3] = new Kategorie(Kategorie.Type.Vieren, spieler.length);
        kategorien[4] = new Kategorie(Kategorie.Type.Fuenfen, spieler.length);
        kategorien[5] = new Kategorie(Kategorie.Type.Sechsen, spieler.length);
        kategorien[6] = new Kategorie(Kategorie.Type.Dreierpasch, spieler.length);
        kategorien[7] = new Kategorie(Kategorie.Type.Viererpasch, spieler.length);
        kategorien[8] = new Kategorie(Kategorie.Type.FullHouse, spieler.length);
        kategorien[9] = new Kategorie(Kategorie.Type.KleineStrasse, spieler.length);
        kategorien[10] = new Kategorie(Kategorie.Type.GrosseStrasse, spieler.length);
        kategorien[11] = new Kategorie(Kategorie.Type.Kniffel, spieler.length);
        kategorien[12] = new Kategorie(Kategorie.Type.Chance, spieler.length);
        for(Kategorie kat : kategorien){
            kat.addListener(this);
        }
    }
    public Spielstand(String name, boolean wuerfelSim, int anzahl) {
        this(name, wuerfelSim, defaultNamen(anzahl));
    }

    public String getName(){
        return name;
    }
    public void setName(String name){
        this.name = name;
    }

    public boolean getWuerfelSim(){
        return wuerfelSim;
    }
    public void setWuerfelSim(boolean wuerfelSim){
        this.wuerfelSim = wuerfelSim;
        updateListeners();
    }

    public String getSpielerName(int index){
        return spieler[index];
    }
    public void setSpielerName(int index, String name){
        spieler[index] = name;
        updateListeners();
    }
    public int getSpielerAnzahl(){
        return spieler.length;
    }

    private void setKategorie(Kategorie kategorie){
        Kategorie kategorie0 = getKategorie(kategorie.kategorie);
        for(int i=0; i<spieler.length; i++){
            kategorie0.setEintrag(i, kategorie.getEintrag(i));
        }
    }
    public Kategorie getKategorie(Kategorie.Type kategorie){
        for(Kategorie kat : kategorien){
            if(kat.kategorie == kategorie)
                return kat;
        }
        throw new IllegalArgumentException("Kategorie.Type nicht gefunden!");
    }
    public Eintrag getEintrag(Kategorie.Type kategorie, int indexSpieler){
        Kategorie kat = getKategorie(kategorie);
        return kat.getEintrag(indexSpieler);
    }
    public void setEintrag(int indexSpieler, Eintrag eintrag){
        Kategorie kat = getKategorie(eintrag.kategorie);
        kat.setEintrag(indexSpieler, eintrag);
    }

    public int getPunkteSumme(int indexSpieler){
        int sum = 0;
        for(Kategorie kat : this){
            sum += kat.getPunkte(indexSpieler);
        }
        return sum;
    }

    public int getNextSpieler(){
        int[] counters = new int[spieler.length];

        //gehe über alle Einträge, und zähle die Einträge, die nicht im Default-Status sind.
        for(Kategorie kat : this)
            for(int indexSpieler = 0; indexSpieler<spieler.length; indexSpieler++)
                if(!kat.getEintrag(indexSpieler).istDefault())
                    counters[indexSpieler]++;

        int nextSpieler = 0;
        int nextCount = counters[0];
        for(int indexSpieler = 0; indexSpieler<spieler.length; indexSpieler++) {
            if (counters[indexSpieler] < nextCount) {
                nextSpieler = indexSpieler;
                nextCount = counters[indexSpieler];
            }
        }

        return nextSpieler;
    }

    private static String[] defaultNamen(int anzahl){
        String[] arr = new String[anzahl];
        for(int i = 0; i<anzahl; i++)
            arr[i] = "Spieler " + (i + 1);
        return arr;
    }

    @NonNull
    @Override
    public Iterator<Kategorie> iterator() {
        return new Iterator<Kategorie>() {
            int index = 0;
            @Override
            public boolean hasNext() {
                return index < kategorien.length;
            }

            @Override
            public Kategorie next() {
                index++;
                return kategorien[index-1];
            }
        };
    }

    public Spielstand clone(){
        Spielstand spielstand = new Spielstand(this.name, this.wuerfelSim, this.spieler.length);
        for(Kategorie kategorie : this){
            spielstand.setKategorie(kategorie);
        }
        return spielstand;
    }

    @Override
    public void modelChanged(Object o) {
        updateListeners();
    }
}
