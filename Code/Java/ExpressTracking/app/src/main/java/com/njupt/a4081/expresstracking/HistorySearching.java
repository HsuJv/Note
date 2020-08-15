package com.njupt.a4081.expresstracking;

import android.content.Context;
import android.content.Intent;
import android.content.res.Resources;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.ContextMenu;
import android.view.MenuItem;
import android.view.MotionEvent;
import android.view.View;
import android.widget.AdapterView;
import android.widget.Toast;

import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * Created by Hsu on 2017/11/2.
 */

public class HistorySearching extends AppCompatActivity {

    SearchingHistoryDataHelper dh = new SearchingHistoryDataHelper(HistorySearching.this);

    private Map<String, String> c2nMap = new HashMap<>();

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.history_display);

        // CompanyCode to Name
        try {
            Resources comp_code = getResources();
            InputStream comp_code_file = comp_code.openRawResource(R.raw.comp_code);
            byte[] reader = new byte[comp_code_file.available()];
            if (comp_code_file.read(reader) != -1) {
                List<String> c2nData = Arrays.asList(new String(reader).split("\r\n"));
                for (String c2nItem : c2nData) {
                    List<String> c2n = Arrays.asList(c2nItem.split(";"));
                    c2nMap.put(c2n.get(1), c2n.get(0));
                }

            }
            comp_code_file.close();
        } catch (IOException e) {
            Log.e("test", e.toString());
        }

        // 绑定SlideListView
        SlideListView slideListView = (SlideListView) findViewById(R.id.history_display_list_view);
        final List<Map<String, String>> HistoryMap = RegisterListView(HistorySearching.this,
                c2nMap);
        Log.e("test", HistoryMap.toString());
        MyAdapter myAdapter = new MyAdapter(HistorySearching.this, HistoryMap);
        slideListView.setAdapter(myAdapter);
        initSlideListView(slideListView, HistoryMap);
        //registerForContextMenu(slideListView);

        // 绑定ListView
        /*ListView lv = (ListView)findViewById(R.id.history_display_list_view);
        final List<Map<String, String>> HistoryMap = RegisterListView(HistorySearching.this,
                c2nMap);
        Log.e("test", HistoryMap.toString());
        MyAdapter myAdapter = new MyAdapter(HistorySearching.this, HistoryMap);
        lv.setAdapter(myAdapter);
        //绑定Menu
        registerForContextMenu(lv);


        // 点击intenet
        lv.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                Intent iDisplayResult = new Intent(HistorySearching.this, DisplayResult.class);

                Bundle mBundle = new Bundle();
                mBundle.putString("ShipperCode", HistoryMap.get((int)id).get("ShipperCode"));
                mBundle.putString("ShipperName", HistoryMap.get((int)id).get("ShipperName"));
                mBundle.putString("LogisticCode", HistoryMap.get((int)id).get("LogisticCode"));
                iDisplayResult.putExtras(mBundle);
                startActivity(iDisplayResult);
            }
        });*/


        // 清空记录
        findViewById(R.id.history_display_delete_all).setOnClickListener(new View.OnClickListener() {
            SlideListView slideListView = (SlideListView) findViewById(R.id.history_display_list_view);

            @Override
            public void onClick(View v) {
                if (slideListView.getAdapter().getCount() != 0) {
                    ConfirmDialog confirmDialog = new ConfirmDialog();
                    confirmDialog.setDialogClickListener(new ConfirmDialog.onDialogClickListener() {
                        @Override
                        public void onConfirmClick() {
                            dh.DeleteAll();
                            slideListView.setAdapter(new MyAdapter(HistorySearching.this,
                                    RegisterListView(HistorySearching.this, c2nMap)));
                            Toast.makeText(HistorySearching.this,
                                    "已清空", Toast.LENGTH_LONG).show();
                        }

                        @Override
                        public void onCancelClick() {
                            //取消操作
                        }
                    });
                    confirmDialog.show(getFragmentManager(), "");
                } else {
                    Toast.makeText(HistorySearching.this, "没有需要清空的记录",
                            Toast.LENGTH_LONG).show();
                }
            }
        });
    }

    //绑定ListView
    public List<Map<String, String>> RegisterListView(Context context, Map<String, String> c2nMap) {
        List<String> HistoryData = new ArrayList<>();
        HistoryData.addAll(dh.DisplayHistory());
        final List<Map<String, String>> HistoryMap = new ArrayList<>();
        for (int i = 0; i < HistoryData.size(); i++) {
            String HistoryItem = HistoryData.get(i);
            for (String j : c2nMap.keySet()) {
                if (HistoryItem.indexOf(j) != -1) {
                    Map<String, String> HistoryMapItem = new HashMap<>();
                    HistoryMapItem.put("ShipperCode", j);
                    HistoryMapItem.put("ShipperName", c2nMap.get(j));
                    HistoryMapItem.put("LogisticCode", HistoryItem.substring(0, HistoryItem
                            .indexOf(';')));
                    HistoryMapItem.put("Time", HistoryItem.substring(HistoryItem.lastIndexOf(';'
                    )));
                    HistoryMap.add(HistoryMapItem);
                }
            }
        }
        return HistoryMap;
    }

    //设置Menu选项
    @Override
    public void onCreateContextMenu(ContextMenu menu, View v, ContextMenu.ContextMenuInfo menuInfo) {
        int groupId = 0;
        //显示轨迹
        int displayCommand_id = 0;
        int displayCommand_order = 0;
        String displayCommand = "显示快递轨迹";
        menu.add(groupId, displayCommand_id, displayCommand_order, displayCommand);
        //删除
        int deleteCommand_id = 1;
        int deleteCommand_order = 1;
        String deleteCommand = "删除该记录";
        menu.add(groupId, deleteCommand_id, deleteCommand_order, deleteCommand);
    }

    //选项事件
    @Override
    public boolean onContextItemSelected(MenuItem item) {
        AdapterView.AdapterContextMenuInfo adaptInfo = (AdapterView.AdapterContextMenuInfo) item.getMenuInfo();
        int selectedPosition = adaptInfo.position;
        final SlideListView slideListView = (SlideListView) findViewById(R.id.history_display_list_view);
        final HashMap<String, String> map = (HashMap<String, String>) slideListView.getItemAtPosition
                (selectedPosition);
        switch (item.getItemId()) {
            case 0:
                Intent iDisplayResult = new Intent(HistorySearching.this, DisplayResult.class);
                Bundle mBundle = new Bundle();
                mBundle.putString("ShipperCode", map.get("ShipperCode"));
                mBundle.putString("ShipperName", map.get("ShipperName"));
                mBundle.putString("LogisticCode", map.get("LogisticCode"));
                iDisplayResult.putExtras(mBundle);
                startActivity(iDisplayResult);
                return true;
            case 1:
                //确认对话框
                ConfirmDialog confirmDialog = new ConfirmDialog();
                confirmDialog.setDialogClickListener(new ConfirmDialog.onDialogClickListener() {
                    @Override
                    public void onConfirmClick() {
                        try {
                            dh.DeleteHistory(map.get("LogisticCode"));
                        } catch (Exception e) {
                            e.printStackTrace();
                        }
                        slideListView.setAdapter(new MyAdapter(HistorySearching.this,
                                RegisterListView(HistorySearching.this, c2nMap)));
                        Toast.makeText(HistorySearching.this,
                                "你已经成功删除", Toast.LENGTH_LONG).show();
                    }

                    @Override
                    public void onCancelClick() {
                        //取消操作
                    }
                });
                confirmDialog.show(getFragmentManager(), "");
                Log.e("dialog", getFragmentManager().toString());
        }
        return false;
    }

    public void initSlideListView(final SlideListView slideListView, final List<Map<String, String>> HistoryMap) {

        //设置列表项Item显示按钮的点击监听事件
        slideListView.setDisplayButtonClickListener(new SlideListView.DisplayButtonClickListener() {
            @Override
            public void onDisplayClick(int position) {
                HashMap<String, String> map = (HashMap<String, String>)slideListView.getItemAtPosition(position);
                Intent iDisplayResult = new Intent(HistorySearching.this, DisplayResult.class);
                Bundle mBundle = new Bundle();
                mBundle.putString("ShipperCode", map.get("ShipperCode"));
                mBundle.putString("ShipperName", map.get("ShipperName"));
                mBundle.putString("LogisticCode", map.get("LogisticCode"));
                iDisplayResult.putExtras(mBundle);
                startActivity(iDisplayResult);
            }
        });

        //设置列表项Item删除按钮的点击监听事件
        slideListView.setDeleteButtonClickListener(new SlideListView.DelButtonClickListener() {
            @Override
            public void onDeleteClick(int position) {
                final HashMap<String, String> map = (HashMap<String, String>)slideListView.getItemAtPosition(position);
                //确认对话框
                ConfirmDialog confirmDialog = new ConfirmDialog();
                confirmDialog.setDialogClickListener(new ConfirmDialog.onDialogClickListener() {
                    @Override
                    public void onConfirmClick() {
                        try {
                            dh.DeleteHistory(map.get("LogisticCode"));
                        } catch (Exception e) {
                            e.printStackTrace();
                        }
                        slideListView.setAdapter(new MyAdapter(HistorySearching.this,
                                RegisterListView(HistorySearching.this, c2nMap)));
                        Toast.makeText(HistorySearching.this,
                                "你已经成功删除", Toast.LENGTH_LONG).show();
                    }

                    @Override
                    public void onCancelClick() {
                        //取消操作
                    }
                });
                confirmDialog.show(getFragmentManager(), "");
                Log.e("dialog", getFragmentManager().toString());
            }
        });

        //设置列表项Item点击按钮的点击监听事件
        slideListView.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> adapterView, View view, int i, long l) {
                Intent iDisplayResult = new Intent(HistorySearching.this, DisplayResult.class);

                Bundle mBundle = new Bundle();
                mBundle.putString("ShipperCode", HistoryMap.get((int) l).get("ShipperCode"));
                mBundle.putString("ShipperName", HistoryMap.get((int) l).get("ShipperName"));
                mBundle.putString("LogisticCode", HistoryMap.get((int) l).get("LogisticCode"));
                iDisplayResult.putExtras(mBundle);
                startActivity(iDisplayResult);
            }
        });
    }

    @Override
    public boolean onTouchEvent(MotionEvent event) {
        Log.e("ListView", "MainActivity-onTouchEvent --> " + event.getAction());
        return super.onTouchEvent(event);
    }

    @Override
    public boolean dispatchTouchEvent(MotionEvent ev) {
        Log.e("ListView", "MainActivity-dispatchTouchEvent --> " + ev.getAction());
        return super.dispatchTouchEvent(ev);
    }
}
