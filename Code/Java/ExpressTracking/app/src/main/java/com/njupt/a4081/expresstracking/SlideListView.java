package com.njupt.a4081.expresstracking;

import android.content.Context;
import android.util.AttributeSet;
import android.util.Log;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewConfiguration;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.ListView;
import android.widget.PopupWindow;

/**
 * Created by aasus on 2017/11/9.
 */

public class SlideListView extends ListView {
    private static final String TAG = "SlideListView";

    private LayoutInflater mlayoutInflater = null;
    /**
     * 用户滑动的最小距离
     */
    private int touchSlop;
    /**
     * 是否响应滑动
     */
    private boolean isSliding;
    /**
     * 手指按下时的x坐标
     */
    private int xDown;
    /**
     * 手指按下时的y坐标
     */
    private int yDown;
    /**
     * 手指移动时的x坐标
     */
    private int xMove;
    /**
     * 手指移动时的y坐标
     */
    private int yMove;

    /**
     * 当前手指触摸的View
     */
    private View mCurrentView;
    /**
     * 当前手指触摸的位置
     */
    private int mCurrentViewPos;

    private DelButtonClickListener mDelListener = null;
    private DisplayButtonClickListener mDisplayListener = null;

    private PopupWindow mPopupWindow = null;
    private Button mDelBtn = null, mDispalyBtn = null;

    private int mPopupWindowWidth, mPopupWindowHeight;

    /**
     * 自定义ListView的构造方法 在里面做一些必要的一些初始化
     *
     * @param context
     * @param attrs
     */
    public SlideListView(Context context, AttributeSet attrs) {
        super(context, attrs);

        mlayoutInflater = LayoutInflater.from(context);
        //用户手指移动的最小距离，用来判断是否响应触发移动事件
        touchSlop = ViewConfiguration.get(context).getScaledTouchSlop();

        View view = mlayoutInflater.inflate(R.layout.slide_layout, null);
        //删除按钮
        mDelBtn = view.findViewById(R.id.slide_item_delete_btn);
        //取消按钮
        mDispalyBtn = view.findViewById(R.id.slide_item_display_btn);
        mPopupWindow = new PopupWindow(view,
                LinearLayout.LayoutParams.WRAP_CONTENT,
                LinearLayout.LayoutParams.WRAP_CONTENT);

        /**
         * 先调用下measure,否则拿不到宽和高
         */
        mPopupWindow.getContentView().measure(0, 0);
        mPopupWindowHeight = mPopupWindow.getContentView().getMeasuredHeight();
        mPopupWindowWidth = mPopupWindow.getContentView().getMeasuredWidth();

    }

    @Override
    public boolean dispatchTouchEvent(MotionEvent ev) {
        Log.e("ListView", "Child-dispatchTouchEvent --> " + ev.getAction());
        int action = ev.getAction();
        int x = (int) ev.getX();
        int y = (int) ev.getY();

        switch (action) {
            case MotionEvent.ACTION_DOWN:
                //手指按下时水平方向x的位置
                xDown = x;
                //手指按下时垂直方向y的位置
                yDown = y;
                /*
                * 如果当前popupWindow显示，则直接隐藏，然后屏蔽ListView的Touch事件的下传
                * */
                if (mPopupWindow.isShowing()) {
                    dismissPopWindow();
                    return false;
                }
                // 获得当前手指按下时的item的位置
                mCurrentViewPos = pointToPosition(xDown, yDown);
                // 获得当前手指按下时的ListView的item项
                mCurrentView = getChildAt(mCurrentViewPos - getFirstVisiblePosition());
                break;
            case MotionEvent.ACTION_MOVE:
                //手指移动时x的位置
                xMove = x;
                //手指移动时y的位置
                yMove = y;
                //水平滑动的距离（可能为负值）
                int dx = xMove - xDown;
                //垂直滑动的距离（可能为负值）
                int dy = yMove - yDown;
                /*
                * 判断是否是从右到左的滑动
                * */
                if (xMove < xDown && Math.abs(dx) > touchSlop && Math.abs(dy) < touchSlop) {
                    Log.e(TAG, "touchslop = " + touchSlop + " , dx = " + dx + " , dy = " + dy);
                    isSliding = true;
                }
                break;
        }

        return super.dispatchTouchEvent(ev);
    }

    @Override
    public boolean onInterceptTouchEvent(MotionEvent ev) {
        Log.e("ListView", "Child-onInterceptTouchEvent --> " + ev.getAction());
        return super.onInterceptTouchEvent(ev);
    }

