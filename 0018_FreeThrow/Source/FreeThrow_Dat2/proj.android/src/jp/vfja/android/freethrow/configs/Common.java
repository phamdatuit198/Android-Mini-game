package jp.vfja.android.freethrow.configs;

import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;

import jp.maru.scorecenter.ScoreCenter;
import jp.vfja.android.freethrow.R;
import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Matrix;
import android.net.Uri;
import android.preference.PreferenceManager;

public class Common {
	
	/**
	 * Init Bitmap
	 * 
	 * @param mContext
	 */
	public static void initBitmap(Context mContext) {
		Config.SPLASH_LOGO = BitmapFactory.decodeResource(mContext.getResources(), R.drawable.splash);
		Config.INFO_BACKGROUND = BitmapFactory.decodeResource(mContext.getResources(), R.drawable.info_background);
		//Config.TOP_BACKGROUND_MIDDLE = Common.ScaleBitmap(BitmapFactory.decodeResource(mContext.getResources(), R.drawable.n_bg), Config.SCREEN_WIDTH - 20,736*Config.ratioX);
		Config.TOP_TITLE = Common.ScaleBitmap(BitmapFactory.decodeResource(mContext.getResources(), R.drawable.title), Config.TOP_TITLE_WIDTH,  Config.TOP_TITLE_HEIGHT);
		Config.GAME_TITLE = Common.ScaleBitmap(BitmapFactory.decodeResource(mContext.getResources(), R.drawable.title), Config.GAME_TITLE_WIDTH,  Config.GAME_TITLE_HEIGHT);
		
		Config.TOP_BUTTON_VFA = Common.ScaleBitmap(BitmapFactory.decodeResource(mContext.getResources(), R.drawable.n_btn_vitalify),Config.TOP_BUTTON_WIDTH_VFA, Config.TOP_BUTTON_HEIGHT);
		Config.TOP_BUTTON_VFA_SWEEL = Common.ScaleBitmap(BitmapFactory.decodeResource(mContext.getResources(), R.drawable.n_btn_vitalify_sweel),Config.TOP_BUTTON_WIDTH_VFA, Config.TOP_BUTTON_HEIGHT);
		Config.TOP_BUTTON_PLAY = Common.ScaleBitmap(BitmapFactory.decodeResource(mContext.getResources(), R.drawable.n_btn_play),Config.TOP_BUTTON_WIDTH, Config.TOP_BUTTON_HEIGHT);
		Config.TOP_BUTTON_RANKIN = Common.ScaleBitmap(BitmapFactory.decodeResource(mContext.getResources(), R.drawable.n_btn_rankin),Config.TOP_BUTTON_WIDTH, Config.TOP_BUTTON_HEIGHT);
		Config.TOP_BUTTON_MANUAL = Common.ScaleBitmap(BitmapFactory.decodeResource(mContext.getResources(), R.drawable.n_btn_manual),Config.TOP_BUTTON_WIDTH, Config.TOP_BUTTON_HEIGHT);
		Config.TOP_BUTTON_INFO = Common.ScaleBitmap(BitmapFactory.decodeResource(mContext.getResources(), R.drawable.n_btn_info),Config.TOP_BUTTON_WIDTH, Config.TOP_BUTTON_HEIGHT);
		Config.TOP_BUTTON_PLAY_SWEEL = Common.ScaleBitmap(BitmapFactory.decodeResource(mContext.getResources(), R.drawable.n_btn_play_click),Config.TOP_BUTTON_WIDTH, Config.TOP_BUTTON_HEIGHT);
		Config.TOP_BUTTON_RANKIN_SWEEL = Common.ScaleBitmap(BitmapFactory.decodeResource(mContext.getResources(), R.drawable.n_btn_rankin_click),Config.TOP_BUTTON_WIDTH, Config.TOP_BUTTON_HEIGHT);
		Config.TOP_BUTTON_MANUAL_SWEEL = Common.ScaleBitmap(BitmapFactory.decodeResource(mContext.getResources(), R.drawable.n_btn_manual_click),Config.TOP_BUTTON_WIDTH, Config.TOP_BUTTON_HEIGHT);
		Config.TOP_BUTTON_INFO_SWEEL = Common.ScaleBitmap(BitmapFactory.decodeResource(mContext.getResources(), R.drawable.n_btn_info_sweel_click),Config.TOP_BUTTON_WIDTH, Config.TOP_BUTTON_HEIGHT);
		
		Config.TOP_COMMON_BACKGROUND = Common.ScaleBitmap(BitmapFactory.decodeResource(mContext.getResources(), R.drawable.n_common_bg), Config.SCREEN_WIDTH, Config.SCREEN_HEIGHT);
		Config.TOP_COMMON_BACKGROUND2 = Common.ScaleBitmap(BitmapFactory.decodeResource(mContext.getResources(), R.drawable.n_bg), Config.SCREEN_WIDTH, Config.SCREEN_HEIGHT);
//		Config.RANKING_NUMBER[0] = BitmapFactory.decodeResource(mContext.getResources(), R.drawable.r1);
//		Config.RANKING_NUMBER[1] = BitmapFactory.decodeResource(mContext.getResources(), R.drawable.r2);
//		Config.RANKING_NUMBER[2] = BitmapFactory.decodeResource(mContext.getResources(), R.drawable.r3);
//		Config.RANKING_NUMBER[3] = BitmapFactory.decodeResource(mContext.getResources(), R.drawable.r4);
//		Config.RANKING_NUMBER[4] = BitmapFactory.decodeResource(mContext.getResources(), R.drawable.r5);
//		Config.RANKING_POINT = BitmapFactory.decodeResource(mContext.getResources(), R.drawable.text_06);
		Config.RANKING_BACK_BUTTON = Common.ScaleBitmap(BitmapFactory.decodeResource(mContext.getResources(), R.drawable.btn_08),Config.RANKING_BACK_WIDTH, Config.RANKING_BACK_HEIGH);
		Config.RANKING_BACK_BUTTON_SWEEL = Common.ScaleBitmap(BitmapFactory.decodeResource(mContext.getResources(), R.drawable.btn_08_click),Config.RANKING_BACK_WIDTH, Config.RANKING_BACK_HEIGH);
		Config.RANKING_SCORE_CENTER_BUTTON = Common.ScaleBitmap(BitmapFactory.decodeResource(mContext.getResources(), R.drawable.btn_09),Config.RANKING_CENTER_WIDTH,Config.RANKING_CENTER_HEIGH);
		Config.RANKING_SCORE_CENTER_BUTTON_SWEEL = Common.ScaleBitmap(BitmapFactory.decodeResource(mContext.getResources(), R.drawable.btn_09_click),Config.RANKING_CENTER_WIDTH,Config.RANKING_CENTER_HEIGH);

		//DatPV Ranking
		Config.RANKING_BACKGROUND = BitmapFactory.decodeResource(
				mContext.getResources(), R.drawable.rankin_board);
		Config.RESULT_BACKGROUND = BitmapFactory.decodeResource(
				mContext.getResources(), R.drawable.result_bg);
		Config.MANUAL_BACKGROUND = BitmapFactory.decodeResource(
				mContext.getResources(), R.drawable.manual_background);
		Config.MANUAL_BG = Common.ScaleBitmap(BitmapFactory.decodeResource(mContext.getResources(), R.drawable.manual_background), Config.MANUAL_WIDTH, Config.MANUAL_HEIGHT);
	}
	public static void recycleBitmap(Context mContext) {
		Config.SPLASH_LOGO.recycle();
		Config.INFO_BACKGROUND.recycle();
		Config.TOP_BACKGROUND_MIDDLE.recycle();
		Config.TOP_TITLE.recycle();
		Config.GAME_TITLE.recycle();
		
		Config.TOP_BUTTON_PLAY.recycle();
		Config.TOP_BUTTON_RANKIN.recycle();
		Config.TOP_BUTTON_MANUAL.recycle();
		Config.TOP_BUTTON_INFO.recycle();
		Config.TOP_BUTTON_PLAY_SWEEL.recycle();
		Config.TOP_BUTTON_RANKIN_SWEEL.recycle();
		Config.TOP_BUTTON_MANUAL_SWEEL.recycle();
		Config.TOP_BUTTON_INFO_SWEEL.recycle();
		
		Config.TOP_COMMON_BACKGROUND.recycle();
		
		Config.RANKING_NUMBER[0].recycle();
		Config.RANKING_NUMBER[1].recycle();
		Config.RANKING_NUMBER[2].recycle();
		Config.RANKING_NUMBER[3].recycle();
		Config.RANKING_NUMBER[4].recycle();
		Config.RANKING_POINT.recycle();
		Config.RANKING_BACK_BUTTON.recycle();
		Config.RANKING_SCORE_CENTER_BUTTON.recycle();
		Config.MANUAL_BG.recycle();
		
		if(Config.RESULT_IMG_RANKIN != null){
			Config.RESULT_IMG_RANKIN.recycle();
			Config.RESULT_IMG_TITLE.recycle();
			Config.RESULT_IMG_TEXT_TOTAL.recycle();
			Config.RESULT_IMG_TEXT_POINT.recycle();
			Config.RESULT_BUTTON_RESTART.recycle();
			Config.RESULT_BUTTON_TOP.recycle();
		}
	}
	/**
	 * Run first on splash screen to configuration size
	 * 
	 * @param ratioX
	 * @param ratioY
	 */
	public static void initSize(float ratioX, float ratioY) {
		Config.ratioX = ratioX;
		Config.ratioY = ratioY;
		Config.SCREEN_WIDTH = (int) (ImageSize.SCREEN_WIDTH * ratioX);
		Config.SCREEN_HEIGHT = (int) (ImageSize.SCREEN_HEIGHT * ratioY);
		Config.TOP_TITLE_WIDTH = (int) (ImageSize.TOP_TITLE_WIDTH* ratioX);
		Config.TOP_TITLE_HEIGHT = (int) (ImageSize.TOP_TITLE_HEIGHT * ratioX);
		Config.GAME_TITLE_WIDTH = (int) (ImageSize.GAME_TITLE_WIDTH* ratioX);
		Config.GAME_TITLE_HEIGHT = (int) (ImageSize.GAME_TITLE_HEIGHT * ratioX);
		
		Config.TOP_LOGO_WIDTH = (int) (ImageSize.TOP_LOGO_WIDTH * ratioX);
		Config.TOP_LOGO_HEIGHT = (int) (ImageSize.TOP_LOGO_HEIGHT * ratioX);
		Config.TOP_BUTTON_WIDTH = (int) (ImageSize.TOP_BUTTON_WIDTH * ratioX);
		Config.TOP_BUTTON_WIDTH_VFA = (int) (ImageSize.TOP_BUTTON_WIDTH_VFA * ratioX);
		Config.TOP_BUTTON_HEIGHT = (int) (ImageSize.TOP_BUTTON_HEIGHT  * ratioX);
		
		Config.TOP_TITLE_Y = (int) (ImageSize.TOP_TITLE_Y* ratioX);
		Config.GAME_TITLE_Y = (int) (ImageSize.GAME_TITLE_Y* ratioX);
		Config.TOP_START_X = (int) (ImageSize.TOP_START_X * ratioX);
		Config.TOP_START1_X = (int) (ImageSize.TOP_START1_X * ratioX);
		Config.TOP_START2_X = (int) (ImageSize.TOP_START2_X * ratioX);
		Config.TOP_START3_X = (int) (ImageSize.TOP_START3_X * ratioX);
		Config.TOP_START_Y = (int) (Config.SCREEN_HEIGHT/2 - ImageSize.TOP_START_FROM_CENTER_Y * ratioX);
		Config.TOP_RANKING_Y = Config.TOP_START_Y + Config.TOP_BUTTON_HEIGHT + (int) (ImageSize.TOP_DIS_Y * ratioX);
		//Config.TOP_MANUAL_Y = Config.TOP_RANKING_Y + Config.TOP_BUTTON_HEIGHT + (int) (ImageSize.TOP_DIS_Y * ratioX);
		Config.TOP_MANUAL_Y = Config.TOP_START_Y;
		Config.TOP_INFO_Y = Config.TOP_MANUAL_Y + Config.TOP_BUTTON_HEIGHT + (int) (ImageSize.TOP_DIS_Y * ratioX);
		Config.TOP_VFA_Y = Config.TOP_INFO_Y + Config.TOP_BUTTON_HEIGHT + (int) (ImageSize.TOP_DIS_Y * ratioX);
		Config.RESULT_VFA_Y = Config.TOP_INFO_Y + Config.TOP_BUTTON_HEIGHT + (int) (ImageSize.TOP_DIS_Y * ratioX);
		Config.RANKING_SCORES_X = (int) (ImageSize.RANKING_SCORES_X * ratioX);
		Config.RANKING_SCORES_Y = (int) (Config.SCREEN_HEIGHT/2 - ImageSize.RANKING_SCORES_FORM_CENTER_Y * ratioX);
		Config.RANKING_SCORES_LINE_X = (int) (ImageSize.RANKING_SCORES_LINE_X * ratioX);
		Config.RANKING_SCORES_LINE_Y = (int) (Config.SCREEN_HEIGHT/2 - ImageSize.RANKING_SCORES_LINE_FROM_CENTER_Y * ratioX);
		
		Config.RANKING_SCORES_LINE_WIDTH = (int) (ImageSize.RANKING_SCORES_LINE_WIDTH * ratioX);
		Config.RANKING_SCORES_LINE_HEIGH = (int) (ImageSize.RANKING_SCORES_LINE_HEIGH * ratioX);
		Config.RANKING_NUMBER_WIDTH = (int) (ImageSize.RANKING_NUMBER_WIDTH * ratioX);
		Config.RANKING_NUMBER_HEIGH = (int) (ImageSize.RANKING_NUMBER_HEIGH * ratioX);
		
		Config.RANKING_POINT_WIDTH = (int) (ImageSize.RANKING_POINT_WIDTH * ratioX);
		Config.RANKING_POINT_HEIGH = (int) (ImageSize.RANKING_POINT_HEIGH * ratioX);
			
	
		Config.RANKING_BACK_WIDTH = (int) (ImageSize.RANKING_BACK_WIDTH * ratioX);
		Config.RANKING_BACK_HEIGH = (int) (ImageSize.RANKING_BACK_HEIGH * ratioX);
		Config.RANKING_BACK_X = (int) (ImageSize.RANKING_BACK_X * ratioX);
		Config.RANKING_BACK_Y = (int) (Config.SCREEN_HEIGHT/2 + ImageSize.RANKING_BACK_FROM_CENTER_Y * ratioX);
		
		Config.RANKING_CENTER_WIDTH = (int) (ImageSize.RANKING_CENTER_WIDTH * ratioX);
		Config.RANKING_CENTER_HEIGH = (int) (ImageSize.RANKING_CENTER_HEIGH * ratioX);
		Config.RANKING_CENTER_X = (int) (ImageSize.RANKING_CENTER_X * ratioX);
		Config.RANKING_CENTER_Y = (int) (Config.SCREEN_HEIGHT/2 + ImageSize.RANKING_CENTER__FROM_CENTER_Y * ratioX);
		
		
		Config.MANUAL_WIDTH = (int) (ImageSize.MANUAL_WIDTH * ratioX);
		Config.MANUAL_HEIGHT = (int) (ImageSize.MANUAL_HEIGHT * ratioX);
		Config.MANUAL_X = 0;
		Config.MANUAL_Y = (Config.SCREEN_HEIGHT - Config.MANUAL_HEIGHT)/2;
		
		Config.MANUAL_STRING_X = (int) (ImageSize.MANUAL_STRING_X * ratioX);
		Config.MANUAL_STRING_Y = (int) (ImageSize.MANUAL_STRING_Y * ratioY);
	}

