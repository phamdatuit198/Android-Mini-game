package jp.vfja.android.NumberGame3;

import jp.maru.mrd.IconCell;
import jp.maru.mrd.IconLoader;
import jp.vfja.android.NumberGame3.common.Config;
import jp.vfja.android.NumberGame3.common.ConnectionDetector;
import net.nend.android.NendAdView;
import android.app.Activity;
import android.content.Context;
import android.graphics.Color;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.Window;
import android.view.WindowManager;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;
import android.widget.RelativeLayout.LayoutParams;

/**
 * ManualActivity
 *
 * @author DAT PHAM
 *
 */
public class ManualActivity extends Activity {
	protected Context mContext;
	protected RelativeLayout parent;
	// private ImageManual mTitle, mManualView;
	protected LinearLayout vGrpAdv;
	protected NendAdView nEndAdView;
	private IconLoader<Integer> _iconLoader;
	private ConnectionDetector cd;
	private final String _LOG_TAG = getClass().getPackage().getName();

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		requestWindowFeature(Window.FEATURE_NO_TITLE);
		getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);
		setContentView(R.layout.manual_view);
		mContext = this;
		initResource();
	}

	@Override
	protected void onResume() {
		if (nEndAdView != null) {
			nEndAdView.resume();
		}

		if (cd.isConnectingToInternet()) {
			vGrpAdv.setVisibility(View.VISIBLE);
			_iconLoader.startLoading(); // start loading icon-AD
		}
		super.onResume();
	}

	@Override
	public void onPause() {
		if (nEndAdView != null) {
			nEndAdView.pause();
		}
		_iconLoader.stopLoading(); // stop loading ad
		super.onPause();
	}

	/**
	 * Init resource
	 */
	private void initResource() {
		parent = (RelativeLayout) findViewById(R.id.top_layout);
		parent.setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View v) {
				onBackPressed();
			}
		});
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
		cd = new ConnectionDetector(mContext);
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
			Log.w(_LOG_TAG, "Exception in creation");
			e.printStackTrace();
		}
	}
}
