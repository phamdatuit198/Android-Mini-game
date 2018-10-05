package jp.vfja.android.CalcMax4.lib;

import jp.vfja.android.CalcMax4.R;
import jp.vfja.android.CalcMax4.configs.Config;
import jp.vfja.android.CalcMax4.view.ImageManual;
import net.nend.android.NendAdView;
import android.app.Activity;
import android.content.Context;
import android.os.Bundle;
import android.view.Window;
import android.view.WindowManager;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;

public class SuperActivity extends Activity{
	protected Context mContext;
	protected RelativeLayout parent;
	private ImageManual mTitle, mbackground, mMiddleBackground;
	protected LinearLayout vGrpAdv;
	protected NendAdView nEndAdView;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		requestWindowFeature(Window.FEATURE_NO_TITLE);
		getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
				WindowManager.LayoutParams.FLAG_FULLSCREEN);
		setContentView(R.layout.activity_top);
		mContext = this;
		initResource();
	}

	@Override
	protected void onResume() {
		if(nEndAdView != null){
			nEndAdView.resume();
		}
		super.onResume();
	}

	@Override
	public void onPause() {
		if(nEndAdView != null){
			nEndAdView.pause();
		}
		super.onPause();
	}

	/**
	 * Init resource
	 */
	private void initResource() {
		initView();
		parent = (RelativeLayout) findViewById(R.id.top_layout);
		parent.addView(mbackground);
		parent.addView(mMiddleBackground);
		try {
			nEndAdView = new NendAdView(getApplicationContext(), Config.NEND_ADV_ID, Config.NEND_ADV_API_KEY);
			RelativeLayout.LayoutParams lp = new RelativeLayout.LayoutParams(
					RelativeLayout.LayoutParams.FILL_PARENT,
					(int) (100 * Config.ratioX));
			lp.leftMargin = 0;
			lp.topMargin = 0;
			parent.addView(nEndAdView, lp);
			nEndAdView.loadAd();
			parent.bringChildToFront(nEndAdView);
		} catch (Exception e) {
			e.printStackTrace();
		}

		loadContentLayout();

	}

	/**
	 * Add children layout components
	 */
	protected void loadContentLayout() {

	}

	/**
	 * Init children layout components
	 */
	protected void initContentLayout() {

	}

	/**
	 * Init Screen Size and others
	 */
	private void initView() {

		mMiddleBackground = new ImageManual(mContext, 0,
				(Config.SCREEN_HEIGHT - 736 * Config.ratioX) / 2,
				736 * Config.ratioX, Config.SCREEN_WIDTH,
				Config.TOP_BACKGROUND_MIDDLE);

		mbackground = new ImageManual(mContext, 0, 0, Config.SCREEN_HEIGHT,
				Config.SCREEN_WIDTH, Config.TOP_COMMON_BACKGROUND);

		initContentLayout();
	}

	/**
	 * loadTitle
	 * 
	 * @param isScreenTop
	 */
	public void loadTitle(boolean isScreenTop) {
		if (isScreenTop) {
			mTitle = new ImageManual(mContext,
					(Config.SCREEN_WIDTH - Config.TOP_TITLE_WIDTH) / 2,
					Config.TOP_TITLE_Y, Config.TOP_TITLE_HEIGHT,
					Config.TOP_TITLE_WIDTH, Config.TOP_TITLE);
			parent.addView(mTitle);
		} else {
			float advTopHigh = 100 * Config.ratioX;
			float TopHigh = Config.SCREEN_HEIGHT / 2 - 736 * Config.ratioX / 2;

			float titleEmpty = TopHigh - advTopHigh;
			System.out.println("titleEmpty :" + titleEmpty);
			System.out.println("Config.GAME_TITLE_HEIGHT :" + Config.GAME_TITLE_HEIGHT);
			if (titleEmpty >= Config.GAME_TITLE_HEIGHT) {
				mTitle = new ImageManual(mContext,
						(Config.SCREEN_WIDTH - Config.GAME_TITLE_WIDTH) / 2,
						advTopHigh, Config.GAME_TITLE_HEIGHT,
						Config.GAME_TITLE_WIDTH, Config.GAME_TITLE);
				parent.addView(mTitle);
			}
		}

	}

	@Override
	protected void onDestroy() {
		try{
			mbackground.stopDraw = true;
			mTitle.stopDraw = true;
			mMiddleBackground.stopDraw = true;
		}catch (Exception e) {
		}
		super.onDestroy();
	}
}
