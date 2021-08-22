package com.example.kniffelhelfer;

import java.util.ArrayList;
import java.util.Collection;
import java.util.function.Predicate;

public class Database extends Model implements Model.Listener{

    private Collection<Spielstand> spielstaende = new ArrayList<Spielstand>();
    private Spielstand current = null;


    public void setCurrent(Spielstand spielstand){
        if(current!=null)
            current.remListener(this);
        current = spielstand;
        current.addListener(this);

        updateListeners();
    }
    public Spielstand getCurrent(){
        return current;
    }

    public void save(Spielstand spielstand){
        delete(spielstand);
        spielstaende.add(spielstand);

        updateListeners();
    }

    public void delete(Spielstand spielstand){
        delete(spielstand.getName());
    }

    public void delete(String name){
        spielstaende.removeIf(new Predicate<Spielstand>() {
            @Override
            public boolean test(Spielstand comp) {
                return name == comp.getName();
            }
        });

    }


    @Override
    public void modelChanged(Object o) {
        updateListeners();
    }
}
