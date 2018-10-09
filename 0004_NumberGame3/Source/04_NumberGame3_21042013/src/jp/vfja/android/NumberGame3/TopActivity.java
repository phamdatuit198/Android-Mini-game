package jp.vfja.android.NumberGame3;

import jp.maru.mrd.IconCell;
import jp.maru.mrd.IconLoader;
import jp.vfja.android.NumberGame3.common.Common;
import jp.vfja.android.NumberGame3.common.Config;
import jp.vfja.android.NumberGame3.common.ConnectionDetector;
import net.nend.android.NendAdView;
import android.app.Activity;
import android.content.Intent;
import android.graphics.Color;
import android.graphics.drawable.AnimationDrawable;
import android.os.Bundle;
import android.util.DisplayMetrics;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.Window;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;
import android.widget.RelativeLayout.LayoutParams;

/**
 * Change top screen on base code
 *
 * @author DAT PHAM
 * @since May 16, 2013
 */
public class TopActivity extends Activity implements OnClickListener {

	/**
	 * This variable is including screen size
	 */
	private DisplayMetrics mDisplayMetrics;

	/**
	 * Image view is showing the title of game
	 */
	private ImageView imgTitle;
	/**
	 * Button use to start playing game
	 */
	private Button btnPlay;
	/**
	 * Button use to show rankin of game
	 */
	private Button btnRankin;
	/**
	 * Button use to show how to play
	 */
	private Button btnManual;
	/**
	 * Button use to show information of company
	 */
	private Button btnInfo;
	/**
	 * Button use to show games of company
	 */
	private Button btnVitalify;

	private ImageView imgChickens;
	// **** Initialize advertisement --- Start
	protected LinearLayout vGrpAdv;
	protected NendAdView nEndAdView;
	private IconLoader<Integer> _iconLoader;
	private ConnectionDetector cd;

	// **** Initialize advertisement --- End

	private RelativeLayout parent;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		requestWindowFeature(Window.FEATURE_NO_TITLE);
		getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);
		mDisplayMetrics = new DisplayMetrics();
		getWindowManager().getDefaultDisplay().getMetrics(mDisplayMetrics);
		setContentView(R.layout.top_screen);
		initializeComponents();
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

	/**
	 * Initialize all components on this screen
	 *
	 * @author ThoLH
	 * @since May 16, 2013
	 */
	private void initializeComponents() {
		imgTitle = (ImageView) findViewById(R.id.img_top_title);
		imgTitle.post(new Runnable() {
			@Override
			public void run() {
				AnimationDrawable animation = (AnimationDrawable) imgTitle.getBackground();
				animation.start();
			}
		});
		btnRankin = (Button) findViewById(R.id.btn_rankin);
		btnRankin.setOnClickListener(this);
		btnInfo = (Button) findViewById(R.id.btn_info);
		btnInfo.setOnClickListener(this);
		btnManual = (Button) findViewById(R.id.btn_manual);
		btnManual.setOnClickListener(this);
		btnPlay = (Button) findViewById(R.id.btn_play);
		btnPlay.setOnClickListener(this);
		btnVitalify = (Button) findViewById(R.id.btn_vitalify);
		btnVitalify.setOnClickListener(this);
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

	@Override
	public void onClick(View v) {
		switch (v.getId()) {
		case R.id.btn_info:
			goToScreen(InfoActivity.class, null);
			break;
		case R.id.btn_manual:
			goToScreen(ManualActivity.class, null);
			break;
		case R.id.btn_play:
			goToScreen(GameActivity.class, null);
			break;
		case R.id.btn_rankin:
			goToScreen(RankingActivity.class, null);
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

}
