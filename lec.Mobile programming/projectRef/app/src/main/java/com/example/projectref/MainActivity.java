package com.example.projectref;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.graphics.Color;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.PopupMenu;

import java.util.ArrayList;

public class MainActivity extends AppCompatActivity {

    public ArrayList<ContentsList> list=new ArrayList<>();

    Button sort,add;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        sort=(Button)findViewById(R.id.alignment);
        add=(Button)findViewById(R.id.add);

        show();

        add.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent =new Intent(getApplicationContext(),MainActivity2.class);
                startActivity(intent);
            }
        });

        sort.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(final View view) {
                final PopupMenu popupMenu = new PopupMenu(getApplicationContext(),view);
                getMenuInflater().inflate(R.menu.popup,popupMenu.getMenu());
                popupMenu.setOnMenuItemClickListener(new PopupMenu.OnMenuItemClickListener() {
                    @Override
                    public boolean onMenuItemClick(MenuItem item) {
                        switch (item.getItemId()){
                            case R.id.sort1:
                                sort.setBackgroundColor(Color.RED);
                                break;
                            case R.id.sort2:
                                sort.setBackgroundColor(Color.BLUE);
                                break;
                            case R.id.sort3:
                                sort.setBackgroundColor(Color.GREEN);
                                break;
                            case R.id.sort4:
                                sort.setBackgroundColor(Color.BLACK);
                                break;
                        }
                        return false;
                    }
                });
                popupMenu.show();
            }
        });
    }

    void sort1(){

    }
    void sort2(){

    }
    void sort3(){

    }
    void sort4(){

    }
    void show(){

    }
}