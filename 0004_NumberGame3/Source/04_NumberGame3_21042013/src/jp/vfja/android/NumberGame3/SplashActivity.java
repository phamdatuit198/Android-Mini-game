package jp.vfja.android.NumberGame3;

import jp.vfja.android.NumberGame3.common.Common;
import jp.vfja.android.NumberGame3.common.Config;
import jp.vfja.android.NumberGame3.view.ImageManual;
import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.graphics.Point;
import android.graphics.Typeface;
import android.os.Bundle;
import android.os.CountDownTimer;
import android.view.Display;
import android.view.KeyEvent;
import android.view.Window;
import android.view.WindowManager;
import android.widget.RelativeLayout;
import android.widget.Toast;

/**
 * SplashActivity
 *
 * @author DAT PHAM
 *
 */
public class SplashActivity extends Activity {
	private Context mContext;
	private RelativeLayout parent;
	private ImageManual mLogo;
	private Point logoPos;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		requestWindowFeature(Window.FEATURE_NO_TITLE);
		getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);
		setContentView(R.layout.activity_splash);
		mContext = this;
		initResource();
	}

	/**
	 * Init resource
	 */
	private void initResource() {
		initData();
		initScreenSize();
		// init font
		Config.fontRanking = Typeface.createFromAsset(mContext.getAssets(), "HGRPP1.TTC");

		parent = (RelativeLayout) findViewById(R.id.parent);
		parent.addView(mLogo);
		moveToTop();
	}

	/**
	 * Move to Menu
	 */
	private void moveToTop() {
		CountDownTimer countDownTimer = new CountDownTimer(5000, 5000) {
			public void onTick(long millisUntilFinished) {
				Toast.makeText(mContext, "" + millisUntilFinished, Toast.LENGTH_SHORT).show();
				// init when count down

			}

			public void onFinish() {
				Intent intent = new Intent(SplashActivity.this, TopActivity.class);
				startActivity(intent);
				overridePendingTransition(R.anim.slide_in_left, R.anim.slide_out_right);
				finish();
			}
		};
		countDownTimer.start();
	}

	/**
	 * Init Data for Game
	 */
	private void initData() {
		Display display = getWindowManager().getDefaultDisplay();
		int screenWidth = display.getWidth();
		int screenHeight = display.getHeight();
		float ratioX = (float) (screenWidth) / (float) (640);
		float ratioY = (float) (screenHeight) / (float) (960);
		System.out.println("ratioX : " + ratioX + " - screenWidth : " + screenWidth);
		System.out.println("ratioY : " + ratioY + " - screenHeight : " + screenHeight);
		Common.initSize(ratioX, ratioY);
		Common.initBitmap(mContext);
		Common.initScoreCenter(mContext);
		Common.initHighScoreLocal(mContext);
	}

	/**
	 * Init Screen Size and others
	 */
	private void initScreenSize() {
		logoPos = new Point(0, (Config.SCREEN_HEIGHT - Config.TOP_LOGO_HEIGHT) / 2);
		mLogo = new ImageManual(mContext, logoPos.x, logoPos.y, Config.TOP_LOGO_HEIGHT, Config.TOP_LOGO_WIDTH, Config.SPLASH_LOGO);
	}

	@Override
	public boolean onKeyDown(int keyCode, KeyEvent event) {
		switch (keyCode) {
		case KeyEvent.KEYCODE_BACK:
			System.out.println("onKeyDown");
			return true;

		default:
			break;
		}
		return super.onKeyDown(keyCode, event);
	}

	@Override
	public boolean onKeyUp(int keyCode, KeyEvent event) {
		switch (keyCode) {
		case KeyEvent.KEYCODE_BACK:
			System.out.println("onKeyUp");
			return true;

		default:
			break;
		}
		return super.onKeyUp(keyCode, event);
	}

	@Override
	protected void onDestroy() {
		super.onDestroy();
		mLogo.stopDraw = true;
		// Config.SPLASH_LOGO.recycle();

	}
}