	/**
	 * Configuration size for
	 * 
	 * @param ratioX
	 * @param ratioY
	 */
	public static void initSizeForResultScreen(float ratioX, float ratioY)
	{

		//DatPV
		Config.RESULT_IMG_RANKIN_HEIGHT = (int) (80 * ratioX);
		Config.RESULT_IMG_RANKIN_WIDTH = (int) (350 * ratioX);
		
		Config.RESULT_IMG_TITLE_HEIGHT = (int) (57 * ratioX);
		Config.RESULT_IMG_TITLE_WIDTH = (int) (148 * ratioX);
		Config.RESULT_IMG_TEXT_TOTAL_HEIGHT = (int) (40 * ratioY);
		Config.RESULT_IMG_TEXT_TOTAL_WIDTH = (int) (152 * ratioX);
		Config.RESULT_IMG_TEXT_POINT_HEIGHT = (int) (33 * ratioX);
		Config.RESULT_IMG_TEXT_POINT_WIDTH = (int) (33 * ratioX);
		Config.RESULT_BUTTON_RESTART_HEIGHT = (int) (100 * ratioX);
		Config.RESULT_BUTTON_RESTART_WIDTH = (int) (280 * ratioX);
		Config.RESULT_BUTTON_TOP_HEIGHT = (int) (100 * ratioX);
		Config.RESULT_BUTTON_TOP_WIDTH = (int) (280 * ratioX);
		Config.RESULT_BUTTON_VFA_HEIGHT = (int) (100 * ratioX);
		Config.RESULT_BUTTON_VFA_WIDTH = (int) (280 * ratioX);
		
	}
	
