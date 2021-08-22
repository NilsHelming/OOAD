package com.example.kniffelhelfer;

import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import androidx.annotation.NonNull;
import androidx.navigation.fragment.NavHostFragment;

import com.example.kniffelhelfer.databinding.FragmentNamenBinding;

import java.util.ArrayList;
import java.util.Collection;
import java.util.List;


public class NamenFragment extends ManagedFragment {

    private FragmentNamenBinding binding;

    private List listNamen = new ArrayList<String>();
    private NameviewAdapter adapter;


    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,Bundle savedInstanceState) {
        binding = FragmentNamenBinding.inflate(inflater, container, false);
        return binding.getRoot();
    }

    public void setNamen(Collection<String> coll){
        listNamen.clear();
        listNamen.addAll(coll);
        try { binding.listView1.setAdapter(adapter);
        }catch(Exception e){}
    }
    public List<String> getNamen(){
        return new ArrayList<String>(listNamen); //return a copy. (otherwise: weird interactions!)
    }


    public void onViewCreated(@NonNull View view, Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);
        adapter = new NameviewAdapter(this.getContext(),listNamen);
        binding.listView1.setItemsCanFocus(true);
        binding.listView1.setAdapter(adapter);

        binding.buttonCheck.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                fragmentDone();
                NavHostFragment.findNavController(NamenFragment.this)
                        .navigate(R.id.action_namenFragment_to_tabellenFragment);

            }
        });
    }

    @Override
    public void onDestroyView() {
        super.onDestroyView();
        binding = null;
    }

}