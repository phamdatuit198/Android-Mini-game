package jp.vfja.android.NumberGame3.common;

import android.graphics.RectF;

public class CustomerRect extends RectF {
	
	public CustomerRect(int x,int y,int w,int h)
	{
		this.left = x;
		this.top = y;
		this.right = w;
		this.bottom = h;
	}
	
}
