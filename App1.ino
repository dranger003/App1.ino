// App1.ino
//

#define CORE_CLK                72000000
#define TIMER_CLK               24000000

#define OFF                     0x0
#define MARK                    0x4
#define SPACE                   0x0

#define REF_PIN                 A0
#define INT_PIN                 A4
#define CTL_PIN                 RX

// HW-C560S
//
namespace HWC560S
{
    const uint16_t FREQUENCY = 37773;
    const double DUTY_CYCLE = 0.37773;

    const uint8_t CODES[][2] =
    {
        { 94, 72 },     // Init
        { 16, 16 },     // 1
        { 16, 44 },     // 2
    };

    const uint8_t KEYS[][51] =
    {
        { 50,   // volume-up
            0, 2, 2, 1, 1, 1, 1, 2, 1, 2, 2, 1, 1, 2, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1,
            1, 1, 2, 1, 1, 1, 1, 1,
            1, 1, 1, 1, 1, 2, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1 },
        { 50,   // volume-down
            0, 2, 2, 1, 1, 1, 1, 2, 1, 2, 2, 1, 1, 2, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1,
            1, 1, 2, 1, 1, 1, 1, 1,
            1, 1, 1, 1, 2, 2, 1, 1, 2, 2, 2, 1, 1, 1, 1, 1, 1 },
        { 50,   // input-bddvd
            0, 2, 2, 1, 1, 1, 1, 2, 1, 2, 2, 1, 1, 2, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1,
            1, 1, 2, 1, 1, 1, 1, 1,
            1, 2, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1 },
        { 50,   // input-sat
            0, 2, 2, 1, 1, 1, 1, 2, 1, 2, 2, 1, 1, 2, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1,
            1, 1, 2, 1, 1, 1, 1, 1,
            1, 2, 1, 2, 2, 2, 2, 1, 2, 1, 2, 1, 2, 1, 1, 1, 1 },
        { 50,   // input-tv
            0, 2, 2, 1, 1, 1, 1, 2, 1, 2, 2, 1, 1, 2, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1,
            1, 1, 2, 1, 1, 1, 1, 1,
            1, 2, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1 },
        { 50,   // input-aux
            0, 2, 2, 1, 1, 1, 1, 2, 1, 2, 2, 1, 1, 2, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1,
            1, 1, 2, 1, 1, 1, 1, 1,
            2, 2, 1, 2, 2, 1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1 },
        { 50,   // power
            0, 2, 2, 1, 1, 1, 1, 2, 1, 2, 2, 1, 1, 2, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1,
            1, 1, 2, 1, 1, 1, 1, 1,
            1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1 },
        { 50,   // input-select
            0, 2, 2, 1, 1, 1, 1, 2, 1, 2, 2, 1, 1, 2, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1,
            1, 1, 2, 1, 1, 1, 1, 1,
            1, 1, 2, 1, 1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1 },
        { 50,   // audio-assign
            0, 2, 2, 1, 1, 1, 1, 2, 1, 2, 2, 1, 1, 2, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1,
            1, 1, 2, 1, 1, 1, 1, 1,
            2, 1, 1, 2, 1, 2, 1, 1, 2, 2, 2, 2, 2, 1, 1, 1, 1 },
        { 50,   // mute
            0, 2, 2, 1, 1, 1, 1, 2, 1, 2, 2, 1, 1, 2, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1,
            1, 1, 2, 1, 1, 1, 1, 1,
            1, 1, 1, 1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1 },
    };

    enum KEY : uint8_t
    {
        VOL_UP,
        VOL_DOWN,
        INPUT_BDDVD,
        INPUT_SAT,
        INPUT_TV,
        INPUT_AUX,
        POWER,
        INPUT_SELECT,
        AUDIO_ASSIGN,
        MUTE,
    };
}

// VIP2262
//
namespace VIP2262
{
    const uint16_t FREQUENCY = 36250;
    const double DUTY_CYCLE = 0.33;

    const uint8_t CODES[][2] =
    {
        { 15,   10 },   // Init
        {  6,   10 },   // 1
        {  6,   16 },   // 2
        {  6,   22 },   // 3
        {  6,   28 },   // 4
    };

