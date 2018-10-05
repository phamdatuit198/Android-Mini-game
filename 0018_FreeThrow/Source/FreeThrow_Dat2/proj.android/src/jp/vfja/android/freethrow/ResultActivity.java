package jp.vfja.android.freethrow;

import jp.maru.mrd.IconCell;
import jp.maru.mrd.IconLoader;
import jp.vfja.android.freethrow.configs.Common;
import jp.vfja.android.freethrow.configs.Config;
import jp.vfja.android.freethrow.configs.ConnectionDetector;
import jp.vfja.android.freethrow.lib.SuperActivity;
import jp.vfja.android.freethrow.view.ButtonView;
import jp.vfja.android.freethrow.view.ButtonView2Status;
import jp.vfja.android.freethrow.view.Image;
import jp.vfja.android.freethrow.view.ImageManual;
import android.content.Intent;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Rect;
import android.os.Bundle;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnTouchListener;
import android.widget.LinearLayout;
import android.widget.RelativeLayout.LayoutParams;


public class ResultActivity extends SuperActivity{
	private ButtonView2Status btnRestart, btnGoTop, btnVitalify;
	private ConnectionDetector cd;
	private IconLoader<Integer> iconLoader;
	private Image imgRankin, imgTitleResult, imgTextTotal, imgTextPoint;
	private ImageManual imgBackground;
	private boolean clicked = false;

	@Override
	protected void initContentLayout() {
		// TODO Auto-generated method stub
		super.initContentLayout();
//		 imgRankin = new Image(mContext, 
//				 250*Config.ratioX, (Config.SCREEN_HEIGHT/2 - 140*Config.ratioX), 
//				 Config.RESULT_IMG_RANKIN_HEIGHT, Config.RESULT_IMG_RANKIN_WIDTH, 
//				 Config.RESULT_IMG_RANKIN);
		imgRankin = new Image(mContext, 
				 150*Config.ratioX, (Config.SCREEN_HEIGHT/2 - 200*Config.ratioX), 
				 Config.RESULT_IMG_RANKIN_HEIGHT, Config.RESULT_IMG_RANKIN_WIDTH, 
				 Config.RESULT_IMG_RANKIN);
		
		imgBackground = new ImageManual(mContext, 0, 0, Config.SCREEN_HEIGHT,
				Config.SCREEN_WIDTH, Config.RESULT_BACKGROUND);
		
		
		
//		 btnGoTop = new ButtonView2Status(mContext, 
//				 Config.TOP_START_X,Config.SCREEN_HEIGHT/2 + 150 *Config.ratioX , 
//				 Config.RESULT_BUTTON_TOP_HEIGHT, Config.RESULT_BUTTON_TOP_WIDTH, "", 
//				 Config.RESULT_BUTTON_TOP,Config.RESULT_BUTTON_TOP_SWELL);
//		 btnRestart = new ButtonView2Status(mContext, 
//				 Config.TOP_START_X, Config.SCREEN_HEIGHT/2 + 40*Config.ratioX, 
//				 Config.RESULT_BUTTON_RESTART_HEIGHT, Config.RESULT_BUTTON_RESTART_WIDTH, "", 
//				 Config.RESULT_BUTTON_RESTART,Config.RESULT_BUTTON_RESTART_SWEEL);
		
		 
		 btnGoTop = new ButtonView2Status(mContext, 
				 Config.TOP_START_X, Config.SCREEN_HEIGHT/2 + 40 *Config.ratioX, 
				 Config.RESULT_BUTTON_TOP_HEIGHT, Config.RESULT_BUTTON_TOP_WIDTH, Config.RESULT_BUTTON_TOP,Config.RESULT_BUTTON_TOP_SWEEL);
		 
		 btnRestart = new ButtonView2Status(mContext, 
				 Config.TOP_START_X, Config.SCREEN_HEIGHT/2 - 100*Config.ratioX, 
				 Config.RESULT_BUTTON_RESTART_HEIGHT, Config.RESULT_BUTTON_RESTART_WIDTH, Config.RESULT_BUTTON_RESTART, Config.RESULT_BUTTON_RESTART_SWEEL);
		
		 btnVitalify = new ButtonView2Status(mContext, 
				 Config.TOP_START_X,Config.SCREEN_HEIGHT/2 + 180 *Config.ratioX, 
				 Config.RESULT_BUTTON_VFA_HEIGHT,
				 Config.RESULT_BUTTON_VFA_WIDTH, Config.RESULT_BUTTON_VITALIFY,Config.RESULT_BUTTON_VITALIFY_SWEEL);
		
		 
	}
	
