package jp.vfja.android.NumberGame3.objects;

import java.io.InputStream;

import jp.vfja.android.NumberGame3.gui.CanvasManager;

import android.content.Context;
import android.content.res.AssetManager;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.BitmapFactory.Options;
import android.graphics.Canvas;

/**
 *
 * @author DAT PHAM
 * @since Apr 23, 2013
 */
public class Basket extends Sprite {

	private Bitmap bmBasket;

	private boolean isTouching;

	public Basket() {
		init();
	}

	private void init() {
		Context context = CanvasManager.getInstance().getContext();
		AssetManager assetManager = context.getAssets();
		InputStream istr;
		try {
			Options opt = new Options();
			opt.inSampleSize = 1;
			istr = assetManager.open("basket.png");
			Bitmap bmTemp = BitmapFactory.decodeStream(istr, null, opt);
			int wi = (int) (CanvasManager.getInstance().mWidth * ((float) bmTemp.getWidth() / 720));
			float ratioW = (float) wi / bmTemp.getWidth();
			int he = (int) (bmTemp.getHeight() * ratioW);
			bmBasket = Bitmap.createScaledBitmap(bmTemp, wi, he, false);
			// bmTemp.recycle();
			istr.close();
			istr = null;
		} catch (Exception e) {
			e.printStackTrace();
		}
		width = bmBasket.getWidth();
		height = bmBasket.getHeight();
	}

	public void onTouchDown(float x, float y) {
		if (x >= this.x && x <= (this.x + width) && y >= this.y && y <= (this.y + height)) {
			isTouching = true;
		}
	}

	public void onTouchMove(float x, float y) {
		if (isTouching) {
			if (x + this.getWidth() <= CanvasManager.getInstance().getWidth())
				this.x = x;
		}
	}

	public void onTouchUp(float x, float y) {
		isTouching = false;
	}

	@Override
	public void onDraw(Canvas canvas) {
		if (attached) {
			if (bmBasket != null) {
				canvas.drawBitmap(bmBasket, x, y, CanvasManager.getInstance().mPaint);
			}
		}
	}

}