    @Override
    public boolean onTouchEvent(MotionEvent ev) {
        Log.e("ListView", "Child-onTouchEvent --> " + ev.getAction());
        int action = ev.getAction();
        /*
        * 如果是从右到左的滑动才响应，之前已在 dispatchTouchEvent 中获得了是否是从右向左滑动
        * */
        if (isSliding) {
            switch (action) {
                case MotionEvent.ACTION_MOVE:
                    int[] location = new int[2];
                    //获得当前item的位置x与y,如果点在item以外的地方,不消费该事件,冒泡传递到MainActivity的onTouchEvent中
                    if (mCurrentView == null) {
                        return false;
                    }
                    mCurrentView.getLocationOnScreen(location);
                    //设置PopupWindow的动画
                    mPopupWindow.setAnimationStyle(R.style.slide_list_anim);
                    mPopupWindow.update();
                    //Log.e(TAG, "width location[0]: " + location[0]);
                    //Log.e(TAG, "height location[1]: " + location[1]);
                    //Log.e(TAG, "mCurrentView.getWidth(): " + mCurrentView.getWidth());
                    //Log.e(TAG, "mCurrentView.getHeight(): " + mCurrentView.getHeight());
                    //Log.e(TAG, "mPopupWindowHeight: " + mPopupWindowHeight);
                    //设置“取消关注”、“删除”按钮PopWindow的显示位置
                    //相对于父控件的位置（例如正中央Gravity.CENTER，下方Gravity.BOTTOM等），可以设置偏移或无偏移
                    //相对某个控件的位置，有偏移;xoff表示x轴的偏移，正值表示向左，负值表示向右；yoff表示相对y轴的偏移，正值是向下，负值是向上；
                    mPopupWindow.showAtLocation(mCurrentView,
                            Gravity.LEFT | Gravity.TOP,
                            location[0] + mCurrentView.getWidth(),
                            location[1] + mCurrentView.getHeight() / 2 - mPopupWindowHeight / 2);

                    String PopupX = String.valueOf(location[0] + mCurrentView.getWidth());
                    String PopupY = String.valueOf(location[1] + mCurrentView.getHeight() / 2 - mPopupWindowHeight / 2);
                    //Log.e(TAG, "location[0] + mCurrentView.getWidth: " + PopupX);
                    //Log.e(TAG, "location[1] + mCurrentView.getHeight() / 2 - mPopupWindowHeight / 2: " + PopupY);
                    //Log.e(TAG, "location[1]: " + location[1]);

                    //设置删除按钮的回调
                    mDelBtn.setOnClickListener(new OnClickListener() {
                        @Override
                        public void onClick(View v) {
                            //通过接口对象调用当前Item上删除按钮的点击方法
                            mDelListener.onDeleteClick(mCurrentViewPos);
                            mPopupWindow.dismiss();
                        }
                    });
                    //设置显示按钮的回调
                    mDispalyBtn.setOnClickListener(new OnClickListener() {
                        @Override
                        public void onClick(View v) {
                            //通过接口对象调用当前Item上取消按钮的点击方法
                            mDisplayListener.onDisplayClick(mCurrentViewPos);
                            mPopupWindow.dismiss();
                        }
                    });
                    break;
                case MotionEvent.ACTION_UP:
                    //设置侧滑关闭
                    isSliding = false;
                    break;
            }
            // 相应滑动期间屏蔽itemClick事件，避免发生冲突
            return true;
        }
        return super.onTouchEvent(ev);
    }

    /**
     * 隐藏popupWindow
     */
    private void dismissPopWindow() {
        if (mPopupWindow != null && mPopupWindow.isShowing()) {
            mPopupWindow.dismiss();
        }
    }

    /**
     * 设置删除按钮点击事件监听
     *
     * @param listener DelButtonClickListener 删除按钮监听接口对象
     */
    public void setDeleteButtonClickListener(DelButtonClickListener listener) {
        mDelListener = listener;
    }

    /**
     * 设置显示按钮点击事件监听
     *
     * @param listener CancelButtonClickListener 按钮点击事件监听接口对象
     */
    public void setDisplayButtonClickListener(DisplayButtonClickListener listener) {
        mDisplayListener = listener;
    }

    /**
     * 删除按钮监听接口
     */
    interface DelButtonClickListener {
        void onDeleteClick(int position);
    }

    /**
     * 显示按钮监听接口
     */
    interface DisplayButtonClickListener {
        void onDisplayClick(int position);
    }
}


