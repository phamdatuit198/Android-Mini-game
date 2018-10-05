package jp.vfja.android.CalcMax4;

import jp.maru.mrd.IconCell;
import jp.maru.mrd.IconLoader;
import jp.vfja.android.CalcMax4.configs.Common;
import jp.vfja.android.CalcMax4.configs.Config;
import jp.vfja.android.CalcMax4.configs.ConnectionDetector;
import jp.vfja.android.CalcMax4.lib.SuperActivity;
import jp.vfja.android.CalcMax4.view.ButtonView2Status;
import android.content.Intent;
import android.graphics.Color;
import android.os.Bundle;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnTouchListener;
import android.widget.LinearLayout;
import android.widget.RelativeLayout.LayoutParams;

/**
 * TopActivity
 * @author admin
 *
 */
public class TopActivity extends SuperActivity {
	private ButtonView2Status btnStart, btnRanking, btnManual, btnInfo,btnVitalify;
	private boolean clicked = false;
	private ConnectionDetector cd;
	private IconLoader<Integer> _iconLoader;

	private final String _LOG_TAG = getClass().getPackage().getName();

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
		btnStart.stopDraw = false;
		btnInfo.stopDraw = false;
		btnManual.stopDraw = false;
		btnRanking.stopDraw = false;
	}

	@Override
	public void onPause() {
		_iconLoader.stopLoading(); // stop loading ad
		btnStart.stopDraw = true;
		btnInfo.stopDraw = true;
		btnManual.stopDraw = true;
		btnRanking.stopDraw = true;
		super.onPause();
	}


	@Override
	protected void loadContentLayout() {
		super.loadContentLayout();
		parent.addView(btnStart);
		parent.addView(btnRanking);
		parent.addView(btnManual);
		parent.addView(btnInfo);
		parent.addView(btnVitalify);
		viewClick();
		setUpIconLoader();
		cd = new ConnectionDetector(mContext);

		parent.bringChildToFront(vGrpAdv);
		loadTitle(true);
	}
	
	@Override
	protected void initContentLayout() {
		super.initContentLayout();
		btnStart = new ButtonView2Status(mContext, Config.TOP_START_X,Config.TOP_START_Y, Config.TOP_BUTTON_HEIGHT,
				Config.TOP_BUTTON_WIDTH, Config.TOP_BUTTON_PLAY, Config.TOP_BUTTON_PLAY_SWEEL);
		
		btnRanking = new ButtonView2Status(mContext, Config.TOP_START_X,Config.TOP_RANKING_Y, Config.TOP_BUTTON_HEIGHT,
				Config.TOP_BUTTON_WIDTH, Config.TOP_BUTTON_RANKIN,Config.TOP_BUTTON_RANKIN_SWEEL);
		
		btnManual = new ButtonView2Status(mContext, Config.TOP_START_X,Config.TOP_MANUAL_Y, Config.TOP_BUTTON_HEIGHT,
				Config.TOP_BUTTON_WIDTH, Config.TOP_BUTTON_MANUAL, Config.TOP_BUTTON_MANUAL_SWEEL);
		
		btnInfo = new ButtonView2Status(mContext, Config.TOP_START_X,Config.TOP_INFO_Y, Config.TOP_BUTTON_HEIGHT,
				Config.TOP_BUTTON_WIDTH, Config.TOP_BUTTON_INFO,Config.TOP_BUTTON_INFO_SWEEL);
		btnVitalify = new ButtonView2Status(mContext, Config.TOP_START_X,Config.TOP_VFA_Y, Config.TOP_BUTTON_HEIGHT,
				Config.TOP_BUTTON_WIDTH, Config.TOP_BUTTON_VFA,Config.TOP_BUTTON_VFA_SWEEL);
	
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
					if(btnStart.isOnSize(x, y)){
						btnStart.setTouched(true);
					}else{
						btnStart.setTouched(false);
					}
					if(btnVitalify.isOnSize(x, y)){
						btnVitalify.setTouched(true);
					}else{
						btnVitalify.setTouched(false);
					}
					if(btnRanking.isOnSize(x, y)){
						btnRanking.setTouched(true);
					}else{
						btnRanking.setTouched(false);
					}
					
					if(btnManual.isOnSize(x, y)){
						btnManual.setTouched(true);
					}else{
						btnManual.setTouched(false);
					}
					if(btnInfo.isOnSize(x, y)){
						btnInfo.setTouched(true);
					}else{
						btnInfo.setTouched(false);
					}
					break;
					
				case MotionEvent.ACTION_UP:
					if(btnStart.isOnSize(x, y)){
						btnStart.setTouched(false);
						//set move here
						Intent intent = new Intent(mContext, PlayGameAct.class);
						startActivity(intent);
						clicked = false;
					}
					if(btnVitalify.isOnSize(x, y)){
						btnVitalify.setTouched(false);
						//set move here
						Common.linkToMarket(TopActivity.this, Config.DEVELOPER_ID);
						clicked = false;
					}
					if(btnRanking.isOnSize(x, y)){
						btnRanking.setTouched(false);
						//set move here
						Intent intent = new Intent(mContext, RankingActivity.class);
						startActivity(intent);
						clicked = false;
					}
					
					if(btnManual.isOnSize(x, y)){
						btnManual.setTouched(false);
						//set move here
						Intent intent = new Intent(mContext, ManualActivity.class);
						startActivity(intent);
						clicked = false;
					}
					
					if(btnInfo.isOnSize(x, y)){
						btnInfo.setTouched(false);
						//set move here
						Intent intent = new Intent(mContext, InfoActivity.class);
						startActivity(intent);
						clicked = false;
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
		Common.recycleBitmap(mContext);
		super.onDestroy();
	}
}
