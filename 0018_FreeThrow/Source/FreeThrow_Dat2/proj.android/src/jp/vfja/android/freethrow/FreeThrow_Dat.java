/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
 ****************************************************************************/
package jp.vfja.android.freethrow;

import jp.vfja.android.freethrow.configs.Common;
import jp.vfja.android.freethrow.configs.Config;
import jp.vfja.android.freethrow.ndkhelper.AndroidNDKHelper;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.json.JSONException;
import org.json.JSONObject;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;

public class FreeThrow_Dat extends Cocos2dxActivity {
	protected View nEndAdView;
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		AndroidNDKHelper.SetNDKReciever(this);
		nEndAdView =getLayoutInflater().inflate(R.layout.ads,null);
		this.framelayout.addView(nEndAdView);
	}

	static {
		System.loadLibrary("game");
	}

	public void endGame(JSONObject prms) {
		Log.d("DATPV-------------", "FINISH");
		String CPPFunctionToBeCalled = null;
		try {
			CPPFunctionToBeCalled = prms.getString("score");
		} catch (JSONException e) {
			e.printStackTrace();
		}
		goToResult(Integer.parseInt(CPPFunctionToBeCalled));
	}

	private void goToResult(int finalPoint) {
		Common.initSizeForResultScreen(Config.ratioX, Config.ratioY);
		Common.initBitmapForResult(this);
		Intent i = new Intent(getApplicationContext(), ResultActivity.class);
		i.putExtra("finalPoint", finalPoint + "");
		startActivity(i);
		finish();
	}
}
