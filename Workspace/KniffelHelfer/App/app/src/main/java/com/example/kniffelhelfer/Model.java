package com.example.kniffelhelfer;

import java.io.Serializable;
import java.util.Collection;
import java.util.LinkedList;

public class Model implements Serializable{
    public interface Listener{
        void modelChanged(Object o);
    }


    private Collection<Listener> listeners = new LinkedList<Listener>();

    public void addListener(Listener listener){
        if(!listeners.contains(listener))
            listeners.add(listener);
    }
    public void remListener(Listener listener){
        listeners.remove(listener);
    }
    protected void updateListeners(){
        for(Listener l : listeners){
            l.modelChanged(this);
        }
    }
}
