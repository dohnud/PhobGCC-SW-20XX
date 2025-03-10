#ifndef ENUMS_H
#define ENUMS_H

enum JumpConfig {
	DEFAULTJUMP,
	SWAP_XZ,
	SWAP_YZ,
	SWAP_XL,
	SWAP_YL,
	SWAP_XR,
	SWAP_YR
};

enum WhichTrigger {
	LTRIGGER,
	RTRIGGER
};

enum Increase {
	INCREASE,
	DECREASE
};

enum WhichAxis {
	XAXIS,
	YAXIS
};

enum WhichStick {
	ASTICK,
	CSTICK
};

enum HardReset {
	HARD,
	SOFT,
	FACTORY
};

enum NotchStatus {
	TERT_INACTIVE,
	TERT_ACTIVE,
	SECONDARY,
	CARDINAL
};

enum ExtrasSlot{
	EXTRAS_UP,
	EXTRAS_DOWN,
	EXTRAS_LEFT,
	EXTRAS_RIGHT,
	EXTRAS_SIZE,
	EXTRAS_UNSET
};

union IntOrFloat{
	int intValue;
	float floatValue;
};

struct ExtrasConfig{
	IntOrFloat config[4];
};

struct Pins{
	int pinLa;
	int pinRa;
	int pinL;
	int pinR;
	int pinAx;
	int pinAy;
	int pinCx;
	int pinCy;
	int pinRX;
	int pinTX;
	int pinDr;
	int pinDu;
	int pinDl;
	int pinDd;
	int pinX;
	int pinY;
	int pinA;
	int pinB;
	int pinZ;
	int pinS;
};

union Buttons{
	uint8_t arr[10];
	struct {

		// byte 0
		uint8_t A : 1;
		uint8_t B : 1;
		uint8_t X : 1;
		uint8_t Y : 1;
		uint8_t S : 1;
		uint8_t orig : 1;
		uint8_t errL : 1;
		uint8_t errS : 1;

		// byte 1
		uint8_t Dl : 1;
		uint8_t Dr : 1;
		uint8_t Dd : 1;
		uint8_t Du : 1;
		uint8_t Z : 1;
		uint8_t R : 1;
		uint8_t L : 1;
		uint8_t high : 1;

		//byte 2-7
		uint8_t Ax : 8;
		uint8_t Ay : 8;
		uint8_t Cx : 8;
		uint8_t Cy : 8;
		uint8_t La : 8;
		uint8_t Ra : 8;

		// magic byte 8 & 9 (only used in origin cmd)
		// have something to do with rumble motor status???
		// ignore these, they are magic numbers needed
		// to make a cmd response work
		uint8_t magic1 : 8;
		uint8_t magic2 : 8;
	};
	struct {
		uint16_t buttons : 16;
		uint8_t astickX : 8;
		uint8_t astickY : 8;
		uint8_t cstickX : 8;
		uint8_t cstickY : 8;
		uint8_t _La : 8;
		uint8_t _Ra : 8;
		uint8_t m1 : 8;
		uint8_t m2 : 8;
	};
  Buttons (uint16_t btn_field=0, uint8_t AX=0, uint8_t AY=0, uint8_t CX=0, uint8_t CY=0, uint8_t LA=0, uint8_t RA=0) :
    buttons(btn_field),
    astickX(AX), astickY(AY),
	cstickX(CX), cstickY(CY),
    _La(LA), _Ra(RA),
    m1(0), m2(0)
  {}
};

#define __FRAMEDURATION 16666.667
#define __FRAMEOFFSET 1000
//               byte 1  byte 0
#define LL_MAX 0b1111111111111111
#define BTN_S  0b0000000000010000
#define BTN_Y  0b0000000000001000
#define BTN_X  0b0000000000000100
#define BTN_B  0b0000000000000010
#define BTN_A  0b0000000000000001
#define BTN_Z  0b0001000000000000
#define TRG_R  0b0010000000000000
#define TRG_L  0b0100000000000000
#define CRD_U  0b0000100000000000
#define CRD_D  0b0000010000000000
#define CRD_R  0b0000001000000000
#define CRD_L  0b0000000100000000


struct _EVIL {
  const unsigned long long duration;
  const Buttons holdmetight;
  
  _EVIL (long long dur=0, Buttons btns=Buttons()):
    duration(dur),
    holdmetight(btns)
  {}
};

struct _REALLY_EVIL {
  const Buttons secret_handshake;
  const int evil_factor;
  const _EVIL mwahahahah[16];
};


const _REALLY_EVIL hoho {
	.secret_handshake = Buttons(TRG_R | BTN_B),
	.evil_factor = 3,
  .mwahahahah = {
      _EVIL(2, Buttons(BTN_X | BTN_Y)),
      _EVIL(3, Buttons()),
      _EVIL(7+2, Buttons(BTN_B))
    }
};

