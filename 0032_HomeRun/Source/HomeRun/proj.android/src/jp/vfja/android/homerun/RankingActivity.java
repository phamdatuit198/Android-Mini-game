package jp.vfja.android.homerun;

import jp.maru.mrd.IconCell;
import jp.maru.mrd.IconLoader;
import jp.vfja.android.homerun.configs.Common;
import jp.vfja.android.homerun.configs.Config;
import jp.vfja.android.homerun.configs.ConnectionDetector;
import jp.vfja.android.homerun.lib.SuperActivity;
import jp.vfja.android.homerun.view.ButtonView;
import jp.vfja.android.homerun.view.ButtonView2Status;
import jp.vfja.android.homerun.view.Image;
import jp.vfja.android.homerun.view.ImageManual;
import android.content.Context;
import android.graphics.Color;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnTouchListener;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.RelativeLayout.LayoutParams;
import android.widget.TextView;

/**
 * Ranking Activity
 * 
 * @author LINHDN
 * @version 1.0.0 - 2013.04.16
 * 
 */
public class RankingActivity extends SuperActivity {
	private TextView tvHighScoreView[] = new TextView[5];
	private TextView tvPointView[] = new TextView[5];
	private TextView tvNumberView[] = new TextView[5];
	private ButtonView scoreTitle;
	ButtonView2Status btnScoreCenter;
	ButtonView2Status btnBack;
	private View mScoreFrame;
	private LayoutInflater inflater = null;
	private IconLoader<Integer> _iconLoader;
	private ConnectionDetector cd;
	private final String _LOG_TAG = getClass().getPackage().getName();
	private ImageManual imgBackground;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
	}
	@Override
	protected void onResume() {
		super.onResume();
		if (cd.isConnectingToInternet()) {
			vGrpAdv.setVisibility(View.VISIBLE);
			_iconLoader.startLoading(); // start loading icon-AD
		}
	}

	@Override
	public void onPause() {
		_iconLoader.stopLoading(); // stop loading ad
		super.onPause();
	}
	@Override
	protected void initContentLayout() {
		super.initContentLayout();
		scoreTitle = new ButtonView(mContext, Config.RANKING_SCORES_X,
				Config.RANKING_SCORES_Y, Config.TOP_BUTTON_HEIGHT,
				Config.TOP_BUTTON_WIDTH, "SCORES", Config.fontRanking,
				Config.TOP_BUTTON_WIDTH / 4);
		int[] highScore = (int[]) Common.getObjFromInternalFile(mContext,
				Config.score_file_save);
		inflater = (LayoutInflater) getSystemService(Context.LAYOUT_INFLATER_SERVICE);
		mScoreFrame = inflater.inflate(R.layout.activity_ranking_score_frame,
				null);

		LayoutParams lp = new LayoutParams(Config.RANKING_SCORES_LINE_WIDTH,
				Config.RANKING_SCORES_LINE_HEIGH);
		lp.leftMargin = Config.RANKING_SCORES_LINE_X;
		lp.topMargin = Config.RANKING_SCORES_LINE_Y;
		mScoreFrame.setLayoutParams(lp);

		tvHighScoreView[0] = (TextView) mScoreFrame.findViewById(
				R.id.high_score_1).findViewById(R.id.score);
		tvHighScoreView[1] = (TextView) mScoreFrame.findViewById(
				R.id.high_score_2).findViewById(R.id.score);
		tvHighScoreView[2] = (TextView) mScoreFrame.findViewById(
				R.id.high_score_3).findViewById(R.id.score);
		tvHighScoreView[3] = (TextView) mScoreFrame.findViewById(
				R.id.high_score_4).findViewById(R.id.score);
		tvHighScoreView[4] = (TextView) mScoreFrame.findViewById(
				R.id.high_score_5).findViewById(R.id.score);
		tvPointView[0] = (TextView) mScoreFrame.findViewById(R.id.high_score_1)
				.findViewById(R.id.define);
		tvPointView[1] = (TextView) mScoreFrame.findViewById(R.id.high_score_2)
				.findViewById(R.id.define);
		tvPointView[2] = (TextView) mScoreFrame.findViewById(R.id.high_score_3)
				.findViewById(R.id.define);
		tvPointView[3] = (TextView) mScoreFrame.findViewById(R.id.high_score_4)
				.findViewById(R.id.define);
		tvPointView[4] = (TextView) mScoreFrame.findViewById(R.id.high_score_5)
				.findViewById(R.id.define);
		//
		tvNumberView[0] = (TextView) mScoreFrame
				.findViewById(R.id.high_score_1).findViewById(R.id.number);
		tvNumberView[1] = (TextView) mScoreFrame
				.findViewById(R.id.high_score_2).findViewById(R.id.number);
		tvNumberView[2] = (TextView) mScoreFrame
				.findViewById(R.id.high_score_3).findViewById(R.id.number);
		tvNumberView[3] = (TextView) mScoreFrame
				.findViewById(R.id.high_score_4).findViewById(R.id.number);
		tvNumberView[4] = (TextView) mScoreFrame
				.findViewById(R.id.high_score_5).findViewById(R.id.number);
		//
		for (int i = 0; i < highScore.length; i++) {
			tvHighScoreView[i].setText("" + highScore[i]);
			tvHighScoreView[i].setTypeface(Config.fontRanking);
			tvHighScoreView[i]
					.setTextSize(Config.RANKING_SCORES_LINE_HEIGH / 14);
			
			if(i==0)
				tvHighScoreView[i].setTextColor(Color.parseColor("#b70202"));
			else if(i == 1)
				tvHighScoreView[i].setTextColor(Color.parseColor("#0b0583"));
			else if(i == 2)
				tvHighScoreView[i].setTextColor(Color.parseColor("#010101"));
			else if(i == 3)
				tvHighScoreView[i].setTextColor(Color.parseColor("#b70202"));
			else 
				tvHighScoreView[i].setTextColor(Color.parseColor("#0b0583"));
		}
		for (int j = 0; j < 5; j++) {
			tvPointView[j].setText("Point");
			tvPointView[j].setTypeface(Config.fontRanking);
			tvPointView[j].setTextSize(Config.RANKING_SCORES_LINE_HEIGH / 14);

			
			tvNumberView[j].setTypeface(Config.fontRanking);
			tvNumberView[j].setTextSize(Config.RANKING_SCORES_LINE_HEIGH / 14);
			
			if(j==0){
				tvNumberView[j].setText("" + (j + 1)+"st");
				tvPointView[j].setTextColor(Color.parseColor("#b70202"));
				tvNumberView[j].setTextColor(Color.parseColor("#b70202"));
				
			}	
			else if(j == 1){
				tvNumberView[j].setText("" + (j + 1)+"nd");
				tvPointView[j].setTextColor(Color.parseColor("#0b0583"));
				tvNumberView[j].setTextColor(Color.parseColor("#0b0583"));
			}		
			else if(j == 2){
				tvNumberView[j].setText("" + (j + 1)+"th");
				tvPointView[j].setTextColor(Color.parseColor("#010101"));
				tvNumberView[j].setTextColor(Color.parseColor("#010101"));
			}
			else if(j == 3){
				tvNumberView[j].setText("" + (j + 1)+"th");
				tvPointView[j].setTextColor(Color.parseColor("#b70202"));
				tvNumberView[j].setTextColor(Color.parseColor("#b70202"));
			} else {
				tvNumberView[j].setText("" + (j + 1)+"th");
				tvPointView[j].setTextColor(Color.parseColor("#0b0583"));
				tvNumberView[j].setTextColor(Color.parseColor("#0b0583"));
			}
			
		}

		btnBack = new ButtonView2Status(mContext,  Config.RANKING_BACK_X, Config.RANKING_BACK_Y, Config.RANKING_BACK_HEIGH, Config.RANKING_BACK_WIDTH, Config.RANKING_BACK_BUTTON, Config.RANKING_BACK_BUTTON_SWEEL);
		
		btnScoreCenter = new ButtonView2Status(mContext, Config.RANKING_CENTER_X, Config.RANKING_CENTER_Y, Config.RANKING_CENTER_HEIGH, Config.RANKING_CENTER_WIDTH, Config.RANKING_SCORE_CENTER_BUTTON, Config.RANKING_SCORE_CENTER_BUTTON_SWEEL);
		
		imgBackground = new ImageManual(mContext, 0, 0, Config.SCREEN_HEIGHT, Config.SCREEN_WIDTH, Config.RANKIN_BACKGROUND);	
	}

	@Override
	protected void loadContentLayout() {
		super.loadContentLayout();
		initView(false);
		parent.addView(imgBackground);
		parent.addView(mScoreFrame);
		parent.addView(btnBack);
		parent.addView(btnScoreCenter);
		setUpIconLoader();
		cd = new ConnectionDetector(mContext);
		parent.bringChildToFront(vGrpAdv);
		viewClick();
	}

	private void viewClick(){
		parent.setOnTouchListener(new OnTouchListener() {
			
			@Override
			public boolean onTouch(View v, MotionEvent event) {
				System.out.println("parent ontouch");
				float x = event.getX();
				float y = event.getY();
				switch (event.getAction()) {
				case MotionEvent.ACTION_DOWN:

				case MotionEvent.ACTION_MOVE:
					if(btnBack.isOnSize(x, y)){
						btnBack.setTouched(true);
					}else{
						btnBack.setTouched(false);
					}
					
					if(btnScoreCenter.isOnSize(x, y)){
						btnScoreCenter.setTouched(true);
					}else{
						btnScoreCenter.setTouched(false);
					}
					
					break;
					
				case MotionEvent.ACTION_UP:
					if(btnBack.isOnSize(x, y)){
						btnBack.setTouched(false);
						//set move here
						finish();
					}
					
					if(btnScoreCenter.isOnSize(x, y)){
						btnScoreCenter.setTouched(false);
						//set move here
						Common.getScore();
					}
					
					break;
				}
				
				return true;
			}
		});
	}
	/**
	 * Init Adv Icons
	 */
	protected void setUpIconLoader() {
		if (_iconLoader != null)
			return;
		try {
			LayoutParams lp = new LayoutParams(Config.SCREEN_WIDTH, (int)(Config.ratioX*150));
			lp.leftMargin = 0;
			lp.topMargin = Config.SCREEN_HEIGHT - (int)(Config.ratioX*150);
			
			
			// Create instance of IconLoader with mediaCode and Context
			_iconLoader = new IconLoader<Integer>(Config._MEDIA_CODE, this);

			// Retrieve ViewGroup object from content view
			vGrpAdv = (LinearLayout) findViewById(R.id.ads);
			vGrpAdv.setLayoutParams(lp);
			// Register children of viewGroup into iconLoader
			int i, c = vGrpAdv.getChildCount();
			for (i = 0; i < c; i++) {
				View view = vGrpAdv.getChildAt(i);
				if (view instanceof IconCell) {
					((IconCell) view).setTitleColor(Color.WHITE);
					((IconCell) view).addToIconLoader(_iconLoader);
				}
			}

			_iconLoader.setRefreshInterval(15);

		} catch (Exception e) {
			Log.w(_LOG_TAG, "Exception in creation");
			e.printStackTrace();
		}
	}

	@Override
	protected void onDestroy() {
		scoreTitle.stopDraw = true;
		btnBack.stopDraw = true;
		btnScoreCenter.stopDraw = true;
		super.onDestroy();
	}
}
