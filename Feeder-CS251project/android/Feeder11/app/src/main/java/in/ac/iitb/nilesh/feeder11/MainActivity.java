package in.ac.iitb.nilesh.feeder11;

import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.text.style.LineBackgroundSpan;
import android.view.View;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.TextView;

import com.prolificinteractive.materialcalendarview.CalendarDay;
import com.prolificinteractive.materialcalendarview.DayViewDecorator;
import com.prolificinteractive.materialcalendarview.DayViewFacade;
import com.prolificinteractive.materialcalendarview.MaterialCalendarView;
import com.prolificinteractive.materialcalendarview.OnDateSelectedListener;

import org.json.JSONException;
import org.json.JSONObject;

import java.util.ArrayList;
import java.util.Collection;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;

public class MainActivity extends AppCompatActivity {

    @Override
    public void onBackPressed(){
        Intent a = new Intent(Intent.ACTION_MAIN);
        a.addCategory(Intent.CATEGORY_HOME);
        a.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
        startActivity(a);
    }
    ArrayList<CalendarDay> markedRed = new  ArrayList<CalendarDay>();
    Map<CalendarDay, ArrayList<String> > assignments = new HashMap<>();
    Map<CalendarDay, ArrayList<String> > feedbacks = new HashMap<>();
    ArrayList<CalendarDay> markedGray = new  ArrayList<CalendarDay>();
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        SharedPreferences sh = getSharedPreferences("main", Context.MODE_PRIVATE);
        boolean logged = sh.getBoolean("auth",false);
        if(!logged){

            Intent intent = new Intent(this, login.class);
            startActivity(intent);
        }
        System.out.println("logged = "+logged);
        JSONObject userdata = null;
        try {
            String x = sh.getString("result", "");
            userdata = new JSONObject(x);
            System.out.println("x = "+x);
            for(int i = 0; i < userdata.getJSONArray("courses").length(); ++i)
            {
                for(int j = 0; j < userdata.getJSONArray("courses").getJSONObject(i).getJSONArray("assignment_deadline").length(); ++j)
                {
                    String mydate = userdata.getJSONArray("courses").getJSONObject(i).getJSONArray("assignment_deadline").getJSONObject(j).getString("deadline_datetime");
                    String yyyy = mydate.substring(0, 4);
                    String mm = mydate.substring(5, 7);
                    String dd = mydate.substring(8, 10);
                    CalendarDay c = CalendarDay.from(Integer.valueOf(yyyy), Integer.valueOf(mm)-1, Integer.valueOf(dd));
                    markedRed.add(c);
                    ArrayList<String> s = assignments.get(c);
                    if(s == null)
                    {
                        s = new ArrayList<>();
                    }
                    s.add(userdata.getJSONArray("courses").getJSONObject(i).getString("course_code")+" "+userdata.getJSONArray("courses").getJSONObject(i).getJSONArray("assignment_deadline").getJSONObject(j).getString("deadline_name")+" "+userdata.getJSONArray("courses").getJSONObject(i).getJSONArray("assignment_deadline").getJSONObject(j).getString("deadline_datetime"));

                    assignments.put(c, s);
                }
            }
            //System.out.println("for 0 : "+userdata.getJSONArray("courses").getJSONObject(0));//.getJSONArray("feedback_forms"));
            for(int i = 0; i < userdata.getJSONArray("courses").length(); ++i)
            {
                for(int j = 0; j < userdata.getJSONArray("courses").getJSONObject(i).getJSONArray("feedback_forms").length(); ++j)
                {
                    String mydate = userdata.getJSONArray("courses").getJSONObject(i).getJSONArray("feedback_forms").getJSONObject(j).getString("feedback_deadline_datetime");
                    String yyyy = mydate.substring(0, 4);
                    String mm = mydate.substring(5, 7);
                    String dd = mydate.substring(8, 10);
                    System.out.println("gray : "+mydate);
                    CalendarDay c = CalendarDay.from(Integer.valueOf(yyyy), Integer.valueOf(mm)-1, Integer.valueOf(dd));
                    markedGray.add(c);
                    ArrayList<String> s = feedbacks.get(c);
                    if(s == null)
                    {
                        s = new ArrayList<>();
                    }
                    s.add(userdata.getJSONArray("courses").getJSONObject(i).getString("course_code")+" "+userdata.getJSONArray("courses").getJSONObject(i).getJSONArray("feedback_forms").getJSONObject(j).getString("feedback_name")+" "+userdata.getJSONArray("courses").getJSONObject(i).getJSONArray("feedback_forms").getJSONObject(j).getString("feedback_deadline_datetime"));
                    feedbacks.put(c, s);
                }
            }
        } catch (JSONException e) {
            System.out.println("exception");
            e.printStackTrace();
        }

        System.out.println("userdata = "+userdata);
        System.out.println("result = "+sh.getString("result", ""));

        setContentView(R.layout.activity_main);
        MaterialCalendarView cal = (MaterialCalendarView) findViewById(R.id.calendarView);
        cal.setOnDateChangedListener(new myCalendar());
        cal.addDecorator(
                new EventDecorator(Color.RED, markedRed)
        );
        CalendarDay c = CalendarDay.from(2016, 11, 9);
//        marked.add(c);
        cal.addDecorator(
                new EventDecorator(Color.DKGRAY, markedGray)
        );
        cal.setTileHeight(100);
//        TextView intro = (TextView) findViewById(R.id.intro) ;
        Button logoutB  = (Button) findViewById(R.id.logout);
        //intro.setText(sh.getString("username", "")+" IS LOGGED IN");
        logoutB.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                SharedPreferences sharedPreferences = getSharedPreferences("main", Context.MODE_PRIVATE);
                SharedPreferences.Editor editor = sharedPreferences.edit();
                editor.putString("username", "");
                editor.putBoolean("auth", false);
                editor.commit();

