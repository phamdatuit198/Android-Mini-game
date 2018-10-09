package jp.vfja.android.NumberGame3;

import jp.maru.mrd.IconCell;
import jp.maru.mrd.IconLoader;
import jp.vfja.android.NumberGame3.common.Common;
import jp.vfja.android.NumberGame3.common.Config;
import jp.vfja.android.NumberGame3.common.ConnectionDetector;
import jp.vfja.android.NumberGame3.common.Constant;
import net.nend.android.NendAdView;
import android.app.Activity;
import android.content.Intent;
import android.graphics.Color;
import android.graphics.Typeface;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.Window;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;
import android.widget.RelativeLayout.LayoutParams;
import android.widget.TextView;

public class ResultActivity extends Activity implements OnClickListener {

	private TextView tvTotal;
	private TextView tvPointText;
	private TextView tvPoint;
	private int mChicken;
	private int mBroken;
	private int mGold;
	private View imgRankin;

	private RelativeLayout parent;

	// **** Initialize advertisement --- Start
	protected LinearLayout vGrpAdv;
	protected NendAdView nEndAdView;
	private IconLoader<Integer> _iconLoader;
	private ConnectionDetector cd;

	// **** Initialize advertisement --- End

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		getWindow().requestFeature(Window.FEATURE_NO_TITLE);
		setContentView(R.layout.finish);
		getCount();
		initComponents();
		calculatePoint();
	}

	private void initComponents() {
		Typeface typeface = Typeface.createFromAsset(getAssets(), "HGRPP1.TTC");
		tvTotal = (TextView) findViewById(R.id.tv_text_total);
		tvTotal.setTypeface(typeface);
		tvPointText = (TextView) findViewById(R.id.tv_text_point);
		tvPointText.setTypeface(typeface);
		tvPoint = (TextView) findViewById(R.id.tv_point_number);
		tvPoint.setTypeface(typeface);
		imgRankin = findViewById(R.id.v_rank_in);
		findViewById(R.id.btn_replay).setOnClickListener(this);
		findViewById(R.id.btn_top).setOnClickListener(this);
		findViewById(R.id.btn_vitalify).setOnClickListener(this);
		parent = (RelativeLayout) findViewById(R.id.top_layout);
		try {
			nEndAdView = new NendAdView(getApplicationContext(), Config.NEND_ADV_ID, Config.NEND_ADV_API_KEY);
			RelativeLayout.LayoutParams lp = new RelativeLayout.LayoutParams(RelativeLayout.LayoutParams.FILL_PARENT, (int) (100 * Config.ratioX));
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

	protected void loadContentLayout() {
		setUpIconLoader();
		cd = new ConnectionDetector(this);
		parent.bringChildToFront(vGrpAdv);
	}

	/**
	 * Init Adv Icons
	 */
	protected void setUpIconLoader() {
		if (_iconLoader != null)
			return;
		try {
			LayoutParams lp = new LayoutParams(Config.SCREEN_WIDTH, (int) (Config.ratioX * 150));
			lp.leftMargin = 0;
			lp.topMargin = Config.SCREEN_HEIGHT - (int) (Config.ratioX * 150);

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
			Log.w(this.getLocalClassName(), "Exception in creation");
			e.printStackTrace();
		}
	}

	private void getCount() {
		Bundle bundle = getIntent().getExtras();
		if (bundle != null) {
			if (bundle.containsKey(Constant.TEXT_CHICKEN)) {
				mChicken = bundle.getInt(Constant.TEXT_CHICKEN);
			}
			if (bundle.containsKey(Constant.TEXT_BROKEN)) {
				mBroken = bundle.getInt(Constant.TEXT_BROKEN);
			}
			if (bundle.containsKey(Constant.TEXT_GOLD)) {
				mGold = bundle.getInt(Constant.TEXT_GOLD);
			}
		}
	}

	private void calculatePoint() {
		int chicken = mChicken * Constant.CHICKEN_POINT;
		int broken = mBroken * Constant.BROKEN_EGG_POINT;
		int gold = mGold * Constant.GOLD_CHICKEN_POINT;

		int total = chicken + broken + gold;
		tvPoint.setText(total + "");
		showRankin(total);
	}

	/**
	 * Show high score ( rank in Image)
	 * 
	 * @param score
	 *            score of user
	 */
	private void showRankin(int score) {
		// get score from file
		int[] scoreCurrent = (int[]) Common.getObjFromInternalFile(this, Config.score_file_save);
		boolean isTopFive = Common.isHighScore(scoreCurrent, score);

		if (!isTopFive) {
			imgRankin.setVisibility(View.INVISIBLE);
			return;
		}
		imgRankin.setVisibility(View.VISIBLE);

		// send score to center
		Common.sendScore(score);

		// save high score
		Common.writeFileToInternal(this, Config.score_file_save, scoreCurrent);

	}

	@Override
	protected void onResume() {
		super.onResume();
		if (nEndAdView != null) {
			nEndAdView.resume();
		}

		if (cd.isConnectingToInternet()) {
			vGrpAdv.setVisibility(View.VISIBLE);
			_iconLoader.startLoading(); // start loading icon-AD
		}
	}

	@Override
	protected void onPause() {
		super.onPause();
		if (nEndAdView != null) {
			nEndAdView.pause();
		}
		_iconLoader.stopLoading(); // stop loading ad
	}

	@Override
	public void onClick(View v) {
		switch (v.getId()) {
		case R.id.btn_replay:
			goToScreen(GameActivity.class, null);
			finish();
			break;
		case R.id.btn_top:
			finish();
			break;
		case R.id.btn_vitalify:
			Common.linkToMarket(this, Config.DEVELOPER_ID);
			break;

		default:
			break;
		}
	}

	/**
	 * Go to screen where you want
	 * 
	 * @author ThoLH
	 * @since May 16, 2013
	 * @param screenClass
	 */
	private void goToScreen(@SuppressWarnings("rawtypes") Class screenClass, Bundle bundle) {
		Intent intent = new Intent(this, screenClass);
		if (bundle != null) {
			intent.putExtras(bundle);
		}
		startActivity(intent);
	}

	// private ButtonView2Status btnRestart, btnGoTop;
	// private ConnectionDetector cd;
	// private IconLoader<Integer> iconLoader;
	// private ImageManual imgRankin, imgTitleResult, imgTextTotal,
	// imgTextPoint;
	//
	// @Override
	// protected void initContentLayout() {
	// super.initContentLayout();
	// imgRankin = new ImageManual(mContext, Config.SCREEN_WIDTH / 2
	// - Config.RESULT_IMG_RANKIN_WIDTH / 2,
	// (Config.SCREEN_HEIGHT / 2 - 140 * Config.ratioX),
	// Config.RESULT_IMG_RANKIN_HEIGHT,
	// Config.RESULT_IMG_RANKIN_WIDTH, Config.RESULT_IMG_RANKIN);
	//
	// imgTitleResult = new ImageManual(mContext, 265 * Config.ratioX,
	// (Config.SCREEN_HEIGHT / 2 - 335 * Config.ratioX),
	// Config.RESULT_IMG_TITLE_HEIGHT, Config.RESULT_IMG_TITLE_WIDTH,
	// Config.RESULT_IMG_TITLE);
	//
	// imgTextTotal = new ImageManual(mContext, 40 * Config.ratioX,
	// Config.SCREEN_HEIGHT / 2 - 265 * Config.ratioX,
	// Config.RESULT_IMG_TEXT_TOTAL_HEIGHT,
	// Config.RESULT_IMG_TEXT_TOTAL_WIDTH,
	// Config.RESULT_IMG_TEXT_TOTAL);
	//
	// imgTextPoint = new ImageManual(mContext, 580 * Config.ratioX,
	// Config.SCREEN_HEIGHT / 2 - 262 * Config.ratioX,
	// Config.RESULT_IMG_TEXT_POINT_HEIGHT,
	// Config.RESULT_IMG_TEXT_POINT_WIDTH,
	// Config.RESULT_IMG_TEXT_POINT);
	//
	// btnGoTop = new ButtonView2Status(mContext, Config.TOP_START_X,
	// Config.SCREEN_HEIGHT / 2 + 66 * Config.ratioX,
	// Config.RESULT_BUTTON_TOP_HEIGHT,
	// Config.RESULT_BUTTON_TOP_WIDTH, Config.RESULT_BUTTON_TOP,
	// Config.RESULT_BUTTON_TOP_WHEEL);
	//
	// btnRestart = new ButtonView2Status(mContext, Config.TOP_START_X,
	// Config.SCREEN_HEIGHT / 2 - 55 * Config.ratioX,
	// Config.RESULT_BUTTON_RESTART_HEIGHT,
	// Config.RESULT_BUTTON_RESTART_WIDTH, Config.RESULT_BUTTON_RESTART,
	// Config.RESULT_BUTTON_RESTART_WHEEL);
	// }
	//
	// @Override
	// protected void loadContentLayout() {
	// super.loadContentLayout();
	// parent.addView(imgTitleResult);
	// parent.addView(imgTextTotal);
	// parent.addView(imgTextPoint);
	// parent.addView(imgRankin);
	// parent.addView(btnRestart);
	// parent.addView(btnGoTop);
	// loadTitle(false);
	// viewClick();
	// setUpIconLoader();
	// cd = new ConnectionDetector(mContext);
	//
	// parent.bringChildToFront(vGrpAdv);// show ads
	// }
	//
	// /**
	// * OnClickListener for Buttons
	// */
	// private void viewClick() {
	// parent.setOnTouchListener(new OnTouchListener() {
	//
	// @Override
	// public boolean onTouch(View v, MotionEvent event) {
	// System.out.println("parent ontouch");
	// float x = event.getX();
	// float y = event.getY();
	// switch (event.getAction()) {
	// case MotionEvent.ACTION_DOWN:
	//
	// case MotionEvent.ACTION_MOVE:
	// if(btnRestart.isOnSize(x, y)){
	// btnRestart.setTouched(true);
	// }else{
	// btnRestart.setTouched(false);
	// }
	// if(btnGoTop.isOnSize(x, y)){
	// btnGoTop.setTouched(true);
	// }else{
	// btnGoTop.setTouched(false);
	// }
	//
	//
	// break;
	//
	// case MotionEvent.ACTION_UP:
	// if(btnRestart.isOnSize(x, y)){
	// btnRestart.setTouched(false);
	// Intent i = new Intent(getApplicationContext(),GameActivity.class);
	// startActivity(i);
	// finish();
	// }
	//
	// if(btnGoTop.isOnSize(x, y)){
	// btnGoTop.setTouched(false);
	// finish();
	// }
	//
	// break;
	// }
	//
	// return true;
	// }
	// });
	// }
	//
	// /**
	// * Set up icon for adv
	// */
	// private void setUpIconLoader() {
	// if (iconLoader != null)
	// return;
	// try {
	// LayoutParams lp = new LayoutParams(Config.SCREEN_WIDTH,
	// (int) (Config.ratioX * 150));
	// lp.leftMargin = 0;
	// lp.topMargin = Config.SCREEN_HEIGHT - (int) (Config.ratioX * 150f);
	//
	// // Create instance of IconLoader with mediaCode and Context
	// iconLoader = new IconLoader<Integer>(Config._MEDIA_CODE, mContext);
	//
	// // Retrieve ViewGroup object from content view
	// vGrpAdv = (LinearLayout) findViewById(R.id.ads);
	//
	// vGrpAdv.setLayoutParams(lp);
	// // Register children of viewGroup into iconLoader
	// int i, c = vGrpAdv.getChildCount();
	// for (i = 0; i < c; i++) {
	// View view = vGrpAdv.getChildAt(i);
	// if (view instanceof IconCell) {
	// ((IconCell) view).setTitleColor(Color.WHITE);
	// ((IconCell) view).addToIconLoader(iconLoader);
	// }
	// }
	//
	// iconLoader.setRefreshInterval(15);
	//
	// } catch (Exception e) {
	// e.printStackTrace();
	// }
	// }
	//
	// @Override
	// protected void onCreate(Bundle savedInstanceState) {
	// super.onCreate(savedInstanceState);
	// String resultPoint = getIntent().getStringExtra("finalPoint");
	// showNumberResultImage(resultPoint);
	// showRankin(Integer.parseInt(resultPoint));
	// }
	//
	// @Override
	// protected void onResume() {
	// super.onResume();
	// if (cd.isConnectingToInternet()) {
	// vGrpAdv.setVisibility(View.VISIBLE);
	// iconLoader.startLoading(); // start loading icon-AD
	// }
	// }
	//
	// @Override
	// public void onPause() {
	// iconLoader.stopLoading();
	// super.onPause();
	// }
	//
	// /**
	// * showNumberResultImage
	// *
	// * @param result
	// * score of user
	// */
	// private void showNumberResultImage(String result) {
	//
	// int textSize = Config.RESULT_IMG_TEXT_POINT_HEIGHT + 5;
	// Paint mPaint = new Paint();
	// mPaint.setTextSize(textSize);
	// mPaint.setTypeface(Config.fontRanking);
	// Rect bounds = new Rect();
	// mPaint.getTextBounds(result, 0, result.length(), bounds);
	//
	// ButtonView txtResult = new ButtonView(mContext, 580 * Config.ratioX -
	// bounds.width() - 10, 215 * Config.ratioY, bounds.height(),
	// bounds.width(), result, Config.fontRanking, textSize, Color.WHITE);
	//
	// parent.addView(txtResult);
	//
	// }
	//
	// /**
	// * Show high score ( rank in Image)
	// *
	// * @param score
	// * score of user
	// */
	// private void showRankin(int score) {
	// // get score from file
	// int[] scoreCurrent = (int[]) Common.getObjFromInternalFile(mContext,
	// Config.score_file_save);
	// boolean isTopFive = Common.isHighScore(scoreCurrent, score);
	//
	// if (!isTopFive) {
	// imgRankin.setVisibility(View.INVISIBLE);
	// return;
	// }
	// imgRankin.setVisibility(View.VISIBLE);
	//
	// // send score to center
	// Common.sendScore(score);
	//
	// // save high score
	// Common.writeFileToInternal(mContext, Config.score_file_save,
	// scoreCurrent);
	//
	// }
}