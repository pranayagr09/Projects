package in.ac.iitb.nilesh.feeder11;

import android.content.Context;
import android.content.SharedPreferences;
import android.graphics.Color;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.TextView;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.DataOutputStream;
import java.io.IOException;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.ArrayList;

public class form extends AppCompatActivity {

    ArrayList<TextView> myview = new ArrayList<>();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        SharedPreferences sh = getSharedPreferences("main", Context.MODE_PRIVATE);
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_form);
        LinearLayout llayout = (LinearLayout) findViewById(R.id.llayout);
        Bundle bundle = getIntent().getExtras();
        System.out.println("bundle = " + bundle.getString("code"));
        String x = sh.getString("result", "");
        JSONObject userdata = null;
        int indexi = 0, indexj = 0;
        try {
            userdata = new JSONObject(x);
            for (int i = 0; i < userdata.getJSONArray("courses").length(); ++i) {
                for (int j = 0; j < userdata.getJSONArray("courses").getJSONObject(i).getJSONArray("feedback_forms").length(); ++j) {
                    String coursecode = userdata.getJSONArray("courses").getJSONObject(i).getString("course_code");
                    String feedbackname = userdata.getJSONArray("courses").getJSONObject(i).getJSONArray("feedback_forms").getJSONObject(j).getString("feedback_name");
                    if (x.contains(coursecode) && x.contains(feedbackname)) {
                        indexi = i;
                        indexj = j;
                    }
                }
            }
            for (int i = 0; i < userdata.getJSONArray("courses").getJSONObject(indexi).getJSONArray("feedback_forms").getJSONObject(indexj).getJSONArray("feedback_questions").length(); ++i) {
                final EditText rowTextView = new EditText(getApplicationContext());
                rowTextView.setTextColor(Color.BLACK);
                llayout.addView(rowTextView);
                rowTextView.setText(userdata.getJSONArray("courses").getJSONObject(indexi).getJSONArray("feedback_forms").getJSONObject(indexj).getJSONArray("feedback_questions").getJSONObject(i).getString("question_name"));
                myview.add(rowTextView);
            }
        } catch (JSONException e) {
            e.printStackTrace();
        }
        Button submitB = (Button) findViewById(R.id.submit);
        ArrayList<String> ans = new ArrayList<>();
        for (int i = 0; i < myview.size(); ++i) {
            ans.add(myview.get(i).getText().toString());
        }
        JSONObject json = new JSONObject();
        try {
            json.put("course_code", userdata.getJSONArray("courses").getJSONObject(indexi).getString("course_code"));
            json.put("feed_name", userdata.getJSONArray("courses").getJSONObject(indexi).getJSONArray("feedback_forms").getJSONObject(indexj).getString("feedback_name"));
            JSONObject jans = new JSONObject();
            for (int i = 0; i < ans.size(); ++i) {
                jans.put("answer" + i, ans.get(i));
            }
            json.put("ans", jans);
        } catch (JSONException e) {
            e.printStackTrace();
        }

        final JSONObject fjson = json;
        System.out.println("fjson = " + fjson);

        submitB.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                String http = "http://192.168.0.114:8011/Feeder11/submit_feed/";
                try {
                    // Simulate network access.
                    HttpURLConnection urlConnection = null;
                    try {
                        URL url = new URL(http);
                        urlConnection = (HttpURLConnection) url.openConnection();
                        urlConnection.setDoOutput(true);
                        urlConnection.setRequestMethod("POST");
                        urlConnection.setUseCaches(false);
                        urlConnection.setRequestProperty("Content-Type", "application/json;charset=utf-8");

                        //Create JSONObject here
                        JSONObject j = new JSONObject();
                        j.put("ele", "");
                        DataOutputStream printout = new DataOutputStream(urlConnection.getOutputStream());
                        printout.writeBytes(fjson.toString());

                        printout.flush();
                        printout.close();

                        int HttpResult = urlConnection.getResponseCode();
                        if (HttpResult == HttpURLConnection.HTTP_OK) {

                        } else {
                            System.out.println(urlConnection.getResponseMessage());
                        }
                    } catch (IOException e) {
                        e.printStackTrace();
                    } catch (JSONException e) {
                        e.printStackTrace();
                    } finally {
                        if (urlConnection != null)
                            urlConnection.disconnect();
                    }
                    Thread.sleep(2000);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        });

    }
}
