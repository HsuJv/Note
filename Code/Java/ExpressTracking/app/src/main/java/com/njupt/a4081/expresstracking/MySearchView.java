package com.njupt.a4081.expresstracking;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.text.Editable;
import android.text.TextWatcher;
import android.util.AttributeSet;
import android.util.Log;
import android.view.KeyEvent;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.view.inputmethod.EditorInfo;
import android.view.inputmethod.InputMethodManager;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.Iterator;


/**
 * Created by Hsu on 2017/11/4.
 */

public class MySearchView extends LinearLayout implements View.OnClickListener {

    /**
     * 输入框
     */
    private EditText etInput;

    /**
     * 删除键
     */
    private ImageView ivDelete;

    /**
     * 搜索键
     */
    private Button btnSearch;

    /**
     * 返回按钮
     */
    private Button btnBack;

    /**
     * 上下文对象
     */
    private Context mContext;

    /**
     * 弹出列表
     */
    private ListView lvTips;


    /**
     * 自动补全adapter 只显示名字
     */
    private ArrayAdapter<String> mAutoCompleteAdapter;

    /**
     * 搜索回调接口
     */
    private SearchViewListener mListener;

    /**
     * 设置搜索回调接口
     *
     * @param listener 监听者
     */
    public void setSearchViewListener(SearchViewListener listener) {
        mListener = listener;
    }

    public MySearchView(Context context, AttributeSet attrs) {
        super(context, attrs);
        mContext = context;
        LayoutInflater.from(context).inflate(R.layout.sample_my_search_view, this);
        initViews();
    }

