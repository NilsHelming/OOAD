package com.example.kniffelhelfer;


import androidx.annotation.NonNull;

public class Kategorie extends Model implements Model.Listener {

    public enum Type{Einsen, Zweien, Dreien, Vieren, Fuenfen, Sechsen, Dreierpasch, Viererpasch,
        FullHouse, KleineStrasse, GrosseStrasse, Kniffel, Chance}

    public final Type kategorie;
    private Eintrag[] eintraege;

    public Kategorie(Type type, int anzahl) {
        this.kategorie = type;
        this.eintraege = new Eintrag[anzahl];
        for(int i = 0; i<anzahl; i++){
            this.eintraege[i] = new Eintrag(type);
            this.eintraege[i].addListener(this);
        }
    }

    public Eintrag getEintrag(int index) {
        return eintraege[index];
    }
    public void setEintrag(int index, @NonNull Eintrag eintrag){
        eintraege[index].setWuerfel(eintrag.getWuerfel());
    }
    public int getPunkte(int index){
        return getPunkte(eintraege[index]);
    }

    public static int getPunkte(@NonNull Eintrag eintrag){
        return getPunkte(eintrag.kategorie, eintrag.getWuerfel());
    }
    public static int getPunkte(@NonNull Type kategorie, WuerfelSet wuerfel){
        switch (kategorie){
            case Einsen:
                return zaehleAugen(wuerfel, 1) * 1;
            case Zweien:
                return zaehleAugen(wuerfel, 2) * 2;
            case Dreien:
                return zaehleAugen(wuerfel, 3) * 3;
            case Vieren:
                return zaehleAugen(wuerfel, 4) * 4;
            case Fuenfen:
                return zaehleAugen(wuerfel, 5) * 5;
            case Sechsen:
                return zaehleAugen(wuerfel, 6) * 6;
            case Dreierpasch: {
                for (Wuerfel w : wuerfel) {
                    if (zaehleAugen(wuerfel, w.getAugenzahl()) >= 3)
                        return zaehleAlleAugen(wuerfel);
                }
                return 0;
            }
            case Viererpasch: {
                for (Wuerfel w : wuerfel) {
                    if (zaehleAugen(wuerfel, w.getAugenzahl()) >= 4)
                        return zaehleAlleAugen(wuerfel);
                }
                return 0;
            }
            case Kniffel:{
                for (Wuerfel w : wuerfel) {
                    if (zaehleAugen(wuerfel, w.getAugenzahl()) >= 5)
                        return 50;
                }
                return 0;
            }
            case FullHouse: {
                boolean dreier = false;
                boolean zweier = false;
                boolean kniffel = false;
                for (Wuerfel w : wuerfel) {
                    int anz = zaehleAugen(wuerfel, w.getAugenzahl());
                    if (anz == 3)
                        dreier = true;
                    else if (anz == 2)
                        zweier = true;
                    else if (anz == 5)
                        kniffel = true;
                }

                if (kniffel || dreier && zweier)
                    return 25;
                else
                    return 0;
            }
            case KleineStrasse: {
                int count = 0;
                for (int augen = 1; augen <= 6; augen++) {
                    if (zaehleAugen(wuerfel, augen) >= 1) {
                        count++;
                        if (count >= 4) {
                            return 30;
                        }
                    } else {
                        count = 0;
                    }
                }
                return 0;
            }
            case GrosseStrasse: {
                int count = 0;
                for (int augen = 1; augen <= 6; augen++) {
                    if (zaehleAugen(wuerfel, augen) >= 1) {
                        count++;
                        if (count >= 5) {
                            return 40;
                        }
                    } else {
                        count = 0;
                    }
                }
                return 0;
            }
            case Chance:
                return zaehleAlleAugen(wuerfel);
            default:
                throw new IllegalArgumentException();
        }
    }

    private static int zaehleAlleAugen(@NonNull WuerfelSet wuerfelSet){
        int sum = 0;
        for(Wuerfel wuerfel : wuerfelSet){
            sum+=wuerfel.getAugenzahl();
        }
        return sum;
    }
    private static int zaehleAugen(@NonNull WuerfelSet wuerfelSet, int augenzahl){
        if(augenzahl==0)
            return 0;
        int sum = 0;
        for(Wuerfel wuerfel : wuerfelSet){
            if(wuerfel.getAugenzahl() == augenzahl)
                sum++;
        }
        return sum;
    }

    @Override
    public void modelChanged(Object o) {
        updateListeners();
    }

    public Kategorie clone(){
        Kategorie kategorie = new Kategorie(this.kategorie, eintraege.length);
        for(int i=0; i<eintraege.length;i++){
            kategorie.setEintrag(i, kategorie.getEintrag(i));
        }
        return kategorie;
    }

    public int getLocale(){
        return getLocale(this.kategorie);
    }
    public static int getLocale(@NonNull Kategorie.Type type){
        switch(type){
            case Einsen:
                return R.string.kategorie_label_einsen;
            case Zweien:
                return R.string.kategorie_label_zweien;
            case Dreien:
                return R.string.kategorie_label_dreien;
            case Vieren:
                return R.string.kategorie_label_vieren;
            case Fuenfen:
                return R.string.kategorie_label_fuenfen;
            case Sechsen:
                return R.string.kategorie_label_sechsen;
            case Dreierpasch:
                return R.string.kategorie_label_dreierpasch;
            case Viererpasch:
                return R.string.kategorie_label_viererpasch;
            case FullHouse:
                return R.string.kategorie_label_fullhouse;
            case KleineStrasse:
                return R.string.kategorie_label_kleinestrasse;
            case GrosseStrasse:
                return R.string.kategorie_label_grossestrasse;
            case Kniffel:
                return R.string.kategorie_label_kniffel;
            case Chance:
                return R.string.kategorie_label_chance;
            default:
                return R.string.error;
        }
    }
}