	/**
	 * Init Bitmap For Result screen
	 * 
	 * @param mContext
	 */
	public static void initBitmapForResult(Context mContext) {
		Config.RESULT_IMG_RANKIN = BitmapFactory.decodeResource(
				mContext.getResources(), R.drawable.rankin);
		Config.RESULT_IMG_TITLE = BitmapFactory.decodeResource(
				mContext.getResources(), R.drawable.n_title_result);
//		Config.RESULT_IMG_TEXT_TOTAL = BitmapFactory.decodeResource(
//				mContext.getResources(), R.drawable.n_result_total);
//		Config.RESULT_IMG_TEXT_POINT = BitmapFactory.decodeResource(
//				mContext.getResources(), R.drawable.n_point);
		
		Config.RESULT_BUTTON_RESTART = Common.ScaleBitmap(BitmapFactory.decodeResource(
				mContext.getResources(), R.drawable.result_btn_01),Config.RESULT_BUTTON_RESTART_WIDTH,Config.RESULT_BUTTON_RESTART_HEIGHT);
		Config.RESULT_BUTTON_TOP = Common.ScaleBitmap(BitmapFactory.decodeResource(
				mContext.getResources(), R.drawable.result_btn_02),Config.RESULT_BUTTON_TOP_WIDTH,Config.RESULT_BUTTON_TOP_HEIGHT);
		Config.RESULT_BUTTON_RESTART_SWEEL = Common.ScaleBitmap(BitmapFactory.decodeResource(
				mContext.getResources(), R.drawable.result_btn_01_hl),Config.RESULT_BUTTON_RESTART_WIDTH,Config.RESULT_BUTTON_RESTART_HEIGHT);
		Config.RESULT_BUTTON_TOP_SWEEL = Common.ScaleBitmap(BitmapFactory.decodeResource(
				mContext.getResources(), R.drawable.result_btn_02_hl),Config.RESULT_BUTTON_TOP_WIDTH,Config.RESULT_BUTTON_TOP_HEIGHT);
		Config.RESULT_BUTTON_VITALIFY = Common.ScaleBitmap(BitmapFactory.decodeResource(mContext.getResources(), R.drawable.result_btn_03),Config.RESULT_BUTTON_VFA_WIDTH, Config.RESULT_BUTTON_VFA_HEIGHT);
		Config.RESULT_BUTTON_VITALIFY_SWEEL = Common.ScaleBitmap(BitmapFactory.decodeResource(mContext.getResources(), R.drawable.result_btn_03_hl),Config.RESULT_BUTTON_VFA_WIDTH, Config.RESULT_BUTTON_VFA_HEIGHT);
		
	}
	
