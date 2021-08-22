package com.example.kniffelhelfer;

import androidx.annotation.NonNull;

import java.util.Arrays;
import java.util.Collection;
import java.util.Iterator;

public class WuerfelSet extends Model implements Iterable<Wuerfel>, Model.Listener{
    private Wuerfel[] wuerfel = new Wuerfel[5];

    public WuerfelSet(){
        for(int i = 0; i<wuerfel.length; i++){
            wuerfel[i] = new Wuerfel();
            wuerfel[i].addListener(this);
        }
    }

    public boolean istDefault(){ //überprüfe, ob die Würfel noch im Default-Status sind.
        for(int i = 0; i<wuerfel.length; i++){
            if(wuerfel[i].getAugenzahl() != 0){
                return false;
            }
        }
        return true;
    }

    public void wuerfeln(){
        wuerfeln(Arrays.asList(0,1,2,3,4));
    }
    public void wuerfeln(int index){
        wuerfeln(Arrays.asList(index));
    }
    public void wuerfeln(@NonNull Collection<Integer> coll){
        for (Integer index: coll){
            getWuerfel(index).wuerfeln(); //throws IndexOutOfBounds / NullPointerException
        }
        if (coll.size() > 0)
            updateListeners();
    }

    public Wuerfel getWuerfel(int index){
        if(index > 4 || index < 0)
            throw new IndexOutOfBoundsException();
        return wuerfel[index];
    }

    public void setAugenzahlen(WuerfelSet set){
        for(int i = 0 ; i<5; i++){
            setAugenzahl(i, set.wuerfel[i]);
        }
    }
    public void setAugenzahl(int index, Wuerfel wuerfel){
        setAugenzahl(index, wuerfel.getAugenzahl());
    }
    public void setAugenzahl(int index, int augenzahl){
        wuerfel[index].setAugenzahl(augenzahl);
    }

    @NonNull
    @Override
    public Iterator<Wuerfel> iterator() {
        return new Iterator<Wuerfel>() {
            int index = 0;
            @Override
            public boolean hasNext() {
                return index < wuerfel.length;
            }

            @Override
            public Wuerfel next() {
                index++;
                return wuerfel[index-1];
            }
        };
    }
    @Override
    public void modelChanged(Object t) {
        updateListeners();
    }
}