	@Override
	protected void loadContentLayout() {
		// TODO Auto-generated method stub
		super.loadContentLayout();
		parent.addView(imgBackground);
		parent.addView(imgRankin);
		parent.addView(btnRestart);
		parent.addView(btnGoTop);
		parent.addView(btnVitalify);
		viewClick();
		setUpIconLoader();
		cd = new ConnectionDetector(mContext);

		parent.bringChildToFront(vGrpAdv);//show ads
		
	}
	
	
	/**
	 * OnClickListener for Buttons
	 */
	private void viewClick() {
		parent.setOnTouchListener(new OnTouchListener() {
			
			@Override
			public boolean onTouch(View v, MotionEvent event) {
				System.out.println("parent ontouch");
				float x = event.getX();
				float y = event.getY();
				switch (event.getAction()) {
				case MotionEvent.ACTION_DOWN:

				case MotionEvent.ACTION_MOVE:
					if(btnRestart.isOnSize(x, y)){
						btnRestart.setTouched(true);
					}else{
						btnRestart.setTouched(false);
					}
					
					if(btnGoTop.isOnSize(x, y)){
						btnGoTop.setTouched(true);
					}else{
						btnGoTop.setTouched(false);
					}
					if(btnVitalify.isOnSize(x, y)){
						btnVitalify.setTouched(true);
					}else{
						btnVitalify.setTouched(false);
					}
					break;
					
				case MotionEvent.ACTION_UP:
					if(btnRestart.isOnSize(x, y)){
						btnRestart.setTouched(false);
						Intent i = new Intent(getApplicationContext(), FreeThrow_Dat.class);
						startActivity(i);
						finish();
					}
					
					if(btnGoTop.isOnSize(x, y)){
						btnGoTop.setTouched(false);
						finish();
					}
					if(btnVitalify.isOnSize(x, y)){
						btnVitalify.setTouched(false);
						//set move here
						Common.linkToMarket(ResultActivity.this, Config.DEVELOPER_ID);
						clicked = false;
					}
					break;
				}
				
				return true;
			}
		});
	}

	/**
	 * Set up icon for adv
	 */
	private void setUpIconLoader() {
		if (iconLoader != null)
			return;
		try {
			LayoutParams lp = new LayoutParams(Config.SCREEN_WIDTH, (int)(Config.ratioX*150));
			lp.leftMargin = 0;
			lp.topMargin = Config.SCREEN_HEIGHT - (int)(Config.ratioX*150f);
			
			// Create instance of IconLoader with mediaCode and Context
			iconLoader = new IconLoader<Integer>(Config._MEDIA_CODE, mContext);

			// Retrieve ViewGroup object from content view
			vGrpAdv = (LinearLayout) findViewById(R.id.ads);
			
			vGrpAdv.setLayoutParams(lp);
			// Register children of viewGroup into iconLoader
			int i, c = vGrpAdv.getChildCount();
			for (i = 0; i < c; i++) {
				View view = vGrpAdv.getChildAt(i);
				if (view instanceof IconCell) {
					((IconCell) view).setTitleColor(Color.WHITE);
					((IconCell) view).addToIconLoader(iconLoader);
				}
			}

			iconLoader.setRefreshInterval(15);

		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		String resultPoint = getIntent().getStringExtra("finalPoint");
		
		showNumberResultImage(resultPoint);
		showRankin(Integer.parseInt(resultPoint));

	}

	@Override
	protected void onResume() {
		super.onResume();
		if (cd.isConnectingToInternet()) {
			vGrpAdv.setVisibility(View.VISIBLE);
			iconLoader.startLoading(); // start loading icon-AD
		}
	}

	@Override
	public void onPause() {
		iconLoader.stopLoading();
		super.onPause();
	}

	@Override
	protected void onDestroy() {
		super.onDestroy();
	}

	/**
	 * showNumberResultImage
	 * @param result score of user
	 */
	private void showNumberResultImage(String result) {
		
		int textSize = Config.RESULT_IMG_TEXT_POINT_HEIGHT+5;
		Paint mPaint = new Paint();
		mPaint.setTextSize(textSize);
		mPaint.setTypeface(Config.fontRanking);
		Rect bounds = new Rect();
		mPaint.getTextBounds(result, 0, result.length(), bounds);
			
//		ButtonView txtResult = new ButtonView(mContext, 
//				580*Config.ratioX -bounds.width()-10 , 215*Config.ratioY, 
//				bounds.height(), bounds.width(), result, 
//				Config.fontRanking, textSize, Color.WHITE);
		ButtonView txtResult = new ButtonView(mContext, 
				580*Config.ratioX -bounds.width()-50 , 245*Config.ratioY, 
				bounds.height(), bounds.width()+2, result, 
				Config.fontRanking, textSize, R.color.color_text_point_result);
		parent.addView(txtResult);
			
	}

	/**
	 * Show high score ( rank in Image)
	 * @param score score of user
	 */
	private void showRankin(int score) {
		// get score from file
		int[] scoreCurrent = (int[]) Common.getObjFromInternalFile(mContext,Config.score_file_save);
		Log.d("DatPV--- scoreCurrent : ",""+scoreCurrent);
		boolean isTopFive = Common.isHighScore(scoreCurrent, score);

		if (!isTopFive) {
			imgRankin.setVisibility(View.INVISIBLE);
			return;
		}
		imgRankin.setVisibility(View.VISIBLE);

		// send score to center
		Common.sendScore(score);

		// save high score
		Common.writeFileToInternal(mContext, Config.score_file_save,
				scoreCurrent);

	}
}