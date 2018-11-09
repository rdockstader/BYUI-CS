package rdockstader.com.teach06;

import android.content.Context;
import android.os.AsyncTask;
import android.util.Log;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.ProgressBar;
import android.widget.Toast;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.List;

public class LoadListAsync extends AsyncTask<Void, Integer, Void> {
    private static final String TAG = "LOAD_LIST_ASYNC";
    private Context context;
    private ProgressBar pb;
    private String output;
    private ArrayAdapter<Integer> aa;

    public LoadListAsync(Context c, ProgressBar bar, ArrayAdapter<Integer> intAA) {
        context = c;
        pb = bar;
        pb.setVisibility(View.VISIBLE);
        aa = intAA;
    }

    @Override
    protected Void doInBackground(Void... voids) {
        File file = new File(context.getFilesDir(), MainActivity.fileName);
        List<Integer> numberList = new ArrayList<>();
        try {
            BufferedReader bufferedReader = new BufferedReader(new FileReader(file));
            String line;
            output = new String();
            while((line = bufferedReader.readLine()) != null) {
                //Log.d(TAG, "loaded new line");
                Integer i = Integer.parseInt(line);
                output += line + ", ";
                numberList.add(i);
                Thread.sleep(250);
                publishProgress(i);
            }
            output = output.substring(0, output.length() - 2);
            output += " Loaded Successfully!";

        } catch (Exception e) {
            e.printStackTrace();
        }

        return null;
    }

    @Override
    protected void onPostExecute(Void aVoid) {
        super.onPostExecute(aVoid);
        Toast toast = Toast.makeText(context, output, Toast.LENGTH_SHORT);
        toast.show();
    }

    @Override
    protected void onProgressUpdate(Integer... values) {
        super.onProgressUpdate(values);
        if(pb != null) pb.incrementProgressBy(10);
        aa.add(values[0]);
        Log.d(TAG, "Progres updated");
    }
}
