package jp.vfja.android.NumberGame3.common;

import jp.maru.scorecenter.ScoreCenter;
import android.graphics.Bitmap;
import android.graphics.Typeface;
/**
 *
 * @author DAT PHAM
 *
 */
public class Config {
	// font use for ranking screen
	public static Typeface fontRanking;

	// Register depend on App
	public static final String scoreboard_id = "jp.vfja.android.NumberGame3.highscore";

	// Register depend on App
	public static final String _MEDIA_CODE = "jp.vfja.android.Pv2M";

	public static final int NEND_ADV_ID = 49044;
	public static final String NEND_ADV_API_KEY = "a65d3f95894266bbd9c71a3a7de1dffb12c74e2b";
	public static final String DEVELOPER_ID = "vitalify.inc";

	//high score local file
	public static final String score_file_save = "highScore.dat";

	public static float ratioX;
	public static float ratioY;

	public static Bitmap SPLASH_LOGO = null;
	public static Bitmap INFO_BACKGROUND = null;
	public static Bitmap TOP_BACKGROUND_MIDDLE = null;
	public static Bitmap TOP_TITLE = null;
	public static Bitmap GAME_TITLE = null;
	public static Bitmap TOP_BUTTON_VFA = null;
	public static Bitmap TOP_BUTTON_PLAY = null;
	public static Bitmap TOP_BUTTON_RANKIN = null;
	public static Bitmap TOP_BUTTON_MANUAL = null;
	public static Bitmap TOP_BUTTON_INFO = null;
	public static Bitmap TOP_BUTTON_VFA_SWEEL = null;
	public static Bitmap TOP_BUTTON_PLAY_SWEEL = null;
	public static Bitmap TOP_BUTTON_RANKIN_SWEEL = null;
	public static Bitmap TOP_BUTTON_MANUAL_SWEEL = null;
	public static Bitmap TOP_BUTTON_INFO_SWEEL = null;


	public static Bitmap TOP_COMMON_BACKGROUND = null;
	public static Bitmap RANKING_NUMBER[] = new Bitmap[5];
	public static Bitmap RANKING_POINT = null;
	public static Bitmap RANKING_BACK_BUTTON = null;
	public static Bitmap RANKING_SCORE_CENTER_BUTTON = null;
	public static Bitmap RANKING_BACK_BUTTON_WHEEL = null;
	public static Bitmap RANKING_SCORE_CENTER_BUTTON_WHEEL = null;
	public static Bitmap MANUAL_BG = null;

	public static int SCREEN_WIDTH;
	public static int SCREEN_HEIGHT;
	public static int TOP_TITLE_WIDTH;
	public static int TOP_TITLE_HEIGHT;
	public static int TOP_LOGO_WIDTH ;
	public static int TOP_LOGO_HEIGHT;
	public static int TOP_BUTTON_WIDTH;
	public static int TOP_BUTTON_HEIGHT;
	public static int TOP_TITLE_Y;
	public static int GAME_TITLE_WIDTH;
	public static int GAME_TITLE_HEIGHT;
	public static int TOP_START_X;
	public static int TOP_START_Y ;
	public static int TOP_RANKING_Y;
	public static int TOP_MANUAL_Y;
	public static int TOP_INFO_Y;
	public static int TOP_VFA_Y;

	public static int RANKING_SCORES_X;
	public static int RANKING_SCORES_Y;
	public static int RANKING_SCORES_LINE_X;
	public static int RANKING_SCORES_LINE_Y;
	public static int RANKING_SCORES_LINE_WIDTH;
	public static int RANKING_SCORES_LINE_HEIGH;
	public static int RANKING_NUMBER_WIDTH ;
	public static int RANKING_NUMBER_HEIGH;
	public static int RANKING_POINT_WIDTH ;
	public static int RANKING_POINT_HEIGH ;
	public static int RANKING_BACK_WIDTH ;
	public static int RANKING_BACK_HEIGH;
	public static int RANKING_BACK_X;
	public static int RANKING_BACK_Y;
	public static int RANKING_CENTER_WIDTH ;
	public static int RANKING_CENTER_HEIGH;
	public static int RANKING_CENTER_X;
	public static int RANKING_CENTER_Y;

	public static int MANUAL_WIDTH ;
	public static int MANUAL_HEIGHT;
	public static int MANUAL_X;
	public static int MANUAL_Y;
	public static int MANUAL_STRING_X;
	public static int MANUAL_STRING_Y;

	public static ScoreCenter scoreCenter;

	/*
	 * Resource in result screen
	 */
	 public static Bitmap RESULT_IMG_RANKIN = null;
	 public static Bitmap RESULT_IMG_TITLE = null;
	 public static Bitmap RESULT_IMG_TEXT_TOTAL = null;
	 public static Bitmap RESULT_IMG_TEXT_POINT = null;
	 public static Bitmap RESULT_BUTTON_RESTART = null;
	 public static Bitmap RESULT_BUTTON_TOP = null;
	 public static Bitmap RESULT_BUTTON_RESTART_WHEEL = null;
	 public static Bitmap RESULT_BUTTON_TOP_WHEEL = null;

	 public static int RESULT_IMG_RANKIN_HEIGHT;
	 public static int RESULT_IMG_RANKIN_WIDTH;
	 public static int RESULT_IMG_TITLE_HEIGHT;
	 public static int RESULT_IMG_TITLE_WIDTH;
	 public static int RESULT_IMG_TEXT_TOTAL_HEIGHT;
	 public static int RESULT_IMG_TEXT_TOTAL_WIDTH;
	 public static int RESULT_IMG_TEXT_POINT_HEIGHT;
	 public static int RESULT_IMG_TEXT_POINT_WIDTH;
	 public static int RESULT_BUTTON_RESTART_HEIGHT;
	 public static int RESULT_BUTTON_RESTART_WIDTH;
	 public static int RESULT_BUTTON_TOP_HEIGHT;
	 public static int RESULT_BUTTON_TOP_WIDTH;

}
