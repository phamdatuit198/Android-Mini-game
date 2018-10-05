package jp.vfja.android.homerun;


import jp.maru.mrd.IconCell;
import jp.maru.mrd.IconLoader;
import jp.vfja.android.homerun.configs.Config;
import jp.vfja.android.homerun.configs.ConnectionDetector;
import jp.vfja.android.homerun.lib.SuperActivity;
import jp.vfja.android.homerun.view.Image;
import jp.vfja.android.homerun.view.ImageManual;
import android.graphics.Color;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnTouchListener;
import android.widget.LinearLayout;
import android.widget.RelativeLayout.LayoutParams;


/**
 * ManualActivity
 * @author LINHDN
 *
 */
public class ManualActivity extends SuperActivity {
	private ImageManual mManualView;
	private Image imgBackground;
	boolean isInitFinish = false;
	private IconLoader<Integer> _iconLoader;
	private ConnectionDetector cd;
	private final String _LOG_TAG = getClass().getPackage().getName();
	@Override
	protected void initContentLayout() {
		super.initContentLayout();
		isInitFinish = false;
		//mManualView = new ImageManual(mContext, Config.MANUAL_X, Config.MANUAL_Y, Config.MANUAL_HEIGHT, Config.MANUAL_WIDTH, Config.MANUAL_BG);
		
//		imgBackground= new Image(mContext, 0, (Config.SCREEN_HEIGHT - 736*Config.ratioX)/2 + 2, 
//				736*Config.ratioX - 2, Config.SCREEN_WIDTH, 
//			Config.MANUAL_BACKGROUND);
		
	}
	
	@Override
	protected void loadContentLayout() {
		initManue();
		//parent.addView(mManualView);
		isInitFinish = true;
		//parent.addView(imgBackground);
		setUpIconLoader();
		cd = new ConnectionDetector(mContext);
		parent.bringChildToFront(vGrpAdv);
		viewTouch();
	}
	
	@Override
	protected void onDestroy() {
		//mManualView.stopDraw = true;
		super.onDestroy();
	}
	
	private void viewTouch(){
		parent.setOnTouchListener(new OnTouchListener() {
			
			@Override
			public boolean onTouch(View v, MotionEvent event) {
				if(!isInitFinish)
					return false;
				switch (event.getAction()) {
				case MotionEvent.ACTION_DOWN:
					System.out.println("parent down");
					break;
					
				case MotionEvent.ACTION_UP:
					System.out.println("parent up");
					finish();
					break;
					
				case MotionEvent.ACTION_MOVE:
					System.out.println("parent move");
					break;
				}
				return true;
			}
		});
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
}
