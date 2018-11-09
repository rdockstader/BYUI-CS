package rdockstader.com.teach06;

import android.content.Context;
import android.os.AsyncTask;
import android.util.Log;
import android.view.View;
import android.widget.ProgressBar;
import android.widget.Toast;

import java.io.File;
import java.io.FileOutputStream;

public class CreateListAsync extends AsyncTask<Void, Integer, Void> {
    private static final String TAG = "CREATE_LIST_ASYNC";
    private Context context;
    private ProgressBar pb;

    public CreateListAsync(Context c, ProgressBar bar) {
        context = c;
        pb = bar;
        pb.setVisibility(View.VISIBLE);
    }


    @Override
    protected Void doInBackground(Void... voids) {

        try {
            Log.d(TAG, "Staring file write");
            FileOutputStream outputStream = context.openFileOutput(MainActivity.fileName, Context.MODE_PRIVATE);
            for(Integer i = 1; i <= 10; i++) {
                outputStream.write(i.toString().getBytes());
                outputStream.write('\n');
                Thread.sleep(250);
                publishProgress(i);
            }
            outputStream.close();
            Log.d(TAG, "File Stream closed");
        } catch (Exception e) {
            e.printStackTrace();
        }

        return null;
    }


    @Override
    protected void onProgressUpdate(Integer... values) {
        super.onProgressUpdate(values);
        if(pb != null) pb.incrementProgressBy(10);
        Log.d(TAG, "Progres updated");
    }

    @Override
    protected void onPostExecute(Void aVoid) {
        super.onPostExecute(aVoid);
        Toast.makeText(context, "Write Complete", Toast.LENGTH_SHORT).show();
        pb.setVisibility(View.INVISIBLE);
    }
}
