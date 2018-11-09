package rdockstader.com.teach06;

import android.content.Context;
import android.os.Environment;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.ProgressBar;
import android.widget.Toast;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.List;

public class MainActivity extends AppCompatActivity {
    public static final String fileName = "numbers.txt";
    private Integer progressStatus = 0;
    private List<Integer> nums;
    private ArrayAdapter<Integer> numsAA;
    ProgressBar pb;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        // Get progress bar
        pb = findViewById(R.id.progBar);

        // Get list view
        ListView listView = findViewById(R.id.listView);
        nums = new ArrayList<>();
        numsAA = new ArrayAdapter<>(this, R.layout.nums_list, nums);
        listView.setAdapter(numsAA);
    }

    public void onCreateClick(View v) {

        pb.setProgress(0);
        CreateListAsync cla = new CreateListAsync(getApplicationContext(), pb);
        cla.execute();
    }

    public void onLoadClick(View v) {
        pb.setProgress(0);
        numsAA.clear();
        LoadListAsync lla = new LoadListAsync(getApplicationContext(), pb, numsAA);
        lla.execute();
    }
}
