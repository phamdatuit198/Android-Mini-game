package jp.vfja.android.NumberGame3.view;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.view.View;
import android.widget.RelativeLayout.LayoutParams;
/**
 * Button with 2 status 
 * @author LinhDN
 *
 */
public class ButtonView2Status extends View {
	/* Height */
	private float height;
	/* Width */
	private float width;
	/* X coordinate */
	private float x;
	/* Y coordinate */
	private float y;
	/* Layout parameters */
	private LayoutParams lp = null;
	private boolean touched;
	public boolean stopDraw = false;

	private Bitmap image;
	private Bitmap swheel;
	/* Construction of Button View */
	public ButtonView2Status(Context context, float x, float y, float height, float width, Bitmap image, Bitmap swheel) {
		super(context);
		this.x = x;
		this.y = y;
		this.height = height;
		this.width = width;
		this.touched = false;
		this.stopDraw = false;
		this.image = image;
		this.swheel = swheel;
		resetLayout();
	}

	/* Draw a View */
	@Override
	protected void onDraw(Canvas canvas) {
		super.onDraw(canvas);
		if (stopDraw)
			return;
		if(touched){
			canvas.drawBitmap(swheel, 0, 0, null);
		}else{
			canvas.drawBitmap(image, 0, 0, null);
		}
	}
	
	public float getX() {
		return this.x;
	}



	public boolean getTouched() {
		return this.touched;
	}

	public void setTouched(boolean touched) {
		this.touched = touched;
		invalidate();
	}
	public boolean isOnSize(float x, float y){
		if(x >= this.x && x <= this.x + this.width && y > this.y  && y < this.y + this.height){
			return true;
		}else{
			return false;
		}
	}
	
	/* Return Y coordinate */
	public float getY() {
		return this.y;
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