    const uint8_t KEYS[][19] =
    {
    //  { 18, 0, 1, 3, 2, 2, 1, 1, 1, 1, 1, 3, 2, 3, ?, ?, ?, ?, 1 },
        { 18, 0, 1, 3, 2, 2, 1, 1, 1, 1, 1, 3, 2, 3, 1, 1, 1, 1, 1 }, // 0
        { 18, 0, 1, 3, 2, 2, 1, 1, 1, 1, 1, 3, 2, 3, 1, 1, 1, 2, 1 }, // 1
        { 18, 0, 1, 3, 2, 2, 1, 1, 1, 1, 1, 3, 2, 3, 1, 1, 1, 3, 1 }, // 2
        { 18, 0, 1, 3, 2, 2, 1, 1, 1, 1, 1, 3, 2, 3, 1, 1, 1, 4, 1 }, // 3
        { 18, 0, 1, 3, 2, 2, 1, 1, 1, 1, 1, 3, 2, 3, 1, 1, 2, 1, 1 }, // 4
        { 18, 0, 1, 3, 2, 2, 1, 1, 1, 1, 1, 3, 2, 3, 1, 1, 2, 2, 1 }, // 5
        { 18, 0, 1, 3, 2, 2, 1, 1, 1, 1, 1, 3, 2, 3, 1, 1, 2, 3, 1 }, // 6
        { 18, 0, 1, 3, 2, 2, 1, 1, 1, 1, 1, 3, 2, 3, 1, 1, 2, 4, 1 }, // 7
        { 18, 0, 1, 3, 2, 2, 1, 1, 1, 1, 1, 3, 2, 3, 1, 1, 3, 1, 1 }, // 8
        { 18, 0, 1, 3, 2, 2, 1, 1, 1, 1, 1, 3, 2, 3, 1, 1, 3, 2, 1 }, // 9
        { 18, 0, 1, 3, 2, 2, 1, 1, 1, 1, 1, 3, 2, 3, 1, 1, 3, 3, 1 }, // last
        { 18, 0, 1, 3, 2, 2, 1, 1, 1, 1, 1, 3, 2, 3, 1, 1, 4, 1, 1 }, // power
        { 18, 0, 1, 3, 2, 2, 1, 1, 1, 1, 1, 3, 2, 3, 1, 1, 4, 4, 1 }, // info
        { 18, 0, 1, 3, 2, 2, 1, 1, 1, 1, 1, 3, 2, 3, 1, 2, 1, 1, 1 }, // volume-up
        { 18, 0, 1, 3, 2, 2, 1, 1, 1, 1, 1, 3, 2, 3, 1, 2, 1, 2, 1 }, // volume-down
        { 18, 0, 1, 3, 2, 2, 1, 1, 1, 1, 1, 3, 2, 3, 1, 3, 1, 1, 1 }, // channel-up
        { 18, 0, 1, 3, 2, 2, 1, 1, 1, 1, 1, 3, 2, 3, 1, 3, 1, 2, 1 }, // channel-down
        { 18, 0, 1, 3, 2, 2, 1, 1, 1, 1, 1, 3, 2, 3, 1, 3, 3, 1, 1 }, // fast-forward
        { 18, 0, 1, 3, 2, 2, 1, 1, 1, 1, 1, 3, 2, 3, 1, 3, 3, 2, 1 }, // rewind
        { 18, 0, 1, 3, 2, 2, 1, 1, 1, 1, 1, 3, 2, 3, 1, 3, 4, 1, 1 }, // play
        { 18, 0, 1, 3, 2, 2, 1, 1, 1, 1, 1, 3, 2, 3, 1, 4, 1, 1, 1 }, // pause
        { 18, 0, 1, 3, 2, 2, 1, 1, 1, 1, 1, 3, 2, 3, 1, 4, 1, 2, 1 }, // stop
        { 18, 0, 1, 3, 2, 2, 1, 1, 1, 1, 1, 3, 2, 3, 1, 4, 2, 4, 1 }, // record
        { 18, 0, 1, 3, 2, 2, 1, 1, 1, 1, 1, 3, 2, 3, 1, 4, 3, 1, 1 }, // settings
        { 18, 0, 1, 3, 2, 2, 1, 1, 1, 1, 1, 3, 2, 3, 1, 4, 3, 2, 1 }, // favorites
        { 18, 0, 1, 3, 2, 2, 1, 1, 1, 1, 1, 3, 2, 3, 2, 1, 2, 1, 1 }, // recordings
        { 18, 0, 1, 3, 2, 2, 1, 1, 1, 1, 1, 3, 2, 3, 2, 1, 4, 1, 1 }, // forward
        { 18, 0, 1, 3, 2, 2, 1, 1, 1, 1, 1, 3, 2, 3, 2, 1, 4, 2, 1 }, // replay
        { 18, 0, 1, 3, 2, 2, 1, 1, 1, 1, 1, 3, 2, 3, 2, 2, 2, 1, 1 }, // menu
        { 18, 0, 1, 3, 2, 2, 1, 1, 1, 1, 1, 3, 2, 3, 2, 2, 2, 2, 1 }, // exit
        { 18, 0, 1, 3, 2, 2, 1, 1, 1, 1, 1, 3, 2, 3, 2, 2, 3, 1, 1 }, // up
        { 18, 0, 1, 3, 2, 2, 1, 1, 1, 1, 1, 3, 2, 3, 2, 2, 3, 2, 1 }, // down
        { 18, 0, 1, 3, 2, 2, 1, 1, 1, 1, 1, 3, 2, 3, 2, 2, 3, 3, 1 }, // left
        { 18, 0, 1, 3, 2, 2, 1, 1, 1, 1, 1, 3, 2, 3, 2, 2, 3, 4, 1 }, // right
        { 18, 0, 1, 3, 2, 2, 1, 1, 1, 1, 1, 3, 2, 3, 2, 2, 4, 1, 1 }, // select
        { 18, 0, 1, 3, 2, 2, 1, 1, 1, 1, 1, 3, 2, 3, 3, 1, 1, 4, 1 }, // back
        { 18, 0, 1, 3, 2, 2, 1, 1, 1, 1, 1, 3, 2, 3, 3, 1, 2, 3, 1 }, // search
        { 18, 0, 1, 3, 2, 2, 1, 1, 1, 1, 1, 3, 2, 3, 3, 2, 4, 3, 1 }, // delete
        { 18, 0, 1, 3, 2, 2, 1, 1, 1, 1, 1, 3, 2, 3, 4, 1, 4, 1, 1 }, // guide
        { 18, 0, 1, 3, 2, 2, 1, 1, 1, 1, 1, 3, 2, 3, 4, 3, 1, 2, 1 }, // enter
        { 18, 0, 1, 3, 2, 2, 1, 1, 1, 1, 1, 3, 2, 3, 4, 4, 1, 1, 1 }, // video-on-demand
    };