    private void initViews() {
        etInput = findViewById(R.id.search_et_input);
        ivDelete = findViewById(R.id.search_iv_delete);
        btnSearch = findViewById(R.id.new_search_search_btn);
        btnBack = findViewById(R.id.search_btn_back);
        lvTips = findViewById(R.id.search_lv_tips);

        lvTips.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> adapterView, View view, int i, long l) {
                // set edit text
                String text = lvTips.getAdapter().getItem(i).toString();
                etInput.setText(text);
                // set the selected to first
                etInput.setSelection(text.length());
                // hint list view gone and result list view show
                lvTips.setVisibility(View.GONE);
                notifyStartSearching();
            }
        });

        ivDelete.setOnClickListener(this);
        btnBack.setOnClickListener(this);
        btnSearch.setOnClickListener(this);

        etInput.addTextChangedListener(new EditChangedListener());
        etInput.setOnClickListener(this);

        // enter "Enter"
        etInput.setOnEditorActionListener(new TextView.OnEditorActionListener() {
            @Override
            public boolean onEditorAction(TextView textView, int actionId, KeyEvent keyEvent) {
                if (actionId == EditorInfo.IME_ACTION_SEARCH) {
                    lvTips.setVisibility(GONE);
                    notifyStartSearching();
                }
                return true;
            }
        });
    }

    /**
     * 通知监听者 进行搜索操作
     *
     */
    private void notifyStartSearching() {

        // 隐藏软键盘
        InputMethodManager imm = (InputMethodManager) mContext.getSystemService(Context.INPUT_METHOD_SERVICE);
        imm.toggleSoftInput(0, InputMethodManager.HIDE_NOT_ALWAYS);

        this.onClick(findViewById(R.id.new_search_search_btn));
    }


    /**
     * 设置自动补全adapter
     */
    public void setAutoCompleteAdapter(ArrayAdapter<String> adapter) {
        this.mAutoCompleteAdapter = adapter;
    }

    private class EditChangedListener implements TextWatcher {
        @Override
        public void beforeTextChanged(CharSequence charSequence, int i, int i2, int i3) {

        }

        @Override
        public void onTextChanged(CharSequence charSequence, int i, int i2, int i3) {
            if (!"".equals(charSequence.toString())) {
                ivDelete.setVisibility(VISIBLE);
                lvTips.setVisibility(VISIBLE);
                if (mAutoCompleteAdapter != null && lvTips.getAdapter() != mAutoCompleteAdapter) {
                    lvTips.setAdapter(mAutoCompleteAdapter);
                }
                //更新autoComplete数据
                if (mListener != null) {
                    mListener.onRefreshAutoComplete(charSequence + "");
                }
            } else {
                lvTips.setVisibility(GONE);
            }
        }

        @Override
        public void afterTextChanged(Editable editable) {
        }
    }

    @Override
    public void onClick(View view) {
        switch (view.getId()) {
            /*case R.id.search_et_input:
                lvTips.setVisibility(VISIBLE);
                break;*/
            case R.id.search_iv_delete:
                etInput.setText("");
                // 隐藏软键盘
                InputMethodManager imm = (InputMethodManager) mContext.getSystemService(Context.INPUT_METHOD_SERVICE);
                imm.toggleSoftInput(0, InputMethodManager.HIDE_NOT_ALWAYS);

                // 隐藏删除按钮
                ivDelete.setVisibility(GONE);
                break;
            case R.id.search_btn_back:
                ((Activity) mContext).finish();
                break;
            case R.id.new_search_search_btn:
                final LinearLayout search_layout = this.findViewById(R.id.new_search_linearLayout);
                final LinearLayout.LayoutParams layoutParams =
                        new LinearLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT);
                final EditText editText = this.findViewById(R.id.search_et_input);


                final Handler handler = new Handler() {
                    public void handleMessage(Message msg) {
                        super.handleMessage(msg);
                        /*TextView textView = new TextView(mContext);
                        search_layout.addView(textView, layoutParams);
                        textView.setText("客官，您输入的单号不存在哟~");*/
                        Toast.makeText(mContext, "您输入的单号不存在~", Toast.LENGTH_SHORT).show();
                    }
                };
                new Thread(new Runnable() {
                    @Override
                    public void run() {
                        // 获取查询
                        String expNo = editText.getText().toString();
                        Log.e("eT", expNo);
                        OrderDistinguish api = new OrderDistinguish();
                        try {
                            String result = api.getOrderTracesByJson(expNo);

                            // 获取companyCode和companyName
                            try {
                                JSONObject jso = new JSONObject(result);
                                Iterator it = jso.keys();
                                Bundle bd = new Bundle();

                                while (it.hasNext()) {
                                    String key = (String) it.next();
                                    Object value = jso.get(key);
                                    if (key.equalsIgnoreCase("Success")) {
                                        if (value.toString().equalsIgnoreCase("false")) {
                                            if (search_layout.getChildCount() == 0) {
                                                // Print error log
                                                Message msg = new Message();
                                                bd.putString("Success", "false");
                                                msg.setData(bd);
                                                handler.sendMessage(msg);
                                            }
                                            break;
                                        }
                                    } else if (key.equalsIgnoreCase("LogisticCode")) {
                                        bd.putString(key, value.toString());
                                    } else if (key.equalsIgnoreCase("Shippers")) {
                                        try {
                                            Intent iDisplay = new Intent(mContext, DisplayResult
                                                    .class);

                                            JSONArray jsonArray = jso.getJSONArray("Shippers");
                                            //单号不存在但Success=true
                                            if (jsonArray.length() == 0) {
                                                if (search_layout.getChildCount() == 0) {
                                                    Message msg = new Message();
                                                    bd.putString("Success", "false");
                                                    msg.setData(bd);
                                                    handler.sendMessage(msg);
                                                }
                                                break;
                                            }
                                            for (int i = 0; i < jsonArray.length(); i++) {
                                                JSONObject jsonObject = jsonArray.getJSONObject(i);
                                                Iterator It = jsonObject.keys();
                                                while (It.hasNext()) {
                                                    String Key = (String) It.next();
                                                    Object Value = jsonObject.get(Key);
                                                    bd.putString(Key, Value.toString());
                                                }
                                            }
                                            iDisplay.putExtras(bd);
                                            mContext.startActivity(iDisplay);

                                            // Save into sql
                                            SearchingHistoryDataHelper dh = new
                                                    SearchingHistoryDataHelper(mContext);
                                            dh.InsertHistory(expNo, bd.getString("ShipperCode"));
                                        } catch (JSONException e) {
                                            e.printStackTrace();
                                        }
                                        break;
                                    }
                                }
                            } catch (JSONException e) {
                                Log.e("JSON2Re", e.toString());
                            }

                        } catch (Exception e) {
                            Log.e("search api", e.toString());
                        }
                    }
                }).start();
                break;
        }
    }

    /**
     * search view回调方法
     */
    public interface SearchViewListener {

        /**
         * 更新自动补全内容
         *
         * @param text 传入补全后的文本
         */
        void onRefreshAutoComplete(String text);
    }

}