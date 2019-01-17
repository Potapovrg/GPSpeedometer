#include "Simple_distance.h"

const int32_t DEGREE = 600000;

int32_t Diff (int32_t deg1, int32_t deg2) {
  int32_t result = deg2 - deg1;
  if (result > 180 * DEGREE) return result - 360 * DEGREE;
  else if (result < -180 * DEGREE) return result + 360 * DEGREE;
  else return result;
}

uint32_t CosFix (int32_t angle) {
  uint32_t u = labs(angle)>>16;
  u = (u * u * 6086)>>24;
  return 246 - u;
}

uint32_t DistanceBetween (Position *p1, Position *p2) {
	uint32_t result;
  int32_t dx = (Diff(p2->Lon, p1->Lon) * CosFix((p1->Lat + p2->Lat)/2)) / 256;
  int32_t dy = Diff(p2->Lat, p1->Lat);
  uint32_t adx = labs(dx);
  uint32_t ady = labs(dy);
  uint32_t b = max(adx, ady);
  uint32_t a = min(adx, ady);
  if (b == 0) return 0;
  result = 95 * (b + (110 * a / b * a + 128) / 256) / 512;
	return result;
}