	/**
	 * Scale bitmap to new size
	 * 
	 * @param bm
	 * @param width
	 * @param height
	 * @return
	 */
	public static Bitmap ScaleBitmap(Bitmap bm, float width, float height) {
		Bitmap result = null;
		if (bm == null) {
			return null;
		}

		Matrix matrix = new Matrix();
		int w = bm.getWidth();
		int h = bm.getHeight();
		float resizeScaleWidth = width / w;
		float resizeScaleHeight = height / h;
		
		if(resizeScaleWidth == 1 && resizeScaleHeight == 1)
			return bm;
		
		matrix.postScale(resizeScaleWidth, resizeScaleHeight);

		result = Bitmap.createBitmap(bm, 0, 0, w, h, matrix, true);
		return result;
	}
	/**
	 * Link to market
	 * @param activity - Activity 
	 * @param developerId - id of deverloper
	 */
	public static void linkToMarket(Activity activity, String developerId){
		Intent intent = new Intent(Intent.ACTION_VIEW);
		String url = String.format("market://search?q=%s&c=apps", developerId);
		
		intent.setData(Uri.parse(url));
		activity.startActivity(intent);
	}
	/**
	 * Init Score Center
	 * @param mContext
	 */
	public static void initScoreCenter(Context mContext) {
		Config.scoreCenter = ScoreCenter.getInstance();
		Config.scoreCenter.initialize(mContext);
		Config.scoreCenter.setLogEnable(true);
		Config.scoreCenter.setKeepViewCacheEnable(true);

		// welcome
		Config.scoreCenter.hello();
	}
	
