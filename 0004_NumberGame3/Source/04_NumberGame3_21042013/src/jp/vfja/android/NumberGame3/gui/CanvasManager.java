package jp.vfja.android.NumberGame3.gui;

import jp.vfja.android.NumberGame3.common.CustomerRect;
import jp.vfja.android.NumberGame3.screen.SplashScreen;
import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.view.MotionEvent;
import android.view.View;

public class CanvasManager extends View implements Runnable {

	private Thread mThread;
	private boolean isGameLoop = true;
	private Page CurrentPage;
	public static CanvasManager instance;
	public Res mRes;
	public Paint mPaint;
	public int mWidth, mHeight;
	private Context context;
	private CustomerRect mLayer;

	public CanvasManager(Context context) {
		super(context);
		this.context = context;

	}

	public void init() {
		setFocusable(true);
		setFocusableInTouchMode(true);
		mLayer = new CustomerRect(0, 0, mWidth, mHeight);
		instance = this;
		mPaint = new Paint();
		mPaint.setColor(Color.WHITE);
		mRes = new Res(context);
		mRes.onLoadSplashScreen();
		CurrentPage = new SplashScreen();
		CurrentPage.initPage();
		starGameLoop();
	}

	public void setSizeScreen(int width, int height) {
		mWidth = width;
		mHeight = height;
	}

	public static CanvasManager getInstance() {
		return instance;
	}

	public void starGameLoop() {
		isGameLoop = true;
		mThread = new Thread(this);
		mThread.start();
	}

	public void stopGameLoop() {
		if (mThread != null) {
			isGameLoop = false;
			mThread = null;
			System.gc();
		}
	}

	public void setCurrentScreen(Page page) {
		if (page != null) {
			CurrentPage = page;
		}
	}

	@Override
	public boolean onTouchEvent(MotionEvent event) {
		final int action = event.getAction();
		final float x = event.getX();
		final float y = event.getY();
		switch (action) {
		case MotionEvent.ACTION_DOWN:
			CurrentPage.onTouchDown(x, y);
			break;
		case MotionEvent.ACTION_MOVE:
			CurrentPage.onTouchMove(x, y);
			break;
		case MotionEvent.ACTION_UP:
			CurrentPage.onTouchUp(x, y);
			break;

		default:
			return false;
		}
		return true;
	}

	@Override
	public void onDraw(Canvas canvas) {
		canvas.drawRect(mLayer, mPaint);
		if (CurrentPage != null) {
			CurrentPage.onDraw(canvas);
		}
	}

	public void updateGame() {
		if (CurrentPage != null) {
			CurrentPage.updateGame();
		}
	}

	@Override
	public void run() {

		while (isGameLoop) {
			updateGame();
			postInvalidate();
			try {
				Thread.sleep(30);
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
	}

	public void onStop() {
		CurrentPage.onStop();
	}

	public void onResume() {
		CurrentPage.onResume();
	}

	public void onDestroy() {
		isGameLoop = false;
		CurrentPage.onDestroy();
	}
}
