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
 * Created by Hsu on 2017/11/7.
 */

public class DisplayAdapter extends BaseAdapter {
    private Context context;
    private LayoutInflater layoutInflater;
    private List<Map<String, String>> data;

    public DisplayAdapter(Context context, List<Map<String, String>> data) {
        this.context = context;
        this.data = data;
        this.layoutInflater = LayoutInflater.from(this.context);
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
        public TextView description;
        public TextView time;
    }

    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        Info info = new Info();
        convertView = layoutInflater.inflate(R.layout.display_item, null);
        info.description = convertView.findViewById(R.id.display_item_description);
        info.time = convertView.findViewById(R.id.display_item_time);

        //设置数据
        info.description.setText(data.get(position).get("AcceptStation"));
        info.time.setText(data.get(position).get("AcceptTime"));

        // 最近一条改色
        if (position == 0){
            info.description.setTextColor(info.description.getResources().getColor(R.color.colorRecentItem));
            info.time.setTextColor(info.time.getResources().getColor(R.color.colorRecentItem));
        }
        else{
            info.description.setTextColor(info.description.getResources().getColor(R.color.black));
        }
        return convertView;
    }
}