    enum KEY : uint8_t
    {
        N0,
        N1,
        N2,
        N3,
        N4,
        N5,
        N6,
        N7,
        N8,
        N9,
        LAST,
        POWER,
        INFO,
        VOL_UP,
        VOL_DOWN,
        CHNL_UP,
        CHNL_DOWN,
        FF,
        REW,
        PLAY,
        PAUSE,
        STOP,
        RECORD,
        SETTINGS,
        FAVORITES,
        RECORDINGS,
        FWD,
        REPLAY,
        MENU,
        EXIT,
        UP,
        DOWN,
        LEFT,
        RIGHT,
        SELECT,
        BACK,
        SEARCH,
        DELETE,
        GUIDE,
        ENTER,
        VOD,
    };
}

void _pwm(uint16_t pin, uint32_t frequency, double duty)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    pinMode(pin, AF_OUTPUT_PUSHPULL);

    TIM_TypeDef *p = PIN_MAP[pin].timer_peripheral;

    if (p == TIM2)
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    else if (p == TIM3)
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    else if (p == TIM4)
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

    const uint16_t TIM_ARR = (uint16_t)(TIMER_CLK / frequency) - 1;

    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure = { 0 };
    TIM_TimeBaseStructure.TIM_Period = TIM_ARR;
    TIM_TimeBaseStructure.TIM_Prescaler = (uint16_t)(CORE_CLK / TIMER_CLK) - 1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(p, &TIM_TimeBaseStructure);

    TIM_OCInitTypeDef TIM_OCInitStructure = { 0 };
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_Pulse = (uint16_t)((TIM_ARR + 1) * duty);

    if (PIN_MAP[pin].timer_ch == TIM_Channel_1) {
        TIM_OC1Init(p, &TIM_OCInitStructure);
        TIM_OC1PreloadConfig(p, TIM_OCPreload_Enable);
    }
    else if (PIN_MAP[pin].timer_ch == TIM_Channel_2) {
        TIM_OC2Init(p, &TIM_OCInitStructure);
        TIM_OC2PreloadConfig(p, TIM_OCPreload_Enable);
    }
    else if (PIN_MAP[pin].timer_ch == TIM_Channel_3) {
        TIM_OC3Init(p, &TIM_OCInitStructure);
        TIM_OC3PreloadConfig(p, TIM_OCPreload_Enable);
    }
    else if (PIN_MAP[pin].timer_ch == TIM_Channel_4) {
        TIM_OC4Init(p, &TIM_OCInitStructure);
        TIM_OC4PreloadConfig(p, TIM_OCPreload_Enable);
    }

    TIM_ARRPreloadConfig(p, ENABLE);
    TIM_Cmd(p, ENABLE);
}

