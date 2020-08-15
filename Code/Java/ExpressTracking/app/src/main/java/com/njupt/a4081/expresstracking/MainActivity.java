package com.njupt.a4081.expresstracking;

import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.Button;
import android.widget.ImageButton;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        ImageButton NewSearching = (ImageButton)findViewById(R.id.main_new_searching);
        ImageButton HistorySearching = (ImageButton)findViewById(R.id.main_history_searching);

        NewSearching.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent iNewSearching = new Intent(MainActivity.this, NewSearchActivity.class);
                startActivity(iNewSearching);
            }
        });

        HistorySearching.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent iHistorySearching = new Intent(MainActivity.this, HistorySearching.class);
                startActivity(iHistorySearching);
            }
        });

    }
}
