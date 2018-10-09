package jp.vfja.android.NumberGame3.screen;

import java.io.InputStream;

import jp.vfja.android.NumberGame3.ResultActivity;
import jp.vfja.android.NumberGame3.common.Constant;
import jp.vfja.android.NumberGame3.common.CustomerRect;
import jp.vfja.android.NumberGame3.common.RandomUtilities;
import jp.vfja.android.NumberGame3.gui.CanvasManager;
import jp.vfja.android.NumberGame3.gui.Page;
import jp.vfja.android.NumberGame3.listeners.OnBroken;
import jp.vfja.android.NumberGame3.listeners.OnGrown;
import jp.vfja.android.NumberGame3.listeners.OnHatched;
import jp.vfja.android.NumberGame3.objects.Basket;
import jp.vfja.android.NumberGame3.objects.Chicken;
import jp.vfja.android.NumberGame3.objects.Egg;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.res.AssetManager;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.BitmapFactory.Options;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.os.CountDownTimer;

public class SplashScreen extends Page {

	private Chicken chicken;
	private Chicken chicken1;
	private Chicken chicken2;
	private Chicken chicken3;
	private Egg egg;
	private Egg egg1;
	private Egg egg2;
	private Egg egg3;
	private Basket basket;

	private int padding;

	private CustomerRect rectBottom;
	private Paint mPaint;
	private Bitmap bmBrokenEgg;
	private Bitmap bmChicken;
	private Bitmap bmGoldChicken;
	private Bitmap bmClock;
	private Bitmap bmStraw;

	private float brokenY;

	private int brokenCount;
	private int chickenCount;
	private int goldChickenCount;
	private boolean endingGame = false;

	private static int countdownMinute = 59;

	private CountDownTimer mTimer;

	private float leftPadding = 10;
	private boolean isPausing = false;

	/**
	 * The background of playing screen
	 */
	private Bitmap bmBackground;