const _REALLY_EVIL wowo {
	.secret_handshake = Buttons(TRG_R | BTN_A),
	.evil_factor = 2,
  .mwahahahah = {
      _EVIL(2, Buttons(BTN_X | BTN_Y)),
      _EVIL(40, Buttons()),
    }
};

// FOX MULTISHINE
const _REALLY_EVIL hehe {
  .secret_handshake = Buttons(TRG_L | BTN_B),
  .evil_factor = 3,
  .mwahahahah = {
    _EVIL(2, Buttons(BTN_Y)),
    _EVIL(1, Buttons()),
    _EVIL(6+2, Buttons(BTN_B)),
  }
};

#define PANDORAS_FAVORITE_NUMBER 3
const _REALLY_EVIL* PANDORAS_BOX[PANDORAS_FAVORITE_NUMBER] = {
  &wowo,
  &hoho,
  &hehe
};

struct HardwareButtons{
	uint8_t L;
	uint8_t R;
	uint8_t Z;
	uint8_t X;
	uint8_t Y;
};

struct Cardinals{
	uint8_t l : 1;
	uint8_t r : 1;
	uint8_t u : 1;
	uint8_t d : 1;
};

struct ControlConfig{
	JumpConfig jumpConfig;
	const int jumpConfigMin;
	const int jumpConfigMax;
	int lConfig;
	int rConfig;
	const int triggerConfigMin;
	const int triggerConfigMax;
	const int triggerDefault;
	int lTriggerOffset;
	int rTriggerOffset;
	const int triggerMin;
	const int triggerMax;
	int cXOffset;
	int cYOffset;
	const int cMax;
	const int cMin;
	int rumble;//0 is off, nonzero is on, higher is stronger
	const int rumbleMin;
	const int rumbleMax;
	const int rumbleDefault;
	bool safeMode;
	int autoInit;
	int lTrigInitial;
	int rTrigInitial;
	int xSnapback;//0 disables the filter entirely, 4 is default
	int ySnapback;
	const int snapbackMin;
	const int snapbackMax;
	const int snapbackDefault;
	const int snapbackFactoryAX;
	const int snapbackFactoryAY;
	const float smoothingMin;
	const float smoothingMax;
	const float snapbackFactoryCX;
	const float snapbackFactoryCY;
	const float smoothingFactoryAX;
	const float smoothingFactoryAY;
	int axWaveshaping;
	int ayWaveshaping;
	int cxWaveshaping;
	int cyWaveshaping;
	const int waveshapingMin;
	const int waveshapingMax;
	const float waveshapingFactoryAX;
	const float waveshapingFactoryAY;
	const float waveshapingFactoryCX;
	const float waveshapingFactoryCY;
	ExtrasConfig extras[EXTRAS_SIZE];
};

struct FilterGains {
	//What's the max stick distance from the center
	float maxStick;
	//filtered velocity terms
	//how fast the filtered velocity falls off in the absence of stick movement.
	//Probably don't touch this.
	float xVelDecay;//0.1 default for 1.2ms timesteps, larger for bigger timesteps
	float yVelDecay;
	//how much the current position disagreement impacts the filtered velocity.
	//Probably don't touch this.
	float xVelPosFactor;//0.01 default for 1.2ms timesteps, larger for bigger timesteps
	float yVelPosFactor;
	//how much to ignore filtered velocity when computing the new stick position.
	//DO CHANGE THIS
	//Higher gives shorter rise times and slower fall times (more pode, less snapback)
	float xVelDamp;//0.125 default for 1.2ms timesteps, smaller for bigger timesteps
	float yVelDamp;
	//speed and accel thresholds below which we try to follow the stick better
	//These may need tweaking according to how noisy the signal is
	//If it's noisier, we may need to add additional filtering
	//If the timesteps are *really small* then it may need to be increased to get
	//  above the noise floor. Or some combination of filtering and playing with
	//  the thresholds.
	float velThresh;//1 default for 1.2ms timesteps, larger for bigger timesteps
	float accelThresh;//5 default for 1.2ms timesteps, larger for bigger timesteps
	//This just applies a low-pass filter.
	//The purpose is to provide delay for single-axis ledgedashes.
	//Must be between 0 and 1. Larger = more smoothing and delay.
	float xSmoothing;
	float ySmoothing;
	//Same thing but for C-stick
	float cXSmoothing;
	float cYSmoothing;
};

Buttons _btn;

Buttons _hardware;

int _rumblePower = 0;//just so it isn't uninitialized at startup

#endif //ENUMS_H
