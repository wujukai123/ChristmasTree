#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.14159265359
 
float sx, sy;
 
float sdCircle(float px, float py, float r) { float dx = px - sx, dy = py - sy; return sqrtf(dx * dx + dy * dy) - r; }
 
float opUnion(float d1, float d2) { return d1 < d2 ? d1 : d2; }
 
#define T px + scale * r * cosf(theta), py + scale * r * sin(theta)
 
float f(float px, float py, float theta, float scale, int n) {
	float d = 0.0f;
	for (float r = 0.0f; r < 0.8f; r += 0.02f)
		d = opUnion(d, sdCircle(T, 0.05f * scale * (0.95f - r)));
	if (n > 0) {
		for (int t = -1; t <= 1; t += 2) {
			float tt = theta + t * 1.8f;
			float ss = scale * 0.9f;
			for (float r = 0.2f; r < 0.8f; r += 0.1f) {
				d = opUnion(d, f(T, tt, ss * 0.5f, n - 1));
				ss *= 0.8f;
			}
		}
	}
	return d;
}

int ribbon() {
	float x = (fmodf(sy, 0.1f) / 0.1f - 0.5f) * 0.5f;
	return sx >= x - 0.05f && sx <= x + 0.05f;
}

int main(int argc, char* argv[]) {
	int n = argc > 1 ? atoi(argv[1]) : 4;
	float zoom = argc > 2 ? atof(argv[2]) : 1.0f;
	for (sy = 0.8f; sy > 0.0f; sy -= 0.02f / zoom, putchar('\n'))
		for (sx = -0.35f; sx < 0.35f; sx += 0.01f / zoom) {
			if (f(0, 0, PI * 0.5f, 1.0f, n) < 0.0f) {
				if (sy < 0.1f) putchar('.');
				else {
					if (ribbon()) putchar('=');
					else putchar("............................#j&o"[rand() % 32]);
				}
			} else putchar(' ');
		}
    return 0;
}