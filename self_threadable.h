// Inherit from this and just implement async() and you're good to go!
class SelfThreadable {
    TaskHandle_t m_thr = nullptr;
    // params from constructor
    const char* m_name;
    const size_t m_stack;
    const UBaseType_t m_pri;
    
    virtual void async() = 0;
public:
    SelfThreadable(const SelfThreadable&) = delete;
    SelfThreadable(SelfThreadable&&) = delete;
    void operator=(const SelfThreadable&) = delete;
    void operator=(SelfThreadable&&) = delete;
    
    SelfThreadable(const char* name, const size_t stack = 2048, const UBaseType_t pri = tskIDLE_PRIORITY)
        : m_name(name), m_stack(stack), m_pri(pri) {}
        
    SelfThreadable(const bool start_right_away, const char* name, const size_t stack = 2048, const UBaseType_t pri = tskIDLE_PRIORITY)
        : m_name(name), m_stack(stack), m_pri(pri) {
        if (start_right_away) async_start();
    }
    
    ~SelfThreadable() {
        if (m_thr) vTaskDelete(m_thr);
        m_thr = nullptr;
    }
    
    void async_start() {
        xTaskCreate(
            [](void* t){((SelfThreadable*)t)->async();},
            m_name, m_stack, this, m_pri, &m_thr
        );
    }
};