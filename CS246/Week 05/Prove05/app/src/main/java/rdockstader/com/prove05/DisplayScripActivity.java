package rdockstader.com.prove05;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;

public class DisplayScripActivity extends AppCompatActivity {
    private static final String TAG = "DisplayScriptActivity";
    private Scripture scripture;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_display_scrip);

        Intent intent = getIntent();
        Log.d(this.TAG, "Display being created");
        if(intent.getStringExtra(MainActivity.LOAD_MESSAGE) != null) {
            Log.d(this.TAG, "Reading saved scripture");
            loadScripture();
        } else {
            Log.d(this.TAG, "Displaying new scripture");
            this.scripture = intent.getParcelableExtra(MainActivity.EXTRA_MESSAGE);
        }



        TextView textView = findViewById(R.id.textView);
        textView.setText(scripture.toString());
    }

    public void saveScipture(View view) {
        Log.d(this.TAG, "Saving Scripture");
        SharedPreferences sharedPref = this.getPreferences(Context.MODE_PRIVATE);
        SharedPreferences.Editor editor = sharedPref.edit();
        editor.putString(getString(R.string.saved_book),  this.scripture.getBook());
        editor.putString(getString(R.string.saved_chap),  this.scripture.getChapter());
        editor.putString(getString(R.string.saved_verse),  this.scripture.getVerse());
        editor.commit();

        Toast.makeText(this, "Scripture Saved!", Toast.LENGTH_SHORT).show();
    }

    private void loadScripture() {
        Log.d(TAG,"Loading Saved Scripture ");
        SharedPreferences sharedPref = this.getPreferences(Context.MODE_PRIVATE);
        Scripture scripture = new Scripture(sharedPref.getString(getString(R.string.saved_book), "ERROR"),
                sharedPref.getString(getString(R.string.saved_chap), "-1"),
                sharedPref.getString(getString(R.string.saved_verse), "-1"));

        this.scripture = scripture;
    }
}
