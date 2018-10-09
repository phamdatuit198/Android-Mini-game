package jp.vfja.android.NumberGame3.common;

import java.util.Random;

public class RandomUtilities {

	public static int randomTypeEgg() {
		Random random = new Random();
		int min = 0;
		int max = 100;
		int randomNum = random.nextInt(max - min + 1) + min;
		if (randomNum <= Constant.GOLD_RATIO) {
			return 1;
		} else {
			return 0;
		}
	}

	public static int randomHatchingChicken() {
		Random random = new Random();
		int min = 1;
		int max = 100;
		int randomNum = random.nextInt(max - min + 1) + min;
		return randomNum;
	}
}
