package jp.vfja.android.homerun.view;



import jp.vfja.android.homerun.configs.Common;
import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.view.View;
import android.view.animation.Animation;
import android.view.animation.Animation.AnimationListener;
import android.view.animation.AnimationSet;
import android.view.animation.TranslateAnimation;
import android.widget.RelativeLayout.LayoutParams;
public class Image extends View {

	/* Height */
	private float height;
	/* Width */
	private float width;
	/* X coordinate */
	private float x;
	/* Y coordinate */
	private float y;
	/* Moving state */
	private boolean mov_status = false;

	/* Layout parameters */
	private LayoutParams lp = null;

	private Bitmap imgBitmap;

	public boolean stopDraw = false;
	
	public Bitmap getImgBitmap() {
		return imgBitmap;
	}

	public void setImgBitmap(Bitmap imgBitmap) {
		this.imgBitmap = imgBitmap;
		invalidate();
	}

	/* Construction of card */
	public Image(Context context, float x, float y, float height, float width, Bitmap imgBitmap) {
		
		super(context);
		this.stopDraw = false;
		this.x = x;
		this.y = y;
		this.height = height;
		this.width = width;
		this.imgBitmap = Common.ScaleBitmap(imgBitmap, width, height);
		resetLayout();
	}

	/* Draw a card */
	@Override
	protected void onDraw(Canvas canvas) {
		super.onDraw(canvas);
		if (this.width == 0 || this.height == 0 || this.stopDraw || imgBitmap == null) {
			return;
		}
		canvas.drawBitmap(imgBitmap, 0, 0, null);
		

	}

	/* Set width coordinate */
	public void setWidth(float w) {
		this.width = w;
	}

	public void setHeigh(float h) {
		this.height = h;
	}

	/* Set X coordinate */
	public void set_X(float x) {
		this.x = x;
	}

	/* Set Y coordinate */
	public void set_Y(float y) {
		this.y = y;
	}

	/* Set Height */
	public void setmHeight(int height) {
		this.height = height;
	}

	/* Set Width */
	public void setmWidth(int width) {
		this.width = width;
	}

	/* Return X coordinate */
	public float get_X() {
		return this.x;
	}

	/* Return Y coordinate */
	public float get_Y() {
		return this.y;
	}

	/* Return Height */
	public float getmHeight() {
		return this.height;
	}

	/* Return Width */
	public float getmWidth() {
		return this.width;
	}

	/* Move Card from a position to another */
	public void moveCard(float desX, float desY) {
		set_X(desX);
		set_Y(desY);
		resetLayout();
	}

	/* Move Card from a position to another using animation */
	public void moveCardByAnimation(float origX, float origY, float desX,float desY) {
		if (mov_status == true) {
			return;
		}
		AnimationSet animation = new AnimationSet(true);

		TranslateAnimation translateAnimation = new TranslateAnimation(0, desX
				- origX, 0, desY - origY);
		translateAnimation.setDuration(800);
		animation.addAnimation(translateAnimation);

		final float finalX = desX;
		final float finalY = desY;
		animation.setAnimationListener(new AnimationListener() {

			@Override
			public void onAnimationEnd(Animation arg0) {
				clearAnimation();
				set_X(finalX);
				set_Y(finalY);
				resetLayout();
				mov_status = false;
			}

			@Override
			public void onAnimationRepeat(Animation arg0) {
			}

			@Override
			public void onAnimationStart(Animation arg0) {
			}
		});
		mov_status = true;
		startAnimation(animation);
	}

	/* ... */
	public void moveCardByAnimation(float origX, float origY, float desX,
			float desY, final int width, final int height) {
		if (mov_status == true) {
			return;
		}
		AnimationSet animation = new AnimationSet(true);

		TranslateAnimation translateAnimation = new TranslateAnimation(0, desX
				- origX, 0, desY - origY);
		translateAnimation.setDuration(800);
		animation.addAnimation(translateAnimation);

		final float finalX = desX;
		final float finalY = desY;
		animation.setAnimationListener(new AnimationListener() {

			@Override
			public void onAnimationEnd(Animation arg0) {
				clearAnimation();
				setWidth(width);
				setHeigh(height);
				set_X(finalX);
				set_Y(finalY);
				resetLayout();
				mov_status = false;

			}

			@Override
			public void onAnimationRepeat(Animation arg0) {
			}

			@Override
			public void onAnimationStart(Animation arg0) {

			}
		});
		mov_status = true;
		startAnimation(animation);
	}

	/* onFocus effect */
	public boolean getMov_Status() {
		return this.mov_status;
	}

	/* Reset layout */
	private void resetLayout() {
		/* Set parameter for the ball */
		lp = (LayoutParams) getLayoutParams();
		if (lp == null) {
			lp = new LayoutParams((int) width, (int) height);
			lp.leftMargin = (int) x;
			lp.topMargin = (int) y;
		} else {
			lp.leftMargin = (int) x;
			lp.topMargin = (int) y;
			lp.height = (int) (height);
			lp.width = (int) (width);
		}
		setLayoutParams(lp);
	}
}