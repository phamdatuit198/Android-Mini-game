package jp.vfja.android.CalcMax4;

import java.util.Random;
import java.util.Timer;
import java.util.TimerTask;

import jp.vfja.android.CalcMax4.configs.Common;
import jp.vfja.android.CalcMax4.configs.Config;


import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.graphics.Typeface;
import android.graphics.drawable.Drawable;
import android.opengl.Visibility;
import android.os.AsyncTask;
import android.os.Bundle;
import android.os.Handler;
import android.os.SystemClock;
import android.preference.PreferenceManager;
import android.provider.ContactsContract.CommonDataKinds.Event;
import android.util.Log;
import android.view.Display;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.View.OnTouchListener;
import android.view.Window;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.ProgressBar;
import android.widget.RelativeLayout;
import android.widget.TextView;

public class PlayGameAct extends Activity implements OnClickListener,OnTouchListener {

	private ProgressBar mProgressBar;
	private TextView mNumOne;
	private TextView mNumTwo;
	private TextView mNumThree;
	private TextView mNumFour;

	private TextView mCalculationsOne;
	private TextView mCalculationsTwo;

	private Button mChooseGreater;
	private Button mChooseLesser;
	private Button mChooseEqual;

	private TextView mCurrentRound;
	private TextView mScore;
	private TextView mRoundAll;
	private TextView mScoreResult;
	private TextView mTitle1;
	private TextView mTitle2;
	private TextView mTitleBot1;
	private TextView mTitleBot2;
	
	private RelativeLayout rlChooseOperator;
	private RelativeLayout rlScoreResult;
	private RelativeLayout rlPlaying;
	private RelativeLayout rlTopTitle;
	private int num1;
	private int num2;
	private int num3;
	private int num4;

