package com.example.kniffelhelfer;

import android.os.Bundle;

import androidx.annotation.NonNull;
import androidx.navigation.fragment.NavHostFragment;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import com.example.kniffelhelfer.databinding.FragmentOptionenBinding;

public class OptionenFragment extends ManagedFragment {

    private FragmentOptionenBinding binding;

    @Override
    public View onCreateView(
            LayoutInflater inflater, ViewGroup container,
            Bundle savedInstanceState
    ) {

        binding = FragmentOptionenBinding.inflate(inflater, container, false);
        return binding.getRoot();

    }

    public void setName(String name){
        binding.textBoxName.setText(name);
    }
    public String getName(){
        return binding.textBoxName.getText().toString();
    }
    public void setPlayerCount(int num, boolean editable){
        binding.textBoxPlayerCount.setText(""+num);
        binding.textBoxPlayerCount.setEnabled(editable);
    }
    public int getPlayerCount(){
        String temp = binding.textBoxPlayerCount.getText().toString();
        if (!temp.equals(""))
            return Integer.parseInt(temp);
        else
            return -1;

    }
    public void setSimulate(boolean sim){
        binding.checkBoxSimulate.setChecked(sim);
    }
    public boolean getSimulate(){
        return binding.checkBoxSimulate.isChecked();
    }


    public void onViewCreated(@NonNull View view, Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);

        binding.buttonCheck.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                fragmentDone();
                NavHostFragment.findNavController(OptionenFragment.this)
                        .navigate(R.id.action_optionenFragment_to_namenFragment);
            }
        });
    }
}