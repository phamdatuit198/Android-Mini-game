package jp.vfja.android.NumberGame3.objects;

import java.io.InputStream;

import jp.vfja.android.NumberGame3.gui.CanvasManager;
import jp.vfja.android.NumberGame3.listeners.OnBroken;
import jp.vfja.android.NumberGame3.listeners.OnGrown;

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
public class Egg extends Sprite {

	public static final int STATUS_FALLING = 1;
	public static final int STATUS_BROKEN = 2;
	public static final int STATUS_GROWN = 3;
	public static final int TYPE_GOLD = 1;
	public static final int TYPE_NORMAL = 0;

	private int type;
	private Bitmap[] bmEggs;
	private int index;
	private int velocity;
	private int brokenTime;
	private int grownTime;

	private Basket basket;

	private OnGrown listener;
	private OnBroken brokenListener;

	public Egg() {
		init();
	}

	private void init() {
		bmEggs = new Bitmap[6];
		Context context = CanvasManager.getInstance().getContext();
		AssetManager assetManager = context.getAssets();
		InputStream istr;
		try {
			// Options opts = new Options();
			for (int i = 0; i < bmEggs.length; i++) {
				istr = assetManager.open("egg_" + i + ".png");
				Bitmap bmTemp = BitmapFactory.decodeStream(istr);
				int wi = (int) (CanvasManager.getInstance().mWidth * ((float) bmTemp.getWidth() / 720));
				float ratioW = (float) wi / bmTemp.getWidth();
				int he = (int) (bmTemp.getHeight() * ratioW);
				bmEggs[i] = Bitmap.createScaledBitmap(bmTemp, wi, he, false);
				// bmTemp.recycle();
				istr.close();
				istr = null;
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
		index = 0;
		width = bmEggs[index].getWidth();
		height = bmEggs[index].getHeight();
	}

	public int getVelocity() {
		return velocity;
	}

	public void setVelocity(int velocity) {
		this.velocity = velocity;
	}

	public int getType() {
		return type;
	}

	public void setOnGrownListener(OnGrown listener) {
		this.listener = listener;
	}

	public void setOnBrokenListener(OnBroken listener) {
		this.brokenListener = listener;
	}

	public void setType(int type) {
		this.type = type;
		if (type == TYPE_NORMAL)
			index = 0;
		else {
			index = 3;
		}
	}

	public void setBasket(Basket basket) {
		this.basket = basket;
	}

	@Override
	public int getWidth() {
		if (bmEggs == null || bmEggs[index] == null) {
			return super.getWidth();
		} else {
			return bmEggs[index].getWidth();
		}
	}

	@Override
	public int getHeight() {
		if (bmEggs == null || bmEggs[index] == null) {
			return super.getHeight();
		} else {
			return bmEggs[index].getHeight();
		}
	}

	@Override
	public void onDraw(Canvas canvas) {
		super.onDraw(canvas);
		if (attached) {
			if (bmEggs != null) {
				if (bmEggs[index] != null && !bmEggs[index].isRecycled()) {
					canvas.drawBitmap(bmEggs[index], x, y, CanvasManager.getInstance().mPaint);
				}
			}
		}
	}

	@Override
	public void updateGame() {
		super.updateGame();
		if (attached) {
			switch (status) {
			case STATUS_FALLING:
				falling();
				break;
			case STATUS_BROKEN:
				broken();
				break;
			case STATUS_GROWN:
				grown();
				break;

			default:
				break;
			}
		}
	}

	private void falling() {
		float dy = y + height;
		if (basket != null && dy >= (basket.getY() + 10) && dy <= (basket.getY() + basket.getHeight() - 5) && x + (width / 2) >= (basket.getX()) && x + (width / 2) <= (basket.getX() + basket.getWidth())) {
			this.setStatus(STATUS_GROWN);
		} else if (dy >= CanvasManager.getInstance().mHeight - (CanvasManager.getInstance().mHeight * 0.12)) {
			this.setStatus(STATUS_BROKEN);
		} else {
			if (type == TYPE_GOLD) {
				y += velocity + 2;
			} else {
				y += velocity;
			}
		}
	}

	private void broken() {
		if (brokenTime >= 3000) {
			this.setAttached(false);
			brokenTime = 0;
			if (brokenListener != null) {
				this.brokenListener.onBroken();
			}
		} else {
			if (type == TYPE_NORMAL) {
				index = 1;
			} else {
				index = 4;
			}
		}
		brokenTime += 100;

	}

	private void grown() {
		if (grownTime <= 3000) {
			int oldIndex = index;
			if (type == TYPE_NORMAL) {
				index = 2;
			} else {
				index = 5;
			}
			if (oldIndex != index) {
				x = x + ((bmEggs[oldIndex].getWidth() - bmEggs[index].getWidth()) / 2);
			}
			if (grownTime <= 1000) {
				y -= 5;
			} else {
				y += 5;
			}

		} else {
			this.setAttached(false);
			grownTime = 0;
			if (this.listener != null) {
				this.listener.onGrown(type);
			}
		}
		grownTime += 100;
	}
}