	private int mScoreGame;
	private int counter = 1;
	private int mProcessBarResume=0;
	private int myTime = 0;
	private int myTimeTemp = 0;
	private int mTimePeriod = 12000; //default
	private Boolean mFlgResetButtonChoose = false;
	private Boolean mFlgActionDownButton = false;
	private long mSumScore;
	private Boolean mFlgChoose = false;
	private Boolean mFlgContinue = false;
	private String mOperatorResult;
	private String mOperatorChoose;
	private Timer timer;
	private TimeAsyncTask timeAsynnTask;
	private String PLUS="+";
	private String MINUS="-";
	private String MULTIPLY="x";
	private String DIVIDE = "Ö";
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);

		// set up notitle
		requestWindowFeature(Window.FEATURE_NO_TITLE);
		getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
				WindowManager.LayoutParams.FLAG_FULLSCREEN);
		
		setContentView(R.layout.play_game);

		initData();

	//loadProcessBar();
		
	}
	/**
	 * get width height device
	 */
	public int getSizeDevice(){
		Display mDisplay = this.getWindowManager().getDefaultDisplay();
		int width = mDisplay.getWidth();
		int height = mDisplay.getHeight();
		
		return width;
	}
	/**
	 * 
	 */
	public void loadProcessBar() {

		final Handler handler = new Handler();
		timer = new Timer();
		timer.scheduleAtFixedRate(new TimerTask() {

			@Override
			public void run() {
				// TODO Auto-generated method stub
				handler.post(new Runnable() {

					@Override
					public void run() {
						// TODO Auto-generated method stub
						try {
							mCurrentRound.setText(String.valueOf(counter));
							mChooseEqual.setEnabled(true);
							mChooseGreater.setEnabled(true);
							mChooseLesser.setEnabled(true);
							if(mProcessBarResume!=0){
								mProgressBar.setProgress(mProcessBarResume);
								Log.d("DatPV---","ProcessBar"+mProgressBar.getProgress());
								mProcessBarResume = 0;
							}else
								mProgressBar.setProgress(0);
							timeAsynnTask = new TimeAsyncTask(
									PlayGameAct.this);
							timeAsynnTask.execute();
						} catch (Exception e) {
							// TODO: handle exception
							e.printStackTrace();
						}
						if (counter == Config.PERIOD_NUMBER) {
							Log.d("finish counter", " : " + counter);
							timer.cancel();

						}

					}
				});

			}
		}, 0, 12000);
	}
	
	/**
	 * 
	 */
	public void initData() {

		mProgressBar = (ProgressBar) findViewById(R.id.progressbar_Horizontal);
		mProgressBar.setProgress(0);

		mNumOne = (TextView) findViewById(R.id.tv_num_one);
		mNumTwo = (TextView) findViewById(R.id.tv_num_two);
		mNumThree = (TextView) findViewById(R.id.tv_num_three);
		mNumFour = (TextView) findViewById(R.id.tv_num_four);

		mCalculationsOne = (TextView) findViewById(R.id.tv_calculations_one);
		mCalculationsTwo = (TextView) findViewById(R.id.tv_calculations_two);

		mChooseGreater = (Button) findViewById(R.id.bt_choose_greater);
		mChooseLesser = (Button) findViewById(R.id.bt_choose_lesser);
		mChooseEqual = (Button) findViewById(R.id.bt_choose_equal);

		mCurrentRound = (TextView) findViewById(R.id.current_round);
		mScore = (TextView) findViewById(R.id.bottom_score);
		mRoundAll = (TextView) findViewById(R.id.current_round_all);
		mScoreResult = (TextView) findViewById(R.id.tv_score_result);
		mTitle1 = (TextView) findViewById(R.id.tv_title_play_1);
		mTitle2 = (TextView) findViewById(R.id.tv_title_play_2);
		mTitleBot1 = (TextView)findViewById(R.id.bottom_title);
		mTitleBot2 = (TextView)findViewById(R.id.tv_point);
		rlChooseOperator = (RelativeLayout) findViewById(R.id.rl_choose_operator);
		rlScoreResult = (RelativeLayout) findViewById(R.id.rl_score_result);
		rlPlaying = (RelativeLayout) findViewById(R.id.rl_playing);
		rlTopTitle = (RelativeLayout)findViewById(R.id.top_menu_layout);
		// setting period
		mRoundAll.setText("/" +  Config.PERIOD_NUMBER
				+ getString(R.string.play_point));

		// setting click
		
		mChooseEqual.setOnTouchListener(this);
		mChooseGreater.setOnTouchListener(this);
		mChooseLesser.setOnTouchListener(this);
		
//		mChooseEqual.setOnClickListener(this);
//		mChooseGreater.setOnClickListener(this);
//		mChooseLesser.setOnClickListener(this);
		// setting font
		Typeface type = Typeface.createFromAsset(getAssets(), "HGRPP1.TTC");
		mNumOne.setTypeface(type);
		mNumTwo.setTypeface(type);
		mNumThree.setTypeface(type);
		mNumFour.setTypeface(type);
		mCalculationsOne.setTypeface(type);
		mCalculationsTwo.setTypeface(type);
		mTitle1.setTypeface(type);
		mTitle2.setTypeface(type);
		mTitleBot1.setTypeface(type);
		mTitleBot2.setTypeface(type);
		mCurrentRound.setTypeface(type);
		mRoundAll.setTypeface(type);
		mScoreResult.setTypeface(type);
		
		//set title 
		int width = getSizeDevice();
		if(width == Config.WIDTH_DEVICE)
			rlTopTitle.setVisibility(View.VISIBLE);
		else
			rlTopTitle.setVisibility(View.INVISIBLE);
			

	}

	/**
	 * 
	 */
	public void random() {
		int[] arrayNum1 = randomNumber(mCalculationsOne);
		int[] arrayNum2 = randomNumber(mCalculationsTwo);

		num1 = arrayNum1[0];
		num2 = arrayNum1[1];
		num3 = arrayNum2[0];
		num4 = arrayNum2[1];

		mNumOne.setText(String.valueOf(arrayNum1[0]));
		mNumTwo.setText(String.valueOf(arrayNum1[1]));
		mNumThree.setText(String.valueOf(arrayNum2[0]));
		mNumFour.setText(String.valueOf(arrayNum2[1]));
	}

	/**
	 * 
	 */
	public void operation() {
		
		final int numResult1 = mathNum(mCalculationsOne, num1, num2);
		final int numResult2 = mathNum(mCalculationsTwo, num3, num4);

		if (numResult1 < numResult2)
			mOperatorResult = "<";
		else if (numResult1 > numResult2)
			mOperatorResult = ">";
		else
			mOperatorResult = "=";

		// show score

		rlScoreResult.setVisibility(View.VISIBLE);

		// sum score
		sumScoreGame();

		if (counter ==  Config.PERIOD_NUMBER) {

			SharedPreferences preferences = PreferenceManager
					.getDefaultSharedPreferences(this);
			SharedPreferences.Editor editor = preferences.edit();
			editor.putLong(Config.SCORE_SUM, mSumScore);
			editor.commit();
			Log.d("DatPV",
					"---getPreferences : "
							+ preferences.getLong(Config.SCORE_SUM, 0));

			final Handler handler = new Handler();
			Timer t = new Timer();
			t.schedule(new TimerTask() {
				public void run() {
					handler.post(new Runnable() {
						public void run() {
							goToAndStop(mSumScore);
						}
					});
				}
			}, 900);

		}
		//set lood 
		counter++;
		mChooseEqual.setEnabled(false);
		mChooseGreater.setEnabled(false);
		mChooseLesser.setEnabled(false);
		if(mProgressBar.getProgress() == 100 && mFlgActionDownButton==true)
			resetButtonChoose();
		
		if (mFlgChoose || mFlgContinue ) {
			final Handler handler2 = new Handler();
			Timer t2 = new Timer();
			t2.schedule(new TimerTask() {
				public void run() {
					handler2.post(new Runnable() {
						public void run() {
							Log.d("DatPV","load again process bar");
							
							timer.cancel();							
							mFlgContinue = false;
							loadProcessBar();
						}
					});
				}
			}, 1200);
		}
		
				
		
		
	}
	/**
	 * 
	 */
	public void resetButtonChoose(){
		mFlgResetButtonChoose = true;
		mChooseEqual.setBackgroundResource(R.drawable.play_btn_02);
		mChooseGreater.setBackgroundResource(R.drawable.play_btn_01);
		mChooseLesser.setBackgroundResource(R.drawable.play_btn_03);
	}
	/**
	 * 
	 */
	private void sumScoreGame() {
		Log.d("mScoreGame", " : " + mScoreGame);

		if (mOperatorResult.equals(mOperatorChoose)) {
			// when you choose correct
			final int scoreResult = (100 - mScoreGame)*99 ;
			mSumScore = mSumScore + scoreResult;
			mScore.setText(String.valueOf(mSumScore));
			mScoreResult.setText("+" + String.valueOf(scoreResult));
		} else
			// when you choose incorrect
			mScoreResult.setText("+0");
	}

	/**
	 * 
	 */
	public int mathNum(TextView Calculations, int num1, int num2) {
		String operator = (String) Calculations.getText();
		int math = 0;
		if (operator.equals(PLUS))
			math = num1 + num2;
		else if (operator.equals(MINUS))
			math = num1 - num2;
		else if (operator.equals(MULTIPLY))
			math = num1 * num2;
		else
			math = num1 / num2;
		return math;
	}

	/**
	 * 
	 */
	@Override
	protected void onDestroy() {
		// TODO Auto-generated method stub
		super.onDestroy();
		timer.cancel();
	}
	/**
	 * 
	 */
	@Override
	protected void onPause() {
		// TODO Auto-generated method stub
		super.onPause();
		mProcessBarResume = mProgressBar.getProgress();
		myTimeTemp = myTime;
		mFlgContinue = true;
		timeAsynnTask.cancel(true);
		timer.cancel();		
	}
	/**
	 * 
	 */
	@Override
	protected void onResume() {
		// TODO Auto-generated method stub
		super.onResume();
			loadProcessBar();
		
	}
	/**
	 * 
	 */
	
	public class TimeAsyncTask extends AsyncTask<Void, Integer, Void> {

		private Context mContext;
		//private int myTime;
		

		public TimeAsyncTask(Context context) {
			// TODO Auto-generated constructor stub
			mContext = context;
			//mProgressBarAsync = progressBar;
		}

		@Override
		protected void onPreExecute() {
			// TODO Auto-generated method stub
			super.onPreExecute();
			rlScoreResult.setVisibility(View.GONE);
			// reset Operator
			mScoreResult.setText("+0");
			mOperatorChoose = "";
			mScoreGame = 100;
			mFlgChoose = false;
			
			
			if(myTimeTemp != 0){
				myTime = myTimeTemp;
				Log.d("myTimeTemp",""+myTime);
				myTimeTemp = 0;
			}else{
				random();
				myTime = 0;
			}
				
		}

		@Override
		protected Void doInBackground(Void... params) {
			// TODO Auto-generated method stub
			mChooseEqual.setEnabled(true);
			mChooseGreater.setEnabled(true);
			mChooseLesser.setEnabled(true);
			
			while (myTime < 100) {
				myTime++;
				if (mProgressBar.getProgress() != 100) {
					publishProgress(myTime);
					SystemClock.sleep(99);
				} else
					break;
			}
			Log.d("DatPV-----", " myTime :" + myTime);
			return null;
		}

		@Override
		protected void onProgressUpdate(Integer... values) {
			// TODO Auto-generated method stub
			super.onProgressUpdate(values);
			mProgressBar.setProgress(values[0]);
			
		}

		@Override
		protected void onPostExecute(Void result) {
			// TODO Auto-generated method stub
			super.onPostExecute(result);
			mScoreGame = myTime;
			operation();

		}
	}
	
	
	
	@Override
	public void onClick(View v) {
		// TODO Auto-generated method stub
		switch (v.getId()) {
		case R.id.bt_choose_equal:
			//if(mFlgResetButtonChoose == false){
				mOperatorChoose = "=";
				mFlgChoose = true;
				mChooseEqual.setEnabled(false);
				if(mProgressBar.getProgress()!=100){
					mProgressBar.setProgress(100);
					timer.cancel();
				}
//			}
//			mFlgResetButtonChoose = false;
			// loodProcessBar();
			break;
		case R.id.bt_choose_greater:
			//if(mFlgResetButtonChoose==false){
				mOperatorChoose = ">";
				mFlgChoose = true;
				mChooseGreater.setEnabled(false);
				if(mProgressBar.getProgress()!=100){
					mProgressBar.setProgress(100);
					timer.cancel();
				}
//			}
//			mFlgResetButtonChoose = false;
			break;
		case R.id.bt_choose_lesser:
			//if(mFlgResetButtonChoose == false){
				mOperatorChoose = "<";
				mFlgChoose = true;
				mChooseLesser.setEnabled(false);
				if(mProgressBar.getProgress()!=100){
					mProgressBar.setProgress(100);
					timer.cancel();
				}
//			}
//			mFlgResetButtonChoose = false;
			break;
		default:
			break;
		}
	}

	/**
	 * 
	 */
	public int[] randomNumber(TextView textview) {

		Random random = new Random();
		int randomOperator = random.nextInt(4);
		int num2 = 0;
		int num1 = 0;
		switch (randomOperator) {
		case 0:
			// plus +
			textview.setText(PLUS);
			num1 = (int) (Math.random() * 9);
			num2 = (int) (Math.random() * (9 - num1));
			break;
		case 1:
			textview.setText(MINUS);
			// minus -
			num1 = (int) (Math.random() * 10);
			num2 = (int) (Math.random() * num1);
			break;
		case 2:
			// asterisk *
			textview.setText(MULTIPLY);
			num1 = (int) (Math.random() * 10);
			if (num1 >= 5)
				num2 = (int) (Math.random() * 2);
			else if (num1 == 4)
				num2 = (int) (Math.random() * 3);
			else if (num1 == 3)
				num2 = (int) (Math.random() * 4);
			else if (num1 == 2)
				num2 = (int) (Math.random() * 5);
			else
				num2 = (int) (Math.random() * 10);
			break;
		case 3:
			// semi-colon :
			textview.setText(DIVIDE);
			num1 = (int) (Math.random() * 10);
			switch (num1) {
			case 0:
				num2 = (int) (Math.random() * 9 + 1);
				break;
			case 1:
				num2 = 1;
				break;
			case 2:
				num2 = (int) (Math.random() * 2 + 1);
				break;
			case 3:
				int[] array = { 1, 3 };
				num2 = array[random.nextInt(array.length)];
				break;
			case 4:
				int[] array2 = { 1, 2, 4 };
				num2 = array2[random.nextInt(array2.length)];
				break;
			case 5:
				int[] array3 = { 1, 5 };
				num2 = array3[random.nextInt(array3.length)];
				break;
			case 6:
				int[] array4 = { 1, 2, 3, 6 };
				num2 = array4[random.nextInt(array4.length)];
				break;
			case 7:
				int[] array5 = { 1, 7 };
				num2 = array5[random.nextInt(array5.length)];
				break;
			case 8:
				int[] array6 = { 1, 2, 4 };
				num2 = array6[random.nextInt(array6.length)];
				break;
			case 9:
				int[] array7 = { 1, 3, 9 };
				num2 = array7[random.nextInt(array7.length)];
				break;
			default:
				break;
			}

			break;
		default:
			break;
		}
		int[] num = { num1, num2 };
		return num;

	}

	private void goToAndStop(long finalPoint) {
		Common.initSizeForResultScreen(Config.ratioX, Config.ratioY);
		Common.initBitmapForResult(this);

		Intent i = new Intent(getApplicationContext(), ResultActivity.class);
		i.putExtra("finalPoint", finalPoint + "");
		startActivity(i);
		finish();
	}
	@Override
	public boolean onTouch(View v, MotionEvent event) {
		// TODO Auto-generated method stub
		
		switch (v.getId()) {
		case R.id.bt_choose_equal:			
			if(event.getAction() == MotionEvent.ACTION_DOWN){
				mChooseEqual.setBackgroundResource(R.drawable.play_btn_02_hl);
				mFlgActionDownButton = true;
			}else if(event.getAction() == MotionEvent.ACTION_UP){
				Log.d("DatPV","-------######");
				mChooseEqual.setBackgroundResource(R.drawable.play_btn_02);
				Log.d("DatPV mFlgResetButtonChoose: ",""+mFlgResetButtonChoose);
				Log.d("DatPV FlgActionDown: ",""+mFlgActionDownButton);
				if(mFlgResetButtonChoose==false){
					mOperatorChoose = "=";
					mFlgChoose = true;
					if(mProgressBar.getProgress()!=100){
						mProgressBar.setProgress(100);
						timer.cancel();
					}			
				}
				mFlgActionDownButton = false;
				mFlgResetButtonChoose = false;
			}
					
			break;
		case R.id.bt_choose_greater:
			if(event.getAction() == MotionEvent.ACTION_DOWN){
				mChooseGreater.setBackgroundResource(R.drawable.play_btn_01_hl);
				mFlgActionDownButton = true;
			}else if(event.getAction() == MotionEvent.ACTION_UP){
				mChooseGreater.setBackgroundResource(R.drawable.play_btn_01);
				if(mFlgResetButtonChoose==false){
					mOperatorChoose = ">";
					mFlgChoose = true;
					if(mProgressBar.getProgress()!=100){
						mProgressBar.setProgress(100);
						timer.cancel();
					}
					
				}
				
				mFlgActionDownButton = false;
				mFlgResetButtonChoose = false;
			}
			break;
		case R.id.bt_choose_lesser:
			if(event.getAction() == MotionEvent.ACTION_DOWN){
				mChooseLesser.setBackgroundResource(R.drawable.play_btn_03_hl);
				mFlgActionDownButton = true;
			}else if(event.getAction() == MotionEvent.ACTION_UP){
				mChooseLesser.setBackgroundResource(R.drawable.play_btn_03);
				if(mFlgResetButtonChoose == false){
					mOperatorChoose = "<";
					mFlgChoose = true;
					if(mProgressBar.getProgress()!=100){
						mProgressBar.setProgress(100);
						timer.cancel();
					}
				}
				mFlgActionDownButton = false;
				mFlgResetButtonChoose = false;
			}
			break;
		default:
			break;
		}
		return true;
	}
	
}
