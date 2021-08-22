package com.example.kniffelhelfer;

import android.util.Log;

import androidx.fragment.app.Fragment;

public class SpielstandController implements Manager.Listener, ManagedFragment.Listener {
    private Manager manager;
    private OptionenController optionenController;
    public SpielstandController(Manager m){
        manager = m;
        optionenController = new OptionenController(m);

        m.addListener(this);
    }

    @Override
    public void onFragmentAdded(Fragment f) {

        if(f instanceof SpielstandFragment){
            SpielstandFragment spielstandFragment = (SpielstandFragment) f;
            spielstandFragment.addListener(this);
        }
    }

    @Override
    public void onFragmentRemoved(Fragment f) {
        if(f instanceof SpielstandFragment){
            SpielstandFragment spielstandFragment = (SpielstandFragment) f;
            spielstandFragment.remListener(this);
        }

    }

    @Override
    public void onFragmentDone(Fragment f) {
        SpielstandFragment spielstandFragment = (SpielstandFragment) f;
        //get selected Spielstand (null = new one)

        optionenController.setSpielstand(null);
    }
}
