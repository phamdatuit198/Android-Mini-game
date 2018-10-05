package jp.vfja.android.homerun.configs;

import jp.maru.scorecenter.ScoreCenter;
import android.graphics.Bitmap;
import android.graphics.Typeface;

/**
 * 
 * @author LINHDN
 * 
 */
public class Config {
	// font use for ranking screen
	public static Typeface fontRanking;

	// Register depend on App
	public static final String scoreboard_id = "jp.vfja.android.homerun.highscore";

	// Register depend on App
	public static final String _MEDIA_CODE = "jp.vfja.android.PORz";

	// high score local file
	public static final String score_file_save = "highScore.dat";
	
	public static final int NEND_ADV_ID = 52032;
	public static final String NEND_ADV_API_KEY = "2f93370034c8d55479c161a2131721a76b57317b";
	public static final String DEVELOPER_ID = "vitalify.inc";
	
	
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
	public static Bitmap TOP_COMMON_BACKGROUND2 = null;
	public static Bitmap RANKING_NUMBER[] = new Bitmap[5];
	public static Bitmap RANKING_POINT = null;
	public static Bitmap RANKING_BACK_BUTTON = null;
	public static Bitmap RANKING_SCORE_CENTER_BUTTON = null;
	public static Bitmap RANKING_BACK_BUTTON_SWEEL = null;
	public static Bitmap RANKING_SCORE_CENTER_BUTTON_SWEEL = null;
	public static Bitmap MANUAL_BG = null;

	public static int SCREEN_WIDTH;
	public static int SCREEN_HEIGHT;
	public static int TOP_TITLE_WIDTH;
	public static int TOP_TITLE_HEIGHT;
	public static int TOP_LOGO_WIDTH;
	public static int TOP_LOGO_HEIGHT;
	public static int TOP_BUTTON_WIDTH;
	public static int TOP_BUTTON_HEIGHT;
	public static int TOP_BUTTON_WIDTH_VFA;
	public static int TOP_TITLE_Y;
	public static int GAME_TITLE_Y;
	public static int GAME_TITLE_WIDTH;
	public static int GAME_TITLE_HEIGHT;
	public static int TOP_START_X;
	public static int TOP_START_Y;
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
	public static int RANKING_NUMBER_WIDTH;
	public static int RANKING_NUMBER_HEIGH;
	public static int RANKING_POINT_WIDTH;
	public static int RANKING_POINT_HEIGH;
	public static int RANKING_BACK_WIDTH;
	public static int RANKING_BACK_HEIGH;
	public static int RANKING_BACK_X;
	public static int RANKING_BACK_Y;
	public static int RANKING_CENTER_WIDTH;
	public static int RANKING_CENTER_HEIGH;
	public static int RANKING_CENTER_X;
	public static int RANKING_CENTER_Y;

	public static int MANUAL_WIDTH;
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
	public static Bitmap RESULT_BUTTON_RESTART_SWEEL = null;
	public static Bitmap RESULT_BUTTON_TOP_SWEEL = null;
	public static Bitmap RESULT_BUTTON_VITALIFY = null;
	public static Bitmap RESULT_BUTTON_VITALIFY_SWEEL = null;
	public static int RESULT_IMG_RANKIN_HEIGHT = 29;
	public static int RESULT_IMG_RANKIN_WIDTH = 148;
	public static int RESULT_IMG_TITLE_HEIGHT = 57;
	public static int RESULT_IMG_TITLE_WIDTH = 109;
	public static int RESULT_IMG_TEXT_TOTAL_HEIGHT = 40;
	public static int RESULT_IMG_TEXT_TOTAL_WIDTH = 152;
	public static int RESULT_IMG_TEXT_POINT_HEIGHT = 33;
	public static int RESULT_IMG_TEXT_POINT_WIDTH = 33;
	public static int RESULT_BUTTON_RESTART_HEIGHT = 90;
	public static int RESULT_BUTTON_RESTART_WIDTH = 300;
	public static int RESULT_BUTTON_TOP_HEIGHT = 90;
	public static int RESULT_BUTTON_TOP_WIDTH = 300;
	public static int RESULT_BUTTON_VFA_HEIGHT = 90;
	public static int RESULT_BUTTON_VFA_WIDTH = 300;
	public static int RESULT_VFA_Y;
	public static int RESULT_IMG_TEXTVIEW_HEIGHT = 50;
	public static int RESULT_IMG_TEXTVIEW_WIDTH = 200;
	public static int RESULT_IMG_POINT_WIDTH = 200;
	// DATPV
	public static final int PERIOD_NUMBER = 20;
	public static String SCORE_SUM = "SCORE_SUM";
	//public static Bitmap RANKING_BACKGROUND = null;
	public static Bitmap RESULT_BACKGROUND = null;
	public static Bitmap RANKIN_BACKGROUND = null;
	public static Bitmap MANUAL_BACKGROUND = null;
	public static int  WIDTH_DEVICE = 720;
	public static int HEIGHT_DEVICE = 1280;
	
	public static int TOP_START1_X;
	public static int TOP_START2_X;
	public static int TOP_START3_X;
	
	
	public static String TRACKER_ID = "UA-41271131-11";
	public static String SPLASH_SCREEN = "splash";
	public static String TOP_SCREEN = "top";
	public static String RANKIN_SCREEN = "ranking";
	public static String MANUAL_SCREEN = "howto";
	public static String INFO_SCREEN = "info";
	public static String GAME_SCREEN = "play";
	public static String RESULT_SCREEN = "result";

	public static String GA_TOP_PLAY_BTN = "play_cl";
	public static String GA_TOP_RANKIN_BTN = "ranking_cl";
	public static String GA_TOP_MANUAL_BTN = "howto_cl";
	public static String GA_TOP_INFO_BTN = "info_cl";
	public static String GA_TOP_VFA_BTN = "games_cl";
	public static String GA_TOP_TWITTER_BTN = "twitter_cl";
	public static String GA_TOP_REVIEW_BTN = "review_cl";
	public static String GA_RESULT_REPLAY_BTN = "replay_cl";
	public static String GA_RESULT_TOP_BTN = "top_cl";
	public static String GA_RESULT_VFA_BTN = "games_cl";
	public static String GA_RESULT_TWITTER_BTN = "twitter_cl";
	public static String GA_RANKIN_BACK_BTN = "back_cl";
	public static String GA_RANKIN_SCORE_CENTER_BTN = "wr_cl";
	public static String GA_ADS_ASTA = "ad_asta_cl";
	public static String GA_ADS_APPBANK = "ad_apb_cl";
	public static String GA_ADS_GAME_FEAT = "ad_gf_cl";
	public static String GA_ADS_BEAD = "ad_bead_cl";
}