                Intent i = new Intent(getApplicationContext(), login.class);
                startActivity(i);
            }
        });
    }
    //ArrayList<TextView> myview = new ArrayList<>();
    public class myCalendar implements OnDateSelectedListener {
        @Override
        public void onDateSelected(MaterialCalendarView widget, final CalendarDay date, boolean selected) {
            TextView text = (TextView) findViewById(R.id.deadlines);
            text.setText("");

            LinearLayout myLinearLayout = (LinearLayout)findViewById(R.id.llayout);

            myLinearLayout.removeAllViewsInLayout();

            if (markedRed.contains(date)) {
                final TextView rwTextView = new TextView(getApplicationContext());
                rwTextView.setTextColor(Color.BLACK);
                rwTextView.setText("\nASSIGNMENT DEADLINES");
                //myview.add(rwTextView);
                widget.setTileHeight(70);
                for(int i = 0; i < assignments.get(date).size(); ++i) {
                    final TextView rowTextView = new TextView(getApplicationContext());
                    rowTextView.setTextColor(Color.BLACK);
                    rowTextView.setText(assignments.get(date).get(i));
                    //myview.add(rowTextView);
                    myLinearLayout.addView(rowTextView);
                }
            }
            if (markedGray.contains(date)) {
                widget.setTileHeight(70);
                final TextView rwTextView = new TextView(getApplicationContext());
                rwTextView.setTextColor(Color.BLACK);
                rwTextView.setText("\nFEEDBACK DEADLINES");
               // myview.add(rwTextView);

                myLinearLayout.addView(rwTextView);
                //Toast.makeText(getApplicationContext(), "hello", Toast.LENGTH_SHORT).show();
                for(int i = 0; i < feedbacks.get(date).size(); ++i) {
                    final TextView rowTextView = new TextView(getApplicationContext());
                    rowTextView.setTextColor(Color.BLACK);
                    rowTextView.setText(feedbacks.get(date).get(i));
                    //myview.add(rowTextView);
                    myLinearLayout.addView(rowTextView);
                    final int j = i;
                    rowTextView.setOnClickListener(new View.OnClickListener() {
                        @Override
                        public void onClick(View v) {
                            Intent intent = new Intent(getApplicationContext(), form.class);
                            intent.putExtra("code",feedbacks.get(date).get(j));
                            startActivity(intent);
                        }
                    });
                }
            }
            if(!markedRed.contains(date) && !markedGray.contains(date)) {
                widget.setTileHeight(100);
                text.setText("");
            }
        }
    }

    public class DotSpan implements LineBackgroundSpan {

        /**
         * Default radius used
         */
        public static final float DEFAULT_RADIUS = 3;

        private final float radius;
        private final int color;

        /**
         * Create a span to draw a dot using default radius and color
         *
         * @see #DotSpan(float, int)
         * @see #DEFAULT_RADIUS
         */
        public DotSpan() {
            this.radius = DEFAULT_RADIUS;
            this.color = 0;
        }

        /**
         * Create a span to draw a dot using a specified color
         *
         * @param color color of the dot
         * @see #DotSpan(float, int)
         * @see #DEFAULT_RADIUS
         */
        public DotSpan(int color) {
            this.radius = DEFAULT_RADIUS;
            this.color = color;
        }

        /**
         * Create a span to draw a dot using a specified radius
         *
         * @param radius radius for the dot
         * @see #DotSpan(float, int)
         */
        public DotSpan(float radius) {
            this.radius = radius;
            this.color = 0;
        }

        /**
         * Create a span to draw a dot using a specified radius and color
         *
         * @param radius radius for the dot
         * @param color  color of the dot
         */
        public DotSpan(float radius, int color) {
            this.radius = radius;
            this.color = color;
        }

        @Override
        public void drawBackground(
                Canvas canvas, Paint paint,
                int left, int right, int top, int baseline, int bottom,
                CharSequence charSequence,
                int start, int end, int lineNum
        ) {
            int oldColor = paint.getColor();
            if (color != 0) {
                paint.setColor(color);
            }

            if(color == Color.RED)
                canvas.drawCircle(left + 5*radius, (bottom + top)/2, radius, paint);
            else {
                if (color == Color.DKGRAY)
                    canvas.drawCircle(right - 5*radius, (bottom + top) / 2, radius, paint);
                else
                    canvas.drawCircle((right+left)/2, bottom - radius, radius, paint);
            }
            paint.setColor(oldColor);
        }
    }

    public class EventDecorator implements DayViewDecorator {

        private int color;
        private HashSet<CalendarDay> dates;

        public EventDecorator(int color, Collection<CalendarDay> dates) {
            this.color = color;
            this.dates = new HashSet<>(dates);
        }

        @Override
        public boolean shouldDecorate(CalendarDay day) {
            return dates.contains(day);
        }

        @Override
        public void decorate(DayViewFacade view) {

            view.addSpan(new DotSpan(5, color));
        }
    }


}
