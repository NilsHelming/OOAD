package com.example.kniffelhelfer;

public class Eintrag extends Model implements Model.Listener {
    private WuerfelSet wuerfel;
    public final Kategorie.Type kategorie;

    public Eintrag(Kategorie.Type type){
        wuerfel = new WuerfelSet();
        wuerfel.addListener(this);
        kategorie = type;
    }

    public int getPunkte(){
        return Kategorie.getPunkte(this);
    }
    public boolean istDefault() { return wuerfel.istDefault(); }

    public WuerfelSet getWuerfel() {
        return wuerfel;
    }
    public void setWuerfel(WuerfelSet set){
        wuerfel.setAugenzahlen(set);
    }

    public Eintrag clone(){
        Eintrag eintrag = new Eintrag(kategorie);
        eintrag.setWuerfel(wuerfel);
        return eintrag;
    }

    @Override
    public void modelChanged(Object o) {
        updateListeners();
    }
}
