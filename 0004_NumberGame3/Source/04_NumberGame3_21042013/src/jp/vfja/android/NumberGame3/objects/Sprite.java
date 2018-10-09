package jp.vfja.android.NumberGame3.objects;

import android.graphics.Canvas;

public class Sprite {

	protected float x;
	protected float y;

	protected int width;
	protected int height;

	protected int status;

	protected boolean attached;

	public void onDraw(Canvas canvas) {

	}

	public void updateGame() {

	}

	public void clearData() {

	}

	public float getX() {
		return x;
	}

	public void setX(float x) {
		this.x = x;
	}

	public float getY() {
		return y;
	}

	public void setY(float y) {
		this.y = y;
	}

	public int getWidth() {
		return width;
	}

	public void setWidth(int width) {
		this.width = width;
	}

	public int getHeight() {
		return height;
	}

	public void setHeight(int height) {
		this.height = height;
	}

	public int getStatus() {
		return status;
	}

	public void setStatus(int status) {
		this.status = status;
	}

	public boolean isAttached() {
		return attached;
	}

	public void setAttached(boolean attached) {
		this.attached = attached;
	}

}
