package jp.vfja.android.NumberGame3.gui;

import android.content.Context;
import android.graphics.Bitmap;

public class Res {
	
	public Context context;
	public Bitmap mBgSplashScreen = null;
	public Bitmap [] logo = null;
	
	public Res(Context context)
	{
		this.context=context;
	}
	public void onLoadSplashScreen()
	{
		// AssetManager assetManager = context.getAssets();
		// InputStream istr;
		// try {
		// // istr = assetManager.open("ga.png");
		// // mBgSplashScreen = BitmapFactory.decodeStream(istr);
		// logo = new Bitmap[9];
		// for(int i=0;i<logo.length;i++)
		// {
		// istr = assetManager.open("blanket000"+(i+1)+".png");
		// logo[i]=BitmapFactory.decodeStream(istr);
		// istr.close();
		// istr=null;
		// }
		// } catch (Exception e) {
		// e.printStackTrace();
		// }
	}
	
	public void clearSplashScreen()
	{
		
		
	}
}
