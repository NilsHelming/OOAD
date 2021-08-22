package com.example.kniffelhelfer;

import android.content.Context;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.Button;
import android.widget.TextView;

import java.util.List;


public class TabelleviewAdapter extends BaseAdapter {
    private class ViewHolder{
        TextView label;
        TextView content;
        Button button;
    }
    public static class Eintrag{
        public int label;
        public String content;
        public Eintrag(int label, String content){
            this.label = label;
            this.content = content;
        }
    }

    private Context context;
    private List<Eintrag> list;
    private View.OnClickListener listener;

    LayoutInflater mInflater;
    public TabelleviewAdapter(Context context, List<Eintrag> list, View.OnClickListener listener){
        this.context = context;
        this.list = list;
        this.listener = listener;
    }

    @Override
    public int getCount() {
        // TODO Auto-generated method stub
        return list.size();
    }

    @Override
    public Object getItem(int arg0) {
        // TODO Auto-generated method stub
        return arg0;
    }

    @Override
    public long getItemId(int arg0) {
        // TODO Auto-generated method stub
        return arg0;
    }

    @Override
    public View getView(int position, View convertView, ViewGroup arg2) {
        final ViewHolder holder = new ViewHolder();
        mInflater = (LayoutInflater) context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
        convertView = mInflater.inflate(R.layout.tabelleview_adapter, null);
        holder.label = (TextView) convertView.findViewById(R.id.label);
        holder.content = (TextView) convertView.findViewById(R.id.content);
        holder.button = (Button) convertView.findViewById(R.id.button);

        holder.label.setText(list.get(position).label);
        holder.content.setText(list.get(position).content);
        holder.button.setId(position);
        holder.button.setOnClickListener(listener);

        convertView.setTag(holder);

        return convertView;
    }

}


