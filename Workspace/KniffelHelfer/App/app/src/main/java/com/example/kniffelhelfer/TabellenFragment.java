package com.example.kniffelhelfer;

import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;

import androidx.annotation.NonNull;
import androidx.navigation.fragment.NavHostFragment;

import com.example.kniffelhelfer.databinding.FragmentTabelleBinding;

import java.util.ArrayList;
import java.util.Collection;
import java.util.List;

public class TabellenFragment extends ManagedFragment {

    private FragmentTabelleBinding binding;
    private final List<String> spielerNamen = new ArrayList<String>();

    private List<TabelleviewAdapter.Eintrag> listEintraege = new ArrayList<TabelleviewAdapter.Eintrag>();
    private TabelleviewAdapter adapter;

    private int indexEintrag = 0;

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState){
        binding = FragmentTabelleBinding.inflate(inflater, container, false);
        return binding.getRoot();
    }

    public void setSpielerSelectListener(AdapterView.OnItemSelectedListener listener){
        binding.dropdownSpieler.setOnItemSelectedListener(listener);
    }

    public void setSpielerNamen(List<String> spielerNamen) {
        if(!this.spielerNamen.equals(spielerNamen)) {
            this.spielerNamen.clear();
            this.spielerNamen.addAll(spielerNamen);
        }

    }
    public void setSelectedSpieler(int index){
        binding.dropdownSpieler.setSelection(index);
    }
    public int getSelectedSpieler(){
        return binding.dropdownSpieler.getSelectedItemPosition();
    }
    public int getSelectedEintrag(){
        return indexEintrag;
    }

    public void setEintraege(Collection<TabelleviewAdapter.Eintrag> collection){
        listEintraege.clear();
        listEintraege.addAll(collection);
        try { binding.listView1.setAdapter(adapter);
        }catch(Exception e){}
    }

    public void onViewCreated(@NonNull View view, Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);

        // preparing Dropdown
        ArrayAdapter<String> dataAdapter = new ArrayAdapter<String>(getActivity(), android.R.layout.simple_spinner_item, spielerNamen);
        dataAdapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        binding.dropdownSpieler.setAdapter(dataAdapter);

        adapter = new TabelleviewAdapter(this.getContext(), listEintraege, new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                indexEintrag = view.getId();
                fragmentDone();
                NavHostFragment.findNavController(TabellenFragment.this)
                        .navigate(R.id.action_tabellenFragment_to_eintragFragment);
            }
        });
        binding.listView1.setAdapter(adapter);
    }

    @Override
    public void onDestroyView() {
        super.onDestroyView();
        binding = null;
    }

}