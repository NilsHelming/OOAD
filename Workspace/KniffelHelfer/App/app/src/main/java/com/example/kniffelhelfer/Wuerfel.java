package com.example.kniffelhelfer;

public class Wuerfel extends Model {
    private int augenzahl = 0;
    
    public void reset(){
        augenzahl = 0;
        updateListeners();
    }
    public void wuerfeln(){
        augenzahl = (int) (Math.random()*6+1);
        updateListeners();
    }
    public void setAugenzahl(int n){
        if (n<=6 && n>=0) {
            augenzahl = n;
            updateListeners();
        } else
            throw new IllegalArgumentException();
    }
    public int getAugenzahl(){
        return augenzahl;
    }
}
