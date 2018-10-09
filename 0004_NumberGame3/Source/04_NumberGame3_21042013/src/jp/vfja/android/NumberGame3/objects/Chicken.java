package jp.vfja.android.NumberGame3.objects;

import java.io.InputStream;

import jp.vfja.android.NumberGame3.common.Constant;
import jp.vfja.android.NumberGame3.gui.CanvasManager;
import jp.vfja.android.NumberGame3.listeners.OnHatched;

import android.content.Context;
import android.content.res.AssetManager;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;

/**
 *
 * @author DAT PHAM
 * @since Apr 22, 2013
 */
public class Chicken extends Sprite {
	public static final int WAITING = 1;
	public static final int HATCHING = 2;
	public static final int UNRELEASED = 3;

	private int index;
	private Bitmap[] bmChickens;
	private int waitingCount = 0;
	private int hatchingTime = 0;

	private int waitingTime = 0; // O is unlimited

	private float oldX = 0;

	private OnHatched listener;

	public Chicken() {
		init();
	}

	private void init() {
		bmChickens = new Bitmap[2];
		Context context = CanvasManager.getInstance().getContext();
		AssetManager assetManager = context.getAssets();
		InputStream istr;
		try {
			for (int i = 0; i < bmChickens.length; i++) {
				istr = assetManager.open("chicken_" + i + ".png");
				Bitmap bmTemp = BitmapFactory.decodeStream(istr);
				int wi = (CanvasManager.getInstance().mWidth - (5 * 10)) / 4;
				float ratioW = (float) wi / bmTemp.getWidth();
				int he = (int) (bmTemp.getHeight() * ratioW);
				bmChickens[i] = Bitmap.createScaledBitmap(bmTemp, wi, he, false);
				// bmTemp.recycle();
				istr.close();
				istr = null;
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
		index = 0;
		width = bmChickens[index].getWidth();
		height = bmChickens[index].getHeight();
	}

	public void setOnHatchedListener(OnHatched listener) {
		this.listener = listener;
	}

	public void setWaitingTime(int time) {
		this.waitingTime = time;
		waitingCount = 0;
	}

	@Override
	public void onDraw(Canvas canvas) {
		super.onDraw(canvas);
		if (attached) {
			if (bmChickens != null) {
				if (bmChickens[index] != null) {
					canvas.drawBitmap(bmChickens[index], x, y, CanvasManager.getInstance().mPaint);
				}
			}
		}
	}

	@Override
	public void updateGame() {
		super.updateGame();
		switch (status) {
		case WAITING:
			waiting();
			break;
		case HATCHING:
			hatching();
			break;

		default:
			break;
		}
	}

	private void waiting() {
		hatchingTime = 0;
		if (oldX == 0) {
			oldX = x;
		}
		if (waitingTime != 0 && waitingCount >= waitingTime * 100) {
			this.setStatus(HATCHING);
			waitingTime = 0;
			waitingCount = 0;
		} else if (waitingCount % 3000 == 0) {
			if (x <= oldX) {
				x = oldX + 5;
			} else {
				x = oldX - 5;
			}
		}
		waitingCount += 100;
		index = 0;
	}

	private void hatching() {
		if (oldX != 0 && x != oldX) {
			x = oldX;
		}
		waitingCount = 0;
		if (hatchingTime <= Constant.HATCHING_TIME) {
			if (hatchingTime % 500 == 0) {
				if (index == 1) {
					index = 0;
				} else {
					index = 1;
				}
			}
		} else {
			if (listener != null) {
				listener.onHatched();
			}
			this.setStatus(WAITING);
			waitingTime = 0;
			hatchingTime = 0;
		}
		// }
		hatchingTime += 100;
	}

}
