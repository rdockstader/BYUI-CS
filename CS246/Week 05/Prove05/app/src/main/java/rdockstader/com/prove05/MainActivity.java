package rdockstader.com.prove05;

import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.EditText;

public class MainActivity extends AppCompatActivity {
    public static final String EXTRA_MESSAGE = "com.rdockstader.prove05.scripture";
    public static final String LOAD_MESSAGE = "com.rdockstader.prove05.LOAD";
    private static final String TAG = "MainActivity";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    public void submitScripture(View view) {

        Intent intent = new Intent(this, DisplayScripActivity.class);
        EditText book = (EditText) findViewById(R.id.scripBook);
        EditText chapter = (EditText) findViewById(R.id.scripChap);
        EditText verse = (EditText) findViewById(R.id.scriptVerse);
        Scripture scripture = new Scripture(book.getText().toString(), chapter.getText().toString(), verse.getText().toString());
        Log.d(TAG,"About to create intent with " + scripture.toString());
        intent.putExtra(EXTRA_MESSAGE, scripture);
        Log.d(TAG,"Scripture added, starting Activity");
        startActivity(intent);
    }

    public void loadScripture(View view) {
        Intent intent = new Intent(this, DisplayScripActivity.class);

        intent.putExtra(LOAD_MESSAGE, "load");
        Log.d(TAG,"Scripture added, starting Activity");
        startActivity(intent);

    }
}
