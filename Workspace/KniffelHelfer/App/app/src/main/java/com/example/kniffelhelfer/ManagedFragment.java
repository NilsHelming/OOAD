package com.example.kniffelhelfer;

import android.os.Bundle;
import android.util.Log;
import android.view.View;

import androidx.annotation.NonNull;
import androidx.fragment.app.Fragment;
import androidx.lifecycle.ViewModelProvider;
import androidx.navigation.fragment.NavHostFragment;

import java.util.Collection;
import java.util.LinkedList;

public class ManagedFragment extends Fragment {
    public interface Listener{
        void onFragmentDone(Fragment f);
    }
    private Collection<ManagedFragment.Listener> listeners = new LinkedList<ManagedFragment.Listener>();
    int navigationId = 0;

    public void addListener(ManagedFragment.Listener listener){
        if(!listeners.contains(listener))
            listeners.add(listener);
    }
    public void remListener(ManagedFragment.Listener listener){
        listeners.remove(listener);
    }
    protected void fragmentDone(){
        for(ManagedFragment.Listener l : listeners){
            l.onFragmentDone(this);
        }
    }

    protected Manager getManager(){
        return new ViewModelProvider(requireActivity()).get(Manager.class);
    }

    public void onViewCreated(@NonNull View view, Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);
        navigationId = NavHostFragment.findNavController(ManagedFragment.this).getCurrentDestination().getId();

        getManager().addFragment(navigationId, this);
    }

    @Override
    public void onDestroyView() {
        getManager().remFragment(navigationId, this);
        super.onDestroyView();
    }
}
