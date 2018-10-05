package jp.vfja.android.CalcMax4.view;


import jp.vfja.android.CalcMax4.R;
import jp.vfja.android.CalcMax4.configs.Common;
import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Paint.FontMetrics;
import android.graphics.Paint.Style;
import android.graphics.Typeface;
import android.view.View;
import android.widget.RelativeLayout.LayoutParams;

public class ButtonView extends View {
	/* Height */
	private float height;
	/* Width */
	private float width;
	/* X coordinate */
	private float x;
	/* Y coordinate */
	private float y;
	/* Time coordinate */
	private String title;
	/* Layout parameters */
	private LayoutParams lp = null;
	private boolean clicked;
	private Paint mTextPaint;
	public boolean stopDraw = false;
	private float textWidth;
	private float textHeight;

	private Bitmap background;
	/* Construction of Button View */
	public ButtonView(Context context, float x, float y, float height,
			float width, String title, Bitmap bitmap) {
		super(context);
		this.x = x;
		this.y = y;
		this.height = height;
		this.width = width;
		this.title = title;
		this.clicked = false;
		this.stopDraw = false;
		this.mTextPaint = new Paint();
		this.mTextPaint.setColor(Color.BLACK);
		this.mTextPaint.setTextSize(width / 9);
		this.mTextPaint.setStyle(Style.STROKE);
		this.mTextPaint.setTypeface(Typeface.DEFAULT_BOLD);
		FontMetrics fontMetrics = mTextPaint.getFontMetrics();
		this.textWidth = mTextPaint.measureText(title);
		this.textHeight = (fontMetrics.ascent + fontMetrics.descent);
		this.background = Common.ScaleBitmap(bitmap, width, height);
		resetLayout();
	}

	public ButtonView(Context context, float x, float y, float height,float width, String title, Typeface font, float size) {
		super(context);
		this.x = x;
		this.y = y;
		this.height = height;
		this.width = width;
		this.title = title;
		this.clicked = false;
		this.stopDraw = false;
		this.mTextPaint = new Paint();
		this.mTextPaint.setColor(Color.BLACK);
		this.mTextPaint.setTextSize(size);
		this.mTextPaint.setStyle(Style.FILL);
		this.mTextPaint.setAntiAlias(true);
		this.mTextPaint.setTypeface(font);
		FontMetrics fontMetrics = mTextPaint.getFontMetrics();
		this.textWidth = mTextPaint.measureText(title);
		this.textHeight = (fontMetrics.ascent + fontMetrics.descent);
		this.background = null;
		resetLayout();
	}
	
	public ButtonView(Context context, float x, float y, float height,float width, String title, Typeface font, float size, int color) {
		super(context);
		this.x = x;
		this.y = y;
		this.height = height;
		this.width = width;
		this.title = title;
		this.clicked = false;
		this.stopDraw = false;
		this.mTextPaint = new Paint();
		if(color==0)
			this.mTextPaint.setColor(Color.BLACK);
		else
		{
			this.mTextPaint.setColor(color);
			this.mTextPaint.setShadowLayer((float) 0.1, 1, -1,   getResources().getColor(R.color.black));
			
		}
		this.mTextPaint.setTextSize(size);
		this.mTextPaint.setStyle(Style.FILL);
		this.mTextPaint.setAntiAlias(true);
		this.mTextPaint.setTypeface(font);
		FontMetrics fontMetrics = mTextPaint.getFontMetrics();
		this.textWidth = mTextPaint.measureText(title);
		this.textHeight = (fontMetrics.ascent + fontMetrics.descent);
		this.background = null;
		resetLayout();
	}
	/* Draw a View */
	@Override
	protected void onDraw(Canvas canvas) {
		super.onDraw(canvas);
		if (stopDraw)
			return;
		if(background != null)
			canvas.drawBitmap(background, 0, 0, null);
		
		canvas.drawText(title, (width - textWidth) / 2, (height - textHeight) / 2, mTextPaint);

	}

	/* Return X coordinate */
	public float getX() {
		return this.x;
	}

	/* Return X coordinate */
	public boolean getClicked() {
		return this.clicked;
	}

	public void setClicked(boolean clicked) {
		this.clicked = clicked;
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