package jp.vfja.android.freethrow;





import jp.vfja.android.freethrow.configs.Config;
import jp.vfja.android.freethrow.view.Image;
import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.graphics.Point;
import android.net.Uri;
import android.os.Bundle;
import android.text.Html;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.View.OnTouchListener;
import android.view.Window;
import android.view.WindowManager;
import android.widget.RelativeLayout;
import android.widget.RelativeLayout.LayoutParams;
import android.widget.TextView;

/**
 * InfoActivity
 * @author LINHDN
 *
 */
public class InfoActivity extends Activity {
	String info1 = "We will be No.1 Mobile Software company in the world.\n " +
	"- IT Outsource/Offshore Development In Vietnam.\n " +
	"- We are strong about IT and focus on Developing apps for smartphone.\n\n";
	
	String url1r = "http://vitalify.jp/";
	String url2r = "http://www.vitalify.asia/";
	String url1 = "<a href = \"\">http://vitalify.jp/</a>";
	String url2 = "<a href = \"\">http://www.vitalify.asia/</a>";
	private Context mContext;
	private RelativeLayout parent;
	private Image mBackground;
	private Point backgroundPos;
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		requestWindowFeature(Window.FEATURE_NO_TITLE);
		getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
				WindowManager.LayoutParams.FLAG_FULLSCREEN);
		setContentView(R.layout.activity_info);
		initResource();
	}

	private void initResource() {
		mContext = this;
		parent = (RelativeLayout) findViewById(R.id.parent);
		
		backgroundPos = new Point(0,(Config.SCREEN_HEIGHT - Config.TOP_LOGO_HEIGHT)/2 );
		mBackground = new Image(mContext, backgroundPos.x, backgroundPos.y, Config.TOP_LOGO_HEIGHT, Config.TOP_LOGO_WIDTH, Config.INFO_BACKGROUND);
		
		parent.addView(mBackground);
		
		TextView infoContentTv = new TextView(getApplicationContext());
		LayoutParams lp = new LayoutParams((int)(510*Config.ratioX), (int)(260*Config.ratioX));
		lp.leftMargin = (int) ((Config.SCREEN_WIDTH - 510*Config.ratioX)/2);
		lp.topMargin = (int) (Config.SCREEN_HEIGHT/2 - 15*Config.ratioX);
		infoContentTv.setLayoutParams(lp);
		parent.addView(infoContentTv);
		infoContentTv.setText(info1);
		
		TextView infoUrl1Tv = new TextView(getApplicationContext());
		LayoutParams lp1 = new LayoutParams(LayoutParams.WRAP_CONTENT, (int)(46*Config.ratioX));
		lp1.leftMargin = (int) ((Config.SCREEN_WIDTH - 510*Config.ratioX)/2);
		lp1.topMargin = (int) (Config.SCREEN_HEIGHT/2 + 244*Config.ratioX);
		infoUrl1Tv.setLayoutParams(lp1);
		parent.addView(infoUrl1Tv);
		infoUrl1Tv.setText(Html.fromHtml(url1));
		
		
		TextView infoUrl2Tv = new TextView(getApplicationContext());
		LayoutParams lp2 = new LayoutParams(LayoutParams.WRAP_CONTENT, (int)(46*Config.ratioX));
		lp2.leftMargin = (int) ((Config.SCREEN_WIDTH - 510*Config.ratioX)/2);
		lp2.topMargin = (int) (Config.SCREEN_HEIGHT/2 + 290*Config.ratioX);
		infoUrl2Tv.setLayoutParams(lp2);
		parent.addView(infoUrl2Tv);
		infoUrl2Tv.setText(Html.fromHtml(url2));
		
		
		infoUrl1Tv.setOnClickListener(new OnClickListener() {
			public void onClick(View v) {
				Intent i = new Intent(Intent.ACTION_VIEW);
				i.setData(Uri.parse(url1r));
				startActivity(i);
			}
		});
		
		infoUrl2Tv.setOnClickListener(new OnClickListener() {
			public void onClick(View v) {
				Intent i = new Intent(Intent.ACTION_VIEW);
				i.setData(Uri.parse(url2r));
				startActivity(i);
			}
		});
		viewTouch();
	}
	
	private void viewTouch(){
		parent.setOnTouchListener(new OnTouchListener() {
			
			@Override
			public boolean onTouch(View v, MotionEvent event) {
				if(event.getAction() == MotionEvent.ACTION_DOWN){
					finish();
				}
				return false;
			}
		});
	}
	@Override
	protected void onDestroy() {
		mBackground.stopDraw = true;
		super.onDestroy();
	}
	
}
