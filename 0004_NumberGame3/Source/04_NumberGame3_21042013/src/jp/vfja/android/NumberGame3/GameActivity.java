package jp.vfja.android.NumberGame3;

import jp.vfja.android.NumberGame3.gui.CanvasManager;
import android.app.Activity;
import android.os.Bundle;
import android.util.DisplayMetrics;
import android.view.Window;
import android.view.WindowManager;

public class GameActivity extends Activity {

	CanvasManager canvas;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		requestWindowFeature(Window.FEATURE_NO_TITLE);
		getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);
		DisplayMetrics metrics = new DisplayMetrics();
		getWindowManager().getDefaultDisplay().getMetrics(metrics);
		canvas = new CanvasManager(this);
		canvas.setSizeScreen(metrics.widthPixels, metrics.heightPixels);
		canvas.init();
		setContentView(canvas);
	}

	@Override
	public void onBackPressed() {
		canvas.stopGameLoop();
		finish();
	}

	@Override
	protected void onStop() {
		super.onStop();
		if (canvas != null) {
			canvas.onStop();
		}
	}

	@Override
	protected void onResume() {
		super.onResume();
		if (canvas != null) {
			canvas.onResume();
		}
	}

	@Override
	protected void onDestroy() {
		super.onDestroy();
		if (canvas != null) {
			canvas.onDestroy();
		}
	}

}
