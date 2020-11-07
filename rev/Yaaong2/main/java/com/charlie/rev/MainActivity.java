package com.charlie.rev;

import androidx.appcompat.app.AppCompatActivity;

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;


import com.bumptech.glide.Glide;

public class MainActivity extends AppCompatActivity {

    static {
        System.loadLibrary("Prob");
    }

    public native boolean CheckString(String str);

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        final EditText t = findViewById(R.id.editText);
        t.setHint("INPUT FLAG");

        final String[] alert_msg = new String[1];
        //imgView.setImageResource(R.drawable.cat);

        final AlertDialog dig = new AlertDialog.Builder(MainActivity.this).create();

        LayoutInflater factory = LayoutInflater.from(MainActivity.this);
        final View customView = factory.inflate(R.layout.custom_dialog, null);

        final ImageView imgView = customView.findViewById(R.id.imageView3);

        Button btn = findViewById(R.id.button);
        btn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if (CheckString(t.getText().toString())){
                    dig.setTitle("SUCCESS");
                    Glide.with(MainActivity.this)
                            .load(R.raw.cat)
                            .into(imgView);
                }
                else {
                    dig.setTitle("FAIL");
                    Glide.with(MainActivity.this)
                            .load(R.raw.codingcat)
                            .into(imgView);
                }
                dig.setView(customView);
                dig.setButton(DialogInterface.BUTTON_POSITIVE, "OK", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialogInterface, int i) {
                        return;
                    }
                });
                dig.show();
            }
        });
    }

}