volatile uint8_t _r = 0;

const uint8_t (*_pcs)[2] = 0;
const uint8_t *_sqs = 0;

volatile uint16_t _pc = 0;
volatile uint16_t _si = 1;
volatile uint16_t _pi = 0;

void _ISR() {
    if (!_r)
        return;

    if (_pc == 0) {
        pinMode(CTL_PIN, MARK);
    }
    else if (_pc == _pcs[_sqs[_si]][_pi % 2]) {
        _pc = 0;

        if (_si == _sqs[0]) {
            pinMode(CTL_PIN, OFF);
            _si = 1;
            _pi = 0;
            _r = 0;
            return;
        }

        if (_pi % 2) {
            pinMode(CTL_PIN, MARK);
            ++_si;
        }
        else {
            pinMode(CTL_PIN, SPACE);
        }

        ++_pi;
    }

    ++_pc;
}

void set(uint16_t frequency, double duty_cycle, const uint8_t (*codes)[2])
{
    _pwm(REF_PIN, frequency, duty_cycle);

    _pwm(CTL_PIN, frequency, duty_cycle);
    pinMode(CTL_PIN, OFF);

    pinMode(INT_PIN, INPUT);
    attachInterrupt(INT_PIN, _ISR, FALLING);

    _pcs = codes;
}

void setup()
{
    Serial.begin(115200);
    while (!Serial.available()) {
        Serial.print(".");
        delay(1000);
    }

    Serial.println("\r\nsetup()");
}

void loop()
{
    if (Serial.available())
    {
        uint8_t k = Serial.read();
        switch (k)
        {
            case '1':
                set(VIP2262::FREQUENCY, VIP2262::DUTY_CYCLE, VIP2262::CODES);
                Serial.println("VIP2262");
                break;
            case '2':
                set(HWC560S::FREQUENCY, HWC560S::DUTY_CYCLE, HWC560S::CODES);
                Serial.println("HW-C560S");
                break;
            case 'q':
                _sqs = HWC560S::KEYS[HWC560S::VOL_UP];
                _r = !_r;
                break;
            case 'w':
                _sqs = HWC560S::KEYS[HWC560S::VOL_DOWN];
                _r = !_r;
                break;
            case 'e':
                _sqs = VIP2262::KEYS[VIP2262::EXIT];
                _r = !_r;
                break;
            case 'u':
                _sqs = VIP2262::KEYS[VIP2262::UP];
                _r = !_r;
                break;
            case 'd':
                _sqs = VIP2262::KEYS[VIP2262::DOWN];
                _r = !_r;
                break;
            case 'l':
                _sqs = VIP2262::KEYS[VIP2262::LEFT];
                _r = !_r;
                break;
            case 'r':
                _sqs = VIP2262::KEYS[VIP2262::RIGHT];
                _r = !_r;
                break;
            case 's':
                _sqs = VIP2262::KEYS[VIP2262::SELECT];
                _r = !_r;
                break;
            case 'g':
                _sqs = VIP2262::KEYS[VIP2262::GUIDE];
                _r = !_r;
                break;
            default:
                break;
        }
    }
}