	/**
	 * Init Hight Score Local
	 * @param mContext
	 */
	public static void initHighScoreLocal(Context mContext){
		Object db = Common.getObjFromInternalFile(mContext, Config.score_file_save);;
		if(db == null){
			int[] highScore = new int[5];
			for(int i = 0; i < 5 ; i ++){
				highScore[i] = 0;
			}
			Common.writeFileToInternal(mContext, Config.score_file_save, highScore);
		}
	}

	/**
	 * Send Score To Score Center 
	 * @param mContext
	 * @param score
	 */
	public static void sendScore(int score) {
		if(Config.scoreCenter == null){
			Config.scoreCenter = ScoreCenter.getInstance();
		}
		
		try {
			Config.scoreCenter.postScore(Config.scoreboard_id, java.lang.String.valueOf(score));
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	/**
	 * Get Score with score board id
	 * @param nameId
	 */
	public static void getScore(String nameId) {
		Config.scoreCenter.show(nameId);
	}

	/**
	 * Get all score
	 */
	public static void getScore() {
		Config.scoreCenter.show(Config.scoreboard_id);
	}

	/**
	 * Set value type String into preference
	 * 
	 * @param context
	 * @param value
	 */
	public static void SetPreferByString(Context context, String key,
			String value) {
		SharedPreferences mPrefer = PreferenceManager
				.getDefaultSharedPreferences(context);
		Editor editor = mPrefer.edit();
		editor.putString(key, value);
		editor.commit();
	}

	/**
	 * Get value by String type from preference
	 * 
	 * @param context
	 * @return
	 */
	public static String GetPreferByString(Context context, String key) {
		SharedPreferences mPrefer = PreferenceManager
				.getDefaultSharedPreferences(context);
		return mPrefer.getString(key, "");
	}

	/**
	 * Set value int type into preference
	 * 
	 * @param context
	 * @param value
	 */
	public static void SetPreferByInt(Context context, String key, int value) {
		SharedPreferences mPrefer = PreferenceManager
				.getDefaultSharedPreferences(context);
		Editor editor = mPrefer.edit();
		editor.putInt(key, value);
		editor.commit();
	}

	/**
	 * Get value by int type from preference
	 * 
	 * @param context
	 * @return
	 */
	public static int GetPreferByInt(Context context, String key) {
		SharedPreferences mPrefer = PreferenceManager
				.getDefaultSharedPreferences(context);
		return mPrefer.getInt(key, -1);
	}

	/**
	 * Get value by int type from preference
	 * 
	 * @param context
	 * @param key
	 * @param defValue
	 * @return
	 */
	public static int GetPreferByInt(Context context, String key, int defValue) {
		SharedPreferences mPrefer = PreferenceManager
				.getDefaultSharedPreferences(context);
		return mPrefer.getInt(key, defValue);
	}

	/**
	 * Set value boolean type into preference
	 * 
	 * @param context
	 * @param key
	 * @param value
	 */
	public static void SetPreferByBoolean(Context context, String key,
			boolean value) {
		SharedPreferences mPrefer = PreferenceManager
				.getDefaultSharedPreferences(context);
		Editor editor = mPrefer.edit();
		editor.putBoolean(key, value);
		editor.commit();
	}

	/**
	 * Get value by boolean type from preference
	 * 
	 * @param context
	 * @return
	 */
	public static boolean GetPreferByBoolean(Context context, String key) {
		SharedPreferences mPrefer = PreferenceManager.getDefaultSharedPreferences(context);
		return mPrefer.getBoolean(key, false);
	}
	
	/**
	 * write File to internal storage
	 * 
	 * @param context
	 * @param fileName
	 * @param data
	 * 
	 * @return boolean : true is write file success
	 * 
	 */
	public static synchronized boolean writeFileToInternal(Context context, String fileName, Object data) {
		FileOutputStream fos;
		try {
			fos = context.openFileOutput(fileName, Context.MODE_PRIVATE);
			ObjectOutputStream os = new ObjectOutputStream(fos);
			os.writeObject(data);
			os.close();

			return true;
		} catch (FileNotFoundException e) {
			return false;
		} catch (IOException e) {
			return false;
		} catch (Exception e) {
			return false;
		}
	}

	/**
	 * get object data from file
	 * 
	 * @param context
	 * @param fileName
	 * 
	 * @return object from file
	 */
	public static Object getObjFromInternalFile(Context context, String fileName) {
		try {
			InputStream fis = context.openFileInput(fileName);
			ObjectInputStream is = new ObjectInputStream(fis);
			Object result = is.readObject();
			is.close();
			return result;
		} catch (Exception e) {
			return null;
		}
	}

	/**
	 * Delete cache total history file
	 * 
	 * @param mContext
	 * @param fileName
	 */
	public static void deleteFileFromInternal(Context mContext, String fileName) {
		try {
			mContext.deleteFile(fileName);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	/**
	 * @param scoreArray
	 * @param newScore
	 * @return is new high score on top 5
	 */
	public static boolean isHighScore(int[] scoreArray, int newScore){
		int pos = scoreArray.length;
		for(int i = 0; i < scoreArray.length ; i++){
			if(newScore >= scoreArray[i]){
				pos = i;
				break;
			}
		}
		if(pos == scoreArray.length)
			return false;
		
		for (int i = scoreArray.length - 1; i >= pos + 1; i--) {
			scoreArray[i] = scoreArray[i - 1];
		}
		scoreArray[pos] = newScore;
		
		return true;
	}
}
