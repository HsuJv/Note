package com.njupt.a4081.expresstracking;

import android.app.DialogFragment;
import android.graphics.Color;
import android.graphics.drawable.ColorDrawable;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.view.Window;
import android.widget.Button;

/**
 * Created by Administrator on 2017/11/4.
 */

public class ConfirmDialog extends DialogFragment {
    private View mView;
    private onDialogClickListener myListener;


    //初始化对话框
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState){
        getDialog().requestWindowFeature(Window.FEATURE_NO_TITLE);
        mView = inflater.inflate(R.layout.confirm_dialog,container);
        getDialog().getWindow().setBackgroundDrawable(new ColorDrawable(Color.WHITE));
        initView();
        return mView;
    }

    //绑定按钮
    private void initView() {
        Button confirm_btn = mView.findViewById(R.id.confirm_dialog_button_confirm);
        Button cancel_btn = mView.findViewById(R.id.confirm_dialog_button_cancel);

        confirm_btn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(myListener!=null){
                    myListener.onConfirmClick();
                }
                dismiss();
            }
        });
        cancel_btn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(myListener!=null){
                    myListener.onCancelClick();
                }
                dismiss();
            }
        });

    }

    public interface onDialogClickListener{
        void onConfirmClick();
        void onCancelClick();
    }
    public void setDialogClickListener(onDialogClickListener myListener){
        this.myListener = myListener;
    }
}
