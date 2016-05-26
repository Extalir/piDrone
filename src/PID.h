#include <wiringPi.h>
#include <stdlib.h>

class PIDQuad
{
  private:
    float filter;
    int Hz;
  public:
    float sampleTime;

    struct var_PID
    {
      float Kp, Ki, Kd;
      float Iterm, Imax, lastInput, lastDinput;
      float outPut;
      float setPoint;
      float outMax;
      unsigned long lastTime;
    };
    PIDQuad(void);
    bool resetPID(struct var_PID* PID);
    void LowResetPID(struct var_PID* PID);
    bool initPID(struct var_PID* PID, float kp, float ki, float kd, float setpoint, float imax, float outmax);
    void CalculatePID(struct var_PID* PID, float SetPoint, double MyInput);
    ~PIDQuad(void);
};
