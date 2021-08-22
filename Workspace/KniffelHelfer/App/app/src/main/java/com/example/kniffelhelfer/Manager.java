package com.example.kniffelhelfer;

import android.util.ArrayMap;
import android.util.Log;

import androidx.annotation.NonNull;
import androidx.fragment.app.Fragment;
import androidx.lifecycle.ViewModel;

import java.util.Collection;
import java.util.LinkedList;
import java.util.Map;

public class Manager extends ViewModel {
    private Map<Integer, Fragment> fragmentMap = new ArrayMap<Integer, Fragment>();

    private Database db = new Database();
    private SpielstandController spielstandController;
    private TabellenController tabellenController;

    public Manager(){
        spielstandController = new SpielstandController(this);
        tabellenController = new TabellenController(this);
    }

    public Database getDatabase(){
        return db;
    }
    public SpielstandController getSpielstandController(){
        return spielstandController;
    }
    public TabellenController getTabellenController(){
        return tabellenController;
    }

    public void addFragment(int id, Fragment fragment){
        fragmentMap.put(id, fragment);
        for(Manager.Listener l : listeners){
            l.onFragmentAdded(fragment);
        }
    }
    public void remFragment(int id, Fragment fragment){
        fragmentMap.remove(id, fragment);
        for(Manager.Listener l : listeners){
            l.onFragmentRemoved(fragment);
        }
    }

    public interface Listener{
        void onFragmentAdded(Fragment f);
        void onFragmentRemoved(Fragment f);
    }

    private Collection<Manager.Listener> listeners = new LinkedList<Manager.Listener>();

    public void addListener(Manager.Listener listener){
        if(!listeners.contains(listener))
            listeners.add(listener);
    }
}
