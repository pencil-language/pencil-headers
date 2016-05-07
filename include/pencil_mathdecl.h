#ifndef PENCIL_MATHDECLS_H
#define PENCIL_MATHDECLS_H

static int32_t abs32(int32_t x);
static int64_t abs64(int64_t x);

static int min(int x, int y);
static long lmin(long x, long y);
//static long long llmin(long long x, long long y);
static int32_t min32(int32_t x, int32_t y);
static int64_t min64(int64_t x, int64_t y);

static int max(int x, int y);
static long lmax(long x, long y);
//static long long llmax(long long x, long long y);
static int32_t max32(int32_t x, int32_t y);
static int64_t max64(int64_t x, int64_t y);

static int clamp(int x, int minval, int maxval);
static long lclamp(long x, long minval, long maxval);
//long long llclamp(long long x, long long minval, long long maxval);
static int32_t clamp32(int32_t x, int32_t minval, int32_t maxval);
static int64_t clamp64(int64_t x, int64_t minval, int64_t maxval);
static double fclamp(double x, double minval, double maxval);
static float fclampf(float x, float minval, float maxval);

static double mix(double x, double y, double a);
static float mixf(float x, float y, float a);

static double atan2pi(double x, double y);
static float atan2pif(float x, float y);

#endif /* PENCIL_MATHDECLS_H */
