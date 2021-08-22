package com.example.kniffelhelfer;

import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.CompoundButton;
import android.widget.RadioGroup;
import android.widget.ToggleButton;

import androidx.annotation.NonNull;
import androidx.navigation.fragment.NavHostFragment;

import com.example.kniffelhelfer.databinding.FragmentEintragBinding;
import com.google.android.material.button.MaterialButton;

public class EintragFragment extends ManagedFragment implements CompoundButton.OnCheckedChangeListener {

    private FragmentEintragBinding binding;

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        binding = FragmentEintragBinding.inflate(inflater, container, false);
        return binding.getRoot();

    }

    public void setSpielerText(String text){
        binding.textSpieler.setText(text);
    }
    public void setKategorieLocale(int id){
        binding.textKategorie.setText(id);
    }
    public void setPunkteText(int punkte){
        binding.textPunkte.setText(""+punkte);
    }

    public void setWuerfelText(String w0, String w1, String w2, String w3, String w4){
        binding.buttonWuerfel0.setText(w0);
        binding.buttonWuerfel0.setTextOff(w0);
        binding.buttonWuerfel0.setTextOn(w0);

        binding.buttonWuerfel1.setText(w1);
        binding.buttonWuerfel1.setTextOff(w1);
        binding.buttonWuerfel1.setTextOn(w1);

        binding.buttonWuerfel2.setText(w2);
        binding.buttonWuerfel2.setTextOff(w2);
        binding.buttonWuerfel2.setTextOn(w2);

        binding.buttonWuerfel3.setText(w3);
        binding.buttonWuerfel3.setTextOff(w3);
        binding.buttonWuerfel3.setTextOn(w3);

        binding.buttonWuerfel4.setText(w4);
        binding.buttonWuerfel4.setTextOff(w4);
        binding.buttonWuerfel4.setTextOn(w4);
    }

    public void setAugenButtonListener(View.OnClickListener listener){
        binding.buttonAugen1.setOnClickListener(listener);
        binding.buttonAugen2.setOnClickListener(listener);
        binding.buttonAugen3.setOnClickListener(listener);
        binding.buttonAugen4.setOnClickListener(listener);
        binding.buttonAugen5.setOnClickListener(listener);
        binding.buttonAugen6.setOnClickListener(listener);
    }

    public int getSelectedWuerfel(){
        if(binding.buttonWuerfel0.isChecked())
            return 0;
        if(binding.buttonWuerfel1.isChecked())
            return 1;
        if(binding.buttonWuerfel2.isChecked())
            return 2;
        if(binding.buttonWuerfel3.isChecked())
            return 3;
        if(binding.buttonWuerfel4.isChecked())
            return 4;
        return -1;
    }
    public void setSelectedWuerfel(int index){
        if(index == 0)
            binding.buttonWuerfel0.setChecked(true);
        else if(index == 1)
            binding.buttonWuerfel1.setChecked(true);
        else if(index == 2)
            binding.buttonWuerfel2.setChecked(true);
        else if(index == 3)
            binding.buttonWuerfel3.setChecked(true);
        else if(index == 4)
            binding.buttonWuerfel4.setChecked(true);

    }

    public void onViewCreated(@NonNull View view, Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);

        binding.buttonWuerfel0.setTag(0);
        binding.buttonWuerfel0.setOnCheckedChangeListener(this);
        binding.buttonWuerfel1.setTag(1);
        binding.buttonWuerfel1.setOnCheckedChangeListener(this);
        binding.buttonWuerfel2.setTag(2);
        binding.buttonWuerfel2.setOnCheckedChangeListener(this);
        binding.buttonWuerfel3.setTag(3);
        binding.buttonWuerfel3.setOnCheckedChangeListener(this);
        binding.buttonWuerfel4.setTag(4);
        binding.buttonWuerfel4.setOnCheckedChangeListener(this);

        binding.buttonAugen1.setTag(1);
        binding.buttonAugen2.setTag(2);
        binding.buttonAugen3.setTag(3);
        binding.buttonAugen4.setTag(4);
        binding.buttonAugen5.setTag(5);
        binding.buttonAugen6.setTag(6);


        binding.buttonCheck.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                fragmentDone();
                NavHostFragment.findNavController(EintragFragment.this)
                        .navigateUp();
            }
        });
    }

    @Override
    public void onDestroyView() {
        super.onDestroyView();
        binding = null;
    }

    @Override
    public void onCheckedChanged(CompoundButton compoundButton, boolean b) {
        if(!b) {
            if(getSelectedWuerfel()<0) //if none is selected
                binding.buttonWuerfel0.setChecked(true); //select first!
            return;
        }else{
            int indexWuerfel = (int) compoundButton.getTag();
            if(indexWuerfel!=0)
                binding.buttonWuerfel0.setChecked(false);
            if(indexWuerfel!=1)
                binding.buttonWuerfel1.setChecked(false);
            if(indexWuerfel!=2)
                binding.buttonWuerfel2.setChecked(false);
            if(indexWuerfel!=3)
                binding.buttonWuerfel3.setChecked(false);
            if(indexWuerfel!=4)
                binding.buttonWuerfel4.setChecked(false);
        }

    }
}