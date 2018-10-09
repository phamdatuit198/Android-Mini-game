package jp.vfja.android.NumberGame3;

import jp.maru.mrd.IconCell;
import jp.maru.mrd.IconLoader;
import jp.vfja.android.NumberGame3.common.Common;
import jp.vfja.android.NumberGame3.common.Config;
import jp.vfja.android.NumberGame3.common.ConnectionDetector;
import net.nend.android.NendAdView;
import android.app.Activity;
import android.graphics.Color;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;
import android.widget.RelativeLayout.LayoutParams;
import android.widget.TextView;

/**
 * Ranking Activity
 *
 * @author DAT PHAM
 * @version 1.0.0 - 2013.04.16
 *
 */
public class RankingActivity extends Activity implements OnClickListener {

	private TextView tvFirst;
	private TextView tvSecond;
	private TextView tvThird;
	private TextView tvFourth;
	private TextView tvFifth;
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
		setContentView(R.layout.rankin_view);
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

	@Override
	public void onClick(View v) {
		switch (v.getId()) {
		case R.id.btn_back:
			onBackPressed();
			break;
		case R.id.btn_leaderboard:
			Common.getScore();
			break;

		default:
			break;
		}
	}

	/**
	 * Initialize all components
	 *
	 * @author ThoLH
	 * @since May 16, 2013
	 */
	private void initializeComponents() {
		setTypeface();
		setRankin();
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
	 * Set typeface to all textviews
	 *
	 * @author ThoLH
	 * @since May 16, 2013
	 */
	private void setTypeface() {
		tvFifth = (TextView) findViewById(R.id.tv_fifth_point);
		tvFifth.setTypeface(Config.fontRanking);
		((TextView) findViewById(R.id.tv_fifth_text_point)).setTypeface(Config.fontRanking);
		tvFirst = (TextView) findViewById(R.id.tv_first_point);
		tvFirst.setTypeface(Config.fontRanking);
		((TextView) findViewById(R.id.tv_first_text_point)).setTypeface(Config.fontRanking);
		tvFourth = (TextView) findViewById(R.id.tv_fourth_point);
		tvFourth.setTypeface(Config.fontRanking);
		((TextView) findViewById(R.id.tv_fourth_text_point)).setTypeface(Config.fontRanking);
		tvSecond = (TextView) findViewById(R.id.tv_second_point);
		tvSecond.setTypeface(Config.fontRanking);
		((TextView) findViewById(R.id.tv_second_text_point)).setTypeface(Config.fontRanking);
		tvThird = (TextView) findViewById(R.id.tv_third_point);
		tvThird.setTypeface(Config.fontRanking);
		((TextView) findViewById(R.id.tv_third_text_point)).setTypeface(Config.fontRanking);
		((TextView) findViewById(R.id.tv_text_third)).setTypeface(Config.fontRanking);
		((TextView) findViewById(R.id.tv_text_one)).setTypeface(Config.fontRanking);
		((TextView) findViewById(R.id.tv_text_second)).setTypeface(Config.fontRanking);
		((TextView) findViewById(R.id.tv_text_fourth)).setTypeface(Config.fontRanking);
		((TextView) findViewById(R.id.tv_text_fifth)).setTypeface(Config.fontRanking);

		findViewById(R.id.btn_back).setOnClickListener(this);
		findViewById(R.id.btn_leaderboard).setOnClickListener(this);
	}

	/**
	 * Set all scores to textviews
	 *
	 * @author ThoLH
	 * @since May 16, 2013
	 */
	private void setRankin() {
		int[] highScore = (int[]) Common.getObjFromInternalFile(this, Config.score_file_save);
		TextView[] textViews = new TextView[5];
		textViews[0] = tvFirst;
		textViews[1] = tvSecond;
		textViews[2] = tvThird;
		textViews[3] = tvFourth;
		textViews[4] = tvFifth;
		for (int i = 0; i < highScore.length; i++) {
			textViews[i].setText(highScore[i] + "");
		}

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

}