	public SplashScreen() {
		// Options options = new Options();
		// options.inSampleSize = 2;
		Context context = CanvasManager.getInstance().getContext();
		AssetManager assetManager = context.getAssets();
		InputStream istr;
		try {
			istr = assetManager.open("playing_background.png");
			Bitmap bmTemp = BitmapFactory.decodeStream(istr, null, null);
			bmBackground = Bitmap.createScaledBitmap(bmTemp, CanvasManager.getInstance().mWidth, CanvasManager.getInstance().mHeight, false);
			// bmTemp.recycle();
			istr.close();
			istr = null;
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	@Override
	public void initPage() {
		super.initPage();
		initBase();

		countdownMinute = 59;
		final int velocity = (CanvasManager.getInstance().mWidth * 6) / 480;
		// initTimer();
		// Initialize basket
		basket = new Basket();
		basket.setX(0);
		basket.setY(CanvasManager.getInstance().mHeight - (int) (CanvasManager.getInstance().mHeight * 0.165));
		basket.setAttached(true);

		// Initialize chickens
		float chickenY = (float) (CanvasManager.getInstance().mHeight * 0.15);
		chicken = new Chicken();
		chicken.setStatus(Chicken.WAITING);
		chicken.setAttached(true);
		int width = CanvasManager.getInstance().mWidth;
		padding = (width - (4 * chicken.getWidth())) / 5;
		chicken.setX(padding);
		chicken.setY(chickenY);
		chicken.setWaitingTime(RandomUtilities.randomHatchingChicken());
		chicken1 = new Chicken();
		chicken1.setStatus(Chicken.WAITING);
		chicken1.setAttached(true);
		chicken1.setY(chickenY);
		chicken1.setX(padding * 2 + chicken.getWidth());
		chicken1.setWaitingTime(RandomUtilities.randomHatchingChicken());
		chicken2 = new Chicken();
		chicken2.setStatus(Chicken.WAITING);
		chicken2.setAttached(true);
		chicken2.setY(chickenY);
		chicken2.setX(padding * 3 + chicken.getWidth() * 2);
		chicken2.setWaitingTime(RandomUtilities.randomHatchingChicken());
		chicken3 = new Chicken();
		chicken3.setStatus(Chicken.WAITING);
		chicken3.setAttached(true);
		chicken3.setY(chickenY);
		chicken3.setX(padding * 4 + chicken.getWidth() * 3);
		chicken3.setWaitingTime(RandomUtilities.randomHatchingChicken());

		// Initialize eggs
		egg = new Egg();
		egg.setAttached(false);
		egg1 = new Egg();
		egg1.setAttached(false);
		egg2 = new Egg();
		egg2.setAttached(false);
		egg3 = new Egg();
		egg3.setAttached(false);
		egg.setOnGrownListener(new OnGrown() {
			@Override
			public void onGrown(int type) {
				int time = RandomUtilities.randomHatchingChicken();
				chicken.setWaitingTime(time);
				chicken.setStatus(Chicken.WAITING);
				if (type == Egg.TYPE_GOLD) {
					goldChickenCount++;
				} else {
					chickenCount++;
				}
			}
		});

		egg.setOnBrokenListener(new OnBroken() {

			@Override
			public void onBroken() {
				int time = RandomUtilities.randomHatchingChicken();
				chicken.setWaitingTime(time);
				chicken.setStatus(Chicken.WAITING);
				brokenCount++;
			}
		});
		egg1.setOnBrokenListener(new OnBroken() {

			@Override
			public void onBroken() {
				int time = RandomUtilities.randomHatchingChicken();
				chicken1.setWaitingTime(time);
				chicken1.setStatus(Chicken.WAITING);
				brokenCount++;
			}
		});
		egg2.setOnBrokenListener(new OnBroken() {

			@Override
			public void onBroken() {
				int time = RandomUtilities.randomHatchingChicken();
				chicken2.setWaitingTime(time);
				chicken2.setStatus(Chicken.WAITING);
				brokenCount++;
			}
		});
		egg3.setOnBrokenListener(new OnBroken() {

			@Override
			public void onBroken() {
				int time = RandomUtilities.randomHatchingChicken();
				chicken3.setWaitingTime(time);
				chicken3.setStatus(Chicken.WAITING);
				brokenCount++;
			}
		});
		egg2.setOnGrownListener(new OnGrown() {
			@Override
			public void onGrown(int type) {
				int time = RandomUtilities.randomHatchingChicken();
				chicken2.setWaitingTime(time);
				chicken2.setStatus(Chicken.WAITING);
				if (type == Egg.TYPE_GOLD) {
					goldChickenCount++;
				} else {
					chickenCount++;
				}
			}
		});
		egg1.setOnGrownListener(new OnGrown() {
			@Override
			public void onGrown(int type) {
				int time = RandomUtilities.randomHatchingChicken();
				chicken1.setWaitingTime(time);
				chicken1.setStatus(Chicken.WAITING);
				if (type == Egg.TYPE_GOLD) {
					goldChickenCount++;
				} else {
					chickenCount++;
				}
			}
		});
		egg3.setOnGrownListener(new OnGrown() {
			@Override
			public void onGrown(int type) {
				int time = RandomUtilities.randomHatchingChicken();
				chicken3.setWaitingTime(time);
				chicken3.setStatus(Chicken.WAITING);
				if (type == Egg.TYPE_GOLD) {
					goldChickenCount++;
				} else {
					chickenCount++;
				}
			}
		});
		chicken.setOnHatchedListener(new OnHatched() {
			@Override
			public void onHatched() {
				if (egg != null) {
					egg.setAttached(true);
					egg.setStatus(Egg.STATUS_FALLING);
					egg.setVelocity(velocity);
					egg.setType(RandomUtilities.randomTypeEgg());
					egg.setX(chicken.getX() + ((chicken.getWidth() - egg.getWidth()) / 2));
					egg.setY(chicken.getY() + chicken.getHeight());
					egg.setBasket(basket);

				}
			}
		});
		chicken1.setOnHatchedListener(new OnHatched() {
			@Override
			public void onHatched() {
				if (egg1 != null) {
					egg1.setAttached(true);
					egg1.setStatus(Egg.STATUS_FALLING);
					egg1.setVelocity(velocity);
					egg1.setType(RandomUtilities.randomTypeEgg());
					egg1.setX(chicken1.getX() + ((chicken1.getWidth() - egg1.getWidth()) / 2));
					egg1.setY(chicken1.getY() + chicken1.getHeight());
					egg1.setBasket(basket);

				}
			}
		});
		chicken2.setOnHatchedListener(new OnHatched() {
			@Override
			public void onHatched() {
				if (egg2 != null) {
					egg2.setAttached(true);
					egg2.setStatus(Egg.STATUS_FALLING);
					egg2.setVelocity(velocity);
					egg2.setType(RandomUtilities.randomTypeEgg());
					egg2.setX(chicken2.getX() + ((chicken2.getWidth() - egg2.getWidth()) / 2));
					egg2.setY(chicken2.getY() + chicken2.getHeight());
					egg2.setBasket(basket);

				}
			}
		});
		chicken3.setOnHatchedListener(new OnHatched() {
			@Override
			public void onHatched() {
				if (egg3 != null) {
					egg3.setAttached(true);
					egg3.setStatus(Egg.STATUS_FALLING);
					egg3.setVelocity(velocity);
					egg3.setType(RandomUtilities.randomTypeEgg());
					egg3.setX(chicken3.getX() + ((chicken3.getWidth() - egg3.getWidth()) / 2));
					egg3.setY(chicken3.getY() + chicken3.getHeight());
					egg3.setBasket(basket);

				}
			}
		});

	}

	@Override
	public void onResume() {
		super.onResume();
		isPausing = false;
		initTimer();
		mTimer.start();
	}

	@Override
	public void onStop() {
		super.onStop();
		isPausing = true;
		if (mTimer != null) {
			mTimer.cancel();
		}
		mTimer = null;

	}

	private void initTimer() {
		mTimer = new CountDownTimer(countdownMinute * 1000, 1000) {

			@Override
			public void onTick(long millisUntilFinished) {
				if (!isPausing)
					countdownMinute = (int) millisUntilFinished / 1000;
			}

			@Override
			public void onFinish() {
				endingGame = true;
				Intent intent = new Intent(CanvasManager.getInstance().getContext(), ResultActivity.class);
				intent.putExtra(Constant.TEXT_BROKEN, brokenCount);
				intent.putExtra(Constant.TEXT_CHICKEN, chickenCount);
				intent.putExtra(Constant.TEXT_GOLD, goldChickenCount);
				CanvasManager.getInstance().getContext().startActivity(intent);
				((Activity) CanvasManager.getInstance().getContext()).finish();
				// clearScreen();
			}
		};
	}

	private void initBase() {
		brokenCount = 0;
		chickenCount = 0;
		goldChickenCount = 0;
		rectBottom = new CustomerRect(0, CanvasManager.getInstance().mHeight - 80, CanvasManager.getInstance().mWidth, CanvasManager.getInstance().mHeight);
		mPaint = new Paint();
		Context context = CanvasManager.getInstance().getContext();
		AssetManager assetManager = context.getAssets();
		InputStream istr;
		try {
			Options opts = new Options();
			// opts.inSampleSize = 2;
			Bitmap bmTemp;
			istr = assetManager.open("gold_chicken.png");
			bmTemp = BitmapFactory.decodeStream(istr, null, opts);
			int w = CanvasManager.getInstance().mWidth * 60 / 480;
			float ratio = (float) w / bmTemp.getWidth();
			int h = (int) (bmTemp.getHeight() * ratio);
			bmGoldChicken = Bitmap.createScaledBitmap(bmTemp, w, h, false);
			//bmTemp.recycle();
			istr.close();
			istr = null;

			istr = assetManager.open("chicken.png");
			bmTemp = BitmapFactory.decodeStream(istr, null, opts);
			bmChicken = Bitmap.createScaledBitmap(bmTemp, w, h, false);
			//bmTemp.recycle();
			istr.close();
			istr = null;
			// opts.inSampleSize = 4;
			istr = assetManager.open("broken_egg.png");
			bmTemp = BitmapFactory.decodeStream(istr, null, opts);
			bmBrokenEgg = Bitmap.createScaledBitmap(bmTemp, w, h, false);
			bmTemp.recycle();
			istr.close();
			istr = null;

			istr = assetManager.open("clock.png");
			bmTemp = BitmapFactory.decodeStream(istr, null, opts);
			bmClock = Bitmap.createScaledBitmap(bmTemp, w, h, false);
			//bmTemp.recycle();
			istr.close();
			istr = null;

			// opts.inSampleSize = 4;
			istr = assetManager.open("straw.png");
			bmTemp = BitmapFactory.decodeStream(istr, null, opts);
			int wi = (CanvasManager.getInstance().mWidth - (5 * 10)) / 4;
			float ratioW = (float) wi / bmTemp.getWidth();
			int he = (int) (bmTemp.getHeight() * ratioW);
			bmStraw = Bitmap.createScaledBitmap(bmTemp, wi, he, false);
			//bmTemp.recycle();
			istr.close();
			istr = null;

		} catch (Exception e) {
			e.printStackTrace();
		}
		brokenY = CanvasManager.getInstance().mHeight - bmChicken.getHeight() - 20;
	}

	@Override
	public void onTouchDown(float x, float y) {
		super.onTouchDown(x, y);
		basket.onTouchDown(x, y);
	}

	@Override
	public void onTouchMove(float x, float y) {
		super.onTouchMove(x, y);
		basket.onTouchMove(x, y);
	}

	@Override
	public void onTouchUp(float x, float y) {
		super.onTouchUp(x, y);
		basket.onTouchUp(x, y);
	}

	@Override
	public void onDraw(Canvas canvas) {

		// Drawing background
		if (bmBackground != null) {
			canvas.drawBitmap(bmBackground, 0, 0, CanvasManager.getInstance().mPaint);
		}

		float chickenY = (float) (CanvasManager.getInstance().mHeight * 0.15) + 10;

		if (chicken != null) {
			chicken.onDraw(canvas);
			if (bmStraw != null)
				canvas.drawBitmap(bmStraw, padding, chickenY - bmStraw.getHeight() + chicken.getHeight(), CanvasManager.getInstance().mPaint);
		}
		if (chicken1 != null) {
			chicken1.onDraw(canvas);
			if (bmStraw != null)
				canvas.drawBitmap(bmStraw, padding * 2 + chicken1.getWidth(), chickenY - bmStraw.getHeight() + chicken1.getHeight(), CanvasManager.getInstance().mPaint);
		}
		if (chicken2 != null) {
			chicken2.onDraw(canvas);
			if (bmStraw != null)
				canvas.drawBitmap(bmStraw, padding * 3 + chicken2.getWidth() * 2, chickenY - bmStraw.getHeight() + chicken2.getHeight(), CanvasManager.getInstance().mPaint);
		}
		if (chicken3 != null) {
			chicken3.onDraw(canvas);
			if (bmStraw != null)
				canvas.drawBitmap(bmStraw, padding * 4 + chicken.getWidth() * 3, chickenY - bmStraw.getHeight() + chicken3.getHeight(), CanvasManager.getInstance().mPaint);
		}
		if (basket != null) {
			basket.onDraw(canvas);
		}
		if (egg != null) {
			egg.onDraw(canvas);
		}
		if (egg1 != null) {
			egg1.onDraw(canvas);
		}
		if (egg2 != null) {
			egg2.onDraw(canvas);
		}
		if (egg3 != null) {
			egg3.onDraw(canvas);
		}
		mPaint.setColor(Color.TRANSPARENT);
		canvas.drawRect(rectBottom, mPaint);

		mPaint.setColor(Color.WHITE);

		int textSize = (28 * CanvasManager.getInstance().mWidth) / 480;
		mPaint.setTextSize(textSize);

		float pointX = (CanvasManager.getInstance().mWidth - (5 * 10)) / 4;
		float textY = brokenY + (bmChicken.getHeight() / 2) + (textSize / 2);
		// Drawing chickens counted
		canvas.drawBitmap(bmChicken, padding, brokenY, CanvasManager.getInstance().mPaint);
		canvas.drawText("x " + chickenCount, leftPadding + padding + bmChicken.getWidth(), textY, mPaint);
		// Drawing broken eggs counted
		canvas.drawBitmap(bmBrokenEgg, leftPadding + pointX + padding * 2, brokenY, CanvasManager.getInstance().mPaint);
		canvas.drawText("x " + brokenCount, leftPadding + pointX + padding * 2 + bmBrokenEgg.getWidth(), textY, mPaint);
		// Drawing gold chickens counted
		canvas.drawBitmap(bmGoldChicken, leftPadding + 2 * pointX + padding * 3, brokenY, CanvasManager.getInstance().mPaint);
		canvas.drawText("x " + goldChickenCount, leftPadding + 2 * pointX + padding * 3 + bmGoldChicken.getWidth(), textY, mPaint);

		// Drawing clock
		canvas.drawBitmap(bmClock, leftPadding + 3 * pointX + padding * 4, brokenY, CanvasManager.getInstance().mPaint);
		// Drawing minutes counting down
		mPaint.setColor(Color.YELLOW);
		canvas.drawText(countdownMinute + "", leftPadding + 3 * pointX + padding * 4 + bmClock.getWidth(), textY, mPaint);
	}

	@Override
	public void updateGame() {
		super.updateGame();
		if (!endingGame) {
			if (chicken != null) {
				chicken.updateGame();
			}
			if (chicken1 != null) {
				chicken1.updateGame();
			}
			if (chicken2 != null) {
				chicken2.updateGame();
			}
			if (chicken3 != null) {
				chicken3.updateGame();
			}

			if (egg != null) {
				egg.updateGame();
			}
			if (egg1 != null) {
				egg1.updateGame();
			}
			if (egg2 != null) {
				egg2.updateGame();
			}
			if (egg3 != null) {
				egg3.updateGame();
			}

		}
	}

	@Override
	public void onDestroy() {
		super.onDestroy();
		countdownMinute = 59;
		if (mTimer != null)
			mTimer.cancel();
		clearScreen();
	}

	private void clearScreen() {
		if (bmBackground != null)
			bmBackground.recycle();
		bmBackground = null;
		if (bmBrokenEgg != null)
			bmBrokenEgg.recycle();
		bmBrokenEgg = null;
		if (bmChicken != null)
			bmChicken.recycle();
		bmChicken = null;
		if (bmGoldChicken != null)
			bmGoldChicken.recycle();
		bmGoldChicken = null;
		if (bmClock != null)
			bmClock.recycle();
		bmClock = null;
		if (bmStraw != null)
			bmStraw.recycle();
		bmStraw = null;
	}

}
