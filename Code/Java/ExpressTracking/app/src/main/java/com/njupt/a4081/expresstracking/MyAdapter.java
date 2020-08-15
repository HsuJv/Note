package com.njupt.a4081.expresstracking;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.TextView;

import java.util.List;
import java.util.Map;

/**
 * Created by Hsu on 2017/11/2.
 */

public class MyAdapter extends BaseAdapter {
    private Context context;
    private LayoutInflater layoutInflater;
    private List<Map<String, String>> data;

    public MyAdapter(Context context, List<Map<String, String>> data) {
        this.context = context;
        this.data = data;
        this.layoutInflater = LayoutInflater.from(context);
    }

    @Override
    public int getCount() {
        return data.size();
    }

    @Override
    public Object getItem(int position) {
        return data.get(position);
    }

    @Override
    public long getItemId(int position) {
        return position;
    }

    public class Info {
        public TextView name;
        public TextView num;
        public TextView time;
    }

    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        Info info = new Info();
        convertView = layoutInflater.inflate(R.layout.history_item, null);
        info.name = convertView.findViewById(R.id.history_item_name);
        info.num = convertView.findViewById(R.id.history_item_num);
        info.time = convertView.findViewById(R.id.history_item_time);

        //设置数据
        info.name.setText(data.get(position).get("ShipperName"));
        info.num.setText(data.get(position).get("LogisticCode"));
        info.time.setText(data.get(position).get("Time"));
        return convertView;
    }
}
